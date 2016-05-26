#ifndef FCFSSCHEDULING_H
#define FCFSSCHEDULING_H

#include <iostream>
#include "list_scheduling.h"

class FCFSScheduling : public ListScheduling {
	public:
		FCFSScheduling() {};
		virtual void schedule(std::list<Program>& programs);
};

void FCFSScheduling::schedule(std::list<Program>& progs) {
	std::cout << "FCFS!\n";
	programs = progs;
	program = programs.end();
}

#endif