#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "process.h"


// Runs a process
class Processor{
    public:
        Processor() {};

        // Essential class functions
        void newProcess(Process* p);
        bool runProcess();
        Process checkProcess() {return *m_process;}
        bool isFree() {return free;}

    private:
        // Each processor holds one process at a time
        Process* m_process = nullptr;
        // Shows whether the processor is free to admit a new process or not
        bool free = true;
};


#endif