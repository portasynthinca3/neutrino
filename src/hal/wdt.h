#pragma once

#include "../stdlib.h"

#define RTC_CNTL_WDTCONFIGx_REG(x)    REG(0x3FF4808C + (x * 4))
#define RTC_CNTL_WDTFEED_REG          REG(0x3FF480A0)
#define RTC_CNTL_WDTPROTECT_REG       REG(0x3FF480A4)

#define TIMGn_BASE(n)                 (n ? 0x3FF60000 : 0x3FF5F000)
#define TIMGn_Tx_WDTCONFIGz_REG(n, z) REG(TIMGn_BASE(n) + 0x48 + (z * 4))
#define TIMGn_Tx_WDTFEED_REG(n)       REG(TIMGn_BASE(n) + 0x60)
#define TIMGn_Tx_WDTPROTECT_REG(n)    REG(TIMGn_BASE(n) + 0x64)

void rtc_wdt_feed (void);
void timg_wdt_feed(uint8_t n);
void wdt_feed     (void);

void rtc_wdt_disable (void);
void timg_wdt_disable(uint8_t n);
void wdt_disable     (void);