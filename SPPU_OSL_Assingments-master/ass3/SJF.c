#include<stdio.h>
#include<stdbool.h>

struct process{
    int pid,at,bt,tat,wt,rt,ct;
    bool is_completed;

};

int main(){

    int i,n;
    float avg_wt,avg_tat = 0;
    printf("Enter number of processes : ");
    scanf("%d",&n);

    struct process p[n];

    for(int i = 0;i<n;i++){

        printf("Enter process id:");
        scanf("%d",&p[i].pid);

        printf("Enter Arrival time :");
        scanf("%d",&p[i].at);
        
        printf("Enter Burst time:");
        scanf("%d",&p[i].bt);
        printf("\n");

        p[i].is_completed = false;
        p[i].rt = p[i].bt;
        
    }

    sjf(p,n);

    printf("\n\nsr.no\tPID\tAT\tBT\tCT\tTAT\tWT");
    for(int i = 0;i<n;i++){
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;

        printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d",(i+1),p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);

    }

    avg_wt /= n;
    avg_tat /= n;
    printf("Average waiting time = %fms\n",&avg_wt);
    printf("Average Turnaround time = %fms\n",&avg_tat);
    return 0;

}

void sjf(struct process p[],int n){

    int curr_time = 0,completed = 0,index,i,temp;

    while(completed != n){
       temp = 9999;
       bool found = false;

       for(int i = 0;i<n;i++){
        if(!p[i].is_completed && p[i].at < curr_time && p[i].rt < temp){
            temp = p[i].rt;
            index = i;
        }
       }
       p[index].rt -= 1;

       if(p[index].rt == 0){
        printf("Completed process %d at time %d",p[index].pid,(curr_time + 1));
        p[index].is_completed = true;
        p[index].ct = curr_time +1;
        p[index].tat = p[index].ct - p[index].at;
        p[index].wt = p[index].tat - p[index].bt;
        completed += 1;
       }
       curr_time += 1;

    }
}