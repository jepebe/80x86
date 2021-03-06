#pragma once

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "80x86.h"

typedef struct {
    char *name;
    struct timespec time;
    u16 count;
    u16 success;
    u16 fail;

} Tester;

Tester create_tester(char *name) {
    Tester tester;
    tester.name = name;
    timespec_get(&tester.time, TIME_UTC);
    tester.count = 0;
    tester.success = 0;
    tester.fail = 0;

    printf("\x1b[33m--== %s ==--\x1b[0m\n", name);
    return tester;
}

static inline double timespec_diff(struct timespec *a) {
    struct timespec result;
    struct timespec b;
    timespec_get(&b, TIME_UTC);
    result.tv_sec = b.tv_sec - a->tv_sec;
    result.tv_nsec = b.tv_nsec - a->tv_nsec;
    if (result.tv_nsec < 0) {
        --result.tv_sec;
        result.tv_nsec += 1000000000L;
    }
    double t = result.tv_sec * 1000000000.0;
    t += result.tv_nsec;
    t /= 1000000000.0;

    return t;
}

void test(Tester *tester, bool test_state, char *message) {
    tester->count++;

    if (test_state) {
        tester->success++;
        if (message) {
            printf("\x1b[0;32m\u2705  Test #%02d OK! %s\x1b[0m\n", tester->count, message);
        }
    } else {
        tester->fail++;

        printf("\x1b[0;31m\u274C  Test #%02d Error! %s\x1b[0m\n", tester->count, message);
    }
}

void testi(Tester *tester, int a, int b, char *msg) {
    tester->count++;
    int count = tester->count;

    if (a == b) {
        tester->success++;
        if (msg) {
            printf("\x1b[0;32m\u2705  Test #%02d %d == %d %s\x1b[0m\n", count, a, b, msg);
        }
    } else {
        tester->fail++;
        if (!msg) {
            msg = "";
        }
        printf("\x1b[0;31m\u274C  Test #%02d  %d != %d %s\x1b[0m\n", count, a, b, msg);
    }
}

void testc(Tester *tester, char a, char b, char *msg) {
    tester->count++;
    int count = tester->count;

    if (a == b) {
        tester->success++;
        if (msg) {
            printf("\x1b[0;32m\u2705  Test #%02d %c == %c %s\x1b[0m\n", count, a, b, msg);
        }
    } else {
        tester->fail++;
        if (!msg) {
            msg = "";
        }
        printf("\x1b[0;31m\u274C  Test #%02d  %c != %c %s\x1b[0m\n", count, a, b, msg);
    }
}

void test_u64(Tester *tester, uint64_t a, uint64_t b, char *msg) {
    tester->count++;
    int count = tester->count;

    if (a == b) {
        tester->success++;
        if (msg) {
            printf("\x1b[0;32m\u2705  Test #%02d %llu == %llu %s\x1b[0m\n", count, a, b, msg);
        }
    } else {
        tester->fail++;
        if (!msg) {
            msg = "";
        }
        printf("\x1b[0;31m\u274C  Test #%02d %llu != %llu %s\x1b[0m\n", count, a, b, msg);
    }
}

void test_str(Tester *tester, char *a, char *b, char *msg) {
    tester->count++;
    int count = tester->count;

    if (strcmp(a, b) == 0) {
        tester->success++;
        if (msg) {
            printf("\x1b[0;32m\u2705  Test #%02d %s == %s %s\x1b[0m\n", count, a, b, msg);
        }
    } else {
        tester->fail++;
        printf("\x1b[0;31m\u274C  Test #%02d %s != %s %s\x1b[0m\n", count, a, b, msg);
    }
}

void test_section(char *name) {
    printf("\n\x1b[33m[%s]\x1b[0m\n", name);
}

int test_summary(Tester *tester) {
    printf("\n");
    if (tester->fail > 0) {
        u16 fail_count = tester->fail;
        u16 count = tester->count;
        printf("\x1b[0;31mError! %d of %d test(s) failed!\x1b[0m\n", fail_count, count);
    } else {
        u16 success = tester->success;
        printf("\x1b[0;32mSuccess! %d test(s) ran successfully!\x1b[0m\n", success);
    }
    double diff = timespec_diff(&tester->time);
    printf("\x1b[33mRunning time: %0.5f s.\x1b[0m\n", diff);

    return tester->fail;
}
