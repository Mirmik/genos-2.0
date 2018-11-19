#include <sched/sched.h>
#include <arch/startup.h>
#include <gxx/syslock.h>

#define PRIORITY_TOTAL 4

static struct dlist_head runlist[PRIORITY_TOTAL];
DLIST_HEAD(waitlist);
DLIST_HEAD(finallist);
//struct dlist_head zombie_list;

struct schedee * __current_schedee = NULL;
struct schedee * current_schedee() {
	return __current_schedee;
}

void schedee_manager_init() {
	for (int i = 0; i < PRIORITY_TOTAL; ++i) 
		dlist_init(&runlist[i]);
}

void schedee_run(struct schedee * sch) {
	sch->state = SCHEDEE_STATE_RUN;
	system_lock();
	dlist_move(&sch->lnk, &runlist[sch->prio]);
	system_unlock();
}

void __schedee_wait_for(struct schedee * parent, struct schedee * child) {
	parent->state = SCHEDEE_STATE_WAIT_SCHEDEE;
	system_lock();
	dlist_move(&parent->lnk, &waitlist);
	system_unlock();
}

void schedee_wait(struct schedee * sch) {
	sch->state = SCHEDEE_STATE_WAIT;
	system_lock();
	dlist_move(&sch->lnk, &waitlist);
	system_unlock();
}

void schedee_final(struct schedee * sch) {
	sch->state = SCHEDEE_STATE_FINAL;
	system_lock();
	dlist_move(&sch->lnk, &finallist);
	system_unlock();
}

void schedee_stop(struct schedee * sch) {
	sch->state = SCHEDEE_STATE_STOP;
	system_lock();
	dlist_del_init(&sch->lnk);
	system_unlock();
}

void __schedee_execute(struct schedee * sch) {
	__current_schedee = sch;
	sch->flag.runned = 1;
	system_unlock();
	sch->sch_op->execute(sch);
}

void schedee_manager() 
{
	struct schedee* sch;

	while (!dlist_empty(&finallist)) 
	{
		sch = dlist_first_entry(&finallist, struct schedee, lnk);
				
		//данная функция инициализирует процедуру удаления
		//процесса из системы. Удаление может быть достаточно
		//длительным, но в любом случае это не проблемы планировщика.
		dlist_del(&sch->lnk);
		schedee_notify_finalize(sch);
		sch->sch_op->finalize(sch);
	}
		
	//atomic_section_enter();
	system_lock();

	for (int priolvl = 0; priolvl < PRIORITY_TOTAL; priolvl++) 
	{
		if (!dlist_empty(&runlist[priolvl])) 
		{					
			sch = dlist_first_entry(&runlist[priolvl], struct schedee, lnk);
			dlist_move_tail(&sch->lnk, &runlist[priolvl]);
			__schedee_execute(sch); //unlock here
			return;
		}
	}

	system_unlock();

	//Nobody to run
	return;
}

int __displace__() {
	struct schedee * sch = current_schedee();

	if (sch->flag.can_displace == 0) 
		return -1;

	sch->sch_op->displace(sch);
	return 0;
}

int __kill_stack_and_schedule_invoke__() {
	RESET_STACK();
	while(1) __schedule__();
}