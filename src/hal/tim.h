#pragma once

#include "../stdlib.h"

#define TIMGn_BASE(n)                 (n ? 0x3FF60000 : 0x3FF5F000)

#define TIMGn_TxCONFIG_REG(n, x)      REG(TIMGn_BASE(n) + (x * 0x24) + 0x00)
#define TIMGn_TxLO_REG(n, x)          REG(TIMGn_BASE(n) + (x * 0x24) + 0x04)
#define TIMGn_TxHI_REG(n, x)          REG(TIMGn_BASE(n) + (x * 0x24) + 0x08)
#define TIMGn_TxUPDATE_REG(n, x)      REG(TIMGn_BASE(n) + (x * 0x24) + 0x0C)
#define TIMGn_TxALARMLO_REG(n, x)     REG(TIMGn_BASE(n) + (x * 0x24) + 0x10)
#define TIMGn_TxALARMHI_REG(n, x)     REG(TIMGn_BASE(n) + (x * 0x24) + 0x14)
#define TIMGn_TxLOADLO_REG(n, x)      REG(TIMGn_BASE(n) + (x * 0x24) + 0x18)
#define TIMGn_TxLOADHI_REG(n, x)      REG(TIMGn_BASE(n) + (x * 0x24) + 0x1C)
#define TIMGn_TxLOAD_REG(n, x)        REG(TIMGn_BASE(n) + (x * 0x24) + 0x20)

#define TIMGn_Tx_WDTCONFIGz_REG(n, z) REG(TIMGn_BASE(n) + 0x48 + (z * 4))
#define TIMGn_Tx_WDTFEED_REG(n)       REG(TIMGn_BASE(n) + 0x60)
#define TIMGn_Tx_WDTPROTECT_REG(n)    REG(TIMGn_BASE(n) + 0x64)

void     tim_config     (uint8_t group, uint8_t tim, uint8_t en, uint8_t inc, uint8_t reload, uint16_t div);
uint64_t tim_read       (uint8_t group, uint8_t tim);
void     tim_write      (uint8_t group, uint8_t tim, uint64_t val);
void     tim_alarm_set  (uint8_t group, uint8_t tim, uint64_t val);
void     tim_alarm_en   (uint8_t group, uint8_t tim, uint8_t en);
void     tim_reload_set (uint8_t group, uint8_t tim, uint64_t val);