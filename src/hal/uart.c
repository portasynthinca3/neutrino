#include "uart.h"
#include "../stdlib.h"
#include "wdt.h"

void uart_config(uint8_t n, uint8_t stop_len, uint8_t bits) {
    write_reg(UARTn_CONF0_REG(n), read_reg(UARTn_CONF0_REG(n)) | (stop_len << 4) | (bits << 2));
}

void uart_txfifo_rst(uint8_t n) {
    write_reg(UARTn_CONF0_REG(n), read_reg(UARTn_CONF0_REG(n)) | (1 << 18));
}

void uart_clk(uint8_t n, uint32_t baud) {
    uint64_t div = (40000000UL << 4) / baud;
    uint32_t dec = div >> 4;
    uint32_t frag = div & 0xF;
    write_reg(UARTn_CLKDIV_REG(n), dec | (frag << 20));
}

void uart_send_char(uint8_t n, char c) {
    // wait for the buffer to contain < 16 chars
    while((read_reg(UARTn_STATUS_REG(n)) >> 16) & 0xFF);
    write_reg(UARTn_FIFO_REG(n), (uint32_t)c);
}

void uart_send_str(uint8_t n, char* str) {
    char c;
    while((c = *(str++)))
        uart_send_char(n, c);
}