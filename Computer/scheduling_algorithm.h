#ifndef SCHEDULINGALGORITHM_H
#define SCHEDULINGALGORITHM_H

#include <list>
#include <memory>
#include "types.h"
#include "program.h"

class SchedulingAlgorithm {
	protected:
		typedef ComputerTypes::time_type time_type;
	public:
		SchedulingAlgorithm() {};
		virtual ~SchedulingAlgorithm() {};
		virtual void schedule(std::list<Program>& programs) = 0;
		virtual bool programsAvail() const = 0;
		virtual Program& nextProgram(time_type& quantum) = 0;
		virtual void quantumEnd() = 0;
};
class ListScheduling;
std::shared_ptr<SchedulingAlgorithm> createFCFSScheduling();
std::shared_ptr<SchedulingAlgorithm> createRRScheduling(ComputerTypes::time_type quantum);
std::shared_ptr<SchedulingAlgorithm> createSJFScheduling();

#endif