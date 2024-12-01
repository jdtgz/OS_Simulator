#include "processor.h"

// Switches which process is in the processor
void Processor::newProcess(Process p){
    m_process = p;
    free = false;
}

// Updates process depending if it is complete or not. Returns true if complete.
bool Processor::runProcess(){
    if(m_process.processorTime >= m_process.reqProcessorTime){
        m_process.state = done;
        free = true;
        return true;
    } 
    else {
        m_process.processorTime++;
        return false;
    }
}