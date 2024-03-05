#include<cstdio>
#include<stdlib.h>
#include"signal.h"

void do_stuff_1(void *a) {
    printf("do_stuff_1 a=%d\n", *((int*)a));
}

void do_stuff_2(void *a) {
    printf("do_stuff_2 a=%d\n", *((int*)a));
}

void do_stuff_3(void *a) {
    printf("do_stuff_3 a=%d\n", *((int*)a));
}

int main(int argv, char **argc) {
    Signal test = signal_new(SIGNAL_DEFAULT_CAP);

    signal_connect(&test, &do_stuff_1);
    signal_connect(&test, &do_stuff_2);
    signal_connect(&test, &do_stuff_3);
    signal_disconnect(&test, &do_stuff_2);

    int a = 25;
    signal_fire(&test, (void*)&a);

    signal_free(&test);

    return EXIT_SUCCESS;
}