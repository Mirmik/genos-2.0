#include <fs/node.h>
#include <stdlib.h>
#include <string.h>
//#include <embox/unit.h>
/*
#include <mem/misc/pool.h>
#include <limits.h>
#include <errno.h>
#include <assert.h>

//#define MAX_NODE_QUANTITY OPTION_GET(NUMBER,fnode_quantity)
#ifndef MAX_NODE_QUANTITY
#	define MAX_NODE_QUANTITY 10
#endif

struct node_tuple {
	struct node node;
	struct nas nas;
	struct node_fi fi;
};

POOL_DEF(node_pool, struct node_tuple, MAX_NODE_QUANTITY);

//EMBOX_UNIT_INIT(node_init);

static int node_init(void) {
	return 0;
}

/*static inline int flock_init(node_t *node) {
	/* flock initialization */
/*	mutex_init(&node->flock.exlock);
	node->flock.shlock_count = 0;
	dlist_init(&node->flock.shlock_holders);
	spin_init(&node->flock.flock_guard, __SPIN_UNLOCKED);

	return ENOERR;
}*/

struct node *node_alloc(const char *name, unsigned int name_len) {
	struct node * node = (struct node *) malloc(sizeof(struct node));
	strncpy(node->name, name, name_len);

	tree_link_init(&node->tree_link);

	node->mounted = 0;

/*	struct node_tuple *nt;
	struct node *node;
	struct nas *nas;

	assert(name_len <= GENOS_NAME_MAX);

	if (!name_len) {
		name_len = strlen(name);
	}

	if (!*name || name_len > NAME_MAX) {
		//TODO behave more clever here? -- Eldar
		return NULL;
	}

	nt = pool_alloc(&node_pool);
	if (!nt) {
		return NULL;
	}

	memset(nt, 0, sizeof(struct node_tuple));

	node = &nt->node;
	nas = &nt->nas;

	node->nas = nas;
	nas->node = node;

	nas->fi = &nt->fi;

	tree_link_init(&node->tree_link);

	strncpy((char *) node->name, name, name_len);
	node->name[name_len] = '\0';

	node->mounted = 0;

	//flock_init(node);
*/
	return node;
}

/*void node_free(node_t *node) {
	pool_free(&node_pool, member_cast_out(node, struct node_tuple, node));
}
*/