#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
// 1) produser cant produse when buffer is full
// 2) consumer cant consume when buffer is empty
// 3) when one p or c is in critical sec then
//    no other p or c will allowed to enter in criticl sec

// declearing simaphore variable
sem_t empty, full;
// one mutex variable

pthread_mutex_t mutex;

int buffer[5];
int count = 0;
void producer(void *arg)
{
    long int num = (long int)arg; // typecast arg value in int format

    sem_wait(&empty);
    // producer is allowed to produse data
    // producer is waiting for his turn
    pthread_mutex_lock(&mutex);
    // locking critical secition when produser is allowed to enter in creatical section
    pthread_t self_id;
    self_id = pthread_self();

    // produser is procusing data
    buffer[count] = rand() % 10; // assign random value hear
    printf("\n Producer : %ld with thread id : (%lu) PRODUSED DATA : %d ", num + 1, self_id, buffer[count]);
    count++;
    printf("\nBUFFER => ");

    for (int i = 0; i < count; i++)
        printf("%d ", buffer[i]);
    printf("\n");

    sleep(1);

    pthread_mutex_unlock(&mutex); // unlocking critical secition when

    sem_post(&full); //produser is increamenting full value
}
void consumer(void *arg)
{
    long int num = (long int)arg;

    sem_wait(&full);

    pthread_mutex_lock(&mutex);

    pthread_t self_id;
    self_id = pthread_self();

    count--;
    printf("\n counsumer : %ld with thread id :  (%lu) CONSUMED DATA : %d ", num + 1, self_id, buffer[count]);
    sleep(1);
    printf("\nBUFFER => ");

    for (int i = 0; i < count; i++)
        printf("%d ", buffer[i]);
    printf("\n");

    pthread_mutex_unlock(&mutex);

    sem_post(&empty);
}
int main()
{
    int np, nc;
    // pthread_t p[10],c[10];

    printf("Enter number of producer and consumers \n");
    scanf("%d %d", &np, &nc); // read no of produser and counsumer

    pthread_t *p;
    p = (pthread_t *)malloc(sizeof(pthread_t) * np);
    pthread_t *c;
    c = (pthread_t *)malloc(sizeof(pthread_t) * nc);

    // initilize sima variable
    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);
    // initilize mutex variable
    pthread_mutex_init(&mutex, NULL);

    // sima =  use for sincronization
    // mutex = use for locking and unlocking

    unsigned long int i, j, k, l;

    // hear we are creating produser theread
    for (i = 0; i < np; i++)
    {
        pthread_create(&p[i], NULL, (void *)producer, (void *)i);
    }
    for (j = 0; j < nc; j++)
    {
        pthread_create(&c[j], NULL, (void *)consumer, (void *)j);
    }

    // join produser threads
    for (k = 0; k < np; k++)
    {
        pthread_join(p[k], NULL);
    }
    for (l = 0; l < nc; l++)
    {
        pthread_join(c[l], NULL);
    }
}