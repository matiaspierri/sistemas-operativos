/****************************  incrlock.c *******************************/
/*
 * compilar con:
 *    gcc -Wall -O0 -pthread  -o incrlock incrlock.c
 *
 * ver https://gcc.gnu.org/onlinedocs/gcc/_005f_005fatomic-Builtins.html
 */
#include <pthread.h>
#include <stdio.h>
#define THREADS 2
#define K 10 * 1000 * 1000

unsigned x=0;

void* atomic_threadfunc() {
    for (int i = 0; i < K; ++i)
        //  x++;   fue remplazado por
        __atomic_fetch_add(&x, 1, __ATOMIC_SEQ_CST);
    return 0;
}

int main() {
    pthread_t th[2];
    int tn[2]={0,1};  // número de hilo a pasar a pthread_create
    for (int i = 0; i < THREADS; ++i)
        pthread_create(&th[i], NULL, atomic_threadfunc, &tn[i]);
    for (int i = 0; i < THREADS; ++i)
        pthread_join(th[i], NULL);
    printf("%u\n", x);
}