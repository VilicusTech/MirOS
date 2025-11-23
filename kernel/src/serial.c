#include <stdint.h>
#include <serial.h>

#define COM1 0x3F8

static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret; 
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void serial_init(void) {
    outb(COM1 + 1, 0x00);   // Disable interrupts
    outb(COM1 + 3, 0x80);   // Enable DLAB
    outb(COM1 + 0, 0x03);   // Divisor = 3 -> 38400 baud
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x03);   // 8 bits, no parity, one stop bit
    outb(COM1 + 2, 0xC7);   // Enable FIFO, clear, 14-byte threshold
    outb(COM1 + 4, 0x0B);   // IRQs enabled, RTS/DSR set
}

static int serial_can_write(void) {
    return inb(COM1 + 5) & 0x20;
}

void serial_write_char(char c) {
    while (!serial_can_write());
    outb(COM1, c);
}

void serial_write(const char *s) {
    for (; *s; s++) {
        if (*s == '\n') serial_write_char('\r');
        serial_write_char(*s);
    }
}