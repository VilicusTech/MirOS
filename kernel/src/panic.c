#include <stdint.h>
#include <stdarg.h>
#include <panic.h>
#include <serial.h>
#include <fb.h>

static void panic_putc(char c) {
    fb_putc(c);
    serial_write(c);
}

static void panic_vprint(const char *fmt, va_list args) {
    char buf[512];

    int i = 0;

    for (; *fmt && i < 510; fmt++) {
        if (*fmt != '%') {
            buf[i++] = *fmt;
            continue;
        }

        fmt++;

        if (*fmt == 's') {
            const char *s = va_arg(args, const char *);
            while (*s && i < 510) buf[i++] = *s++;
        }
        else if (*fmt == 'c') {
            buf[i++] = (char)va_arg(args, int);
        }
        else if (*fmt == 'd') {
            int v = va_arg(args, int);
            char tmp[32]; int ti = 0;

            if (v < 0) { buf[i++] = '-'; v = -v; }
            do { tmp[ti++] = (v % 10) + '0'; v /= 10; } while (v);
            while (ti--) buf[i++] = tmp[ti];
        }
        else if (*fmt == 'p' || *fmt == 'x') {
            uint64_t v = va_arg(args, uint64_t);
            char hex[] = "0123456789ABCDEF";
            buf[i++] = '0'; buf[i++] = 'x';
            for (int shift = 60; shift >= 0; shift -= 4)
                buf[i++] = hex[(v >> shift) & 0xF];
        }
        else {
            buf[i++] = '?';
        }
    }

    buf[i] = '\0'

    for (int j = 0; buf[j]; j++)
        panic_putc(buf[j]);
}

noreturn void panic(const char *fmt, ...) {
    serial_write_str("\n\n !!! PANIC !!!\n");
    fb_write_str("\n\nKERNEL PANIC: ");

    va_list args;
    va_start(args, fmt);
    panic_vprintf(fmt, args);
    va_end(args);

    serial_write_str("\nSystem halted.\n");
    fb_write_str("\nHALTING.\n");

    for (;;) __asm__("hlt");
}

noreturn void panic_early(const char *msg) {
    serial_write_str("EARLY PANIC: ");
    serial_write_str(msg);

    fb_write_str("EARLY PANIC: ");
    fb_write_str(msg);

    for (;;) __asm__("hlt");
}