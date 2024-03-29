#pragma once

#include <sys/cdefs.h>
#include <stddef.h>

typedef char *string_t;

#ifdef __cplusplus
extern "C" {
#endif

int memcmp(const void*, const void*, size_t);
void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, int, size_t);
char *strcat(char *dest, const char *src);
char *strcpy(char *dest, const char *src);
size_t strlen(const char*);

#ifdef __cplusplus
}
#endif