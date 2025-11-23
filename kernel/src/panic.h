#include <stdnoreturn.h>
#include <stdarg.h>

void panic(const char *fmt, ...);
void panic_early(const char *msg);

#define PANIC(...) panic(__VA_ARGS__)

#define ASSERT(expr) do {if (!(expr)) {panic("Assertion failed: %s (%s:%d)", #expr, __FILE__, __LINE__);}} while (0)
