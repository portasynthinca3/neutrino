#include "neutrino.h"

#include "stdlib.h"
#include "hal/wdt.h"
#include "hal/uart.h"
#include "hal/gpio.h"
#include "hal/cpu.h"
#include "hal/tim.h"

void krnl_log(const char* format, ...) {
    va_list valist;
    va_start(valist, _sprintf_argcnt((char*)format));
    char buf[512];
    _sprintf(buf, format, valist);

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

    krnl_log("configuring timers");

    krnl_log("boot done. Nice to meet you!");

    tim_reload_set(0, 0, 1000);
    tim_write(0, 0, 1000);
    tim_alarm_set(0, 0, 0);
    tim_alarm_en(0, 0, 1);
    tim_config(0, 0, 1, 0, 1, 6750);
    while(1) {
        uint32_t val = tim_read(0, 0);
        krnl_log("%d", val);
    }

    while(1);
}