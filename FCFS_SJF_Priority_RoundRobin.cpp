#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<math.h>
#include<string.h>
#include<string>
using namespace std;
int pro,i,j,k,arrival[100],burst[100],sec=0,wait,final_time,waiting[100],turn,l=0,n,ans,pos[10],prior[10],minimum,maximum,qt,rm[10],b;
int last_execution[100];  // taking variable in this ways allows us to use them anywhere in the code as they are declared
double throughput,avgwait,avgturn; 
bool ok;
void FCFS()
{
    printf("enter the number of processes: ");
    scanf("%d", &pro);
    printf("enter the arrival time: ");
    for(i=0;i<pro;i++)
    {
        scanf("%d", &arrival[i]);
    }
    printf("enter the burst time: ");
    for(i=0;i<pro;i++)
    {
        scanf("%d", &burst[i]);

    }
    for(i=0;i<pro;i++)
    {
        if(i==0)
        {
            sec=sec+burst[i]; 
        }
        else
        {
            wait=sec-arrival[i];
            sec=sec+burst[i];
            printf("sec %d\n", sec);
            printf("wait %d\n", wait);
            k++;
            waiting[k]=wait;
        }
    }
    wait=0;
    turn=0;
    for(i=0;i<pro;i++)
    {
        wait=wait+waiting[i];
        turn=turn+(burst[i]+waiting[i]);
    }
  avgwait=wait/pro;
  avgturn=turn/pro;
  throughput=(double)pro/(double)sec;
  printf("Average Waiting Time   : %lf\n", avgwait);
  printf("\n");
  printf("Average Turnaround Time: %lf\n", avgturn);
  printf("\n");
  printf("Throughput             : %lf\n", throughput);

  for(i=0;i<pro;i++)
  {
    waiting[i]=0;
  }
  for(i=0;i<pro;i++)
  {
    burst[i]=0;
  }
  for(i=0;i<pro;i++)
  {
    arrival[i]=0;
  }
}

void SJF()
{
    printf("enter the number of processes: ");
    scanf("%d", &pro);
    printf("enter the burst time: ");
    for(i=0;i<pro;i++)
    {
        waiting[i]=0;
        scanf("%d", &burst[i]);

    }
    minimum=burst[0];
    for(j=1;j<pro;j++)
    {
       if(minimum>burst[j])
       {
           minimum=burst[j];
       }
    }

    maximum=burst[0];
    for(j=1;j<pro;j++)
    {
       if(maximum<burst[j])
       {
           maximum=burst[j];
       }
    }

    ans=0;
    l=0;
    k=0;
    for(n=minimum;n<=maximum;n++)
    {
        for(i=0;i<pro;i++)
        {
            if(burst[i]==n)
            {
                waiting[l]=ans;
                l++;
                ans=ans+burst[i];
                pos[k]=i;
                k++;
            }

        }
    }
    turn=0;
    for(i=0;i<l;i++)
    {
        wait=wait+waiting[i];
        printf("wait %d\n", wait);
        turn=turn+(waiting[i]+burst[i]);
        printf("turn %d\n", turn);
    }
    avgwait=(double)wait/(double)pro;
    avgturn=(double)turn/(double)pro;
    throughput=(double)pro/(double)ans;
    printf("average waiting time : %lf\n", avgwait);
    printf("average turnaround time : %lf\n", avgturn);
    printf("throughput : %lf\n", throughput);
}

void prio()
{
    printf("enter the number of processes: ");
    scanf("%d", &pro);
    printf("enter the priority: ");
    for(i=0;i<pro;i++)
    {
        scanf("%d", &prior[i]);
    }
    minimum=prior[0];
    for(j=1;j<(pro-1);j++)
    {
       if(minimum>prior[j])
       {
           minimum=prior[j];
       }
    }

    maximum=prior[0];
    for(j=1;j<(pro-1);j++)
    {
       if(maximum<prior[j])
       {
           maximum=prior[j];
       }
    }

    printf("enter the burst time: ");
    for(i=0;i<pro;i++)
    {
        scanf("%d", &burst[i]);
    }

    int l=0;
    waiting[0]=0;

    for(n=minimum;n<=maximum;n++)
    {
         for(i=0;i<pro;i++)
         {
             if(prior[i]==n)
             {
                 ans=ans+burst[i];
                 k++;
                 pos[k]=i;
                 l++;
                 waiting[l]=ans;
             }

         }
    }
         for(i=0;i<l;i++)
         {
             wait=wait+waiting[i];
             printf("wait %d\n", wait);
             turn=turn+(waiting[i]+burst[i]);
             printf("turn %d\n", turn);
         }
         avgwait=(double)wait/(double)pro;
         avgturn=(double)turn/(double)pro;
         throughput=(double)pro/(double)ans;
         printf("average waiting time : %lf\n", avgwait);
         printf("average turnaround time : %lf\n", avgturn);
         printf("throughput : %lf\n", throughput);
    }


void RR()
{
    printf("enter the number of processes: ");
    scanf("%d", &pro);
    printf("enter the burst time: ");
    for(i=0;i<pro;i++)
    {
        waiting[i]=0;
        last_execution[i]=0;
        scanf("%d", &burst[i]);
    }
    printf("enter the time quantum: \n");
    scanf("%d", &qt);
    b=pro;
    ans=0;
    k=0;
    while(b!=0)
    {
        for(i=0;i<pro;i++)
        {
            if(burst[i]<=qt&&burst[i]!=0)
            {
                waiting[i]+=(ans-last_execution[i]);
                ans=ans+burst[i];
                burst[i]=0;
                b--;
                last_execution[i]=ans;
            }
            else if(burst[i]>qt)
            {
                waiting[i]+=(ans-last_execution[i]);
                ans=ans+qt;
                burst[i]=burst[i]-qt;
                last_execution[i]=ans;
            }
        }
    }
    wait=0;
    turn=0;
    for(i=0;i<pro;i++)
    {
        wait+=waiting[i];
        turn+=last_execution[i];
    }
         avgwait=(double)wait/(double)pro;
         avgturn=(double)turn/(double)pro;
         throughput=(double)pro/(double)ans;
         printf("average waiting time : %lf\n", avgwait);
         printf("average turnaround time : %lf\n", avgturn);
         printf("throughput : %lf\n", throughput);


}

int main()
{
    FCFS();
    SJF();
    prio();
    RR();
}

//done by Mushrit Shabnam
