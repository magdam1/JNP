#include <iostream>
#include "exceptions.h"
#include "cpu.h"
#include "ram.h"

bool CPU::valid_register (register_type rnum) {
	return ((rnum > 0) && (rnum <= this->numOfRegisters));
}
CPU& CPU::operator= (const CPU& c) {
	this->numOfRegisters = c->numOfRegisters;
	this->registers = c.registers;
	this->ram = c.ram;
}
void CPU::set (register_type rnum, value_type val) {
	try {
		if (!valid_register(rnum))
			throw InvalidRegisterException();
		this->registers[rnum] = val;
	}
	catch (InvalidRegisterException e) {
		std::cerr << e.what() << std::endl;
	}
}
void CPU::load (register_type rnum, memory_type maddr) {
	try {
		if (!valid_register(rnum))
			throw InvalidRegisterException();
		this->registers[rnum] = this->ram->getMemoryAddrValue(maddr); //shared ptr?
	}
	catch (InvalidRegisterException e) {
		std::cerr << e.what() << std::endl;
	}
}
void CPU::add (register_type rnum1, register_type rnum2) {
	try {
		if (!valid_register(rnum1)
			|| !valid_register(rnum2))
			throw InvalidRegisterException();
		this->registers[rnum1] += this->registers[rnum2];
	}
	catch (InvalidRegisterException e) {
		std::cerr << e.what() << std::endl;
	}
}
void CPU::sub (register_type rnum1, register_type rnum2) {
	try {
		if (!valid_register(rnum1)
			|| !valid_register(rnum2))
			throw InvalidRegisterException();
		this->registers[rnum1] -= this->registers[rnum2];
	}
	catch (InvalidRegisterException e) {
		std::cerr << e.what() << std::endl;
	}
}
void CPU::mul (register_type rnum1, register_type rnum2) {
	try {
		if (!valid_register(rnum1)
			|| !valid_register(rnum2))
			throw InvalidRegisterException();
		this->registers[rnum1] *= this->registers[rnum2];
	}
	catch (InvalidRegisterException e) {
		std::cerr << e.what() << std::endl;
	}
}
void CPU::div (register_type rnum1, register_type rnum2) {
	try {
		if (!valid_register(rnum1)
			|| !valid_register(rnum2))
			throw InvalidRegisterException();
		if (rnum2 == 0)
			throw DivisionByZero();
		this->registers[rnum1] /= this->registers[rnum2];
	}
	catch (std::exception e) {
		std::cerr << e.what() << std::endl;
	}
}
void CPU::println (register_type rnum) {
	try {
		if (!valid_register(rnum))
			throw InvalidRegisterException();
		std::cout << this->registers[rnum] << std::endl;
	}
	catch (InvalidRegisterException e) {
		std::cerr << e.what() << std::endl;
	}
}
register_type CPU::getNrOfRegisters() {
	return this->numOfRegisters;
}
value_type CPU::getRegisterValue (register_type rnum) {
	try {
		if (!valid_register(rnum))
			throw InvalidRegisterException();
		return this->registers[rnum];
	}
	catch (InvalidRegisterException e) {
		std::cerr << e.what() << std::endl;
	}
}