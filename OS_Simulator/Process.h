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


class Process
{
	public:
		Process();
		~Process();

		void printProcess();

		void printProcessSet(std::vector<Process>& processVec);

		unsigned int getID();
		void setID(unsigned int newID);
		
		State getState();
		void setState(State newState);

		long getArrivalTime();
		void setArrivalTime(long arrival);

		long getReqProcTime();
		void setReqProcTime(long newTime);

		long getProcessorTime();
		void setProcessorTime(long newTime);

		long getDoneTime();
		void setDoneTime(long newTime);

	private:
		unsigned int id;

		State curState; 
		
		long arrivalTime;
		
		long reqProcessorTime;
		
		long processorTime;
		
		long doneTime;
};