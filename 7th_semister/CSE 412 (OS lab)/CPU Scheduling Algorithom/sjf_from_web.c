#include <stdio.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    int response_time;
};

void findAverageTime(struct Process proc[], int n) {
    float total_waiting_time = 0, total_turnaround_time = 0, total_response_time = 0;

    // Sort processes according to their arrival time
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].arrival_time > proc[j].arrival_time) {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
    //finding of which arrived process has the least amount of burst time
    int complete = 0, t = 0, min_index = 0;
    while (complete != n) {
        int found = 0;
        int min_burst = 9999; // A large value

        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= t && proc[i].completion_time == 0) {
                if (proc[i].burst_time < min_burst) {
                    min_burst = proc[i].burst_time;
                    min_index = i;
                    found = 1;
                }
            }
        }

        if (found) {
            // Update response time
            if (proc[min_index].response_time == 0) {
                proc[min_index].response_time = t - proc[min_index].arrival_time; // Calculate response time
            }

            // Process the found process
            t += proc[min_index].burst_time;
            proc[min_index].completion_time = t;
            proc[min_index].turn_around_time = proc[min_index].completion_time - proc[min_index].arrival_time;
            proc[min_index].waiting_time = proc[min_index].turn_around_time - proc[min_index].burst_time;

            total_waiting_time += proc[min_index].waiting_time;
            total_turnaround_time += proc[min_index].turn_around_time;
            total_response_time += proc[min_index].response_time;

            complete++;
        } else {
            // If no process is found, increase time
            t++;
        }
    }

    // Display completion time, turnaround time, waiting time, and response time for each process
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].id,
               proc[i].arrival_time,
               proc[i].burst_time,
               proc[i].completion_time,
               proc[i].turn_around_time,
               proc[i].waiting_time,
               proc[i].response_time);
    }

    // Calculating average times
    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
    printf("Average Response Time: %.2f\n", total_response_time / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        proc[i].id = i + 1;
        scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time);
        proc[i].completion_time = 0; // Initialize completion time
        proc[i].response_time = 0;    // Initialize response time
    }

    findAverageTime(proc, n);

    return 0;
}
