#include "wdt.h"
#include "../stdlib.h"

void rtc_wdt_feed(void) {
    write_reg(RTC_CNTL_WDTFEED_REG, 1 << 31);
}

void timg_wdt_feed(uint8_t n) {
    write_reg(TIMGn_Tx_WDTFEED_REG(n), 0xDEADBEEF);
}

void wdt_feed() {
    rtc_wdt_feed();
    timg_wdt_feed(0);
    timg_wdt_feed(1);
}