#include "wdt.h"
#include "../stdlib.h"

void rtc_wdt_feed(void) {
    write_reg(RTC_CNTL_WDTFEED_REG, 1 << 31);
}

void timg_wdt_feed(uint8_t n) {
    write_reg(TIMGn_Tx_WDTFEED_REG(n), 0xDEADBEEF);
}

void wdt_feed(void) {
    rtc_wdt_feed();
    timg_wdt_feed(0);
    timg_wdt_feed(1);
}



void rtc_wdt_disable(void) {
    for(int i = 1; i <= 4; i++)
        write_reg(RTC_CNTL_WDTCONFIGx_REG(i), 0xFFFFFFFF);
}

void timg_wdt_disable(uint8_t n) {
    write_reg(TIMGn_Tx_WDTCONFIGz_REG(n, 1), 0xFFFF << 16);
    for(int i = 2; i <= 5; i++)
        write_reg(TIMGn_Tx_WDTCONFIGz_REG(n, i), 0xFFFFFFFF);
}

void wdt_disable(void) {
    rtc_wdt_disable();
    timg_wdt_disable(0);
    timg_wdt_disable(0);
}