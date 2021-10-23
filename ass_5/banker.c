#include <stdio.h>
#include <stdlib.h>
#define MAX 20
void init_code() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}
int main()
{
    init_code();
    int Max[MAX][MAX], need[MAX][MAX], allocation[MAX][MAX], available[MAX], completed[MAX], safeSequence[MAX];
    int p, r, i, j, process, count;
    count = 0;

    printf("Enter the no of processes : ");
    scanf("%d", &p);

    for (i = 0; i < p; i++)
        completed[i] = 0; //  flag whether the process completed or not

    printf("\n\nEnter the no of resources : ");
    scanf("%d", &r);

    printf("\n\nEnter the allocation for each process : ");
    for (i = 0; i < p; i++)
    {
        printf("\nFor process %d : ", i + 1);
        for (j = 0; j < r; j++)
            scanf("%d", &allocation[i][j]);
    }
    printf("\n\nEnter the Max Matrix for each process : ");
    for (i = 0; i < p; i++)
    {
        printf("\nFor process %d : ", i + 1);
        for (j = 0; j < r; j++)
            scanf("%d", &Max[i][j]);
    }
    printf("\n\nEnter the Current Available Resources with OS : ");
    for (i = 0; i < r; i++)
        scanf("%d", &available[i]);

    for (i = 0; i < p; i++)
        for (j = 0; j < r; j++)
            need[i][j] = Max[i][j] - allocation[i][j];


    while (count != p && process != -1) {
        for (int i = 0; i < p; i++) { // check for each process 
            if (completed[i] == 0) { // if that process not completed

                int flag = 0;
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > available[j]) {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    safeSequence[count++] = i;
                    for (int y = 0; y < r; y++)
                        available[y] += allocation[i][y];
                    completed[i] = 1;
                }
            }
        }
    }

    if (count == p)
    {
        printf("\nThe system is in a safe state!!\n");
        printf("Safe Sequence : < ");
        for (i = 0; i < p; i++)
            printf("%d ", safeSequence[i]);
        printf(">\n");
    }
    else
        printf("\nThe system is in an unsafe state!!");
}

// The system is in a safe state!!
// Safe Sequence : < 1 3 4 0 2 >
// 5
// 3
// 0 1 0
// 2 0 0
// 3 0 2
// 2 1 1
// 0 0 2
// 7 5 3
// 3 2 2 
// 9 0 2
// 2 2 2
// 4 3 3
// 3 3 2