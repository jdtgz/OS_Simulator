#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "processor.h"


// For later use
enum Alg { FIFO, RR, SJN, SRT };
// To know what action happened at each time interval. May help when adding visuals.
enum stepActionEnum {noAct, admitNewProc, handleInterrupt, beginRun, continueRun, ioRequest, complete};


// Schedules the process to be run by the processor
class Scheduler{
    public:
        Scheduler(Processor mProcessor) : m_processor(mProcessor) {}; 

        // Essential class functions
        void addNewArrival(Process* p);
        virtual void addNewProcess();
        stepActionEnum runProcesses(const long& time);

        // Debugging helper
        virtual void print() {cout << "FIFO" << endl;}
        void printReadyProcesses();
    protected:
        // New processes admitted by process management
        list<Process*> new_processes;
        // All processes in sorted order to feed to the processor. Essentially the ready queue
        list<Process*> m_processes;
        // The scheduler is linked to a processor. May change to have multiple processors
        Processor m_processor;
};

class FirstInFirstOut : public Scheduler{
    public:
        using Scheduler::Scheduler;
};

class ShortestJobNext : public Scheduler{
    public:
        // Essential Overrides
        ShortestJobNext(Processor mProc) : Scheduler(mProc) {};
        void addNewProcess() override;

        // Debugging Overrides
        void print() override {cout << "SJN" << endl;}
};

class Factory{
    public:
        static Scheduler* createAlgorithm(const int& choice, Processor mProcessor){
            switch (choice){
                case FIFO:
                    cout << "FIFO Chosen" << endl;
                    return new FirstInFirstOut(mProcessor);
                case SJN:
                    cout << "SJN chosen" << endl;
                    return new ShortestJobNext(mProcessor);
                default:
                    cout << "Defaulting to FIFO" << endl;
                    return new FirstInFirstOut(mProcessor);
            }
        }
};

#endif