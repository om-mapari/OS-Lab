#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
int main()
{
    int fd;
    int words = 0, lines = 0, chars = 0;
    // file path FIFO
    char *fifo1 = "fifo1";
    char *fifo2 = "fifo2";
    // creating fifo
    mkfifo(fifo1, 0666);
    mkfifo(fifo2, 0666);
    // buffer to store message
    char arr1[80], arr2[80];
    // open FIFO for write only
    fd = open(fifo1, O_WRONLY);
    // take input
    printf("\nEnter message: ");
    fgets(arr2, 80, stdin);
    // write input to fifo and close
    write(fd, arr2, strlen(arr2) + 1);
    close(fd);
    // open fifo for read only
    fd = open(fifo2, O_RDONLY);
    // read from fifo
    read(fd, arr1, sizeof(arr1));
    printf("\nRecieved: %s\n", arr1);
    // calculate message
    int i = 0;
    while (arr1[i] != '\0')
    {
        if (arr1[i] == ' ' || arr1[i] == '\n')
        {
            words++;
        }
        else
        {
            chars++;
        }
        if (arr1[i] == '\n')
        {
            lines++;
        }
        i++;
    }
    printf("\n No of Words: %d", words);
    printf("\n No of Characters: %d", chars);
    printf("\n No of Lines: %d", lines);
    // close fifo
    close(fd);
    return 0;
}