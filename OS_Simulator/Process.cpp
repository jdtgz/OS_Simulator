#include "Process.h"


Process::Process() : id(99999), arrivalTime(-1), doneTime(-1), 
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