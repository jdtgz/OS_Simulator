#include "CentralProcessor.h"


CentralProcessor::CentralProcessor()
{
    m_process = nullptr;
    free = true;
}


CentralProcessor::~CentralProcessor()
{
    delete m_process;
}


void CentralProcessor::newProcess(Process* p)
{
    m_process = p;
    free = false;
}


bool CentralProcessor::runProcess(const long& time)
{
	if(m_process->processorTime >= m_process->reqProcessorTime )
    {
        m_process->curState = DONE;
        m_process->doneTime = time;
        m_process = nullptr;

        free = true;
        return true;
    } 
    else 
    {
        m_process->processorTime++;
        return false;
    }
}


Process* CentralProcessor::checkProcess()
{
	return m_process;
}


bool CentralProcessor::isFree()
{
	return free;
}
