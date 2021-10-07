
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define SIZE 20

// Queue
void push(int);
void pop();
int fronte();
int empty();
int items[SIZE], front = -1, rear = -1;

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

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

void sortP(struct process s[], int n) // using bubble sort
{
    struct process temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < (n - 1 - i); j++)
        {
            if (s[j].arrival_time > s[j + 1].arrival_time)
            {
                temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
}

int main()
{

    int n;
    int tq;
    struct process p[100];

    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;

    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;

    int burst_remaining[100];
    int idx;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("nter time quantum: ");
    scanf("%d", &tq);
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

    sortP(p, n);
    int current_time = 0;
    push(0); // running queue
    int completed = 0;
    int mark[100]; // mark those who entered in running Queue
    for (int i = 0; i < 100; i++)
    {
        mark[i] = 0;
    }

    mark[0] = 1;

    int gantt[100];
    int g = 0;
    int gantt_time[100];
    int tn = 0;
    int st = -1;

    while (completed != n)
    {
        idx = fronte();
        gantt[g++] = p[idx].pid;
        pop();

        if (burst_remaining[idx] == p[idx].burst_time) // first time in readyQ
        {
            p[idx].start_time = max(current_time, p[idx].arrival_time); // set start point
            current_time = p[idx].start_time;
            if (st == -1)
                st = current_time;
        }

        if (burst_remaining[idx] - tq > 0) // normal where burst use
        {
            burst_remaining[idx] -= tq; // use tq burst time
            current_time += tq;
            gantt_time[tn++] = tq;
        }
        else // for b_r[idx] == 0 and // for b_r[idx] < 0
        {
            gantt_time[tn++] = burst_remaining[idx];
            current_time += burst_remaining[idx];
            burst_remaining[idx] = 0;
            completed++; // process totally completed
            p[idx].completion_time = current_time;

            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_response_time += p[idx].response_time;
        }

        for (int i = 1; i < n; i++) // push the processes in runningQ to ReadyQ
        {
            if (burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0)
            {
                push(i);
                mark[i] = 1;
            }
        }

        if (burst_remaining[idx] > 0) // repushing the process in queue cause its burst remaining
        {                             // else the process is done so dont push back in queue
            push(idx);
        }

        if (empty()) // if empty search for those whose never been in runningQ and push back
        {
            for (int i = 1; i < n; i++)
            {
                if (burst_remaining[i] > 0)
                {
                    push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    avg_response_time = (float)total_response_time / n;

    printf("\n\n");
    printf("## ROUND ROBIN CPU SCHEDULING ALGORITHM ##");

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

    int c = 1;
    int time[50];
    int ti = 0;

    printf("\n");
    printf("\nGANTT CHART\n");

    for (int i = 0; i < g; ++i)
    {
        printf("________");
    }
    printf("\n");
    for (int i = 0; i < g; i++)
    {

        printf("|  P%d   ", gantt[i]);
    }
    printf("|\n");

    for (int i = 0; i < g; ++i)
    {
        printf("‾‾‾‾‾‾‾‾");
    }

    printf("\n");
    printf("%d", st);
    printf("\t\t");
    int sum = 0;
    for (int i = 0; i < g; i++)
    {
        sum += gantt_time[i];

        printf("%d", st + sum);
        printf("\t\t");
    }
}

void push(int value)
{
    if (rear == SIZE - 1)
        return;

    if (front == -1)
        front = 0;
    rear++;
    items[rear] = value;
}

void pop()
{
    if (front == -1)
        return;

    front++;
    if (front > rear)
        front = rear = -1;
}

int empty()
{
    return (front == -1 && rear == -1);
}
int fronte()
{
    return items[front];
}
