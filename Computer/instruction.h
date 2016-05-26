#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <memory>
#include "types.h"
class Computer;

class Instruction {
	protected:
		typedef ComputerTypes::register_type reg_type;
		typedef ComputerTypes::memory_type mem_type;
		typedef ComputerTypes::value_type val_type;
		
	public:
		typedef std::shared_ptr<Instruction> ptr;
		Instruction() {}
		virtual ~Instruction() {}
		virtual void execute(Computer& comp) const = 0;
		/* po stworzeniu obiektu typu 'Instruction' trzeba mu podaÄ‡ liniÄ™ do wykonania */
		virtual void feed(const std::string& line) = 0;
		
	protected:
		bool unfed = true;		// czy obiekt jest niegotowy
		/* nazwa instrukcji */
		virtual std::string getName() const = 0;
		/* funkcje sprawdzajÄ…ce poprawnoÅ›Ä‡ argumentu odpowiedniego typu
			 i zwracajÄ…ce tÄ™ wartoÅ›Ä‡ */
		virtual reg_type validateReg(const std::string& arg);
		virtual mem_type validateMem(const std::string& arg);
		virtual val_type validateVal(const std::string& arg);
};


#endif