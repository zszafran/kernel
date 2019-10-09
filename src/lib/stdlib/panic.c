#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__is_libk) // Disable panic() function if it is not part of kernel
void panic(string_t reason)
{
    printf("\nKernel panic: %s\n", reason);
    halt();
    while (1)
    {
    }
    __builtin_unreachable();
}
#endif