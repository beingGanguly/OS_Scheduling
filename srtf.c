#include <stdio.h>

#define MAX_PROCESSES 100

// Process structure
typedef struct {
    int pid;  // process id
    int burst_time;  // burst time
    int remaining_time;  // remaining burst time
    int arrival_time;  // arrival time
    int waiting_time;  // waiting time
    int turnaround_time;  // turnaround time
} Process;

int main() {
    int n;  // number of processes
    int t;  // current time
    int done = 0;  // number of processes completed
    int smallest;  // index of process with smallest remaining time
    float avg_waiting_time = 0;  // average waiting time
    float avg_turnaround_time = 0;  // average turnaround time
    float avg_completion_time = 0; //average completion time
    
    // Read input
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    Process processes[MAX_PROCESSES];
    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time and burst time of process %d: ", i+1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].pid = i+1;
    }
    
    // Schedule processes
    t = 0;
    while (done < n) {
        smallest = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= t && processes[i].remaining_time > 0) {
                if (smallest == -1 || processes[i].remaining_time < processes[smallest].remaining_time) {
                    smallest = i;
                }
            }
        }
        
        if (smallest == -1) {
            t++;
        } else {
            processes[smallest].remaining_time--;
            if (processes[smallest].remaining_time == 0) {
                done++;
                processes[smallest].turnaround_time = t+1 - processes[smallest].arrival_time;
                processes[smallest].waiting_time = processes[smallest].turnaround_time - processes[smallest].burst_time;
                avg_turnaround_time += processes[smallest].turnaround_time;
                avg_waiting_time += processes[smallest].waiting_time;
                avg_completion_time = avg_turnaround_time+avg_waiting_time;
            }
            t++;
        }
    }
    
    // Print results
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
    printf("Average waiting time: %f\n", avg_waiting_time/n);
    printf("Average turnaround time: %f\n", avg_turnaround_time/n);
    printf("Average turnaround time: %f\n", avg_completion_time/n);
    
    return 0;
}
