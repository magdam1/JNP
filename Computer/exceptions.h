#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

struct UnknownInstructionException : public std::exception {
	virtual const char* what() const throw () {
			return "Unknown instruction!";
		}
};




struct InvalidRegisterException : public std::exception {
	virtual const char* what() const throw () {
			return "Invalid register number!";
		}
};

struct InvalidAddressException : public std::exception {
	virtual const char* what() const throw () {
			return "Invalid memory address!";
		}
};

struct DivisionByZeroException : public std::exception {
	virtual const char* what() const throw () {
			return "Division by zero!";
		}
};




struct IllegalArgumentException : public std::exception {
	virtual const char* what() const throw () {
			return "Illegal argument!";
		}

};

struct NoCPUException : public std::exception {
	virtual const char* what() const throw () {
			return "CPU is not initialized!";
		}

};

struct NoRAMException : public std::exception {
	virtual const char* what() const throw () {
			return "RAM is not initialized!";
		}

};


#endif