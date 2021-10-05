#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string.h>
using namespace std;

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

class soluation
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
    int burst_remaining[100];
    int is_completed[100];

public:
    soluation()
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
            int idS = -1;
            int mn = 10000001;
            for (int i = 0; i < n; i++)
            {

                if (p[i].arrival_time <= current_time && is_completed[i] == 0)
                {
                    if (p[i].burst_time < mn)
                    {
                        mn = p[i].burst_time;
                        idS = i;
                    }
                    if (p[i].burst_time == mn)
                    {
                        if (p[i].arrival_time < p[idS].arrival_time)
                        {
                            mn = p[i].burst_time;
                            idS = i;
                        }
                    }
                }
            }

            if (idS != -1)
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
            else
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

    void PreemptiveSJF()
    {
        int current_time = 0;
        int completed = 0;

        while (completed != n)
        {
            int idS = -1;
            int mn = 10000000;
            for (int i = 0; i < n; i++)
            {

                if (p[i].arrival_time <= current_time && is_completed[i] == 0)
                {
                    if (burst_remaining[i] < mn)
                    {
                        mn = burst_remaining[i];
                        idS = i;
                    }
                    if (burst_remaining[i] == mn)
                    {
                        if (p[i].arrival_time < p[idS].arrival_time)
                        {
                            mn = burst_remaining[i];
                            idS = i;
                        }
                    }
                }
            }

            if (idS != -1)
            {
                if (burst_remaining[idS] == p[idS].burst_time)
                {
                    p[idS].start_time = current_time;
                }
                burst_remaining[idS] -= 1;
                current_time++;

                if (burst_remaining[idS] == 0)
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
            else
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
};

int main()
{
    // init_code();
    soluation s;

    // s.InputProcessData();
    // s.NonPreemptiveSJF();
    // s.PreemptiveSJF();
    // cout << "\n\n\n";
    // s.PrintProcessData();

    while (true)
    {
        cout << "\n==========MENU FOR PROCESSES==========\n";
        cout << "Enter choice No.\n1.INPUT DATA\n2.NON_PREEMPTIVE_SJF\n3.PREEMPTIVE_SJF\n4.PRINT_PROCESS_DATA\n5.STOP\n";
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
            s.PrintProcessData();
        }
        else if (c1 == 5)
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
// TAT = CT - AT
// WT = TAT - BT
// RT = ST - AT

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
