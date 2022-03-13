#pragma once

#define RED(a) "\x1b[31m" a "\x1b[0m"
#define GREEN(a) "\x1b[32m" a "\x1b[0m"
#define YELLOW(a) "\x1b[33m" a "\x1b[0m"
#define CYAN(a) "\x1b[36m" a "\x1b[0m"

#define PRINT_BORDER "==================================================================="

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

