#ifndef LISTSCHEDULING_H
#define LISTSCHEDULING_H

#include <list>
#include <memory>

#include "scheduling_algorithm.h"
#include "program.h"

class ListScheduling : public SchedulingAlgorithm {
	protected:
		std::list<Program> programs;
		std::list<Program>::iterator program;
	public:
		ListScheduling() {};
		virtual ~ListScheduling() {};
		virtual void schedule(std::list<Program>& programs) = 0;
		
		virtual bool programsAvail() const {
			return !programs.empty();
		}
		
		/* domyÅ›lnie: wykonywanie do samego koÅ„ca */
		virtual Program& nextProgram(time_type& quantum) {
			if (++program == programs.end())
				program = programs.begin();
			quantum = program->cend() - program->pc;	// do koÅ„ca
			return *program;
		}
		
		/* jeÅ›li program siÄ™ skoÅ„czyÅ‚, to usuwamy go z listy i przesuwamy
			 iterator na miejsce tuÅ¼ przed usuniÄ™tym */
		virtual void quantumEnd() {
			if (program->pc == program->cend()) {
				program = programs.erase(program);
				--program;
			}
		}
};

#endif