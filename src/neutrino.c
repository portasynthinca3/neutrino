#include "stdlib.h"
#include "hal/wdt.h"
#include "hal/uart.h"
#include "hal/gpio.h"

void neutrino_main(void) {
    wdt_disable();
    uart_clk(0, 115200);

    printf("Hello, ESP%d World!\n", 32);

    while(1);
}