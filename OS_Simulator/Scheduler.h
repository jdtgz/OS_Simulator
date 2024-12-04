/*
 * Scheduler class manages the processes to run in the processor
 * Simulates the OS scheduling algorithm
 */

#include "CentralProcessor.h"


#pragma once
// Scheduling algorithm options
enum Algs { FIFO, RR, SJN };


// Types of actions that can be complete at each time interval/step
enum stepAction { NO_ACT, ADMIT_NEW_PROCESS, 
	BEGIN_RUN, CONTINUE_RUN, COMPLETE, CONTEXT_SWITCH };


// 
struct ProcessInProgress
{
    ProcessInProgress();
    ~ProcessInProgress();

    Process* p;
    stepAction* latestStep;
};


// Parent scheduler class
class Scheduler
{
	public:
        // Constructor & Destructor
		Scheduler();
		~Scheduler();

        // Overloaded Contructor
		Scheduler(CentralProcessor m_processor);

        // Adds a process to the newProcesses list
		void addNewArrival(Process* p);

        // Adds a process from newProcesses to readyProcesses
		virtual Process* addNewProcess();

        // Begins running a new process by inserting it into the processor
		virtual Process* beginNewProcess();

        // Continues running a process
        virtual void continueProcessing(ProcessInProgress& p);

        // Chooses an action above based on the resources available
		ProcessInProgress runProcesses(const long& time);

        // Prints "FIFO" (debugging function)
        virtual void print();

        // Prints all processes in the ready list (debugging function)
		void printReadyProcesses();

	protected:
        // List of newly admitted processes
		std::list<Process*> newProcesses;

        // List of ready to run processes in sorted order
		std::list<Process*> readyProcesses;

        // The processor used to run processes
		CentralProcessor processor;
};


// FIFO child class
class FirstInFirstOut : public Scheduler 
{
    public:
        // Constructor (FIFO is the same as the base scheduler class)
        using Scheduler::Scheduler;
    private:
};


// SJN child class
class ShortestJobNext : public Scheduler 
{
    public:
        // Constructor for SJN
        ShortestJobNext(CentralProcessor mProc);

        // Adds and sorts a new process into readyProcesses based on reqProcessorTime (Override)
        virtual Process* addNewProcess();

        // Prints "SJN" (debugging function)
        virtual void print();
    private:
};


// RR child class
class RoundRobin : public Scheduler 
{
    public:
        // Constructor for RR
        RoundRobin(CentralProcessor mProc);

        // Begins running a new process and sets preempt = 0 (Override)
        virtual Process* beginNewProcess();

        // Continues running a process or switches the active process
        virtual void continueProcessing(ProcessInProgress& proc);

        // Setter function for preemptionTime
        void setPreemptionTime(int timer);

        // Prints "RR" (debugging function)
        virtual void print();
    private:
        // The amount of time a process has in the processor till it is switched
        int preemptionTime;

        // A timer that shows how long the active process has been running for
        int preempt;
};


// A Factory class used to create scheduler subclasses
class Factory 
{
    public:
        // Constructor & Destructor
        Factory();
        ~Factory();

        // Creates a scheduler subclass based on the inputted choice
        static Scheduler* createAlgorithm(const int& choice, CentralProcessor mProcessor);
    private:
};