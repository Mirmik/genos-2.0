#ifndef GENOS_SCHEDEE_H
#define GENOS_SCHEDEE_H

#include <genos/ctrobj.h>
#include <genos/wait.h>
#include <genos/ktimer.h>

#include <genos/resource.h>
//#include <genos/nav.h>

#define RESTBL_SIZE 4

#ifdef MVFS_INCLUDED
struct file;
#endif

#define SCHEDEE_STATE_RUN 			0
#define SCHEDEE_STATE_WAIT 			2
#define SCHEDEE_STATE_WAIT_SCHEDEE 	6
#define SCHEDEE_STATE_STOP 			3
#define SCHEDEE_STATE_FINAL 		4
#define SCHEDEE_STATE_ZOMBIE 		5

#define SCHEDEE_FDMAX 5

extern struct dlist_head schedee_list;

namespace genos
{
	struct schedee
	{
		genos::schedee * parent;

		union
		{
			struct ctrobj ctr;
			struct waiter waiter;
			struct ktimer_base ktimer;
		};

		uint8_t prio;
		uint8_t state;

#if SCHEDEE_DEBUG_STRUCT
		struct dlist_head schedee_list_lnk;
		uint16_t dispcounter;
		uint16_t execcounter;
#endif

		union
		{
			uint8_t flags;
			struct
			{
				uint8_t runned 			: 1;
				uint8_t can_displace 	: 1;
				uint8_t has_context 	: 1;
				uint8_t dynamic 		: 1;
				uint8_t dynamic_heap 	: 1;
				uint8_t killed			: 1;
			} flag;
		};

		int16_t local_errno;

		//genos::restbl restbl;
		genos::resource * resources [RESTBL_SIZE];
		//genos::navblock * navblock = nullptr;

#ifdef MVFS_INCLUDED
		struct node * pwd;
		struct file * fds [SCHEDEE_FDMAX]; //массив файловых дескрипторов
#endif

		schedee() {}

		virtual void execute() = 0;
		virtual int displace() = 0;
		virtual void finalize() = 0;
		virtual void signal_handler(int sig) {}

		//void set_restbl(genos::openres* tbl, uint8_t tblsize)
		//{ restbl.set_table(tbl, tblsize); }

		genos::resource * getres(int i) 
		{
			if (i >= RESTBL_SIZE) 
				return nullptr;
			
			return resources[i];
		}

		void run();
	};
}

/*genos::schedee_operations
{
	void (*execute) (genos::schedee * sch);
	int (*displace) (genos::schedee * sch);
	void (*finalize) (genos::schedee * sch);
};*/

__BEGIN_DECLS

genos::schedee * current_schedee();

/// Уведомить родителя (если он есть), что процесс завершен.
void schedee_notify_finalize(genos::schedee * sch);

/// Проинициализировать структуры данных поддержки файловой системы.
void schedee_mvfs_support_init(genos::schedee* sch);

/// Переоткрыть родительские файлы от своего имени.
void schedee_copy_parent_files(genos::schedee* sch);

void schedee_debug_print_fds(genos::schedee* sch);

/// Проинициализировать основные поля процесса.
static inline
void schedee_init(genos::schedee* sch, int prio)
{

#if SCHEDEE_DEBUG_STRUCT

	// В дальнейшем эту провеку следует убрать, так как нод
	// должен отстыковываться от списка по завершению работы.
	if (!dlist_in(&sch->schedee_list_lnk, &schedee_list))
	{
		ctrobj_init(&sch->ctr, CTROBJ_SCHEDEE_LIST);
		dlist_add(&sch->schedee_list_lnk, &schedee_list);
	}

	else
	{
		dlist_del_init(&sch->ctr.lnk);
	}

	sch->dispcounter = 0;
	sch->execcounter = 0;
#else
	ctrobj_init(&sch->ctr, CTROBJ_SCHEDEE_LIST);
#endif

	sch->prio = prio;
	sch->state = SCHEDEE_STATE_STOP;
	sch->flags = 0;

	sch->parent = current_schedee();

#ifdef MVFS_INCLUDED
	schedee_mvfs_support_init(sch);

	if (sch->parent)
		schedee_copy_parent_files(sch);

#endif //MVFS_INCLUDED

	sch->local_errno = 0;
}

#ifdef MVFS_INCLUDED
int schedee_setfd(genos::schedee * sch, struct file * node, int fd);
int schedee_get_free_fd(genos::schedee * sch);
#endif //MVFS_INCLUDED

#if SCHEDEE_DEBUG_STRUCT
void schedee_list_debug_info();
#endif


__END_DECLS

#endif