#include "Scheduler.h"

/*
 * Scheduler Funcions
 */

// Description: Default constructor 
// Pre Conditions: None
// Post Conditions: Create empty scheduler
// Params: None
Scheduler::Scheduler()
{
}


// Description: Default destructor 
// Pre Conditions: None
// Post Conditions: Delete scheduler
// Params: None
Scheduler::~Scheduler()
{
}


ProcessInProgress::ProcessInProgress()
{
    p = nullptr;
    latestStep = NO_ACT;
}

ProcessInProgress::~ProcessInProgress() 
{
}


// Description: Overload constructor 
// Pre Conditions: None
// Post Conditions: Create FIFO scheduler with a processor
// Params: Central Processor object
Scheduler::Scheduler(CentralProcessor m_processor) : processor(m_processor)
{
}


// Description: Override constructor 
// Pre Conditions: None
// Post Conditions: Create scheduler with a processor
// Params: Central Processor object
void Scheduler::addNewArrival(Process* p)
{
	newProcesses.push_back(p);
    p->curState = NEW_ARRIVAL;
}


// Description: Adds a new process from the new list to the ready list
// Pre Conditions: newProcesses is not empty
// Post Conditions: The process from newProcesses is moved to readyProcesses and its state is updated
// Params: None
void Scheduler::addNewProcess()
{
    readyProcesses.push_back(newProcesses.front());
    newProcesses.front()->curState = READY;
    
	newProcesses.front() = nullptr;
    newProcesses.pop_front();

    currentProcess.p = readyProcesses.back();
}


// Description: Adds a new process to the processor from the ready list
// Pre Conditions: readyProcesses is not empty and processor is free
// Post Conditions: The process is moved from readyProcesses to processor and its state is updated
// Params: None
void Scheduler::beginNewProcess()
{
    processor.newProcess(readyProcesses.front());
    readyProcesses.front()->curState = RUNNING;
    
    readyProcesses.front() = nullptr;
    readyProcesses.pop_front();
}


// Description: Chooses an action to run based on the resources available
// Pre Conditions: Time loop must be started
// Post Conditions: Returns the stepAction taken
// Params: Takes in the time interval
void Scheduler::runProcesses(const long& time)
{
    if (newProcesses.size() > 0) 
    {
        addNewProcess();
        currentProcess.latestStep = ADMIT_NEW_PROCESS;
        return;
    }
    else if (processor.isFree()) 
    {
        if (readyProcesses.size() != 0)
        {
            beginNewProcess();
            currentProcess.latestStep = BEGIN_RUN;
            currentProcess.p = processor.checkProcess();
            return;
        }
        else 
        {
            currentProcess.latestStep = NO_ACT;
            currentProcess.p = nullptr;
            return;
        }
    }

    else 
    {
        currentProcess.p = processor.checkProcess();
        bool processCompleted = processor.runProcess(time);

        if (processCompleted) 
        {
            currentProcess.latestStep = COMPLETE;
            return;
        }
        else 
        {
            currentProcess.latestStep = continueProcessing();
            return;
        }
    }
}


// Description: Returns a continue run stepAction
// Pre Conditions: The process in the processor must be run and incomplete
// Post Conditions: Returns CONTINUE_RUN stepAction
// Params: None
stepAction Scheduler::continueProcessing()
{
	return CONTINUE_RUN;
}


// Description: Prints the scheduler type
// Pre Conditions: Must be FIFO or default Scheduler
// Post Conditions: Prints "FIFO" to the console
// Params: None
void Scheduler::print()
{
    std::cout << "FIFO" << std::endl;
}


// Description: Prints the id of all ready processes
// Pre Conditions: None
// Post Conditions: Prints the id of all ready processes
// Params: None
void Scheduler::printReadyProcesses()
{
    for (const auto& proc : readyProcesses)
    {
        std::cout << proc->id << " ";
    }
    std::cout << std::endl;
}


/*
 * ShortestJobNext Functions
 */

// Description: Overload constructor 
// Pre Conditions: None
// Post Conditions: Create SJN scheduler with processor
// Params: Central processor object
ShortestJobNext::ShortestJobNext(CentralProcessor mProc) : Scheduler(mProc)
{
}


