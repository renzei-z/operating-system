#include <kernel/timer.h>
#include <kernel/idt.h>
#include <kernel/port_io.h>

#include <stdio.h>

uint64_t ticks;
const uint16_t freq = 100;

void timer_init() {
  ticks = 0;
  irq_install_handler(0, &on_irq0);

  // 1.1931816666 MHz
  uint16_t divisor = (uint16_t)(1193182/freq);

  // 00110110
  // - 16-bit binary
  // - square wave
  // - lobyte/hibyte access
  // - channel 0 -> irq 0
  outb(0x43, 0x36);
  outb(0x40, divisor & 0xFF);
  outb(0x40, (divisor >> 8) & 0xFF);
}

void on_irq0(struct interrupt_registers *regs) {
  ticks += 1;
  printf("Timer ticked!\n");
}
