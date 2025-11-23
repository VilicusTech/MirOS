#include <fb.h>

struct limine_framebuffer *fb = 0;

void fb_init(struct limine_framebuffer *framebuffer) {
    fb = framebuffer;
}

void fb_putpixel(int x, int y, uint32_t color) {
    if (!fb) return;

    uint32_t *pixel = (uint32_t*)((uint64_t)fb->address +
                                   (y * fb->pitch) + 
                                   (x * (fb->bpp / 8)));

    *pixel = color;
}