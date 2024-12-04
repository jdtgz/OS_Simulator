/*
 * Process struct holds all process metadata
 * Simulates the OS process control block
 */

#include<iostream>
#include<list>
#include<vector>
#include<sstream>
#include<fstream>
#include<iomanip>


#pragma once
// Types of states for processes 
enum State { READY, RUNNING, BLOCKED, NEW_ARRIVAL, DONE, AWAITING };


struct Process
{
	// Constructor & Destructor
	Process();
	~Process();

	// Prints all member variables
	void printProcess();

	// Unique integer used for process identification
	unsigned int id;

	// The state of the process
	State curState; 
		
	// The time interval at which the process is admitted to the scheduler
	long arrivalTime;
		
	// The total processing time needed
	long reqProcessorTime;
		
	// The processing time consumed
	long processorTime;
		
	// The time interval at which the process is completed
	long doneTime;
};