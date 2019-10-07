#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>
#include <stdarg.h>

typedef int (*OpenFunction)(const char* fn, int flags, ...);
OpenFunction real_open;

int open(const char* fn, int flags, ...) {
    int r = -1;
    va_list args;

    va_start(args, flags);
    if (!real_open) {
        void** pointer;

        pointer = (void**)&real_open;
        *pointer = dlsym(RTLD_NEXT, "open");
    }
    r = real_open(fn, flags, args);
    va_end(args);
    printf("try open %s\n", fn);
    return r;
}
