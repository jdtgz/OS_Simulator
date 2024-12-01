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
                m_processes.insert(proc, tempProc);
                return;
            }
            proc++;
        }
        m_processes.insert(proc, tempProc);
    }
}