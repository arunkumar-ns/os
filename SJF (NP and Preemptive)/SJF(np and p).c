#include <stdio.h>

int main()
{
    int n, at[20], bt[20], rt[20];
    int ct[20], wt[20], tat[20];
    int completed[20]={0};
    int i, time=0, remain, choice, smallest;
    float avgwt=0,avgtat=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("Arrival Time P%d: ",i+1);
        scanf("%d",&at[i]);

        printf("Burst Time P%d: ",i+1);
        scanf("%d",&bt[i]);

        rt[i]=bt[i];
    }

    printf("\n1. SJF Non Preemptive\n2. SJF Preemptive\nEnter choice: ");
    scanf("%d",&choice);

    remain=n;

    /* ---------------- NON PREEMPTIVE ---------------- */

    if(choice==1)
    {
        while(remain>0)
        {
            smallest=-1;

            for(i=0;i<n;i++)
            {
                if(at[i]<=time && completed[i]==0)
                {
                    if(smallest==-1 || bt[i]<bt[smallest])
                        smallest=i;
                }
            }

            if(smallest==-1)
            {
                time++;
                continue;
            }

            time += bt[smallest];
            ct[smallest]=time;
            completed[smallest]=1;
            remain--;
        }
    }

    /* ---------------- PREEMPTIVE (SRTF) ---------------- */

    else
    {
        while(remain>0)
        {
            smallest=-1;

            for(i=0;i<n;i++)
            {
                if(at[i]<=time && rt[i]>0)
                {
                    if(smallest==-1 || rt[i]<rt[smallest])
                        smallest=i;
                }
            }

            if(smallest==-1)
            {
                time++;
                continue;
            }

            rt[smallest]--;
            time++;

            if(rt[smallest]==0)
            {
                ct[smallest]=time;
                remain--;
            }
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");

    for(i=0;i<n;i++)
    {
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];

        avgwt+=wt[i];
        avgtat+=tat[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],ct[i],wt[i],tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f",avgwt/n);
    printf("\nAverage Turnaround Time = %.2f\n",avgtat/n);

    return 0;
}
