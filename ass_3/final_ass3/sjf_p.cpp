#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;
void init_code()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
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

int main()
{
    init_code();
    int n;
    struct process p[100];


    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;

    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;

    int burst_remaining[100];
    int is_completed[100];
    memset(is_completed, 0, sizeof(is_completed));

    cout << setprecision(2) << fixed;

    cout << "Enter the number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << "Enter arrival time of process " << i + 1 << ": ";
        cin >> p[i].arrival_time;
        cout << "Enter burst time of process " << i + 1 << ": ";
        cin >> p[i].burst_time;
        p[i].pid = i + 1;
        burst_remaining[i] = p[i].burst_time;
        cout << endl;
    }

    int current_time = 0;
    int completed = 0;

    int v[100];
    int vcount = 0;
    while (completed != n)
    {
        int idx = -1;
        int mn = 10000000;
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival_time <= current_time && is_completed[i] == 0)
            {
                if (burst_remaining[i] < mn)
                {
                    mn = burst_remaining[i];
                    idx = i;
                }
                if (burst_remaining[i] == mn)
                {
                    if (p[i].arrival_time < p[idx].arrival_time)
                    {
                        mn = burst_remaining[i];
                        idx = i;

                    }
                }


            }
        }

        if (idx != -1)
        {

            v[vcount++] = p[idx].pid;

            if (burst_remaining[idx] == p[idx].burst_time)
            {
                p[idx].start_time = current_time;
            }
            burst_remaining[idx] -= 1;
            current_time++;

            if (burst_remaining[idx] == 0)
            {
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

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

    cout << endl
         << endl;

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
    int c = 1;
    int time[50];
    int ti = 0;
    cout << endl;
    cout << "\nGANTT CHART\n";
    for (int i = 0; i < n * 1.5; ++i)
    {
        cout << "_______";
    }
    cout << endl;
    for (int i = 0; i < vcount; i++)
    {

        if (v[i] != v[i + 1])
        {

            cout << "|  " << "P" << v[i] << "   ";
            time[ti++] = c;
            c = 1;
        }
        else
        {
            c++;
        }
    }
    cout << "|" << endl;

    for (int i = 0; i < n * 1.5; ++i)
    {
        cout << "?????????????????????";
    }
    cout << "\n";
    cout << "0" << "\t\t";
    int sum = 0;
    for (int i = 0; i < ti; i++)
    {
        sum += time[i];
        cout << sum << "\t\t";
    }
}

// 5
// 2 6
// 5 2
// 1 8
// 0 3
// 4 4

// 4
// 0 5
// 1 3
// 2 4
// 4 1