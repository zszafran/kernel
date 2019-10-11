#include <stdint.h>
#include <stdlib.h>
#include <ssp.h>

__attribute__((noreturn)) void __stack_chk_fail(void)
{
#if __STDC_HOSTED__
  abort();
#elif __is_libk
  panic("stack smashing detected");
#endif
}