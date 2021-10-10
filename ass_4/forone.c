#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

sem_t bin_sem;
int data;
void producer()
{

    sem_wait(&bin_sem);

    data = rand() % 10;
    printf("\nProduser prodused => %d", data);
    sleep(1);

    sem_post(&bin_sem);
}
void consumer()
{
    sem_wait(&bin_sem);

    printf("\nConsumer consumed => %d", data);
    sleep(1);

    sem_post(&bin_sem);
}
int main()
{
    int np, nc;
    pthread_t p, c;

    sem_init(&bin_sem, 0, 1);
    
    pthread_create(&p, NULL, (void *)producer, NULL);

    pthread_create(&c, NULL, (void *)consumer, NULL);

    pthread_join(p, NULL);

    pthread_join(c, NULL);
}
