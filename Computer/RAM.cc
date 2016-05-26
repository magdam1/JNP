#include "exceptions.h"
#include "ram.h"
#include "cpu.h"

bool RAM::valid_address (memory_type maddr) {
	return ((maddr >= 0) && (maddr < this->memorySize));
}
RAM& RAM::operator= (const RAM& r) {
	this->memorySize = r.memorySize;
	this->memory = r.memory;
	this->cpu = r.cpu;
}
void RAM::store (memory_type maddr, register_type rnum) {
	try {
		if (!valid_address(maddr))
			throw InvalidAddressException();
		this->memory[maddr] = this->cpu->getRegisterValue(); //shared ptr!!!
	}
	catch (InvalidAddressException e) {
		std::cerr << e.what() << std::endl;
	}
}
memory_type RAM::getMemorySize () {
	return this->memorySize;
}
value_type RAM::getMemoryAddrValue (mamory_type maddr) {
	try {
		if (!valid_address(maddr))
			throw InvalidAddressException();
		return this->memory[maddr];
	}
	catch (InvalidAddressException e) {
		std::cerr << e.what() << std::endl;
	}
}