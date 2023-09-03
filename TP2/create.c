#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* f1(void *x){
  int j = *((int*) x);
  sleep(1);
  printf("f1: %d\n",j);
  pthread_exit(0);
}

void* f2(void *x){
  int j = *((int*) x);
  sleep(1);
  printf("f2: %d\n",j);
  pthread_exit(0);
}

int main()  {
  pthread_t f2_thread, f1_thread;
  int i1,i2;
  i1 = 1;
  i2 = 2;
  pthread_create(&f1_thread,NULL,f1, &i1);
  pthread_create(&f2_thread,NULL,f2, &i2);

  pthread_join(f1_thread, NULL);
  pthread_join(f2_thread, NULL);
  return(0);
}
