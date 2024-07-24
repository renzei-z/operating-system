#include <stdio.h>

#if defined(__is_libk)
#include <kernel/tty.h>
#endif

int putchar(int ic) {
#if defined(__is_libk)
  char c = (char) ic;
  tty_putcn(&c, sizeof(c));
#else
  // TODO: Implement stdio and write syscall.
#endif
  return ic;
}
