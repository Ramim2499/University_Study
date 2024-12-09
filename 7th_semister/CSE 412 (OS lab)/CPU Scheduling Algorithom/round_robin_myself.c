// 08/10/2024
#include<stdio.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    int response_time;
    int remaning_burst_time;
};

void findAvarageTime(struct Process process[], int n, int qt) {
    int complete = 0, t=0;
    while(complete != n) {
        for (int i = 0; i < n; i++) {
            if (process[i].arrival_time <= t) {
                if (process[i].burst_time < qt && process[i].burst_time > 0) {
                    t = process[i].burst_time;
                    process[i].completion_time = t;
                    process[i].turn_around_time = process[i].completion_time - t;
                    //you have to implement gantt chart
                    //follow the sudo code given in teh slide
                }
    }



int main() {
    int n;
    int qt;
    printf("Enter the quantum time: ");
    scanf("%d", &qt);
    printf("Enter the number of Process: ");
    scanf("%d", &n);

    struct Process process[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d", i+1);
        scanf("%d %d", &process[i].arrival_time, &process[i].burst_time);
        process[i].id = i+1;
        process[i].completion_time = 0;
        process[i].response_time = 0;
    }
    findAvarageTime(process, n, qt);

}
