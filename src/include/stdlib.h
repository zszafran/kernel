#pragma once

#include <sys/cdefs.h>
#include <string.h>

#define PANIC(message) panic("%s\n\tFile: %s\n\tLine: %d", message, __FILE__, __LINE__);

#ifdef __cplusplus
extern "C" {
#endif

void halt(void);
__attribute__((__noreturn__)) void abort(void);
__attribute__((__noreturn__)) void panic(const char *__restrict format, ...);
__attribute__((__noreturn__)) void epanic();
char *itoa(int value, char *string, int radix);

#ifdef __cplusplus
}
#endif
