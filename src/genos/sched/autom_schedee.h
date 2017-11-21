#ifndef GENOS_AUTOM_SCHEDEE_H
#define GENOS_AUTOM_SCHEDEE_H

#include <genos/sched/schedee.h>

namespace genos {
	class autom_schedee : public schedee {
		gxx::delegate<void> dlg;

	public:
		autom_schedee(gxx::delegate<void> act) : dlg(act) {}

		void execute() override {
			dlg();
		}
		void finalize() override {}
		void displace() override {}
	};
}

#endif