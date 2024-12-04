#include "Scheduler.h"

/*
 * ProcessInProgress Functions
 */

ProcessInProgress::ProcessInProgress()
{
    p = new Process();
    latestStep = new stepAction;
}

ProcessInProgress::~ProcessInProgress()
{
    delete p;
    delete latestStep;
}


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
Process* Scheduler::addNewProcess()
{
    readyProcesses.push_back(newProcesses.front());
    newProcesses.front()->curState = READY;
    
	newProcesses.front() = nullptr;
    newProcesses.pop_front();

    return readyProcesses.front();
}


// Description: Adds a new process to the processor from the ready list
// Pre Conditions: readyProcesses is not empty and processor is free
// Post Conditions: The process is moved from readyProcesses to processor and its state is updated
// Params: None
Process* Scheduler::beginNewProcess()
{
    processor.newProcess(readyProcesses.front());
    readyProcesses.front()->curState = RUNNING;
    
    readyProcesses.front() = nullptr;
    readyProcesses.pop_front();

    return readyProcesses.front();
}


// Description: Chooses an action to run based on the resources available
// Pre Conditions: Time loop must be started
// Post Conditions: Returns the ProcessInProgress object that includes step and process itself
// Params: Takes in the time interval
ProcessInProgress Scheduler::runProcesses(const long& time)
{
    ProcessInProgress proc;

    if (newProcesses.size() > 0) 
    {
        *proc.p = *addNewProcess();
        *proc.latestStep = ADMIT_NEW_PROCESS;
    }
    else if (processor.isFree()) 
    {
        if (readyProcesses.size() != 0)
        {
            *proc.p = *beginNewProcess();
            *proc.latestStep = BEGIN_RUN;
        }
        else 
        {
            proc.p = nullptr;
            *proc.latestStep = NO_ACT;
        }
    }
    else 
    {
        *proc.p = *(processor.checkProcess());
        bool processCompleted = (proc.p->curState == DONE) ? true : false;

        if (processCompleted) 
        {
            *proc.latestStep = COMPLETE;
        }
        else 
        {
            continueProcessing(proc);
        }
    }  
    
    return proc;
}


// Description: Sets the step to continue run from the ProcessInProgress object
// Pre Conditions: The process in the processor must be run and incomplete
// Post Conditions: returns nothing, but edits the state 
// Params: ProcessInProgess object 
void Scheduler::continueProcessing(ProcessInProgress& proc)
{
    *proc.latestStep = CONTINUE_RUN;
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
Process* ShortestJobNext::addNewProcess()
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

    Process* addedProc = new Process();
    addedProc = newProcesses.front();

    newProcesses.front() = nullptr;
    newProcesses.pop_front();

    return addedProc;
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
Process* RoundRobin::beginNewProcess()
{
    processor.newProcess(readyProcesses.front());
    readyProcesses.front()->curState = RUNNING;

    readyProcesses.front() = nullptr;
    readyProcesses.pop_front();
    preempt = 0;

    return processor.checkProcess();
}


// Description: Continues running or switches the running process
// Pre Conditions: The process in the processor must be run and incomplete
// Post Conditions: returns nothing, but edits the state depending on preempt/preemptionTimer
// Params: ProcessInProgess object 
void RoundRobin::continueProcessing(ProcessInProgress& proc)
{
    if (preempt == preemptionTime) 
    {
        newProcesses.push_front(proc.p);
        addNewProcess();
        beginNewProcess();

        *proc.latestStep = CONTEXT_SWITCH;
    }
    else 
    {
        preempt++;
        *proc.latestStep = CONTINUE_RUN;
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