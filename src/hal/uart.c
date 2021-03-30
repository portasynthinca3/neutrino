#include "uart.h"
#include "../stdlib.h"
#include "wdt.h"

void uart_config(uint8_t n, uint8_t stop_len, uint8_t bits) {
    SET_AT(UARTn_CONF0_REG(n), 4, 2, stop_len);
    SET_AT(UARTn_CONF0_REG(n), 2, 2, bits);
}

void uart_txfifo_rst(uint8_t n) {
    SET_AT(UARTn_CONF0_REG(n), 18, 1, 1);
}

void uart_txfifo_flush(uint8_t n) {
    while((UARTn_STATUS_REG(n) >> 16) & 0xFF);
}

void uart_clk(uint8_t n, uint32_t baud) {
    uint64_t div = (54000000UL << 4) / baud;
    uint32_t dec = div >> 4;
    uint32_t frag = div & 0xF;
    SET_AT(UARTn_CLKDIV_REG(n), 0, 0xFFFFF, dec);
    SET_AT(UARTn_CLKDIV_REG(n), 20, 0xF, frag);
}

void uart_send_char(uint8_t n, char c) {
    // wait for the buffer to contain < 32 chars
    while((UARTn_STATUS_REG(n) >> 16) & 0xFF >= 32);
    UARTn_FIFO_REG(n) = (uint32_t)c;
}

void uart_send_str(uint8_t n, char* str) {
    char c;
    while((c = *(str++)))
        uart_send_char(n, c);
}