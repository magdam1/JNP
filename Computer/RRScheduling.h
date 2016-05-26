#ifndef RRSCHEDULING_H
#define RRSCHEDULING_H

#include "list_scheduling.h"
#include "exceptions.h"

class RRScheduling : public ListScheduling {
	private:
		size_t quantum;
	public:
		RRScheduling(size_t quantum) : quantum(quantum) {
			if (quantum <= 0) throw IllegalArgumentException();
		};
		virtual void schedule(std::list<Program>& progs);
		virtual Program& nextProgram(int& quantum);

};

void RRScheduling::schedule(std::list<Program>& progs) {
	std::cout << "RR!\n";
	programs = progs;
	program = programs.end();
}

/* przedefiniowana domyÅ›lna implementacja */
Program& RRScheduling::nextProgram(int& quantum) {
	if (++program == programs.end())
		program = programs.begin();
	quantum = this->quantum;
	return *program;
}

#endif