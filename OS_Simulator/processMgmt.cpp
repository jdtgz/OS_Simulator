#include "processMgmt.h"

// Moves processes from pending to the scheduler at arrival time
void ProcessManagement::activateProcesses(const int& time){
    static int iter = allProcesses.size()-1;
    if(iter > 0){
        while(allProcesses[iter].arrivalTime == time){
            m_scheduler.addNewArrival(&allProcesses[iter]);
            iter--;
        }
    }
}

// Runs at each time step
stepActionEnum ProcessManagement::runStep(){
    // cout << "processMngmt layer starting" << endl;
    return m_scheduler.runProcesses();
    // cout << "processMngmt layer complete" << endl;
}

// For debugging only
void ProcessManagement::printStates(){
    char stateChar;
    for(auto & Proc : allProcesses)
    {
        switch (Proc.state)
        {
            case ready:
                stateChar = 'r';
                break;
            case processing:
                stateChar = 'p';
                break;
            case blocked:
                stateChar = 'b';
                break;
            case newArrival:
                stateChar = 'n';
                break;
            case done:
                stateChar = 'd';
                break;
            case awaiting:
                stateChar = 'a';
                break;
        }
        cout << stateChar << ' ';
    }
    cout << endl;
}

// For debugging only
void ProcessManagement::printPending(){
    for(auto proc : allProcesses){
        proc.printProcess();
    }
}

// Moves all processes from a file into the allProcesses vector
void ProcessManagement::readProcessFile(const string& fname){
    stringstream ss;
    ifstream in(fname.c_str());
    string line, strItem;
    Process proc;
    unsigned int ioIDctrl(0), procIDctrl(0);
    int ioTime, ioDur;

    allProcesses.clear();
    if(!in.good()){
        cerr << "initProcessSetFromFile error     unable to open file \"" << fname << "\"" << endl;
        return;
    }

    allProcesses.reserve(20);
    while(getline(in, line)){
        ss.clear();
        ss.str(line);

        proc.id = procIDctrl;
        ++procIDctrl;

        ss >> proc.arrivalTime;
        ss >> proc.reqProcessorTime;
        allProcesses.push_back(proc);
    }

    sort(allProcesses.begin(), allProcesses.end(), procComp);
}