// Description: Sorts a new process into the ready list based on the required processing time
// Pre Conditions: newProcesses is not empty
// Post Conditions: Adds the front of newProcesses to readyProcesses
// Params: None
void ShortestJobNext::addNewProcess()
{
    Process* tempProc = newProcesses.front();

    if(readyProcesses.size() == 0)
    {
        readyProcesses.push_back(tempProc);
    } 
    else 
    {
        std::list<Process*>::iterator proc = readyProcesses.begin();

        while(proc != readyProcesses.end())
        {
            if((*proc)->reqProcessorTime > tempProc->reqProcessorTime)
            {
                break;
            }

            proc++;
        }
        readyProcesses.insert(proc, tempProc);
    }
    newProcesses.front()->curState = READY;
    newProcesses.front() = nullptr;
    newProcesses.pop_front();

    currentProcess.p = tempProc;
    tempProc = nullptr;
}


// Description: Prints the scheduler type
// Pre Conditions: Must be a ShortestJobNext scheduler
// Post Conditions: Prints "SJN" to the console
// Params: None
void ShortestJobNext::print()
{
    std::cout << "SJN" << std::endl;
}


/*
 * Round Robin Functions
 */

// Description: Default constructor 
// Pre Conditions: None
// Post Conditions: Create RR scheduler with set preempt and preemptionTime values and a processor
// Params: Central processor object
RoundRobin::RoundRobin(CentralProcessor mProc) : Scheduler(mProc)
{
    preemptionTime = 20;
    preempt = 0;
}


// Description: Adds a new process to the processor from the ready list and resets preempt to 0
// Pre Conditions: readyProcesses is not empty and processor is free
// Post Conditions: The process is moved from readyProcesses to processor and its state is updated
// Params: None
void RoundRobin::beginNewProcess()
{
    processor.newProcess(readyProcesses.front());
    readyProcesses.front()->curState = RUNNING;

    readyProcesses.front() = nullptr;
    readyProcesses.pop_front();
    preempt = 0;
}


// Description: Continues running or switches the running process
// Pre Conditions: The process in the processor must be run and incomplete
// Post Conditions: Returns CONTEXT_SWITCH or CONTINUE_RUN depending on preempt and preemptionTimer
// Params: None
stepAction RoundRobin::continueProcessing()
{
    if (preempt == preemptionTime) 
    {
        newProcesses.push_front(processor.checkProcess());
        addNewProcess();
        beginNewProcess();

        return CONTEXT_SWITCH;
    }
    else 
    {
        preempt++;
        return CONTINUE_RUN;
    }
}


// Description: Setter function for preemptionTime
// Pre Conditions: None
// Post Conditions: Changes preemptionTime
// Params: Integer to set the preemption time to
void RoundRobin::setPreemptionTime(int timer)
{ 
    preemptionTime = timer; 
}


// Description: Prints the scheduler type
// Pre Conditions: Must be a RoundRobin scheduler
// Post Conditions: Prints "RR" to the console
// Params: None
void RoundRobin::print()
{
    std::cout << "RR" << std::endl;
}


/*
 * Factory Functions
 */

// Description: Default constructor 
// Pre Conditions: None
// Post Conditions: Create empty scheduler
// Params: None
Factory::Factory()
{
}


// Description: Default destructor 
// Pre Conditions: None
// Post Conditions: Delete scheduler
// Params: None
Factory::~Factory()
{
}


// Description: Creates a scheduler object based on the choice parameter
// Pre Conditions: None
// Post Conditions: Prints "RR" to the console
// Params: Integer or Enum choice and Central Processor
Scheduler* Factory::createAlgorithm(const int& choice, CentralProcessor mProcessor)
{
    Scheduler* selection;
    
    switch (choice)
    {
        case FIFO:
            std::cout << "FIFO chosen" << std::endl;
            selection = new FirstInFirstOut(mProcessor);
            break;
        case SJN:
            std::cout << "SJN chosen" << std::endl;
            selection = new ShortestJobNext(mProcessor);
            break;
        case RR:
            std::cout << "RR chosen" << std::endl;
            selection = new RoundRobin(mProcessor);
            break;
        default:
            std::cout << "Defaulting to FIFO" << std::endl;
            selection = new FirstInFirstOut(mProcessor);
            break;
    }

    return selection;
}

ProcessInProgress Scheduler::getCurrentProcess() 
{
    return currentProcess;
}