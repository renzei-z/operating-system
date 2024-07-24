#ifndef _KERNEL_TIMER_H_
#define _KERNEL_TIMER_H_

#include "idt.h"

void timer_init();
void on_irq0(struct interrupt_registers *regs);

#endif
