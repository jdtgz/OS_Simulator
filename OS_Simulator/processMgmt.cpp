#include "processMgmt.h"

// Moves processes from pending to the scheduler at arrival time
void ProcessManagement::activateProcesses(const int& time){
    if(m_pending.size() > 0){
        while(m_pending.back().arrivalTime == time){
            m_scheduler.new_processes.push_back(m_pending.back());
            m_pending.pop_back();
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
    m_scheduler.printProcessStates();
}

// For debugging only
void ProcessManagement::printPending(){
    for(auto proc : m_pending){
        proc.printProcess();
    }
}

// Moves all processes from a file into the m_pending vector
void ProcessManagement::readProcessFile(const string& fname){
    stringstream ss;
    ifstream in(fname.c_str());
    string line, strItem;
    Process proc;
    unsigned int ioIDctrl(0), procIDctrl(0);
    int ioTime, ioDur;

    m_pending.clear();
    if(!in.good()){
        cerr << "initProcessSetFromFile error     unable to open file \"" << fname << "\"" << endl;
        return;
    }

    m_pending.reserve(20);
    while(getline(in, line)){
        ss.clear();
        ss.str(line);

        proc.id = procIDctrl;
        ++procIDctrl;

        ss >> proc.arrivalTime;
        ss >> proc.reqProcessorTime;
        m_pending.push_back(proc);
    }

    sort(m_pending.begin(), m_pending.end(), procComp);
}