#include <list>
#include "computer.h" 

int main(int argc, const char * argv[]) {

	std::shared_ptr<Computer> computer(new Computer());

	computer->setCPU(2);

	computer->setRAM(100);

	std::shared_ptr<OS> os = computer->installOS(createRRScheduling(10));

	
	std::string program = "SET R1 123\nPRINTLN R1";
	std::string program2 = "SET R1 13\nSET R3 2\nADD R3 R1\nPRINTLN R3";
	std::string program3 = "MUL R1 R2\nSET R3 1\nADD R3 R1\nPRINTLN R2\nDIV  R5   R1";
	
	/*
	std::string program = "ADD R1 R3\nADD R1 R4";
	std::string program2 = "ADD R5 R3\nADD R1 R3\nADD R2  R3\nADD R1 R3";
	std::string program3 = "ADD R2 R4\nADD R1 R7\nADD R3 R1\nADD R1 R3\nADD  R1 R3";
	*/
	std::list<std::string> programs;

	programs.push_back(program2);
	programs.push_back(program3);
	programs.push_back(program);

	os->executePrograms(programs);

	return 0;

}