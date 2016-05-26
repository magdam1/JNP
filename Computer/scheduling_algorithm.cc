#include "scheduling_algorithm.h"
#include "list_scheduling.h"
#include "FCFSScheduling.h"
#include "RRScheduling.h"
#include "SJFScheduling.h"

std::shared_ptr<SchedulingAlgorithm> createFCFSScheduling () {
	return std::shared_ptr<FCFSScheduling>(new FCFSScheduling());
}

std::shared_ptr<SchedulingAlgorithm> createRRScheduling (ComputerTypes::time_type quantum) {
	return std::make_shared<RRScheduling>(RRScheduling(quantum));
}

std::shared_ptr<SchedulingAlgorithm> createSJFScheduling () {
	return std::make_shared<SJFScheduling>(SJFScheduling());
}