#ifndef PROGRAM_H
#define PROGRAM_H

#include <memory>
#include <vector>
#include "instruction.h"

class Program {
	typedef std::vector<std::shared_ptr<Instruction> > instructions;
	typedef instructions::const_iterator program_counter;
	instructions program;

	public:
		program_counter pc;
		
		Program(const instructions& prog) : program(prog), pc(program.cbegin()) {}
		Program(const Program& prog) : program(prog.program), pc(program.cbegin()) {}
		
		program_counter cbegin() const { return program.cbegin(); }
		program_counter cend() const { return program.cend(); }
		size_t length() const { return program.size(); }
		
		/* zwraca true <=> program siÄ™ jeszcze nie skoÅ„czyÅ‚ */
		bool executeNext(Computer& comp) {
			(*pc)->execute(comp);
			return (++pc != program.cend());
		}
};

#endif