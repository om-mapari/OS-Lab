#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string.h>
#include <queue>
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

class slouation
{
    int n;
    struct process p[100];
    //Avarage
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    //totel
    int total_turnaround_time;
    int total_waiting_time;
    int total_response_time;
    //supportive
    int burst_remaining[100]; // for sjf np and rra
    int is_completed[100];
    //for rra

public:
    slouation()
    {
        total_turnaround_time = 0;
        total_waiting_time = 0;
        total_response_time = 0;
        memset(is_completed, 0, sizeof(is_completed));
    }
    void Reset()
    {
        avg_turnaround_time = 0;
        avg_waiting_time = 0;
        avg_response_time = 0;
        total_turnaround_time = 0;
        total_waiting_time = 0;
        total_response_time = 0;
        memset(is_completed, 0, sizeof(is_completed));
    }
    void InputProcessData()
    {
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
    }
    void PrintProcessData()
    {
        cout << "\nPRINTING PROCESSES DATA....\n";
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
    }
    void NonPreemptiveSJF()
    {
        int current_time = 0;
        int completed = 0;
        while (completed != n)
        {
            int idS = -1;      //selected process id
            int mn = 10000001; //minimum
            for (int i = 0; i < n; i++)
            {
                //which process has arrivied in ready queue && p completed or not
                if (p[i].arrival_time <= current_time && is_completed[i] == 0)
                {
                    if (p[i].burst_time < mn)
                    { // finding minimum burst time and set idS
                        mn = p[i].burst_time;
                        idS = i;
                    }
                    if (p[i].burst_time == mn)
                    { // if two process having same burst time then check arrival time & set idS
                        if (p[i].arrival_time < p[idS].arrival_time)
                        {
                            mn = p[i].burst_time;
                            idS = i;
                        }
                    }
                }
            } //from all the process in readyQueue the process with minimum burst time be selected

            if (idS != -1) // idS process selected
            {
                p[idS].start_time = current_time;
                p[idS].completion_time = p[idS].start_time + p[idS].burst_time;
                p[idS].turnaround_time = p[idS].completion_time - p[idS].arrival_time;
                p[idS].waiting_time = p[idS].turnaround_time - p[idS].burst_time;
                p[idS].response_time = p[idS].start_time - p[idS].arrival_time;

                total_turnaround_time += p[idS].turnaround_time;
                total_waiting_time += p[idS].waiting_time;
                total_response_time += p[idS].response_time;

                is_completed[idS] = 1;
                completed++;
                current_time = p[idS].completion_time;
            }
            else //if the process not in ready Queue i will increment current time
            {
                current_time++;
            }
        }

        avg_turnaround_time = (float)total_turnaround_time / n;
        avg_waiting_time = (float)total_waiting_time / n;
        avg_response_time = (float)total_response_time / n;

        cout << endl
             << endl;
    }
    // TAT = CT - AT
    // WT = TAT - BT
    // RT = ST - AT
    void PreemptiveSJF()
    {
        int current_time = 0;
        int completed = 0;

        while (completed != n)
        {
            int idS = -1;      //selected process id
            int mn = 10000000; //minimum
            for (int i = 0; i < n; i++)
            {
                //which process has arrivied in ready queue && p completed or not
                if (p[i].arrival_time <= current_time && is_completed[i] == 0)
                {
                    if (burst_remaining[i] < mn)
                    { // finding minimum burst time and set idS
                        mn = burst_remaining[i];
                        idS = i;
                    }
                    if (burst_remaining[i] == mn)
                    { // if two process having same burst time then check arrival time & set idS
                        if (p[i].arrival_time < p[idS].arrival_time)
                        {
                            mn = burst_remaining[i];
                            idS = i;
                        }
                    }
                }
            } //from all the process in readyQueue which process has minimum burst time

            if (idS != -1) // idS process selected
            {
                if (burst_remaining[idS] == p[idS].burst_time)
                {
                    p[idS].start_time = current_time;
                }
                burst_remaining[idS] -= 1;
                current_time++;

                if (burst_remaining[idS] == 0) // process completed
                {
                    p[idS].completion_time = current_time;
                    p[idS].turnaround_time = p[idS].completion_time - p[idS].arrival_time;
                    p[idS].waiting_time = p[idS].turnaround_time - p[idS].burst_time;
                    p[idS].response_time = p[idS].start_time - p[idS].arrival_time;

                    total_turnaround_time += p[idS].turnaround_time;
                    total_waiting_time += p[idS].waiting_time;
                    total_response_time += p[idS].response_time;

                    is_completed[idS] = 1;
                    completed++;
                }
            }
            else //if the process not in ready Queue i will increment current time
            {
                current_time++;
            }
        }

        avg_turnaround_time = (float)total_turnaround_time / n;
        avg_waiting_time = (float)total_waiting_time / n;
        avg_response_time = (float)total_response_time / n;

        cout << endl
             << endl;
    }
    // bool compare1(process p1, process p2)
    // {
    //     return p1.arrival_time < p2.arrival_time;
    // }
    void bubbleSort()
    {
        process temp;

        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < (n - 1 - i); j++)
            {
                if (p[j].arrival_time < p[j + 1].arrival_time)
                {
                    temp = p[j];
                    p[j] = p[j + 1];
                    p[j + 1] = temp;
                }
            }
        }
    }
    // bool compare2(process p1, process p2)
    // {
    //     return p1.pid < p2.pid;
    // }
    void RoundRobin()
    {
        int tq;
        cout << "Enter time quantum: ";
        cin >> tq;

        bubbleSort();
        int idx;
        queue<int> q;
        int current_time = 0;
        q.push(0);
        int completed = 0;
        int mark[100];
        memset(mark, 0, sizeof(mark));
        mark[0] = 1;

        while (completed != n)
        {
            idx = q.front();
            q.pop();

            if (burst_remaining[idx] == p[idx].burst_time)
            {
                p[idx].start_time = max(current_time, p[idx].arrival_time);

                current_time = p[idx].start_time;
            }

            if (burst_remaining[idx] - tq > 0)
            {
                burst_remaining[idx] -= tq;
                current_time += tq;
            }
            else
            {
                current_time += burst_remaining[idx];
                burst_remaining[idx] = 0;
                completed++;

                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
                total_response_time += p[idx].response_time;
            }

            for (int i = 1; i < n; i++)
            {
                if (burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0)
                {
                    q.push(i);
                    mark[i] = 1;
                }
            }
            if (burst_remaining[idx] > 0)
            {
                q.push(idx);
            }

            if (q.empty())
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

        // sort(p, p + n, compare2);
    }
};

