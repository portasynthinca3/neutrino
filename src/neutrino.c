#include "neutrino.h"

#include "stdlib.h"
#include "hal/wdt.h"
#include "hal/uart.h"
#include "hal/gpio.h"
#include "hal/cpu.h"

void krnl_log(const char* format, ...) {
    va_list valist;
    va_start(valist, _sprintf_argcnt((char*)format));
    char buf[512];
    int result = _sprintf(buf, format, valist);

    printf("[LOG] ");
    uart_send_str(0, buf);
    puts("");

    va_end(valist);
}

void neutrino_main(void) {
    uart_txfifo_flush(0);
    cpu_set_clk(CPU_CLK_240);
    cpu_set_voltage(CPU_VOLT_900); // seems to be working at 0.9V just fine...
    uart_clk(0, 115200);
    printf("\n\n");

    krnl_log("neutrino v%s compiled on %s %s", VERSION, __DATE__, __TIME__);

    krnl_log("disabling wdt");
    wdt_disable();

    krnl_log("boot done. Nice to meet you!");

    gpio_simple_out(5, 1);
    gpio_set_out(5, 0);

    while(1);
}