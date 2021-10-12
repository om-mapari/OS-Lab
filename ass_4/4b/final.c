#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

pthread_mutex_t wr, mutex;
int a = 10, readcount = 0;
void reader(void *arg)
{
    long int num = (long int)arg;

    pthread_mutex_lock(&mutex);
    readcount++; // make sure only one reader increment readcount
    pthread_mutex_unlock(&mutex);

    if (readcount == 1) // if reader is first reader then only reader will lock writer
        // because it is possible that if writer is in C.S then reader shouldnt allow in C.S
        pthread_mutex_lock(&wr);

    printf("\n Reader %ld is in critical section", num);
    printf("\n Reader %ld is reading data %d", num, a);
    sleep(1);

    pthread_mutex_lock(&mutex);
    readcount--; // make sure only one reader decrement readcount
    pthread_mutex_unlock(&mutex);
    if (readcount == 0) // make sure last reader will unlock writer
        pthread_mutex_unlock(&wr);

    printf("\n Reader %ld left critical section", num);
}
void writer(void *arg)
{
    long int num = (long int)arg;
    pthread_mutex_lock(&wr); // writer will lock wr variable 
    
    printf("\n Writer %ld is in critical section", num);

    printf("\n Writer %ld have written data as %d", num, ++a);
    sleep(1);

    printf("\n Writer %ld left critical section", num);

    pthread_mutex_unlock(&wr); // writer will lock wr variable 
}
int main()
{

    int nr, nw;
    printf("Enter number of reader and writer \n");
    scanf("%d %d", &nr, &nw);

    pthread_t *r;
    r = (pthread_t *)malloc(sizeof(pthread_t) * nr);
    pthread_t *w;
    w = (pthread_t *)malloc(sizeof(pthread_t) * nw);

    pthread_mutex_init(&wr, NULL);
    pthread_mutex_init(&mutex, NULL);

    unsigned long int i, j, k, l;
    for (i = 0; i < nr; i++)
    {
        pthread_create(&r[i], NULL, (void *)reader, (void *)i);
    }
    for (j = 0; j < nw; j++)
    {
        pthread_create(&w[j], NULL, (void *)writer, (void *)j);
    }

    for (k = 0; k < nr; k++)
    {
        pthread_join(r[k], NULL);
    }
    for (l = 0; l < nw; l++)
    {
        pthread_join(w[l], NULL);
    }
}