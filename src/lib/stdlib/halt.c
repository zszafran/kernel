#include <stdlib.h>

void halt(void)
{
  asm volatile("cli\n" ::);
  asm volatile("hlt\n" ::);
}