#include <stdio.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    int response_time;
    int first_response_time;
};

void findAverageTime(struct Process proc[], int n) {
    int complete = 0, t = 0, minimum_index = -1;
    int min_remaining_time = 9999;
    float total_waiting_time = 0, total_turnaround_time = 0, total_response_time = 0;

    while (complete != n) {
        // Find process with the shortest remaining time among the arrived processes
        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= t && proc[i].remaining_time > 0 && proc[i].remaining_time < min_remaining_time) {
                min_remaining_time = proc[i].remaining_time;
                minimum_index = i;
            }
        }

        if (minimum_index != -1) {
            // If first response time hasn't been set, set it
            if (proc[minimum_index].first_response_time == -1) {
                proc[minimum_index].first_response_time = t;
            }

            // Process the selected process
            proc[minimum_index].remaining_time--;
            t++;

            // Check if the process is completed
            if (proc[minimum_index].remaining_time == 0) {
                complete++;
                proc[minimum_index].completion_time = t;
                proc[minimum_index].turn_around_time = proc[minimum_index].completion_time - proc[minimum_index].arrival_time;
                proc[minimum_index].waiting_time = proc[minimum_index].turn_around_time - proc[minimum_index].burst_time;

                total_waiting_time += proc[minimum_index].waiting_time;
                total_turnaround_time += proc[minimum_index].turn_around_time;
                total_response_time += (proc[minimum_index].first_response_time - proc[minimum_index].arrival_time);
            }
        } else {
            t++; // Idle CPU
        }

        min_remaining_time = 9999; // Reset for the next iteration
        minimum_index = -1; // Reset for the next iteration
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
               proc[i].first_response_time - proc[i].arrival_time); // Calculate response time
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
        proc[i].remaining_time = proc[i].burst_time; // Initialize remaining time
        proc[i].completion_time = 0; // Initialize completion time
        proc[i].first_response_time = -1; // Initialize first response time
    }

    findAverageTime(proc, n);

    return 0;
}
