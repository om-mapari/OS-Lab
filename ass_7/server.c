#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#define SIZE 1024
#define BUF_SIZE 100
#define KEY 2345
int main()
{
    char buffer[BUF_SIZE];
    int shmid = shmget((key_t)KEY, SIZE, 0666 | IPC_CREAT);
    printf("\nKey of shared memory is %d\n", shmid);
    void *shared_memory = shmat(shmid, NULL, 0);
    printf("\nProcess attached at %p\n\nEnter a string: ", shared_memory);
    fflush(stdin);
    scanf("%[^\n]%*c", buffer);
    fflush(stdin);
    strcpy(shared_memory, buffer);
    printf("\n’%s’ has been written to the shared memory\n", (char *)shared_memory);
}