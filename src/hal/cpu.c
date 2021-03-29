#include "cpu.h"

void cpu_set_clk(uint8_t fq) {
    SET_AT(RTC_CNTL_CLK_CONF_REG, 27, 3, 1);
    SET_AT(CPU_PER_CONF_REG, 0, 8, fq);
}

void cpu_set_voltage(uint8_t v) {
    SET_AT(RTC_CNTL_VREG_REG, 11, 7, v);
}