#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "processor.h"


// For later use
enum Alg { FIFO, RoundRobin, ShortestJobNext, ShortestRemainingTime };
// To know what action happened at each time interval. May help when adding visuals.
enum stepActionEnum {noAct, admitNewProc, handleInterrupt, beginRun, continueRun, ioRequest, complete};


// Schedules the process to be run by the processor
class Scheduler{
    public:
        Scheduler(Processor mProcessor, Alg mAlgorithm) : m_processor(mProcessor), m_algorithm(mAlgorithm) {}; 

        // Essential class functions
        void addNewProcess();
        stepActionEnum runProcesses();
        bool schedulerEmpty() {return (new_processes.size() == 0 && m_processes.size() == 0 && m_processor.isFree());}

        // For debugging
        void printProcessStates();

        // New processes admitted by process management
        list<Process> new_processes;
    private:
        // For later use
        Alg m_algorithm = FIFO;

        // All processes in sorted order to feed to the processor. Essentially the ready queue
        list<Process> m_processes;
        // The scheduler is linked to a processor. May change to have multiple processors
        Processor m_processor;
};


#endif