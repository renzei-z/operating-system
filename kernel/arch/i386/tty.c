#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t term_row;
static size_t term_col;
static uint8_t term_color;
static uint16_t *term_buf;

void tty_init(void) {
  term_row = 0;
  term_col = 0;
  term_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  term_buf = VGA_MEMORY;
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      term_buf[y * VGA_WIDTH + x] = vga_entry(' ', term_color);
    }
  }
}

void tty_set_color(uint8_t color) {
  term_color = color;
}

void tty_putentry(unsigned char c, uint8_t color, size_t x, size_t y) {
  term_buf[y * VGA_WIDTH + x] = vga_entry(c, color);
}

void tty_putc(char c) {
  if (c == '\n') {
    term_row++;
    term_col = 0;
    return;
  }

  tty_putentry(c, term_color, term_col, term_row);
  term_col++;
}

void tty_putcn(const char *cs, size_t n) {
  for (size_t i = 0; i < n; i++) 
    tty_putc(cs[i]);
}

void tty_puts(const char *s) {
  for (size_t i = 0; s[i] != '\0'; i++)
    tty_putc(s[i]);
}
