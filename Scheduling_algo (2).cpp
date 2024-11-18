//============================================================================
// Name        : Scheduling_algo.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
	Practical No 1:Implement CPU scheduling algorithm
	Write a program to simulate CPU Scheduling Algorithms: FCFS, SJF (Preemptive),
	Priority(Non-Preemptive) and Round Robin (Preemptive).
 */

#include <bits/stdc++.h>
using namespace std;

class Jobs
{
    string name;
    int arrival_t;
    int burst_t;
    int completion_t;
    int turnaround_t;
    int waiting_t;
    int priority_t;

public:

    Jobs()
    {
        name = "";
        arrival_t = 0;
        burst_t = 0;
        completion_t = 0;
        turnaround_t = 0;
        waiting_t = 0;
        priority_t = 0;
    }

    void createJob()
    {
        cout << "Enter name of process : ";
        cin >> name;
        cout << "Arrival Time : ";
        cin >> arrival_t;
        cout << "Burst Time : ";
        cin >> burst_t;
    }

    friend class Scheduler;
};

class Scheduler
{
    Jobs * jobs;
    int np;

public:
    Scheduler()
    {
    	np = 0;
        cout << "Enter number of Processes : ";
        cin >> np;
        jobs = new Jobs[np];

        for (int i = 0; i < np; i++)
        {
            jobs[i].createJob();
            cout << endl;
        }
    }

    void show_jobs(Jobs jobs[], int np)
    {
        cout << "Name\tAT\tBT\tCT\tTAT\tWT" << endl;
        for (int i = 0; i < np; i++)
        {
            cout << jobs[i].name << "\t" << jobs[i].arrival_t << "\t" << jobs[i].burst_t << "\t" << jobs[i].completion_t << "\t" << jobs[i].turnaround_t << "\t" << jobs[i].waiting_t << endl;
        }
    }

    void show_average(float avg_tat, float avg_wt)
    {
        cout << "\nAverage Turn around Time : " << avg_tat << "\nAverage Waiting Time : " << avg_wt << endl;
        cout<<"\n-------------------------------------------------------------------------------------------------\n";
    }

    static bool arrival_comp(Jobs a, Jobs b)
    {
    	return a.arrival_t < b.arrival_t;
    }

    static bool burst_comp(Jobs a, Jobs b)
    {
      	return a.burst_t < b.burst_t;
    }

    static bool priority_comp(Jobs a, Jobs b)
    {
        return a.priority_t < b.priority_t;
    }

    void FCFS()
    {

        Jobs * v = new Jobs[np];
        for (int i = 0; i < np; i++)
            v[i] = jobs[i];

        sort(v,v+np,arrival_comp);

        int ct = 0;
        Jobs gantt[np];
        for (int i = 0; i < np; i++)
        {

            gantt[i] = v[i];
            if(ct >= gantt[i].arrival_t){
            	ct += gantt[i].burst_t;
            }
            else{
            	ct = gantt[i].arrival_t + gantt[i].burst_t;
            }


            gantt[i].completion_t = ct;
            gantt[i].turnaround_t = gantt[i].completion_t - gantt[i].arrival_t;
            gantt[i].waiting_t = gantt[i].turnaround_t - gantt[i].burst_t;
        }

        float avg_tat = 0, avg_wt = 0;
        for (int i = 0; i < np; i++)
        {
            avg_tat += gantt[i].turnaround_t;
            avg_wt += gantt[i].waiting_t;
        }
        avg_tat = avg_tat / np;
        avg_wt = avg_wt / np;

        cout<<"\n-------------------------------FCFS-------------------------------\n\n";
        show_jobs(gantt, np);
        show_average(avg_tat, avg_wt);
    }

    void Priority()
    {
    	cout<<"\n-------------------------------PRIORITY-------------------------------\n\n";
        Jobs *v = new Jobs[np];
        int totalTime = 0;

        for (int i = 0; i < np; i++)
        {
            v[i] = jobs[i];
            cout << "Enter Priority of " << v[i].name << " : ";
            totalTime += v[i].burst_t;
            cin >> v[i].priority_t;
        }

        sort(v, v + np, arrival_comp);

        int aj = 0;
        int timeStamp = v[0].arrival_t;;
        vector<Jobs> ReadyQ;
        Jobs *gantt = new Jobs[np];
        int ja = 0;

        while (1)
        {
            while (aj < np && v[aj].arrival_t <= timeStamp)
            {
                ReadyQ.push_back(v[aj]);
                aj++;
            }

            sort(ReadyQ.begin(), ReadyQ.end(), priority_comp);

            if (ReadyQ.size() > 0)
            {
                gantt[ja] = ReadyQ[0];
                timeStamp += gantt[ja].burst_t;
                gantt[ja].completion_t = timeStamp;
                gantt[ja].turnaround_t = gantt[ja].completion_t - gantt[ja].arrival_t;
                gantt[ja].waiting_t = gantt[ja].turnaround_t - gantt[ja].burst_t;
                ja++;
                ReadyQ.erase(ReadyQ.begin());
            }
            else
            {
            	timeStamp++;
            }

            if(ReadyQ.size()==0 && aj ==np){
                break;
            }
        }

        float avg_tat = 0, avg_wt = 0;

        for (int i = 0; i < np; i++)
        {
        	avg_tat += gantt[i].turnaround_t;
            avg_wt += gantt[i].waiting_t;
        }

        avg_tat = avg_tat / np;
        avg_wt = avg_wt / np;


        show_jobs(gantt, np);
        show_average(avg_tat, avg_wt);
    }

