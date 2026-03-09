#include<stdio.h>

int main()
{
    int n,at[20],bt[20],pr[20],rt[20];
    int ct[20],wt[20],tat[20];
    int completed[20]={0};
    int i,time=0,remain,choice,highest;
    float avgwt=0,avgtat=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("Arrival Time P%d: ",i+1);
        scanf("%d",&at[i]);

        printf("Burst Time P%d: ",i+1);
        scanf("%d",&bt[i]);

        printf("Priority P%d: ",i+1);
        scanf("%d",&pr[i]);

        rt[i]=bt[i];
    }

    printf("\n1. Priority Non Preemptive\n2. Priority Preemptive\nEnter choice: ");
    scanf("%d",&choice);

    remain=n;

    /* ----------- NON PREEMPTIVE ----------- */

    if(choice==1)
    {
        while(remain>0)
        {
            highest=-1;

            for(i=0;i<n;i++)
            {
                if(at[i]<=time && completed[i]==0)
                {
                    if(highest==-1 || pr[i]<pr[highest])
                        highest=i;
                }
            }

            if(highest==-1)
            {
                time++;
                continue;
            }

            time += bt[highest];
            ct[highest]=time;

            completed[highest]=1;
            remain--;
        }
    }

    /* ----------- PREEMPTIVE ----------- */

    else
    {
        while(remain>0)
        {
            highest=-1;

            for(i=0;i<n;i++)
            {
                if(at[i]<=time && rt[i]>0)
                {
                    if(highest==-1 || pr[i]<pr[highest])
                        highest=i;
                }
            }

            if(highest==-1)
            {
                time++;
                continue;
            }

            rt[highest]--;
            time++;

            if(rt[highest]==0)
            {
                ct[highest]=time;
                remain--;
            }
        }
    }

    printf("\nProcess\tAT\tBT\tPR\tCT\tWT\tTAT\n");

    for(i=0;i<n;i++)
    {
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];

        avgwt+=wt[i];
        avgtat+=tat[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],pr[i],ct[i],wt[i],tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f",avgwt/n);
    printf("\nAverage Turnaround Time = %.2f\n",avgtat/n);

    return 0;
}
