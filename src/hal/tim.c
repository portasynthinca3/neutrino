#include "tim.h"
#include "../stdlib.h"

void tim_config(uint8_t group, uint8_t tim, uint8_t en, uint8_t inc, uint8_t reload, uint16_t div) {
    TIMGn_TxCONFIG_REG(group, tim) =
        ((uint32_t)en << 31)     | ((uint32_t)inc << 30)
      | ((uint32_t)reload << 29) | ((uint32_t)div << 13);
}

uint64_t tim_read(uint8_t group, uint8_t tim) {
    TIMGn_TxUPDATE_REG(group, tim) = 1;
    return ((uint64_t)TIMGn_TxHI_REG(group, tim) << 32)
          | (uint64_t)TIMGn_TxLO_REG(group, tim);
}

void tim_write(uint8_t group, uint8_t tim, uint64_t val) {
    tim_reload_set(group, tim, val);
    TIMGn_TxLOAD_REG(group, tim) = 1;
}

void tim_alarm_set(uint8_t group, uint8_t tim, uint64_t val) {
    TIMGn_TxALARMHI_REG(group, tim) = val >> 32;
    TIMGn_TxALARMLO_REG(group, tim) = val & 0xFFFFFFFF;
}

void tim_alarm_en(uint8_t group, uint8_t tim, uint8_t en) {
    SET_AT(TIMGn_TxCONFIG_REG(group, tim), 10, 1, en);
}

void tim_reload_set(uint8_t group, uint8_t tim, uint64_t val) {
    TIMGn_TxLOADHI_REG(group, tim) = val >> 32;
    TIMGn_TxLOADLO_REG(group, tim) = val & 0xFFFFFFFF;
}