    void SJF()
    {
        Jobs *v = new Jobs[np];
        for (int i = 0; i < np; i++)
        {
            v[i] = jobs[i];
        }

        sort(v, v + np, arrival_comp);

        vector<string> gantt;
        int aj = 0;
        int timeStamp = 0;
        vector<Jobs> readyQ;

        while (1)
        {
            while (aj < np && v[aj].arrival_t <= timeStamp)
            {
                readyQ.push_back(v[aj]);
                aj++;
            }

            sort(readyQ.begin(), readyQ.end(), burst_comp);

            if (readyQ.size() > 0)
            {
                gantt.push_back(readyQ[0].name);
                readyQ[0].burst_t--;

                if (readyQ[0].burst_t == 0)
                {
                    for (int i = 0; i < np; i++)
                    {
                        if (jobs[i].name == readyQ[0].name)
                        {
                            jobs[i].completion_t = timeStamp + 1;
                            jobs[i].turnaround_t = jobs[i].completion_t - jobs[i].arrival_t;
                            jobs[i].waiting_t = jobs[i].turnaround_t - jobs[i].burst_t;
                        }
                    }

                    readyQ.erase(readyQ.begin());
                }
            }
            if(readyQ.size()==0 && aj ==np){
            	break;
            }
            timeStamp++;
        }

        float avg_tat = 0, avg_wt = 0;

        for (int i = 0; i < np; i++)
        {
            avg_tat += jobs[i].turnaround_t;
            avg_wt += jobs[i].waiting_t;
        }

        avg_tat = avg_tat / np;
        avg_wt = avg_wt / np;

        cout<<"\n-------------------------------SJC-------------------------------\n\n";
        show_jobs(jobs, np);
        show_average(avg_tat, avg_wt);

    }

    void RoundRobin()
    {
        int interval;
        cout << "Enter the Time Quantum : ";
        cin >> interval;

        Jobs *v = new Jobs[np];
        int totalTime = 0;

        for (int i = 0; i < np; i++)
        {
            v[i] = jobs[i];
            totalTime += v[i].burst_t;
        }

        sort(v, v + np, arrival_comp);

        vector<string> gantt;
        int aj = 0;
        int timeStamp = v[0].arrival_t;
        int added_burst = interval;

        queue<Jobs> readyQ;
        Jobs added_job;
        added_job.burst_t = 0;

        readyQ.push(v[aj]);
        aj++;

        while (1)
        {
            if (readyQ.size() > 0)
            {
                added_job = readyQ.front();
                readyQ.pop();
                gantt.push_back(added_job.name);

                if (added_job.burst_t > interval)
                {
                    added_job.burst_t = added_job.burst_t - interval;
                    added_burst = interval;
                }
                else
                {
                    added_burst = added_job.burst_t;
                    added_job.burst_t = 0;
                }

                if (added_job.burst_t == 0)
                {
                    for (int i = 0; i < np; i++)
                    {
                        if (jobs[i].name == added_job.name)
                        {
                            jobs[i].completion_t = timeStamp + added_burst;
                            jobs[i].turnaround_t = jobs[i].completion_t - jobs[i].arrival_t;
                            jobs[i].waiting_t = jobs[i].turnaround_t - jobs[i].burst_t;
                        }
                    }
                }

            }
            timeStamp += added_burst;


            while (aj < np && v[aj].arrival_t <= timeStamp)
            {
            	readyQ.push(v[aj]);
                aj++;
            }

            if (added_job.burst_t > 0)
            {
                readyQ.push(added_job);
            }

            if(readyQ.size()==0 && aj !=np){

            	readyQ.push(v[aj]);
            	timeStamp = v[aj].arrival_t;
            	aj++;
            }
            if(readyQ.size()==0 && aj ==np){
            	break;
            }

        }

        float avg_tat = 0, avg_wt = 0;

        for (int i = 0; i < np; i++)
        {
            avg_tat += jobs[i].turnaround_t;
            avg_wt += jobs[i].waiting_t;
        }

        avg_tat = avg_tat / np;
        avg_wt = avg_wt / np;

        cout<<"\n-------------------------------RR-------------------------------\n\n";
        show_jobs(jobs, np);
        show_average(avg_tat, avg_wt);
    }
};

int main()
{
    Scheduler schedule;

    schedule.FCFS();
    schedule.SJF();
    schedule.RoundRobin();
    schedule.Priority();
}
