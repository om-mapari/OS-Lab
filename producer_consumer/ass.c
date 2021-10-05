#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

// declearing simaphore variable
sem_t empty,full;
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
    pthread_mutex_lock(&mutex); // locking critical secition when produser is allowed to enter in creatical section 
    
    // produser is procusing data
    buffer[count] = rand()%10; // assign random value hear
    printf("\n Producer : %ld Produced : %d ",num+1,buffer[count]);
    count++;
    sleep(1);

    pthread_mutex_unlock(&mutex);  // unlocking critical secition when 

    sem_post(&full); //produser is increamenting full value

}
void consumer(void *arg)
{
    long int num = (long int)arg;
    
    sem_wait(&full);

    pthread_mutex_lock(&mutex);

    count--;
    printf("\n counsumer : %ld consumed : %d ",num+1,buffer[count]);
    sleep(1);

    pthread_mutex_unlock(&mutex);

    sem_post(&empty);

}
int main()
{
    int np,nc; //number of p and c
    pthread_t p[10],c[10]; //threads variables

    // read no of produser and counsumer 
    printf("Enter number of producer and consumers \n");
    scanf("%d %d",&np,&nc);

    // initilize sima variable
    sem_init(&empty,0,5); 
    // add of sima, 0 -> not sherec, initial value as all solt are empty
    sem_init(&full,0,0);

    // initilize mutex variable
    pthread_mutex_init(&mutex,NULL); 


    // sima =  use for sincronization
    // mutex = use for locking and unlocking 


    unsigned long int i,j,k,l;

    // hear we are creating produser theread 
    for( i = 0; i < np; i++) {
        pthread_create(&p[i], NULL, (void *)producer, (void *)i);
    }
    for( j = 0; j < nc; j++) {
        pthread_create(&c[j], NULL, (void *)consumer, (void *)j);
    }

    // join produser threads
    for( k = 0; k< np; k++) {
        pthread_join(p[k], NULL);
    }
    for( l = 0; l < nc; l++) {
        pthread_join(c[l], NULL);
    }


}
// https://www.youtube.com/watch?v=s1aVNUttOU8
// https://www.youtube.com/watch?v=s1aVNUttOU8