#ifndef SJFSCHEDULING_H
#define SJFSCHEDULING_H

#include <vector>
#include "list_scheduling.h"

class SJFScheduling : public ListScheduling {
	public:
		SJFScheduling() {};
		virtual void schedule(std::list<Program>& progs);
};

bool progs_comp(const Program& prog1, const Program& prog2) {
	return prog1.length() < prog2.length();
}

void SJFScheduling::schedule(std::list<Program>& progs) {
	std::cout << "SJF!\n";
	programs = progs;
	programs.sort(progs_comp);
	program = programs.end();
}

#endif