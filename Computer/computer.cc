#include <iostream>
#include <vector>
#include "exceptions.h"
#include "computer.h"
#include "cpu.h"
#include "ram.h"

Computer::Computer () {
	this->cpu = std::make_shared<CPU>(CPU());
	this->ram = std::make_shared<RAM>(RAM());
}
Computer& Computer::operator= (const Computer& c) {
	this->cpu = c.cpu;
	this->memory = c.memory;
	return *this;
}
void Computer::setCPU (register_type numOfRegisters) {
	try {
		if (numOfRegisters <= 0)
			throw IllegalArgumentException();
		this->cpu = std::make_shared<CPU>(CPU(numOfRegisters, this->ram)); //new?
	}
	catch (IllegalArgumentException e) {
		std::cerr << e.what() << std::endl;
	}
}
void Computer::setRAM (memory_type size) {
	try {
		if (size <= 0)
			throw IllegalArgumentException();
		this->ram = std::make_shared<RAM>(RAM(size, this->cpu));
	}
	catch (IllegalArgumentException e) {
		std::cerr << e.what() << std::endl;
	}
}
std::shared_ptr<OS> Computer::installOS (std::shared_ptr<SchedulingAlgorithm> alg) {
	try {
		if (!this->cpu->getNrOfRegisters())
			throw NoCPUException();
		if (!this->ram->getMemorySize())
			throw NoRAMException();
	}
	catch (std::exception e) {
		std::cerr << e.what() << std::endl;
	}
	return std::make_shared<OS>(OS(*this, alg));
}