#ifndef RAM_H
#define RAM_H

class CPU;

class RAM {
	private:
		typedef ComputerTypes::memory_type memory_type;
		typedef ComputerTypes::value_type value_type;
		memory_type memorySize;
		std::vector<value_type> memory;
		std::shared_ptr<CPU> cpu;
		bool valid_address(memory_type maddr);
	public:
		RAM () : memorySize(0) {}
		RAM (memory_type memorySize, std::shared_ptr<CPU> c) : 	memorySize(memorySize),
																memory(memorySize, 0),
																cpu(c) {}
		RAM (const RAM& r) : memorySize(r.memorySize),
							 memory(r.memory),
							 cpu(r.cpu) {}
		~RAM () {}
		RAM& operator= (const RAM& r);
		void store (memory_type maddr, register_type rnum);
		memory_type getMemorySize ();
		value_type getMemoryAddrValue (mamory_type maddr);
};

#endif