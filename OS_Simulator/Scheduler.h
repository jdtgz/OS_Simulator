/*
 * 
 */

#include "CentralProcessor.h"


#pragma once
enum Algs { FIFO, RR, SJN, SRT };


enum stepAction { NO_ACT, ADMIT_NEW_PROCESS, HANDLE_INTERRUPT, 
	BEGIN_RUN, CONTINUE_RUN, IO_REQUEST, COMPLETE, CONTEXT_SWITCH };


class Scheduler
{
	public:
		Scheduler();
		~Scheduler();

		Scheduler(CentralProcessor m_processor);

		void addNewArrival(Process* p);

		virtual void addNewProcess();

		void beginNewProcess();

		stepAction runProcesses(const long& time);

		virtual stepAction continueProcessing();

		virtual void print();

		void printReadyProcesses();

	protected:
		int preempt; 

		std::list<Process*> newProcesses;

		std::list<Process*> curProcesses;

		CentralProcessor processor;
};


class FirstInFirstOut : public Scheduler 
{
    public:
        using Scheduler::Scheduler;
    private:
};


class ShortestJobNext : public Scheduler 
{
    public:
        // Essential Overrides
        ShortestJobNext(CentralProcessor mProc);
        virtual void addNewProcess();

        // Debugging Overrides
        virtual void print();
    private:
};


class RoundRobin : public Scheduler 
{
    public:
        // Essential Overrides
        RoundRobin(CentralProcessor mProc);
        virtual stepAction continueProcessing();

        // Added Functions
        void setPreemptionTime(int timer);

        // Debugging Overrides
        virtual void print();
    private:
        int preemptionTime;
};


class Factory 
{
    public:
        Factory();
        ~Factory();

        static Scheduler* createAlgorithm(const int& choice, CentralProcessor mProcessor);
    private:
};