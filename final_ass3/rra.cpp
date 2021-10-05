#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <string.h>
using namespace std;
void init_code()
{

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
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

void sortP(process s[], int n) // using bubble sort
{
    process temp;
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
    init_code();
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

    cout << setprecision(2) << fixed;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter time quantum: ";
    cin >> tq;

    for (int i = 0; i < n; i++)
    {
        cout << "Enter arrival time of process " << i + 1 << ": ";
        cin >> p[i].arrival_time;
        cout << "Enter burst time of process " << i + 1 << ": ";
        cin >> p[i].burst_time;
        burst_remaining[i] = p[i].burst_time;
        p[i].pid = i + 1;
        cout << endl;
    }

    sortP(p, n);
    queue<int> q;
    int current_time = 0;
    q.push(0); // running queue
    int completed = 0;
    int mark[100]; // mark those who entered in running Queue
    memset(mark, 0, sizeof(mark));
    mark[0] = 1;

    int gantt[100];
    int g = 0;
    int gantt_time[100];
    int tn = 0;
    int st = -1;

    while (completed != n)
    {
        idx = q.front();
        gantt[g++] = p[idx].pid;
        q.pop();

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
                q.push(i);
                mark[i] = 1;
            }
        }

        if (burst_remaining[idx] > 0) // repushing the process in queue cause its burst remaining
        {   // else the process is done so dont push back in queue
            q.push(idx);
        }

        if (q.empty()) // if empty search for those whose never been in runningQ and push back
        {
            for (int i = 1; i < n; i++)
            {
                if (burst_remaining[i] > 0)
                {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    avg_response_time = (float)total_response_time / n;

    cout << endl;
    cout << "#P\t"
         << "AT\t"
         << "BT\t"
         << "ST\t"
         << "CT\t"
         << "TAT\t"
         << "WT\t"
         << "RT\t"
         << "\n"
         << endl;

    for (int i = 0; i < n; i++)
    {
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" << p[i].start_time << "\t" << p[i].completion_time << "\t" << p[i].turnaround_time << "\t" << p[i].waiting_time << "\t" << p[i].response_time << "\t"
             << "\n"
             << endl;
    }
    cout << "Average Turnaround Time = " << avg_turnaround_time << endl;
    cout << "Average Waiting Time = " << avg_waiting_time << endl;
    cout << "Average Response Time = " << avg_response_time << endl;

    cout << endl;
    cout << "\nGANTT CHART\n";
    for (int i = 0; i < g; ++i)
    {
        cout << "________";
    }
    cout << endl;
    for (int i = 0; i < g; i++)
    {

        cout << "|  "
             << "P" << gantt[i] << "   ";
    }
    cout << "|" << endl;

    for (int i = 0; i < g; ++i)
    {
        cout << "‾‾‾‾‾‾‾‾";
    }
    cout << endl;
    cout << st
         << "\t\t";
    int sum = 0;
    for (int i = 0; i < g; i++)
    {
        sum += gantt_time[i];
        cout << sum + st << "\t\t";
    }
}

// 4
// 2
// 0 5
// 1 3
// 2 4
// 4 1