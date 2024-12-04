#include "Process.h"


// Description: Default constructor 
// Pre Conditions: None
// Post Conditions: Creates a process with set default values
// Params: None
Process::Process() : id(99999), arrivalTime(-1), doneTime(-1), 
	reqProcessorTime(0), processorTime(0), curState(AWAITING)
{
}


// Description: Default destructor 
// Pre Conditions: None
// Post Conditions: Delete process
// Params: None
Process::~Process()
{
}



// Description: Assignment operator overload to allow proper assignement of processes 
// Pre Conditions: other is a valid process with values
// Post Condition: this process and other will be the same
// Params: Process object 
Process& Process::operator=(const Process& other)
{
    this->id = other.id;
    this->curState = other.curState;
    this->arrivalTime = other.arrivalTime;
    this->reqProcessorTime = other.reqProcessorTime;
    this->processorTime = other.processorTime;
    this->doneTime = other.doneTime;

    return *this;
}


// Description: Prints all process details
// Pre Conditions: None
// Post Conditions: Prints all member variables and efficiency to the console
// Params: None
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