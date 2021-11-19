#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

sem_t empty, full;
pthread_mutex_t mutex;

int buffer[5]; 
int count = 0;
void producer(void *arg)
{
    long int num = (long int)arg; 

    sem_wait(&empty);

    pthread_mutex_lock(&mutex); 

    pthread_t self_id;
    self_id = pthread_self();

    buffer[count] = rand() % 10; 
    printf("\n Producer : %ld with thread id : (%lu) PRODUSED DATA : %d ", num + 1, self_id, buffer[count]);
    count++;
    printf("\nBUFFER => ");

    for (int i = 0; i < count; i++)
        printf("%d ", buffer[i]);
    printf("\n");

    sleep(1);

    pthread_mutex_unlock(&mutex); 

    sem_post(&full); 
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


    printf("Enter number of producer and consumers \n");
    scanf("%d %d", &np, &nc); 
    pthread_t *p;
    p = (pthread_t *)malloc(sizeof(pthread_t) * np);
    pthread_t *c;
    c = (pthread_t *)malloc(sizeof(pthread_t) * nc);

  
    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);
  
    pthread_mutex_init(&mutex, NULL);



    unsigned long int i, j, k, l;


    for (i = 0; i < np; i++) 
    {
        pthread_create(&p[i], NULL, (void *)producer, (void *)i);
    }
    for (j = 0; j < nc; j++)
    {
        pthread_create(&c[j], NULL, (void *)consumer, (void *)j);
    }

   
    for (k = 0; k < np; k++) // wait for thread to wait ex
    {
        pthread_join(p[k], NULL);
    }
    for (l = 0; l < nc; l++)
    {
        pthread_join(c[l], NULL);
    }

    pthread_mutex_destroy(&mutex);
}