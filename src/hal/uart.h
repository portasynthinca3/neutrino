#pragma once

#include "../stdlib.h"

#define UARTn_BASE(n)               ((n > 0) ? ((n == 2) ? 0x3FF6E000 : 0x3FF50000) : 0x3FF40000)
#define UARTn_CONF0_REG(n)          REG(UARTn_BASE(n) + 0x20)
#define UARTn_CONF1_REG(n)          REG(UARTn_BASE(n) + 0x24)
#define UARTn_CLKDIV_REG(n)         REG(UARTn_BASE(n) + 0x14)
#define UARTn_FLOW_CONF_REG(n)      REG(UARTn_BASE(n) + 0x34)
#define UARTn_SWFC_CONF_REG(n)      REG(UARTn_BASE(n) + 0x3C)
#define UARTn_SLEEP_CONF_REG(n)     REG(UARTn_BASE(n) + 0x38)
#define UARTn_IDLE_CONF_REG(n)      REG(UARTn_BASE(n) + 0x40)
#define UARTn_RS485_CONF_REG(n)     REG(UARTn_BASE(n) + 0x44)
#define UARTn_STATUS_REG(n)         REG(UARTn_BASE(n) + 0x1C)
#define UARTn_AUTOBAUD_REG(n)       REG(UARTn_BASE(n) + 0x18)
#define UARTn_LOWPULSE_REG(n)       REG(UARTn_BASE(n) + 0x28)
#define UARTn_HIGHPULSE_REG(n)      REG(UARTn_BASE(n) + 0x2C)
#define UARTn_POSPULSE_REG(n)       REG(UARTn_BASE(n) + 0x68)
#define UARTn_NEGPULSE_REG(n)       REG(UARTn_BASE(n) + 0x6C)
#define UARTn_RXD_CNT_REG(n)        REG(UARTn_BASE(n) + 0x30)
#define UARTn_AT_CMD_PRECNT_REG(n)  REG(UARTn_BASE(n) + 0x48)
#define UARTn_AT_CMD_POSTCNT_REG(n) REG(UARTn_BASE(n) + 0x4C)
#define UARTn_AT_CMD_GAPTOUT_REG(n) REG(UARTn_BASE(n) + 0x50)
#define UARTn_AT_CMD_CHAR_REG(n)    REG(UARTn_BASE(n) + 0x54)
#define UARTn_FIFO_REG(n)           REG(UARTn_BASE(n) + 0x00)
#define UARTn_MEM_CONF_REG(n)       REG(UARTn_BASE(n) + 0x58)
#define UARTn_MEM_CNT_STATUS_REG(n) REG(UARTn_BASE(n) + 0x64)
#define UARTn_INT_RAW_REG(n)        REG(UARTn_BASE(n) + 0x04)
#define UARTn_INT_ST_REG(n)         REG(UARTn_BASE(n) + 0x08)
#define UARTn_INT_ENA_REG(n)        REG(UARTn_BASE(n) + 0x0C)
#define UARTn_INT_CLR_REG(n)        REG(UARTn_BASE(n) + 0x10)

void uart_config    (uint8_t n, uint8_t stop_len, uint8_t bits);
void uart_clk       (uint8_t n, uint32_t bauds);
void uart_txfifo_rst(uint8_t n);

void uart_send_char(uint8_t n, char c);
void uart_send_str (uint8_t n, char* str);