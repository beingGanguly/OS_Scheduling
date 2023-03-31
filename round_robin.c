#include <stdio.h>

int main()
{
    int n, i, j;
    float avgwt = 0, avgct = 0, avgtat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], tat[n], wt[n], is_completed[n];

    printf("Enter the arrival time and burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d:\n", i+1);
        printf("Arrival time: ");
        scanf("%d", &at[i]);
        printf("Burst time: ");
        scanf("%d", &bt[i]);
        is_completed[i] = 0;
    }

    int time = 0, min_bt, min_bt_index;
    while (1) {
        min_bt = 99999;
        min_bt_index = -1;

        for (i = 0; i < n; i++) {
            if (at[i] <= time && is_completed[i] == 0) {
                if (bt[i] < min_bt) {
                    min_bt = bt[i];
                    min_bt_index = i;
                }
            }
        }

        if (min_bt_index == -1) {
            time++;
            continue;
        }

        ct[min_bt_index] = time + bt[min_bt_index];
        tat[min_bt_index] = ct[min_bt_index] - at[min_bt_index];
        wt[min_bt_index] = tat[min_bt_index] - bt[min_bt_index];
        avgwt += wt[min_bt_index];
        avgtat += tat[min_bt_index];
        avgct += ct[min_bt_index];

        is_completed[min_bt_index] = 1;
        time = ct[min_bt_index];

        int completed = 1;
        for (i = 0; i < n; i++) {
            if (is_completed[i] == 0) {
                completed = 0;
                break;
            }
        }

        if (completed == 1) {
            break;
        }
    }

    avgwt /= n;
    avgct /= n;
    avgtat /= n;

    printf("\nProcess\tArrival time\tBurst time\tCompletion time\tTurn-around time\tWaiting time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    printf("\nAverage waiting time = %.2f\n", avgwt);
    printf("Average completion time = %.2f\n", avgct);
    printf("Average turn-around time = %.2f\n", avgtat);

    return 0;
}