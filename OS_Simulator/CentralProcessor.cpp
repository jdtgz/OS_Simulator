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
	if(m_process->getProcessorTime() >= m_process->getReqProcTime())
    {
        m_process->setState(DONE);
        m_process->setDoneTime(time);
        m_process = nullptr;

        free = true;
        return true;
    } 
    else 
    {
        m_process->setProcessorTime(m_process->getProcessorTime() + 1);
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
