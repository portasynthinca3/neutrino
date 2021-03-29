#pragma once

#include "../stdlib.h"

#define GPIO_OUT_W1TS_REG(bank)    REG(bank ? 0x3FF44014 : 0x3FF44008)
#define GPIO_OUT_W1TC_REG(bank)    REG(bank ? 0x3FF44018 : 0x3FF4400C)
#define GPIO_ENABLE_W1TS_REG(bank) REG(bank ? 0x3FF44030 : 0x3FF44024)
#define GPIO_ENABLE_W1TC_REG(bank) REG(bank ? 0x3FF44034 : 0x3FF44028)

#define IO_MUX_GPIO5_REG REG(0x3FF4906C)

void gpio_simple_out(uint8_t pad, uint32_t drive);
void gpio_set_out   (uint8_t pad, uint8_t val);