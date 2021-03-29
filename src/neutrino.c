#include "stdlib.h"
#include "hal/wdt.h"
#include "hal/uart.h"
#include "hal/gpio.h"

void neutrino_main(void) {
    //gpio_simple_out(5, 2);
    //gpio_set_out(5, 1);
    //while(1) wdt_feed();
    wdt_disable();
    //uart_config(0, 1, 8);
    uart_clk(0, 115200);
    //uart_txfifo_rst(0);
    uart_send_str(0, "Hello, World!");
    while(1);
}