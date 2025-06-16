#include<stdio.h>

void main()
{
    int count, j, n, time, remain, flag = 0, q;
    int wt = 0, tat = 0;
    
    printf("Enter Total Number of Processes:\t ");
    scanf("%d", &n);
    
    int at[n], bt[n], rt[n];
    remain = n; // Remaining processes

    for(count = 0; count < n; count++)
    {
        printf("Enter Arrival Time and Burst Time for Process %d: ", count + 1);
        scanf("%d", &at[count]);
        scanf("%d", &bt[count]);
        rt[count] = bt[count]; // Remaining time is initialized as burst time
    }

    printf("Enter Time Quantum:\t");
    scanf("%d", &q);

    printf("\n\nProcess\t\tTurnaround Time\t\tWaiting Time\n");

    for(time = 0, count = 0; remain != 0;)
    {
        if(rt[count] <= q && rt[count] > 0) 
        {
            time += rt[count]; // Increase time by remaining time
            rt[count] = 0;
            flag = 1;
        }
        else if(rt[count] > 0) 
        {
            rt[count] -= q;
            time += q;
        }

        if(rt[count] == 0 && flag == 1)
        {
            remain--; // One process is completed
            printf("%d\t\t%d\t\t\t%d\n", count + 1, time - at[count], time - at[count] - bt[count]);
            
            wt += time - at[count] - bt[count]; // Waiting time
            tat += time - at[count]; // Turnaround time
            flag = 0;
        }

        if(count == n - 1) 
            count = 0; // Reset count if we reach the last process
        else if(at[count + 1] <= time) 
            count++; // Move to next process if it has arrived
        else 
            count = 0; // Otherwise reset to 0
    }

    printf("\nAverage Waiting Time = %f\n", wt * 1.0 / n);
    printf("Average Turnaround Time = %f\n", tat * 1.0 / n);
}
