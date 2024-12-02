#include "ProjectManagement.h"


ProjectManagement::ProjectManagement()
{
    mScheduler = nullptr;
}


ProjectManagement::~ProjectManagement()
{
}


ProjectManagement::ProjectManagement(Scheduler* schedule) : mScheduler(schedule)
{
}


void ProjectManagement::activateProcesses(const int& time)
{
    static int iter = totalProcesses.size() - 1;
    
    if (iter > 0) 
    {
        while (totalProcesses[iter].arrivalTime == time)
        {
            mScheduler->addNewArrival(&totalProcesses[iter]);
            iter--;
        }
    }
}


stepAction ProjectManagement::runStep(const long& time)
{
	 return mScheduler->runProcesses(time);
}


void ProjectManagement::printStates()
{
    char stateChar = ' ';

    for (auto& Proc : totalProcesses) 
    {
        switch (Proc.curState) 
        {
            case READY:
                stateChar = 'r';
                break;
            case RUNNING:
                stateChar = 'p';
                break;
            case BLOCKED:
                stateChar = 'b';
                break;
            case NEW_ARRIVAL:
                stateChar = 'n';
                break;
            case DONE:
                stateChar = 'd';
                break;
            case AWAITING:
                stateChar = 'a';
                break;
        }
        std::cout << stateChar << ' ';
    }
    std::cout << std::endl;
}


void ProjectManagement::printAllProcesses()
{
    std::cout << "   ID |   AT |   DT | RQPT |   PT | S |  Eff |" << std::endl;
    for (auto& proc : totalProcesses) {
        proc.printProcess();
    }
    std::cout << std::endl;
}


void ProjectManagement::printScheduler()
{
    mScheduler->print();
    mScheduler->printReadyProcesses();
}


int ProjectManagement::numProcesses()
{
	return totalProcesses.size();
}


void ProjectManagement::readProcessFile(const std::string& file)
{
    std::stringstream ss;
    std::ifstream in(file.c_str());
    std::string line, strItem;

    Process proc;
    unsigned int ioIDctrl(1), procIDctrl(1);
    int ioTime, ioDur;

    totalProcesses.clear();
    if (!in.good())
    {
        std::cerr << "initProcessSetFromFile error     unable to open file \"" << file << "\"" << std::endl;
        return;
    }

    totalProcesses.reserve(20);
    while (getline(in, line)) 
    {
        ss.clear();
        ss.str(line);

        proc.id = procIDctrl;
        ++procIDctrl;

        // Needs fixing...
        ss >> proc.arrivalTime;
        ss >> proc.reqProcessorTime;

        totalProcesses.push_back(proc);
    }

    // need help with "fixing" proComp...
    std::sort(totalProcesses.begin(), totalProcesses.end(), procComp);
}