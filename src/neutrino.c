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
    krnl_log("neutrino v%s compiled on %s %s", VERSION, __DATE__, __TIME__);

    krnl_log("disabling wdt");
    wdt_disable();

    krnl_log("boot done. Nice to meet you!");

    while(1);
}