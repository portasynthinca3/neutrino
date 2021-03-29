#include "gpio.h"
#include "../stdlib.h"

void gpio_simple_out(uint8_t pad, uint32_t drive) {
    uint8_t bank = pad >= 32;
    if(bank) pad -= 32;
    SET_AT(GPIO_ENABLE_W1TS_REG(bank), pad, 1, 1);
    IO_MUX_GPIO5_REG = (2 << 12) | (drive << 10) | (1 << 9); // ikr
}

void gpio_set_out(uint8_t pad, uint8_t val) {
    uint8_t bank = pad >= 32;
    if(bank) pad -= 32;
    if(val) GPIO_OUT_W1TS_REG(bank) = 1 << pad;
       else GPIO_OUT_W1TC_REG(bank) = 1 << pad;
}