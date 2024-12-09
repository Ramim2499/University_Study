#include<stdio.h>

// Structure to represent a process
struct Process {
    int id;               // Process ID
    int burst_time;        // Burst time of the process
    int arrival_time;      // Arrival time of the process
    int waiting_time;      // Waiting time of the process
    int turnaround_time;   // Turnaround time of the process
    int remaining_time;    // Remaining burst time of the process
};

// Function to find the waiting time for all processes
void findWaitingTime(struct Process proc[], int n, int quantum) {
    int t = 0; // Current time
    int done;

    while (1) {
        done = 1; // Assume all processes are done

        // Traverse all processes one by one
        for (int i = 0; i < n; i++) {
            // Check if the process has arrived and still needs CPU time
            if (proc[i].arrival_time <= t && proc[i].remaining_time > 0) {
                done = 0; // There is a pending process

                if (proc[i].remaining_time > quantum) {
                    t += quantum; // Increase current time by quantum
                    proc[i].remaining_time -= quantum; // Decrease remaining time
                } else {
                    t += proc[i].remaining_time;
                    proc[i].waiting_time = t - proc[i].burst_time - proc[i].arrival_time; // Calculate waiting time
                    proc[i].remaining_time = 0; // Process is finished
                }
            }
        }

        // If all processes are done, exit the loop
        if (done == 1)
            break;
    }
}

// Function to calculate turnaround time
void findTurnAroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++)
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time; // TAT = burst time + waiting time
}

// Function to calculate average waiting and turnaround times
void findAvgTime(struct Process proc[], int n, int quantum) {
    int total_wt = 0, total_tat = 0;

    // Find waiting time for all processes
    findWaitingTime(proc, n, quantum);

    // Find turnaround time for all processes
    findTurnAroundTime(proc, n);

    // Display processes along with all details
    printf("\nProcesses    Arrival Time    Burst Time    Waiting Time    Turn Around Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
        printf(" %d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].arrival_time, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time);
    }

    printf("\nAverage waiting time = %.2f", (float)total_wt / n);
    printf("\nAverage turn around time = %.2f", (float)total_tat / n);
}

// Driver code
int main() {
    int n, quantum;

    // Input time quantum
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    // Get the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Create an array of processes
    struct Process proc[n];


    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time);
        proc[i].remaining_time = proc[i].burst_time;  // Initialize remaining time
    }



    // Calculate average time and display process info
    findAvgTime(proc, n, quantum);

    return 0;
}
