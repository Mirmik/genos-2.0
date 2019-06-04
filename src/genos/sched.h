#ifndef GENOS_SCHED_SCHED_H
#define GENOS_SCHED_SCHED_H

#include <genos/schedee.h>

#define DISPLACE_REAL 0
#define DISPLACE_VIRTUAL 1
#define DISPLACE_ERROR -1

__BEGIN_DECLS

void schedee_run(genos::schedee * sch);
void schedee_wait(genos::schedee * sch);
void __schedee_wait_for(genos::schedee * parent, genos::schedee * child);
void schedee_stop(genos::schedee * sch);
//void schedee_final(genos::schedee * sch);

void schedee_exit();

void schedee_manager_init();
void scheduler_init();

void schedee_manager_step();

void __context_displace_vector__() __attribute__((noreturn));
void __schedule__();
int  __displace__();

genos::schedee * create_autom_schedee(void*(*task)(void*, int*), void* arg);
genos::schedee * create_cooperative_schedee(void*(*task)(void*), void* arg, int heapsize);
//genos::schedee * create_process(int(*task)(void*), void* arg, int heapsize);

int schedee_manager_total_planed();

void schedee_manager_debug_info(); 
	
__END_DECLS

#endif