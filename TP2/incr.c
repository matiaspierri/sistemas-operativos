/*
 * compilar con:
 *    gcc -Wall -O0 -pthread  -o incr incr.c
 */
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

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
        enter_region(thread_num);
        x++;  // se incrementa la variable global
        leave_region(thread_num);
    }
    printf("hilo %d finalizando\n", thread_num);
    return 0;
}

int main() {
    pthread_t th[2];
    int tn[2]={0,1};  // número de hilo a pasar a pthread_create

    for (int i = 0; i < THREADS; ++i) {   
       pthread_create(&th[i], NULL, threadfunc, &tn[i]);
       pthread_join(th[i], NULL);
    }
   


    printf("x=%u\n", x);

    clock_t start_clock, end_clock;
    double cpu_time_used_clock;

    start_clock = clock();
    performTask(); // Call the function whose execution time you want to measure
    end_clock = clock();

    cpu_time_used_clock = ((double)(end_clock - start_clock)) / CLOCKS_PER_SEC;
    printf("CPU time used (clock()): %f seconds\n", cpu_time_used_clock);

    // Method 2: Using gettimeofday()
    struct timeval start_timeval, end_timeval;
    double elapsed_timeval;

    gettimeofday(&start_timeval, NULL);
    performTask(); // Call the function whose execution time you want to measure
    gettimeofday(&end_timeval, NULL);

    elapsed_timeval = (end_timeval.tv_sec - start_timeval.tv_sec) +
                      (end_timeval.tv_usec - start_timeval.tv_usec) / 1000000.0;
    printf("Elapsed time (gettimeofday()): %f seconds\n", elapsed_timeval);
}
