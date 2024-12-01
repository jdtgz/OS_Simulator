#pragma once

#include<iostream>
#include<list>
#include<vector>
#include<sstream>
#include<fstream>
#include<iomanip>

using namespace std;


// State of the process
enum State { ready, processing, blocked, newArrival, done, awaiting };


// Process struct
struct Process{
    Process() : id(999999), arrivalTime(-1), doneTime(-1), reqProcessorTime(0), processorTime(0), state(awaiting) {}

    // Essential struct values
    unsigned int id;
    State state;
    long arrivalTime;
    long reqProcessorTime;
    long processorTime;
    long doneTime;

    // Debugging helper
    void printProcess(){
        cout << setw(5) << id << " |";
        cout << setw(2) << arrivalTime << " |";
        cout << setw(5) << doneTime << " |";
        cout << setw(3) << reqProcessorTime << " |";
        cout << setw(3) << processorTime << " |"; 
        cout << setw(2) << state << " |";
        cout << setw(3) << (((doneTime-arrivalTime) + processorTime)/reqProcessorTime) << " |";
        cout << endl;
    }
};


// Print all information about all processes from a vector (debugging helper)
void printProcessSet(vector<Process>& processVector);