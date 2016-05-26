#include <iostream>
#include <sstream>
#include <algorithm>
#include "prostak_parser.h"
#include "program.h"
#include "instruction_set.h"

static bool is_space(const char c) {
	return std::isspace(c);
}

Program ProstakParser::parse(const std::string& source) {
	std::cout << "Parser PROSTAK\n";
	std::vector<Instruction::ptr> result;
	std::istringstream src(source);
	std::istringstream ln;
	std::string line;
	std::string instr;
	
	while(getline(src, line)) {
		ln.clear();
		ln.str(line);
		ln >> instr;
		result.push_back(switchInstr(instr, line));
	}
	
	return Program(result);
}

Instruction::ptr ProstakParser::switchInstr(const std::string& instr, const std::string& line) {
	std::cout << "Instruction: [" << line << "] -> [" << instr << "]\n";
	Instruction::ptr result;
	if			(instr == "SET") 			result = Instruction::ptr(new SetInstr());
	else if (instr == "LOAD") 		result = Instruction::ptr(new LoadInstr());
	else if (instr == "STORE") 		result = Instruction::ptr(new StoreInstr());
	else if (instr == "ADD") 			result = Instruction::ptr(new AddInstr());
	else if (instr == "SUB") 			result = Instruction::ptr(new SubInstr());
	else if (instr == "MUL") 			result = Instruction::ptr(new MulInstr());
	else if (instr == "DIV") 			result = Instruction::ptr(new DivInstr());
	else if (instr == "PRINTLN") 	result = Instruction::ptr(new PrintlnInstr());
	else throw UnknownInstructionException();
	
	result->feed(line);
	return result;
}