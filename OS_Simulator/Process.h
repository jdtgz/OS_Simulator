/*
 * 
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
	public:
		Process();
		~Process();

		void printProcess();

		void printProcessSet(std::vector<Process>& processVec);

		unsigned int id;

		State curState; 
		
		long arrivalTime;
		
		long reqProcessorTime;
		
		long processorTime;
		
		long doneTime;
};