#ifndef OS_H
#define OS_H

#include <list>
#include "types.h"
#include "prostak_parser.h"
#include "scheduling_algorithm.h"

class OS {
	private:
		typedef ComputerTypes::memory_type memory_type;
		typedef ComputerTypes::register_type register_type;
		typedef ComputerTypes::value_type value_type;

		Computer& host;
		ProstakParser parser;
		std::shared_ptr<SchedulingAlgorithm> algorithm;
		
	public:
		typedef std::list<std::string> program;
		typedef std::shared_ptr<OS> ptr;
		OS (Computer& host, std::shared_ptr<SchedulingAlgorithm> alg)
					: host(host), algorithm(alg) {}
		OS (const OS& o) : host(o.host), algorithm(o.algorithm) {}
		OS& operator= (const OS& o);
		void executePrograms(const std::list<std::string>& programs);
};

#endif