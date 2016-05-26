#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>
#include <cstdint>
#include <memory>
#include "OS.h"
#include "ram.h"
#include "types.h"

class SchedulingAlgorithm;

class Computer {
	private:
		typedef ComputerTypes::register_type register_type;
		typedef ComputerTypes::memory_type memory_type;
		typedef ComputerTypes::value_type value_type;
		std::shared_ptr<CPU> cpu;
		std::shared_ptr<RAM> ram;
	public:
		Computer ();
		Computer (const Computer& c) :  cpu(c.cpu),
										ram(c.ram) {}
		~Computer () {}
		Computer& operator= (const Computer& c);
		void setCPU (register_type numOfRegisters);
		void setRAM (memory_type size);
		std::shared_ptr<OS> installOS (std::shared_ptr<SchedulingAlgorithm> alg);
};

#endif