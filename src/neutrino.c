#include "neutrino.h"

#include "stdlib.h"
#include "hal/wdt.h"
#include "hal/uart.h"
#include "hal/gpio.h"
#include "hal/cpu.h"
#include "hal/tim.h"
#include "hal/sched.h"

void krnl_log(const char* component, const char* format, ...) {
    va_list valist;
    va_start(valist, _sprintf_argcnt((char*)format));
    char buf[512];
    _sprintf(buf, format, valist);

    printf("[LOG][%s]\t", component);
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

    krnl_log("K-MAIN", "neutrino v%s compiled on %s %s", VERSION, __DATE__, __TIME__);

    wdt_disable();
    sched_init(5000);

    krnl_log("K-MAIN", "boot done. Nice to meet you!");

    while(1);
}