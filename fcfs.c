#include <stdio.h>

int main()
{
    int n, i, j;
    float avgwt = 0, avgct = 0, avgtat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], tat[n], wt[n];

    printf("Enter the arrival time and burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d:\n", i+1);
        printf("Arrival time: ");
        scanf("%d", &at[i]);
        printf("Burst time: ");
        scanf("%d", &bt[i]);
    }

    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (at[j] > at[j+1]) {
                int temp = at[j];
                at[j] = at[j+1];
                at[j+1] = temp;

                temp = bt[j];
                bt[j] = bt[j+1];
                bt[j+1] = temp;
            }
        }
    }

    for (i = 0; i < n; i++) {
        if (i == 0) {
            ct[i] = at[i] + bt[i];
        } else {
            if (at[i] > ct[i-1]) {
                ct[i] = at[i] + bt[i];
            } else {
                ct[i] = ct[i-1] + bt[i];
            }
        }
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avgwt += wt[i];
        avgct += ct[i];
        avgtat += tat[i];
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