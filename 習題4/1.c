#include <stdio.h>
#include <pthread.h>

#define LOOPS 100
int money = 10000;
int counter = 0;
int counter_a = 0;
int counter_b = 0;

void *inc()
{
  for (int i=0; i<LOOPS; i++) {
    money = money + 1000;
    counter_a = counter_a + 1;
    counter = counter + 1;
    printf("Deposit=%d\n", counter_a);
    printf("money=%d\n", money);
  }
  return NULL;
}

void *dec()
{
  for (int i=0; i<LOOPS; i++) {
    money = money - 1000;
    counter_b = counter_b + 1;
    counter = counter + 1;
    printf("Withdrawal=%d\n", counter_b);
    printf("money=%d\n", money);
  }
  return NULL;
}


int main() 
{
  pthread_t thread1, thread2;

  pthread_create(&thread1, NULL, inc, NULL);
  pthread_create(&thread2, NULL, dec, NULL);

  pthread_join( thread1, NULL);
  pthread_join( thread2, NULL);
  printf("counter=%d\n",counter);
  
}
