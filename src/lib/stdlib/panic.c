#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__is_libk) // Disable panic() function if it is not part of kernel
void panic(const char *__restrict format, ...)
{
    printf("\033[91mPANIC\033[0m ");
    va_list parameters;
    va_start(parameters, format);
    vprintf(format, parameters);
    va_end(parameters);
    printf("\n");

    halt();
    while (1)
    {
    }
    __builtin_unreachable();
}
#endif