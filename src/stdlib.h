#pragma once

#include <stdarg.h>

typedef unsigned char  uint8_t;
typedef signed   char  int8_t;
typedef unsigned short uint16_t;
typedef signed   short int16_t;
typedef unsigned int   uint32_t;
typedef signed   int   int32_t;
typedef unsigned long  uint64_t;
typedef signed   long  int64_t;

typedef uint32_t size_t;

// ESP32 register operations
void     write_reg(uint32_t addr, uint32_t val);
uint32_t read_reg (uint32_t addr);

// Memory operations
void* memset (void* dst, int ch, size_t size);
void* memcpy (void* destination, const void* source, size_t num);
char* strcpy (char* dest, char* src);

// String functions
size_t strlen          (const char* str);
char*  sprintu         (char* str, uint32_t i, uint8_t min);
char*  sprintub16      (char* str, uint32_t i, uint8_t min);
int    _sprintf_argcnt (char* fmt);
int    _sprintf        (char* str, const char* format, va_list valist);
int    puts            (const char* str);
int    sprintf         (char* str, const char* format, ...);
int    printf          (const char* format, ...);
char*  strcat          (char* dest, char* src);
int    strcmp          (const char* str1, const char* str2);
int    atoi            (const char* str);