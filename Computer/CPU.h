#ifndef CPU_H
#define CPU_H

#include "types.h"

class RAM;

class CPU {
	private:
		typedef ComputerTypes::register_type register_type;
		typedef ComputerTypes::value_type value_type;
		register_type numOfRegisters;
		std::vector<value_type> registers;
		std::shared_ptr<RAM> ram;
		bool valid_register(register_type rnum);
	public:
		CPU () : numOfRegisters(0) {}
		CPU (register_type numOfRegisters, std::shared_ptr<RAM> r) : numOfRegisters(numOfRegisters), 
											 						 registers(numOfRegisters + 1, 0), //numeracja od jednego
											 						 ram(r) {}
		CPU (const CPU& c) : numOfRegisters(c.numOfRegisters) 
							 registers(c.registers)
							 ram(c.ram) {}
		~CPU () {}
		CPU& operator= (const CPU& c);
		void set (register_type rnum, value_type val);
		void load (register_type rnum, memory_type maddr);
		void add (register_type rnum1, register_type rnum2);
		void sub (register_type rnum1, register_type rnum2);
		void mul (register_type rnum1, register_type rnum2);
		void div (register_type rnum1, register_type rnum2);
		void println (register_type rnum);
		register_type getNrOfRegisters ();
		value_type getRegisterValue (register_type rnum);
};

#endif
