#include <liballoc.h>

// Lock Memory Data structures.
int liballoc_lock();

// Unlock Memory Data structures.
int liballoc_unlock();

// Allocate Pages.
void* liballoc_alloc(int);

// Free non-used Memory.
int liballoc_free(void*, int);