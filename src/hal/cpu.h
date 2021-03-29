#pragma once

#include "../stdlib.h"

// mhz
#define CPU_CLK_80  0
#define CPU_CLK_160 1
#define CPU_CLK_240 2

// millivolts
#define CPU_VOLT_900  0
#define CPU_VOLT_950  1
#define CPU_VOLT_1000 2
#define CPU_VOLT_1050 3
#define CPU_VOLT_1100 4
#define CPU_VOLT_1150 5
#define CPU_VOLT_1200 6
#define CPU_VOLT_1250 7

#define RTC_CNTL_CLK_CONF_REG REG(0x3FF48070)
#define CPU_PER_CONF_REG      REG(0x3FF0003C)
#define RTC_CNTL_VREG_REG     REG(0x3FF4807C)

void cpu_set_clk     (uint8_t fq);
void cpu_set_voltage (uint8_t v);