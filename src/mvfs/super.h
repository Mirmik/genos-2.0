#ifndef MVFS_SUPER_H
#define MVFS_SUPER_H

/**
 *	Описатели суперблока и индксного дескриптора.
 *
 *	В vfs данные объекты работают в тесной связи. Поэтому айноды включены в этот файл.
 */

//#include <igris/util/member.h>

#include <stdlib.h>
#include <stdint.h>

#include <mvfs/node.h>

struct file;

///	Суперблок смонтированной файловой системы.
struct super_block
{
	const struct file_system_type * fs;
	struct node * root; ///корневой dentry ветви.

	//void *			private;
	uint16_t 		refs;

	/*void common_init(const struct file_system_type * _fs, struct node * _root)
	{
		fs = _fs;
		root = _root;
		root->flag.directory = 1;
		root->sb = this;
	}*/
};

__BEGIN_DECLS

void super_block_init(struct super_block * sb,
                      const struct file_system_type * _fs,
                      struct node * _root);

__END_DECLS

#define SUPER_BLOCK_INIT(name, fs, root) { fs, root, 0 }

#endif