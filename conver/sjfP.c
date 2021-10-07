
#include <stdio.h>
#include <string.h>
#include <math.h>

struct process
{
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

int min(int x, int y)
{
    if (x >= y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

int max(int x, int y)
{
    if (x >= y)
    {
        return y;
    }
    else
    {
        return x;
    }
}

int main()
{
    int n;
    struct process p[100];
    //Avarage
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    //totel
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    //supportive
    int burst_remaining[100];
    int is_completed[100];
    memset(is_completed, 0, sizeof(is_completed));

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time of process %d%s", i + 1, ": ");
        scanf("%d", &p[i].arrival_time);
        printf("Enter burst time of process %d%s", i + 1, ": ");
        scanf("%d", &p[i].burst_time);
        p[i].pid = i + 1;
        burst_remaining[i] = p[i].burst_time;
        printf("\n");
    }

    int current_time = 0;
    int completed = 0;

    int v[100];
    int vcount = 0;
    while (completed != n)
    {
        int idx = -1;      //selected process id
        int mn = 10000000; //minimum
        for (int i = 0; i < n; i++)
        {
            //which process has arrivied in ready queue && p completed or not
            if (p[i].arrival_time <= current_time && is_completed[i] == 0)
            {
                if (burst_remaining[i] < mn)
                { // finding minimum burst time and set idS
                    mn = burst_remaining[i];
                    idx = i;
                }
                if (burst_remaining[i] == mn)
                { // if two process having same burst time then check arrival time & set idS
                    if (p[i].arrival_time < p[idx].arrival_time)
                    {
                        mn = burst_remaining[i];
                        idx = i;
                    }
                }
            }
        }  //from all the process in readyQueue which process has minimum burst time

        if (idx != -1) // idx process selected
        { 

            v[vcount++] = p[idx].pid;

            if (burst_remaining[idx] == p[idx].burst_time)
            {
                p[idx].start_time = current_time;
            }
            burst_remaining[idx] -= 1;
            current_time++;

            if (burst_remaining[idx] == 0) // process completed
            {
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;  // TAT = CT - AT
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;    // WT = TAT - BT
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;   // RT = ST - AT
 
                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
                total_response_time += p[idx].response_time;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else
        {
            current_time++;
        }
    }

    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    for (int i = 0; i < n; i++)
    {
        min_arrival_time = min(min_arrival_time, p[i].arrival_time);
        max_completion_time = max(max_completion_time, p[i].completion_time);
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    avg_response_time = (float)total_response_time / n;

    printf("\n\n");
    printf("## SHORTEST JOB FIRST CPU SCHEDULING ALGORITHM ##");

    printf("\n\n");

    printf("#P\t"
           "AT\t"
           "BT\t"
           "ST\t"
           "CT\t"
           "TAT\t"
           "WT\t"
           "RT\t"
           "\n\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t"
               "%d\t"
               "%d\t"
               "%d\t"
               "%d\t"
               "%d\t"
               "%d\t"
               "%d\t\n\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].start_time, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time, p[i].response_time);
    }

    printf("Average Turnaround Time = %f\n", avg_turnaround_time);
    printf("Average Waiting Time = %f\n", avg_waiting_time);
    printf("Average Response Time = %f\n", avg_response_time);



    printf("\n");
    printf("\nGANTT CHART\n");

    int c = 1;
    int time[50];
    int ti = 0;

    for (int i = 0; i < n * 1.5; ++i)
    {
        printf("_______");
    }
    printf("\n");
    for (int i = 0; i < vcount; i++)
    {

        if (v[i] != v[i + 1])
        {
            printf("|  "
                   "P%d"
                   "   ",
                   v[i]);
            time[ti++] = c;
            c = 1;
        }
        else
        {
            c++;
        }
    }
    printf("|\n");

    for (int i = 0; i < n * 1.5; ++i)
    {
        printf("‾‾‾‾‾‾‾");
    }
    printf("\n");
    printf("0"
           "\t\t");
    int sum = 0;
    for (int i = 0; i < ti; i++)
    {
        sum += time[i];
        printf("%d\t\t", sum);
    }
}

// 5
// 2 6
// 5 2
// 1 8
// 0 3
// 4 4