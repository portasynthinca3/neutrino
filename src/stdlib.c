#include "stdlib.h"

void write_reg(uint32_t addr, uint32_t val) {
    *(volatile unsigned int* const)addr = val;
}

uint32_t read_reg(uint32_t addr) {
    return *(volatile unsigned int* const)addr;
}