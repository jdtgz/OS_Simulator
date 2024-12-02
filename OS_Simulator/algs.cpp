#include "scheduler.h"

void ShortestJobNext::addNewProcess(){
    // cout << "SJN adding new process" << endl;
    Process* tempProc = new_processes.front();
    if(m_processes.size() == 0){
        m_processes.push_back(tempProc);
    } else {
        list<Process*>::iterator proc = m_processes.begin();
        while(proc != m_processes.end()){
            if((*proc)->reqProcessorTime > tempProc->reqProcessorTime){
                break;
            }
            proc++;
        }
        m_processes.insert(proc, tempProc);
    }
    new_processes.front()->state = ready;
    new_processes.front() = nullptr;
    new_processes.pop_front();
    tempProc = nullptr;
}

stepActionEnum RoundRobin::continueProcessing(){
    if(preempt == preemptionTime){
        new_processes.push_front(m_processor.checkProcess());
        addNewProcess();
        beginNewProcess();
        return contextSwitch;
    } else {
        preempt++;
        return continueRun;
    }
}