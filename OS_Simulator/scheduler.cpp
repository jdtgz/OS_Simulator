#include "scheduler.h"

// Adds and sorts a process into the ready queue
void Scheduler::addNewProcess(){
    m_processes.push_back(new_processes.front());
}

// Decides what happens at each time interval. Returns step action documenting what happened.
stepActionEnum Scheduler::runProcesses(){
    // cout << "scheduler layer started" << endl;
    if(new_processes.size() > 0){
        // cout << "admit new process" << endl;
        addNewProcess();
        new_processes.pop_front();
        return admitNewProc;
    } else if(m_processor.isFree()){
        // cout << "processor is free" << endl;
        if(m_processes.size() != 0){
            // cout << "beginning a run" << endl;
            Process tempProc = m_processes.front();
            // tempProc.printProcess();
            m_processor.newProcess(tempProc);
            m_processes.pop_front();
            return beginRun;
        } else {
            // cout << "no action" << endl;
            return noAct;
        }

    } else {
        // cout << "processor not free" << endl;
        bool processCompleted = m_processor.runProcess();
        if(processCompleted){
            return complete;
        } else {
            return continueRun;
        }
    }
}

// For debugging only
void Scheduler::printProcessStates()
{
    char stateChar;
    for(auto & Proc : m_processes)
    {
        switch (Proc.state)
        {
            case ready:
                stateChar = 'r';
                break;
            case processing:
                stateChar = 'p';
                break;
            case blocked:
                stateChar = 'b';
                break;
            case newArrival:
                stateChar = 'n';
                break;
            case done:
                stateChar = 'd';
                break;
        }
        cout << stateChar << ' ';
    }
    cout << endl;
}