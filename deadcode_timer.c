// Dead Code - Timer Class
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

typedef struct {
    clock_t start_time;
    clock_t end_time;
    int is_running;
} Timer;

Timer* timer_create() {
    Timer* timer = (Timer*)malloc(sizeof(Timer));
    if (timer) {
        timer->start_time = 0;
        timer->end_time = 0;
        timer->is_running = 0;
    }
    return timer;
}

void timer_start(Timer* timer) {
    if (timer) {
        timer->start_time = clock();
        timer->is_running = 1;
    }
}

void timer_stop(Timer* timer) {
    if (timer && timer->is_running) {
        timer->end_time = clock();
        timer->is_running = 0;
    }
}

double timer_elapsed_seconds(Timer* timer) {
    if (timer) {
        clock_t end = timer->is_running ? clock() : timer->end_time;
        return ((double)(end - timer->start_time)) / CLOCKS_PER_SEC;
    }
    return 0.0;
}

long timer_elapsed_milliseconds(Timer* timer) {
    if (timer) {
        clock_t end = timer->is_running ? clock() : timer->end_time;
        return (long)(((double)(end - timer->start_time)) / CLOCKS_PER_SEC * 1000);
    }
    return 0;
}

void timer_reset(Timer* timer) {
    if (timer) {
        timer->start_time = 0;
        timer->end_time = 0;
        timer->is_running = 0;
    }
}

int timer_is_running(Timer* timer) {
    if (timer) {
        return timer->is_running;
    }
    return 0;
}

void timer_destroy(Timer* timer) {
    if (timer) {
        free(timer);
    }
}

