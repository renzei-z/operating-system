#ifndef _KERNEL_TTY_H_
#define _KERNEL_TTY_H_

#include <stddef.h>

void tty_init(void);
void tty_putc(char c);
void tty_putcn(const char *cs, size_t n);
void tty_puts(const char *s);

#endif
