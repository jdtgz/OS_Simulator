#include "Scheduler.h"

/*
 * Scheduler Funcions
 */
Scheduler::Scheduler()
{
	preempt = 0;
}


Scheduler::~Scheduler()
{
}


Scheduler::Scheduler(CentralProcessor m_processor) : processor(m_processor)
{
	preempt = 0;
}


void Scheduler::addNewArrival(Process* p)
{
	newProcesses.push_back(p);
    p->curState = NEW_ARRIVAL;
}


void Scheduler::addNewProcess()
{
    readyProcesses.push_back(newProcesses.front());
    newProcesses.front()->curState = READY;
    
	newProcesses.front() = nullptr;
    newProcesses.pop_front();
}


void Scheduler::beginNewProcess()
{
    processor.newProcess(readyProcesses.front());
    readyProcesses.front()->curState = RUNNING;
    
    readyProcesses.front() = nullptr;
    readyProcesses.pop_front();
    preempt = 0;
}


stepAction Scheduler::runProcesses(const long& time)
{
    if (newProcesses.size() > 0) 
    {
        addNewProcess();
        return ADMIT_NEW_PROCESS;
    }
    else if (processor.isFree()) 
    {
        if (readyProcesses.size() != 0)
        {
            beginNewProcess();
            return BEGIN_RUN;
        }
        else 
        {
            return NO_ACT;
        }
    }

    else 
    {
        bool processCompleted = processor.runProcess(time);

        if (processCompleted) 
        {
            return COMPLETE;
        }
        else 
        {
            return continueProcessing();
        }
    }
}


stepAction Scheduler::continueProcessing()
{
	return CONTINUE_RUN;
}


void Scheduler::print()
{
    std::cout << "FIFO" << std::endl;
}


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
ShortestJobNext::ShortestJobNext(CentralProcessor mProc) : Scheduler(mProc)
{
}


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

    tempProc = nullptr;
}


void ShortestJobNext::print()
{
    std::cout << "SJN" << std::endl;
}


/*
 * Round Robin Functions
 */
RoundRobin::RoundRobin(CentralProcessor mProc) : Scheduler(mProc)
{
    preemptionTime = 20;
}


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


void RoundRobin::setPreemptionTime(int timer)
{ 
    preemptionTime = timer; 
}


void RoundRobin::print()
{
    std::cout << "RR" << std::endl;
}


/*
 * Factory Functions
 */
Factory::Factory()
{
}


Factory::~Factory()
{
}


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