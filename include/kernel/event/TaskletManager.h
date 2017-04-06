#ifndef GENOS_TASKLET_MANAGER_H
#define GENOS_TASKLET_MANAGER_H

#include <kernel/event/Tasklet.h>
#include <kernel/csection.h>

namespace Genos {

	class TaskletManager {
		gxx::dlist<Tasklet, &Tasklet::lnk> queue;

	public:
		TaskletManager() {}

		void addToExecute(Tasklet& slot) {
			critical_section_enter();
			queue.move_back(slot);
			critical_section_leave();
		};

		void execute() {
			while(!queue.empty()) {
				critical_section_enter();
				Tasklet& object = *queue.begin();
				queue.del_init(object);
				critical_section_leave();
				object.routine();
			}
		}
	};
}

#endif