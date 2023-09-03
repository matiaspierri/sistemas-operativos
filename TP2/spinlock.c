/*  Compilar con
 *      gcc -Wall -lpthread -o spinlock spinlock.c
 *
 */


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

volatile int i = 0;

static void *f1(void * arg)
{
    while (i==0);   //  spinlock !!!
    printf("Thread %ld: i's value has changed to %d.\n", (long) arg, i);
    return NULL;
}

static void *f2(void * arg)
{
    sleep(20);
    i = 99;
    printf("Thread %ld: t2 has changed the value of i to %d.\n",(long) arg, i);
    return NULL;
}

int main()
{
     pthread_t t1, t2;

     pthread_create(&t1, NULL, f1, (void *) 1 );
     pthread_create(&t2, NULL, f2, (void *) 2 );
     pthread_join(t1, NULL);
     pthread_join(t2, NULL);
     printf("All pthreads finished.\n");
     return 0;
}
