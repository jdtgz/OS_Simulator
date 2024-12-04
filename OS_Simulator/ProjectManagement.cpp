#include "ProjectManagement.h"

// Description: Default constructor 
// Pre Conditions: None
// Post Conditions: Create empty project manager
// Params: None
ProjectManagement::ProjectManagement()
{
    mScheduler = nullptr;
}


// Description: Default destructor 
// Pre Conditions: None
// Post Conditions: Delete project manager
// Params: None
ProjectManagement::~ProjectManagement()
{
}


// Description: Overload constructor 
// Pre Conditions: None
// Post Conditions: Create project manager with a scheduler
// Params: Scheduler pointer
ProjectManagement::ProjectManagement(Scheduler* schedule) : mScheduler(schedule)
{
}


// Description: Adds processes to the scheduler upon arrival time
// Pre Conditions: Must have a scheduler
// Post Conditions: Adds a new process to the scheduler
// Params: The time interval
void ProjectManagement::activateProcesses(const int& time)
{
    static int iter = totalProcesses.size() - 1;
    
    while (iter >= 0 && totalProcesses[iter].arrivalTime == time)
    {
        mScheduler->addNewArrival(&totalProcesses[iter]);
        iter--;
    }
}


// Description: Runs the scheduler for one step
// Pre Conditions: Must have a scheduler
// Post Conditions: Returns the action taken by the scheduler
// Params: The time interval
void ProjectManagement::runStep(const long& time)
{
	 mScheduler->runProcesses(time);
     return;
}


// Description: Prints the states of all processes
// Pre Conditions: None
// Post Conditions: Prints all process states to the console
// Params: None
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


// Description: Prints the process data from all processes
// Pre Conditions: None
// Post Conditions: Prints process data to the console
// Params: Central None
void ProjectManagement::printAllProcesses()
{
    std::cout << "   ID |   AT |   DT | RQPT |   PT | S |  Eff |" << std::endl;
    for (auto& proc : totalProcesses) {
        proc.printProcess();
    }
    std::cout << std::endl;
}


// Description: Prints scheduler data
// Pre Conditions: Must have a scheduler
// Post Conditions: Prints the scheduler type and all ready processes to the console
// Params: None
void ProjectManagement::printScheduler()
{
    mScheduler->print();
    mScheduler->printReadyProcesses();
}


// Description: Returns the total number of processes
// Pre Conditions: None
// Post Conditions: Returns the size of totalProcesses
// Params: Central None
int ProjectManagement::numProcesses()
{
	return totalProcesses.size();
}


// Description: Converts the process file data into a vector
// Pre Conditions: Must have a correctly formatted txt file
// Post Conditions: Fills totalProcesses vector with the processes in the chosen file
// Params: A text file
void ProjectManagement::readProcessFile(const std::string& file)
{
    std::stringstream ss;
    std::ifstream in(file.c_str());
    std::string line, strItem;

    Process proc;
    unsigned int procIDctrl(1);

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

    std::sort(totalProcesses.begin(), totalProcesses.end(), procComp);
}


ProcessInProgress ProjectManagement::getCurrentProcess() 
{
    return mScheduler->getCurrentProcess();
}