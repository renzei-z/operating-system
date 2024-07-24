#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/timer.h>

void kernel_main(void) {
  tty_init();
  gdt_init();
  printf("Initialised GDT.\n");
  idt_init();
  printf("Initialised IDT.\n");
  timer_init();
}
