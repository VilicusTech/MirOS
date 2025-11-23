#include <stdint.h>
#include <limine.h>

void fb_init(struct limine_framebuffer *framebuffer);
void fb_putpixel(int x, int y, uint32_t color);

extern struct limine_framebuffer *fb;