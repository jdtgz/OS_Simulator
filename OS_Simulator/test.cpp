#include "process.h"
#include "processMgmt.h"
#include "processor.h"
#include "scheduler.h"

#include <chrono> // for sleep
#include <thread> // for sleep

int main(){
    Process myProcess;
    Processor myProcessor;
    Scheduler myScheduler(myProcessor, FIFO);

    myScheduler.addNewArrival(&myProcess);
    cout << myProcess.id << endl;
    cout << myScheduler.new_processes.front()->id << endl;
    myScheduler.new_processes.front()->id = 0;
    cout << myProcess.id << endl;
    cout << myScheduler.new_processes.front()->id << endl;
    myScheduler.addNewProcess();
    cout << myScheduler.m_processes.front()->id << endl;
    myScheduler.m_processes.front()->id = 1;
    myProcess.printProcess();
    myScheduler.new_processes.front()->printProcess();
    myScheduler.m_processes.front()->printProcess();


    return 0;
}