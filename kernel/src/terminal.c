#include <terminal.h>
#include <fb.h>
#include <font.h>

static int cursor_x = 0;
static int cursor_y = 0;
static const int char_w =8;
static const int char_h =8;

static uint32_t text_color = 0xFFFFFFFF; // White

void term_putchar(char c) {
    int scale = 2;
    int spacing = 2;
    int line_spacing = 2;
    
    if (!fb) return;

    if (c == '\n') {
        cursor_x = 0;
        cursor_y += char_h * scale + line_spacing;
        return;
    }
    
    for (int y = 0; y < char_h; y++) {
        uint8_t row = font8x8_basic[(int)c][y];
        for (int x = 0; x < char_w; x++) {
            if (row & (1 << x)) {
                //Double pixel count for 16x16
                for (int sy = 0; sy < scale; sy++) {
                    for (int sx = 0; sx < scale; sx++) {
                        fb_putpixel(cursor_x + x*scale + sx, cursor_y + y*scale + sy, text_color);
                    }
                }
            }
        }
    }

    cursor_x += char_w * scale + spacing;

    if (cursor_x + char_w >= (int)fb->width) {
        cursor_x = 0;
        cursor_y += char_h * scale + line_spacing;
    }
}

void term_print(const char *s) {
    while (*s) {
        term_putchar(*s++);
    }
}

void term_init() {
    cursor_x = 0;
    cursor_y = 0;
}