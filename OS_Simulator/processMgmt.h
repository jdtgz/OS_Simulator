#ifndef PROCESS_MGMT_H
#define PROCESS_MGMT_H

#include<algorithm>  // Needed for sort (used in readProcessFile)
#include "scheduler.h"


// Compares processes by arrival time
inline bool procComp(const Process& p1, const Process& p2){
    return p1.arrivalTime > p2.arrivalTime;
}


// Admits new processes into the scheduler at arrival time
class ProcessManagement{
    public:
        ProcessManagement(Scheduler mScheduler) : m_scheduler(mScheduler) {};

        // Essential class functions
        void activateProcesses(const int& time);
        bool processingComplete() {return (m_pending.size() == 0 && m_scheduler.schedulerEmpty());}
        stepActionEnum runStep();

        // Debugging helper
        void printStates();
        void printPending();

        // Temporarily used to move all processes from a file into the m_pending vector
        // Will need to be rewritten depending on how processes are inputted by the user
        void readProcessFile(const string& fname);
    private:
        // Holds all processes before their respective arrival times
        vector<Process> m_pending;
        // The scheduler to be used during simulation
        Scheduler m_scheduler;
};


#endif