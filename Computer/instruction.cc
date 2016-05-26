#include <memory>
#include <iostream>
#include <sstream>
#include "types.h"
#include "instruction.h"
#include "exceptions.h"

Instruction::reg_type Instruction::validateReg(const std::string& arg) {
	if (arg.size() < 2 || arg[0] != 'R')
		throw UnknownInstructionException();
	std::istringstream num(arg.substr(1));
	reg_type number;
	num >> number;
	if (num.fail() || !num.eof())
		throw UnknownInstructionException();
	return number;
}

Instruction::mem_type Instruction::validateMem(const std::string& arg) {
	if (arg.size() < 2 || arg[0] != 'M')
		throw UnknownInstructionException();;
	std::istringstream num(arg.substr(1));
	mem_type number;
	num >> number;
	if (num.fail() || !num.eof())
		throw UnknownInstructionException();
	return number;
}

Instruction::val_type Instruction::validateVal(const std::string& arg) {
	if(arg.empty())
		throw UnknownInstructionException();
	std::istringstream num(arg);
	val_type number;
	num >> number;
	if (num.fail() || !num.eof())
		throw UnknownInstructionException();
	return number;
}