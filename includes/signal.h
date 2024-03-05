#pragma once

typedef void (*fn_ptr)(void *);
typedef struct SIGNAL_T {
    fn_ptr *fn_ptrs;
    int capacity;
    int size;

} Signal;

#define SIGNAL_DEFAULT_CAP 5
#define SIGNAL_GROWTH_SIZE 5

Signal signal_new(int capacity);
void signal_fire(Signal *signal, void *arg);
void signal_connect(Signal *signal, fn_ptr fn);
void signal_disconnect(Signal *signal, fn_ptr fn_remove);
void signal_free(Signal *signal);