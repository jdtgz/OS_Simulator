/*
 * Name: Daniel Toro and Jacob Reese
 * Date: 11/08/2024 
 * File: OS_Simulator.cpp
 * Purpose: ...
 */

#include "Simulator.h"
#include "ProjectManagement.h"

#include <chrono>
#include <thread>

using namespace std;


int main()
{
    Simulator simulation;

    cout << "started" << endl;
    //creating processMgmt object with chosen scheduler
    Algs algorithmChoice = RR;
    ProjectManagement processMgmt = ProjectManagement(Factory::createAlgorithm(algorithmChoice, CentralProcessor()));
    processMgmt.printScheduler();

    cout << "declaring variables" << endl;
    long time = 0;
    long sleepDuration = 0;


    string file = "./procInput1.txt";
    stringstream ss;

    //filling all processes
    cout << "reading process file" << endl;
    processMgmt.readProcessFile(file);
    cout << "reading complete" << endl;
    processMgmt.printAllProcesses();
    int processesRemaining = processMgmt.numProcesses();

    cout << "Starting loop \n" << endl;
    //keep running the loop until all processes have been added and have run to completion
    while (processesRemaining > 0) {
        // cout << "iteration" << endl;
        //Update our current time step
        ++time;
        //let new processes in if there are any
        // cout << "activating processes" << endl;
        processMgmt.activateProcesses(time);
        //run a step
        // cout << "running step" << endl;
        stepAction step = processMgmt.runStep(time);
        if (step == COMPLETE) 
        {
            processesRemaining--;
        }

        // cout << "starting display" << endl;
        // All terminal visuals
        cout << setw(5) << time << "\t";
        switch (step) 
        {
            case ADMIT_NEW_PROCESS:
                cout << "[  admit]\t";
                break;
            case BEGIN_RUN:
                cout << "[  begin]\t";
                break;
            case CONTINUE_RUN:
                cout << "[contRun]\t";
                break;
            case CONTEXT_SWITCH:
                cout << "[  switch]\t";
                break;
            case COMPLETE:
                cout << "[ finish]\t";
                break;
            case NO_ACT:
                cout << "[*noAct*]\t";
                break;
        }
        // cout << "printing states" << endl;
        processMgmt.printStates();
        // processMgmt.printScheduler();

        // Sleep
        // cout << "sleeping" << endl;
        this_thread::sleep_for(chrono::milliseconds(sleepDuration));
    }
    cout << "loop complete" << endl;
    processMgmt.printAllProcesses();

    simulation.run();

    return 0;
}