#include <iostream>
#include <string>
#include <sstream>
#include <list>

#include "computer.h"
#include "OS.h"
#include "program.h"

OS& OS::operator= (const OS& o) {										//////////////////////////??TODODOOOOTODOTODOTOD
	this->host = o.host;
	this->algorithm = o.algorithm;
	return *this;
}

void OS::executePrograms(const std::list<std::string>& progs) {
	std::list<Program> programs;
	ComputerTypes::time_type quantum;		// kwant czasu
	
	for (auto it = progs.cbegin(); it != progs.cend(); ++it) {
		programs.push_back(parser.parse(*it));
	}
	algorithm->schedule(programs);
	while (algorithm->programsAvail()) {
		Program& prog = algorithm->nextProgram(quantum);
		while (quantum > 0 && prog.executeNext(host)){
			--quantum;
		}
		algorithm->quantumEnd();
	}
}
