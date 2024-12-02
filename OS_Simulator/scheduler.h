#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "processor.h"


// Algorithms to use
enum Alg { FIFO, RR, SJN, SRT };
// To know what action happened at each time interval. May help when adding visuals.
enum stepActionEnum {noAct, admitNewProc, handleInterrupt, beginRun, continueRun, complete, contextSwitch};


// Schedules the process to be run by the processor
class Scheduler{
    public:
        Scheduler(Processor mProcessor) : m_processor(mProcessor) {}; 

        int preempt = 0;

        // Essential class functions
        void addNewArrival(Process* p);
        virtual void addNewProcess();
        void beginNewProcess();
        stepActionEnum runProcesses(const long& time);
        virtual stepActionEnum continueProcessing() {return continueRun;}

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

class RoundRobin : public Scheduler{
    public:
        // Essential Overrides
        RoundRobin(Processor mProc) : Scheduler(mProc) {};
        stepActionEnum continueProcessing() override;

        // Added Functions
        void setPreemptionTime(int timer) {preemptionTime = timer;}

        // Debugging Overrides
        void print() override {cout << "RR" << endl;}
    private:
        int preemptionTime = 20;
};

class Factory{
    public:
        static Scheduler* createAlgorithm(const int& choice, Processor mProcessor){
            switch (choice){
                case FIFO:
                    cout << "FIFO chosen" << endl;
                    return new FirstInFirstOut(mProcessor);
                case SJN:
                    cout << "SJN chosen" << endl;
                    return new ShortestJobNext(mProcessor);
                case RR:
                    cout << "RR chosen" << endl;
                    return new RoundRobin(mProcessor);
                default:
                    cout << "Defaulting to FIFO" << endl;
                    return new FirstInFirstOut(mProcessor);
            }
        }
};

#endif