#ifndef _KERNEL_GDT_H_
#define _KERNEL_GDT_H_

#include <stdint.h>

struct gdt_entry_t {
  uint16_t limit;
  uint16_t base_low;
  uint8_t base_mid;
  uint8_t access;
  uint8_t flags;
  uint8_t base_high;
} __attribute__((packed));

struct gdt_ptr_t {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

struct tss_entry_t {
  uint32_t prev_tss;
  uint32_t esp0, ss0, esp1, ss1, esp2, ss2;
  uint32_t cr3, eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
  uint32_t es, cs, ss, ds, fs, gs;
  uint32_t ldt, trap, iomap_base;
} __attribute__((packed));

void gdt_init(void);
void gdt_set_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void write_tss(uint32_t num, uint32_t ss0, uint32_t esp0);

#endif
