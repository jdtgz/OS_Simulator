/*
 * CentralProcessor class runs a single process at a time
 * Simulates the OS processor
 */

#include "Process.h"


#pragma once
class CentralProcessor
{
    public:
        // Constructor & Destructor
        CentralProcessor();
        ~CentralProcessor();

        // Sets m_process and sets free to false
        void newProcess(Process* p);

        // Continues to run a process or completes a process
        bool runProcess(const long& time);

        // Returns m_process
        Process* checkProcess();

        // Returns free
        bool isFree();

    private:
        // Each processor holds one process at a time
        Process* m_process;

        // Shows whether the processor is free to admit a new process or not
        bool free;
};