int main()
{
    // init_code();
    slouation s;

    // s.InputProcessData();
    // s.NonPreemptiveSJF();
    // s.PreemptiveSJF();
    // cout << "\n\n\n";
    // s.PrintProcessData();

    while (true)
    {
        cout << "\n==========MENU FOR PROCESSES==========\n";
        cout << "Enter choice No.\n1.INPUT DATA\n2.NON_PREEMPTIVE_SJF\n3.PREEMPTIVE_SJF\n4.ROUND_ROBIN\n5.PRINT_PROCESS_DATA\n6.STOP\n";
        int c1;
        cout << "Enter Choice:";
        cin >> c1;
        if (c1 == 1)
        {
            s.InputProcessData();
        }
        else if (c1 == 2)
        {
            s.Reset();
            s.NonPreemptiveSJF();
        }
        else if (c1 == 3)
        {
            s.Reset();
            s.PreemptiveSJF();
        }
        else if (c1 == 4)
        {
            s.Reset();
            s.RoundRobin();
        }
        else if (c1 == 5)
        {
            s.PrintProcessData();
        }
        else if (c1 == 6)
        {
            cout << "\nYou are out of .\n";
            break;
        }
        else
        {
            cout << "\n!!!Enter a Valid choice!!!\n";
        }
    }

    return 0;
}

// 5
// 2 6
// 5 2
// 1 8
// 0 3
// 4 4

// 1
// 5
// 2 6
// 5 2
// 1 8
// 0 3
// 4 4
// 3
// 4
// 5

// 1
// 5
// 2 6
// 5 2
// 1 8
// 0 3
// 4 4
// 2
// 4
// 3
// 4
// 5

// TAT = CT - AT
// WT = TAT - BT
// RT = ST - AT