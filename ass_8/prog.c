#include <stdio.h>
#include <stdlib.h>
int arr[100];
int length, n, current;
#define INF 10000000
void SSTF()
{
    int total_track_movement = 0;
    int tempCurrent = current;
    int isVisited[100] = {0};
    printf("\n\nOrder by SSTF: %d \n", tempCurrent);
    int min_diff = INF;
    int closest_index;
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (isVisited[i] == 0)
            {
                if (abs(tempCurrent - arr[i]) < min_diff)
                {
                    closest_index = i;
                    min_diff = abs(tempCurrent - arr[i]);
                }
            }
        }
        isVisited[closest_index] = 1;
        total_track_movement += abs(tempCurrent - arr[closest_index]);
        tempCurrent = arr[closest_index];
        min_diff = INF;
        printf("%d --> ", tempCurrent);
    }
    printf("\nTotal Track movement = %d \n", total_track_movement);
}
int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
void SCAN()
{
    int total_track_movement = 0;
    qsort(arr, n, sizeof(int), cmpfunc);

    total_track_movement = length - 1 - current;
    if (current > arr[0])
    {
        total_track_movement += length - 1 - arr[0];
    }
    printf("\nOrder by SCAN:\n");
    printf("%d --> ", current);
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > current)
        {
            printf("%d --> ", arr[i]);
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (arr[i] < current)
        {
            printf("%d --> ", arr[i]);
        }
    }

    printf("\nTotal Track movement = %d \n", total_track_movement);
}
void CLOOK()
{
    int total_track_movement = 0;
    qsort(arr, n, sizeof(int), cmpfunc);
    total_track_movement = arr[n - 1] - current;
    if (arr[0] < current)
    {
        total_track_movement += arr[n - 1] - arr[0];
    }
    printf("\nOrder by C-LOOK:\n");
    printf("%d --> ", current);
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > current)
        {
            printf("%d --> ", arr[i]);
        }
    }

    int i;
    for (i = 0; arr[i] < current; i++)
    {
        printf("%d --> ", arr[i]);
    }
    if (arr[0] < current)
    {
        total_track_movement += arr[i - 1] - arr[0];
    }
    printf("\nTotal Track movement = %d \n", total_track_movement);
}
void main()
{
    int choice;
    printf("Enter number of Requests::");
    scanf("%d", &n);
    printf("\nEnterRequests::\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("\nEnter total length of the track::");
    scanf("%d", &length);
    printf("\nEnter current position of read-write head::");
    scanf("%d", &current);
    do
    {
        printf("\n-------- MENU ----------\n");
        printf("1.SSTF\n2.SCAN\n3.C-LOOK\n4.EXIT\n\nChoice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            SSTF();
            break;
        case 2:
            SCAN();
            break;
        case 3:
            CLOOK();
            break;
        case 4:
            break;
        }
    } while (choice != 4);
}