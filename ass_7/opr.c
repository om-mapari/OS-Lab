#include <stdlib.h>
#include <stdio.h>

int find(int n, int f, int ind, int frame[f], int pages[n])
{

    int last = ind, res = -1;

    for (int i = 0; i < f; i++)
    {
        int j;
        for (j = ind; j < n; j++)
        {

            if (frame[i] == pages[j])
            {
                if (j > last)
                {
                    last = j;
                    res = i;
                }
                break;
            }
        }

        // if page not referece in future
        if (j == n)
        {
            return i;
        }
    }

    return (res == -1) ? 0 : res;
}

void optimalPage(int n, int f, int frame[f], int pages[n])
{

    printf("\n\nOptimal Page Replacement - \n");

    for (int i = 0; i < f; i++)
        frame[i] = -1;

    int pointer = 0; // keep track on frame ind till it full filled     int count = 0;

    printf("\n\n------------------------------------------------");
    printf("\nPage\t\t\t Page frames");
    printf("\n------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t", pages[i]);

        int available = 0;
        for (int k = 0; k < f; k++)
        {
            if (frame[k] == pages[i])
                available = 1;
        }

        if (available == 0)
        {

            // if frame is not filled completely
            if (pointer < f)
            {
                frame[pointer++] = pages[i];
            }
            else
            {
                int j = find(n, f, i + 1, frame, pages);
                frame[j] = pages[i];
            }
            count++;
        }
        for (int k = 0; k < f; k++)
            printf("%d\t", frame[k]);
        printf("\n\n");
    }

    printf("------------------------------------------------\n");
    printf("Total Page Fault :  %d\n\n", count);
}

int main()
{
    int n, f;

    printf("\nEnter No. of Pages : ");
    scanf("%d", &n);

    int pages[n];

    printf("\nEnter Pages : ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("\nEnter the No. of Frames : ");
    scanf("%d", &f);

    int frame[f];
    optimalPage(n, f, frame, pages);
    return 0;
}
