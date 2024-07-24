#include <kernel/gdt.h>

#include <string.h>

extern void gdt_flush(uint32_t);
extern void tss_flush();

#define GDT_ENTRY_COUNT 6

struct gdt_entry_t gdt_entries[GDT_ENTRY_COUNT];
struct gdt_ptr_t gdt_ptr;
struct tss_entry_t tss_entry;

void gdt_init(void) {
  gdt_ptr.limit = (sizeof(struct gdt_entry_t) * GDT_ENTRY_COUNT) - 1;
  gdt_ptr.base = (uint32_t) &gdt_entries;

  gdt_set_gate(0, 0, 0, 0, 0); // Null segment
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel Code segment
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel Data segment
  gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User Code segment
  gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User Data segment
  write_tss(5, 0x10, 0x00);
  
  // 0x9_ -> 1001 -> Ring 0
  // 0xF_ -> 1111 -> Ring 3
  
  gdt_flush((uint32_t) &gdt_ptr);
  tss_flush();
}

void gdt_set_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
  gdt_entries[num].base_low = (base & 0xFFFF);
  gdt_entries[num].base_mid = (base >> 16) & 0xFF;
  gdt_entries[num].base_high = (base >> 24) & 0xFF;

  gdt_entries[num].limit = (limit & 0xFFFF);
  gdt_entries[num].flags = (limit >> 16) & 0x0F;
  gdt_entries[num].flags |= (gran & 0xF0);

  gdt_entries[num].access = access;
}

void write_tss(uint32_t num, uint32_t ss0, uint32_t esp0) {
  uint32_t base = (uint32_t) &tss_entry;
  uint32_t limit = base + sizeof(tss_entry);

  gdt_set_gate(num, base, limit, 0xE9, 0x00);

  memset(&tss_entry, 0, sizeof(tss_entry));

  tss_entry.ss0 = ss0;
  tss_entry.esp0 = esp0;
  // | 0x3 allows switching from ring 3 -> ring 0
  tss_entry.cs = 0x08 | 0x3;
  tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x10 | 0x3;
}
