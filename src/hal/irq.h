#ifndef HAL_IPL_H_
#define HAL_IPL_H_

#include <sys/cdefs.h>

typedef void(*irq_handler_t)(void*);

__BEGIN_DECLS

void irq_enable(int irqno);
void irq_disable(int irqno);

//Defined in arch/irq.h
//void irqs_enable(void);
//irqstate_t irqs_save(void);
//void irqs_restore(irqstate_t state);
//void irqs_disable(void);

__END_DECLS

#include <arch/irq.h>

#endif /* HAL_IPL_H_ */