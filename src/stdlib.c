#include "stdlib.h"
#include "hal/uart.h"

/*
 * Returns the number of arguments sprintf will require on a string fmt
 */
int _sprintf_argcnt(char* fmt) {
    uint64_t argcnt = 0;
    for(uint64_t i = 0; i < strlen(fmt); i++)
        if(fmt[i] == '%' && (i > 0 && fmt[i - 1] != '%'))
            argcnt++;
    return argcnt;
}

/*
 * Get the length of a zero-terminated string
 */
size_t strlen(const char* str) {
    size_t i = 0;
    while(str[i++] != 0);
    return i - 1;
}

/*
 * Print an uint32_t to the string
 */
char* sprintu(char* str, uint32_t i, uint8_t min) {
    // create some variables
    uint8_t pos = 0;
    uint32_t div = 1000000000; // start with the leftmost digit
    uint8_t started = 0;
    for(int j = 1; j <= 10; j++) {
        // fetch the next digit
        uint8_t digit = (i / div) % 10;
        // if the conversion hasn't started already and the current digit
        //   is greater than zero OR we exceeded the maximum amount of dropped
        //   digits, assume that the conversion has started
        if((!started && digit > 0) || (10 - j < min))
            started = 1;
        // if the conversion has started, write a digit to the string
        if(started)
            str[pos++] = digit + '0';
        // move to the next digit
        div /= 10;
    }
    // mark the end of the string
    str[pos] = 0;
    // return the string
    return str;
}

const char hex_const[16] = "0123456789ABCDEF";

/*
 * Print an uint32_t with base 16 to the string
 */
char* sprintub16(char* str, uint32_t i, uint8_t min) {
    // create some variables
    uint8_t pos = 0;
    uint32_t div = 1U << 28; // start with the leftmost digit
    uint8_t started = 0;
    for(uint8_t j = 1; j <= 8; j++) {
        // fetch the next digit
        uint8_t digit = (i / div) % 16;
        // if the conversion hasn't started already and the current digit
        //   is greater than zero OR we exceeded the maximum amount of dropped
        //   digits, assume that the conversion has started
        if((!started && digit > 0) || (8 - j < min))
            started = 1;
        // if the conversion has started, write a digit to the string
        if(started)
            str[pos++] = hex_const[digit];
        // move to the next digit
        div >>= 4;
    }
    // mark the end of the string
    str[pos] = 0;
    // return the string
    return str;
}

/*
 * Append the string at src to the end of the string at dest
 */
char* strcat(char* dest, char* src) {
    // get the lengths of the strings
    size_t dest_len = strlen(dest);
    size_t src_len = strlen(src);
    // copy the source string
    memcpy((void*)(dest + dest_len), (const void*)src, src_len);
    // mark the end
    dest[dest_len + src_len] = 0;
    // return the destination
    return dest;
}

/*
 * Print formatted string
 */
int _sprintf(char* str, const char* format, va_list valist) {
    // parse the format
    uint64_t str_idx = 0;
    for(uint64_t i = 0; i < strlen(format); i++) {
        // if it's a percentage sign, print something special
        if(format[i] == '%') {
            char fmt = format[++i];
            switch(fmt) {
                case 's': { // string
                    char* str2 = va_arg(valist, char*);
                    for(uint64_t j = 0; j < strlen(str2); j++)
                        str[str_idx++] = str2[j];
                    break;
                }
                case 'c': // character
                    str[str_idx++] = va_arg(valist, int);
                    break;
                case '%': // percentage sign
                    str[str_idx++] = '%';
                    break;
                case 'n': // nothing
                    break;
                case 'd': // integer
                case 'u':
                case 'i': {
                    char buf[16];
                    sprintu(buf, va_arg(valist, uint32_t), 1);
                    for(uint32_t j = 0; j < strlen(buf); j++)
                        str[str_idx++] = buf[j];
                    break;
                }
                case 'p': // hex integer
                case 'x':
                case 'X': {
                    char buf[9];
                    sprintub16(buf, va_arg(valist, uint32_t), 1);
                    for(uint32_t j = 0; j < strlen(buf); j++)
                        str[str_idx++] = buf[j];
                    break;
                }
                default: // unknown
                    return -1;
            }
        } else { // a normal character
            str[str_idx++] = format[i];
        }
    }
    // add terminator
    str[str_idx] = 0;
    // return the amount of characters printed
    return str_idx;
}

/*
 * Print formatted string (wrapper)
 */
int sprintf(char* str, const char* format, ...) {
    va_list valist;
    va_start(valist, _sprintf_argcnt((char*)format));
    int result = _sprintf(str, format, valist);
    va_end(valist);
    return result;
}

/*
 * Print string to UART
 */
int puts(const char* str) {
    uart_send_str(0, (char*)str);
    uart_send_char(0, '\n');
    return 0;
}

/*
 * Print formatted string to UART
 */
int printf(const char* format, ...) {
    va_list valist;
    va_start(valist, _sprintf_argcnt((char*)format));
    char buf[512];
    int result = _sprintf(buf, format, valist);
    uart_send_str(0, buf);
    va_end(valist);
    return result;
}

/*
 * Copy a block of memory
 */
void* memcpy(void* destination, const void* source, size_t num) {
    for(int i = 0; i < num; i++)
        ((uint8_t*)destination)[i] = ((uint8_t*)source)[i];
    return destination;
}

/*
 * Compare two memory blocks
 */
int memcmp(const void* lhs, const void* rhs, size_t cnt) {
    // go through each byte
    for(int i = 0; i < cnt; i++) {
        // return if the blocks aren't equal
        if(((const uint8_t*)lhs)[i] > ((const uint8_t*)rhs)[i])
            return 1;
        else if(((const uint8_t*)lhs)[i] < ((const uint8_t*)rhs)[i])
            return -1;
    }
    // if we didn't return, the blocks are equal
    return 0;
}

/*
 * Compare two zero-terminated strings
 */
int strcmp(const char* str1, const char* str2) {
    // calculate the length of both strings
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    // strings are not equal if they have different lengths (duh)
    if(len1 != len2)
        return (str1[0] > str2[0]) ? 1 : -1;
    // go through each byte
    for(int i = 0; i < len1; i++) {
        // return if the strings aren't equal
        if(str1[i] > str2[i])
            return 1;
        else if(str1[i] < str2[i])
            return -1;
    }
    // if we haven't returned, the strings are equal
    return 0;
}

/*
 * Parse number from string representation
 */
int atoi(const char* str) {
    int n = 0;
    char c;
    // fetch next character
    while((c = *(str++)) != 0) {
        // if it's a digit, append it
        if(c >= '0' && c <= '9') {
            n *= 10;
            n += c - '0';
        } else {
            // error
            return 0;
        }
    }
    return n;
}