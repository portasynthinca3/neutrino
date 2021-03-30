#pragma once

#include "../stdlib.h"
#include "tim.h"

#define RTC_CNTL_WDTCONFIGx_REG(x)    REG(0x3FF4808C + (x * 4))
#define RTC_CNTL_WDTFEED_REG          REG(0x3FF480A0)
#define RTC_CNTL_WDTPROTECT_REG       REG(0x3FF480A4)

void rtc_wdt_feed (void);
void timg_wdt_feed(uint8_t n);
void wdt_feed     (void);

void rtc_wdt_disable (void);
void timg_wdt_disable(uint8_t n);
void wdt_disable     (void);