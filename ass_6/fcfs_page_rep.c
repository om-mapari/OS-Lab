#include <stdio.h>
int main()
{
    printf("\n ENTER THE NUMBER OF PAGES:\n");
    int n;
    scanf("%d", &n);

    printf("\n ENTER THE REFERENCE_STRING :\n");
    int page_arr[50];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &page_arr[i]);
    }

    printf("\n ENTER THE NUMBER OF FRAMES :");
    int nf;
    int frame[10];
    scanf("%d", &nf);
    for (int i = 0; i < nf; i++)
        frame[i] = -1;

    int flag, fault_counter = 0;
    int j = 0;
    printf("\nREFERENCE_STRING  \tPAGE-FRAMES     \tHIT/FAULT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t\t", page_arr[i]);
        flag = 0;

        for (int k = 0; k < nf; k++)
        {
            if (frame[k] == page_arr[i])
            {
                flag = 1;
                for (int k = 0; k < nf; k++)
                    printf("%d\t", frame[k]);
                printf("HIT");
            }
        }
        if (flag == 0)
        {
            frame[j] = page_arr[i];
            j = (j + 1) % nf;
            fault_counter++;
            for (int k = 0; k < nf; k++)
                printf("%d\t", frame[k]);
            printf("FAULT");
        }
        printf("\n");
    }
    printf("\nPage Fault occurred = %d", fault_counter);
    printf("\nTotel HIT occurred = %d", n - fault_counter);
    printf("\nHIT ratio = %f", (double)(n - fault_counter) / n);
    printf("\nMISS ratio = %f", (double)(fault_counter) / n);
    return 0;
}

//  ENTER THE NUMBER OF PAGES:
// 5

//  ENTER THE REFERENCE_STRING :
// 2 3 2 1 7

//  ENTER THE NUMBER OF FRAMES :3

// REFERENCE_STRING        PAGE-FRAMES             HIT/FAULT
// 2                       2       -1      -1      FAULT
// 3                       2       3       -1      FAULT
// 2                       2       3       -1      HIT
// 1                       2       3       1       FAULT
// 7                       7       3       1       FAULT

// Page Fault occurred = 4
// Totel HIT occurred = 1
// HIT ratio = 0.200000
// MISS ratio = 0.800000