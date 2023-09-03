/*
 * compilar con:
 *    gcc -Wall -O0 -pthread  -o incr incr.c
 */
#include <pthread.h>
#include <stdio.h>
#define THREADS 2
#define K 10 * 1000 * 1000

int x=0;  // definición clásica de la variable global
//_Atomic int x=0;  // definción de la variable global como atómica
//  ver https://stackoverflow.com/questions/56810/how-do-i-start-threads-in-plain-c/52453291#52453291

// funciones para implementar la solución de Peterson

int turn=0;
int interested[2] = {0, 0};

void enter_region(int process)
{
    int other=(1-process);
    interested[process]=1;
    turn=process;
    while ( (turn==process) && (interested[other] == 1)  );
}

void leave_region(int process)
{
    interested[process]=0;
}


void* threadfunc(void* arg) {
    int thread_num=* (int*) arg;
    printf("este es el hilo %d\n", thread_num);
    for (int i = 0; i < K; ++i) {
        // enter_region(thread_num);
        x++;  // se incrementa la variable global
        // leave_region(thread_num);
    }
    printf("hilo %d finalizando\n", thread_num);
    return 0;
}

int main() {
    pthread_t th[2];
    int tn[2]={0,1};  // número de hilo a pasar a pthread_create
    // for (int i = 0; i < THREADS; ++i)
    //    pthread_create(&th[i], NULL, threadfunc, &tn[i]);
    // for (int i = 0; i < THREADS; ++i)
    //    pthread_join(th[i], NULL);

   
    for (int i = 0; i < THREADS; ++i)
       pthread_create(&th[i], NULL, threadfunc, &tn[i]);
       pthread_join(th[i], NULL);


    printf("x=%u\n", x);
}
