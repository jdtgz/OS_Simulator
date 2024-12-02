/*
 * 
 */

#include <algorithm>
#include "Scheduler.h"


#pragma once
inline bool procComp(const Process& p1, const Process& p2)
inline bool procComp(const Process& p1, const Process& p2)
inline bool procComp(const Process& p1, const Process& p2)
inline bool procComp(const Process& p1, const Process& p2)
inline bool procComp(const Process& p1, const Process& p2)
inline bool procComp(const Process& p1, const Process& p2)
{
	return p1.arrivalTime > p2.arrivalTime;
}


class ProjectManagement
{
	public:
		ProjectManagement();
		~ProjectManagement();
		ProjectManagement(Scheduler* mScheduler);

		void activateProcesses(const int& time);

		stepAction runStep(const long& time);

		void printStates();

		void printAllProcesses();

		void printScheduler();

		int numProcesses();

		void readProcessFile(const std::string& file);
	private:
		std::vector<Process> totalProcesses;

		Scheduler* mScheduler;
};