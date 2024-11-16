#include<stdio.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    int response_time;
};

void findAverageTime(struct Process process[], int n) {
    float total_waiting_time = 0, total_turnaround_time = 0, total_response_time = 0;

    int complete = 0, t = 0;
    while(complete != n) {
        int found = 0;
        for(int i = 0; i < n; i++) {
            if(process[i].arrival_time <= t) {
                one:
                process[i].completion_time = process[i].burst_time + t;
                t += process[i].burst_time;
                process[i].turn_around_time = process[i].completion_time - process[i].arrival_time;
                process[i].waiting_time = process[i].turn_around_time - process[i].burst_time;
                complete++;
            }
            else {
                t = process[i].arrival_time;
                goto one;
            }
        }
    }
    // Display completion time, turnaround time, waiting time, and response time for each process
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               process[i].id,
               process[i].arrival_time,
               process[i].burst_time,
               process[i].completion_time,
               process[i].turn_around_time,
               process[i].waiting_time,
               process[i].response_time);
    }
    //printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    //printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
    //printf("Average Response Time: %.2f\n", total_response_time / n);
}
int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process process[n];
    for(int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i+1);
        scanf("%d %d", &process[i].arrival_time, &process[i].burst_time);
        process[i].id = i+1;
        process[i].completion_time = 0;
        process[i].response_time = 0;
    }
    findAverageTime(process, n);
}