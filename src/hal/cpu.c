#include "cpu.h"

void cpu_set_clk(uint8_t fq) {
    uint32_t oa = RTC_CNTL_CLK_CONF_REG;
    uint32_t ob = CPU_PER_CONF_REG;

    uint32_t a = SET_AT(RTC_CNTL_CLK_CONF_REG, 27, 3, 1);
    uint32_t b = SET_AT(CPU_PER_CONF_REG, 0, 3, fq);

    printf("%x %x %x %x\n", oa, ob, a, b);
}

void cpu_set_voltage(uint8_t v) {
    SET_AT(RTC_CNTL_VREG_REG, 11, 7, v);
}