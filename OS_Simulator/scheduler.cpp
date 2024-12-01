#include "scheduler.h"

// Allows processMgmt to fill the new_processes list
void Scheduler::addNewArrival(Process* p){
    new_processes.push_back(p);
    p->state = newArrival;
}

// Adds and sorts a process into the ready queue
void Scheduler::addNewProcess(){
    m_processes.push_back(new_processes.front());
}

// Decides what happens at each time interval. Returns step action documenting what happened.
stepActionEnum Scheduler::runProcesses(const long& time){
    // cout << "scheduler layer started" << endl;
    if(new_processes.size() > 0){
        // cout << "admit new process" << endl;
        addNewProcess();
        new_processes.front()->state = ready;
        new_processes.front() = nullptr;
        new_processes.pop_front();
        return admitNewProc;
    } else if(m_processor.isFree()){
        // cout << "processor is free" << endl;
        if(m_processes.size() != 0){
            // cout << "beginning a run" << endl;
            m_processor.newProcess(m_processes.front());
            m_processes.front() = nullptr;
            m_processes.pop_front();
            return beginRun;
        } else {
            // cout << "no action" << endl;
            return noAct;
        }

    } else {
        // cout << "processor not free" << endl;
        bool processCompleted = m_processor.runProcess(time);
        if(processCompleted){
            return complete;
        } else {
            return continueRun;
        }
    }
}