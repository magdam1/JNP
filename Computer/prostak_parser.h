#ifndef PROSTAKPARSER_H
#define PROSTAKPARSER_H

#include "program.h"
class Instruction;

class ProstakParser {

	public:
		ProstakParser() {}
		
		Program parse(const std::string& source);
		std::shared_ptr<Instruction> switchInstr(const std::string& instr, const std::string& args);
		
};

#endif