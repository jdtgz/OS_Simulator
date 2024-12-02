/*
 * 
 */

#include "Process.h"


#pragma once
class CentralProcessor
{
    public:
        CentralProcessor();
        ~CentralProcessor();

        // Essential class functions
        void newProcess(Process* p);

        bool runProcess(const long& time);

        Process* checkProcess();

        bool isFree();

    private:
        // Each processor holds one process at a time
        Process* m_process;

        // Shows whether the processor is free to admit a new process or not
        bool free;
};