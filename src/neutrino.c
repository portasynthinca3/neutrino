#include "stdlib.h"
#include "hal/wdt.h"

void print(const char* str) {
    char c;
    while((c = *str++)) {

    }
}

void neutrino_main(void) {
    print("Hello, world!")
    while(1) {
        wdt_feed();
    }
}