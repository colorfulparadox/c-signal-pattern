#include"signal.h"
#include<cstdio>
#include<cstdlib>

Signal signal_new(int capacity) {
    return Signal {
        .fn_ptrs = (fn_ptr*)malloc(sizeof(fn_ptr) * capacity),
        .capacity = capacity,
        .size = 0,
    };
}

void signal_fire(Signal *signal, void *arg) {
    for (int i = 0; i < signal->size; i++) {
        signal->fn_ptrs[i](arg);
    }
}

void expand_signal_array(Signal *signal) {
    signal->capacity += SIGNAL_GROWTH_SIZE;
    void *realloc_result = realloc(signal->fn_ptrs, signal->capacity * sizeof(fn_ptr));
    if (realloc_result == NULL) {
        fprintf(stderr, "!!! ERROR: FAILED TO REALLOC MEM TO EXTEND SIGNAL ARRAY !!!\n");
        exit(EXIT_FAILURE);
    }
    *(signal->fn_ptrs) =  (fn_ptr)realloc_result;
}

void signal_connect(Signal *signal, fn_ptr fn) {
    if (signal->capacity == signal->size-1) {
        expand_signal_array(signal);
    }
    signal->fn_ptrs[signal->size] = fn;
    signal->size += 1;
}

void signal_disconnect(Signal *signal, fn_ptr fn_remove) {
    for (int i = 0; i < signal->size; i++) {
        fn_ptr fn = signal->fn_ptrs[i];
        if (fn != fn_remove) continue;

        if (signal->size-1 == i) {
            signal->size -= 1;
            break;
        }

        signal->fn_ptrs[i] = signal->fn_ptrs[signal->size-1];
        signal->size -= 1;
    }
}

void signal_free(Signal *signal) {
    signal->size = -99999;
    signal->capacity = -99999;
    free(signal->fn_ptrs);
}