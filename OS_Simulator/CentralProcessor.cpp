#include "CentralProcessor.h"

// Description: Default constructor 
// Pre Conditions: None
// Post Conditions: Creates a free processor
// Params: None
CentralProcessor::CentralProcessor()
{
    m_process = nullptr;
    free = true;
}


// Description: Default destructor 
// Pre Conditions: None
// Post Conditions: Delete processor
// Params: None
CentralProcessor::~CentralProcessor()
{
    delete m_process;
}


// Description: Admits a new process
// Pre Conditions: Is either free or the current process is preempted
// Post Conditions: m_process is set to the new process and free is false
// Params: Process pointer
void CentralProcessor::newProcess(Process* p)
{
    m_process = p;
    free = false;
}


// Description: Run the process a step
// Pre Conditions: Must have a process
// Post Conditions: Returns the process after having updated it
// Params: The time interval
Process* CentralProcessor::runProcess(const long& time)
{
	if(m_process->processorTime >= m_process->reqProcessorTime )
    {
        m_process->curState = DONE;
        m_process->doneTime = time;

        free = true;
        return m_process;
    } 
    else 
    {
        m_process->processorTime++;
        return m_process;
    }
}


// Description: Returns the process pointer
// Pre Conditions: None
// Post Conditions: Returns m_process
// Params: None
Process* CentralProcessor::checkProcess()
{
	return m_process;
}


// Description: Returns whether the processor is free or not
// Pre Conditions: None
// Post Conditions: Returns free
// Params: None
bool CentralProcessor::isFree()
{
	return free;
}
