#include <stdio.h>
// Least Recently Used
int findLRU(int time[], int n)
{
    int i, min = time[0], pos = 0;

    for (i = 1; i < n; ++i)
    {
        if (time[i] < min)
        {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}
int main()
{
    printf("\n ENTER THE NUMBER OF PAGES:\n");
    int n;
    scanf("%d", &n);

    printf("\n ENTER THE REFERENCE_STRING :\n");
    int pages[50];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("\n ENTER THE NUMBER OF FRAMES :");
    int nf;
    int frame[10];
    scanf("%d", &nf);
    for (int i = 0; i < nf; i++)
        frame[i] = -1;

    int time[10];
    int flag1, flag2, fault_counter = 0;
    int count = 0;

    printf("\nREFERENCE_STRING  \tPAGE-FRAMES     \tHIT/FAULT\n");
    for (int i = 0; i < n; i++)
    {

        printf("%d\t\t\t", pages[i]);
        flag1 = flag2 = 0;

        // case 1 : hit
        for (int j = 0; j < nf; j++)
        {
            if (frame[j] == pages[i])
            {
                count++;
                time[j] = count;
                flag1 = flag2 = 1;
                for (int k = 0; k < nf; k++)
                    printf("%d\t", frame[k]);
                printf("HIT");
                break;
            }
        }
        // case 2 : page fault + free frame
        if (flag1 == 0)
        {
            for (int j = 0; j < nf; j++)
            {
                if (frame[j] == -1)
                {
                    count++;
                    fault_counter++;
                    frame[j] = pages[i];
                    time[j] = count;
                    flag2 = 1;
                    for (int k = 0; k < nf; k++)
                        printf("%d\t", frame[k]);
                    printf("FAULT");
                    break;
                }
            }
        }
        // case 3 : page fault + no free frame
        if (flag2 == 0)
        {

            int pos = findLRU(time, nf);
            count++;
            fault_counter++;
            frame[pos] = pages[i];
            time[pos] = count;
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
// 7                       2       7       1       FAULT

// Page Fault occurred = 4
// Totel HIT occurred = 1
// HIT ratio = 0.200000
// MISS ratio = 0.800000