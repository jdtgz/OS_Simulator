/*
 * ProjectManagement class holds all OS simulating objects
 * Handles interactions between the user and the OS
 */

#include <algorithm>
#include "Scheduler.h"


#pragma once
// Compares processes by arrival time
inline bool procComp(const Process& p1, const Process& p2)
{
	return p1.arrivalTime > p2.arrivalTime;
}


// Manages all processes and OS simulation aspects
class ProjectManagement
{
	public:
		// Constructor & Destructor
		ProjectManagement();
		~ProjectManagement();

		// Overloaded constructor
		ProjectManagement(Scheduler* mScheduler);

		// Reads processes in a file into totalProcesses
		void readProcessFile(const std::string& file);

		// Feeds process pointers into the scheduler upon arrival time
		void activateProcesses(const int& time);

		// Runs a single scheduler step
		ProcessInProgress runStep(const long& time);

		// Prints the states of all processes (debugging function)
		void printStates();

		// Prints the process data of all processes (debugging function)
		void printAllProcesses();

		// Prints the scheduler type and all ready processes
		void printScheduler();

		// Returns the total number of processes
		int numProcesses();
	private:
		// Vector of all processes
		std::vector<Process> totalProcesses;

		// A pointer to the scheduler used
		Scheduler* mScheduler;
};