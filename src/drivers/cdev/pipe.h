#ifndef GENOS_DRIVERS_PIPE_H
#define GENOS_DRIVERS_PIPE_H

#include <drivers/cdev/cdev.h>
#include <igris/datastruct/ring.h>

struct pipe
{
	struct char_device 	cdev;
	struct ring_head 	ring;
	char* 				buf;
};

__BEGIN_DECLS

int pipe_write(struct char_device * cdev,
               const char* data,
               unsigned int size,
               int flags);

int pipe_read(struct char_device * cdev,
               char* data,
               unsigned int size,
               int flags);

int pipe_waitread(struct char_device * cdev);

const struct char_device_operations pipe_ops = 
{
	.write = pipe_write,
	.read = pipe_read,
	.waitread = pipe_waitread
}

static inline
void pipe_init(struct pipe * p, char * buf, int len)
{
	char_device_init(p->cdev, pipe_operations);
	ring_init(&p->ring, len);
}

__END_DECLS

#endif