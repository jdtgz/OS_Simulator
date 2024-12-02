#include "Process.h"


Process::Process() : arrivalTime(-1), doneTime(-1), 
	reqProcessorTime(0), processorTime(0), curState(AWAITING)
{
}


Process::~Process()
{
}


void Process::printProcess()
{
    std::cout << std::setw(5) << id << " |";
    std::cout << std::setw(5) << arrivalTime << " |";
    std::cout << std::setw(5) << doneTime << " |";
    std::cout << std::setw(5) << reqProcessorTime << " |";
    std::cout << std::setw(5) << processorTime << " |";
    std::cout << std::setw(2) << curState << " |";
    std::cout << std::setw(5) << 
        (((doneTime - arrivalTime) + processorTime) / reqProcessorTime) << " |" 
        << std::endl;
}


void Process::printProcessSet(std::vector<Process>& processVec)
{
    std::cout << "AT | DT | RQPT | PT | S | IO" << std::endl;
    for (auto& Proc : processVec)
    {
        Proc.printProcess();
    }
}


unsigned int Process::getID()
{
    return id;
}


void Process::setID(unsigned int newID)
{
    id = newID;
}


State Process::getState()
{
    return curState;
}


void Process::setState(State newState)
{
    curState = newState;
}


long Process::getArrivalTime()
{
    return arrivalTime;
}


void Process::setArrivalTime(long arrival)
{
    arrivalTime = arrival;
}


long Process::getReqProcTime()
{
    return reqProcessorTime;
}


void Process::setReqProcTime(long newTime)
{
    reqProcessorTime = newTime;
}


long Process::getProcessorTime()
{
    return processorTime;
}


void Process::setProcessorTime(long newTime)
{
    processorTime = newTime;
}


long Process::getDoneTime()
{
    return doneTime;
}


void Process::setDoneTime(long newTime)
{
    doneTime = newTime;
}