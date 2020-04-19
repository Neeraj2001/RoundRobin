#include<stdio.h>
#include<conio.h>

void rrobin(int no,int remt[10],int Cur_t,int AT[10], int BT[10]);

int main()
{
	int p_no,j,no,CT,RemProc,Time_Q;
	int AT[10],BT[10],remt[10];
	int x=1,indicator = 0,WT = 0,TAT = 0;
	printf("Enter number of processes ");
	scanf("%d",&no);
	if(no <=0)
    {
        printf("\nNo of Processes should not be 0\n");
        return 0;
    }
	RemProc = no;

	printf("\nEnter the Arrival Time and Burst Time of the processes\n");
	for(p_no = 0;p_no < no;p_no++)
	{
		printf("\nProcess P%d :-\n",p_no+1);
		printf("Arrival time : ");
		scanf("%d",&AT[p_no]);
		if(AT[p_no]<0)
        {
            printf("\nArrival Time Should not be less than 0 Please Try Again\n");
            return 0;
        }
		printf("Burst time : ");
		scanf("%d",&BT[p_no]);
		if(BT[p_no]<=0)
        {
            printf("Burst Time Should not be less than 0 Please Try Again");
            return 0;
        }
		remt[p_no]=BT[p_no];
	}
	printf("\nThe details of Time Quantum are as follows:\n");
	printf("\tTime Quantum for first round is 6.\n");
	Time_Q=6;
	CT=0;
	for(p_no=0;RemProc!=0;)
	{
		if(remt[p_no]<=Time_Q && remt[p_no]>0)
		{
			CT+=remt[p_no];
			remt[p_no]=0;
			indicator=1;
		}
		else if(remt[p_no]>0)
		{
			remt[p_no]-=Time_Q;
			CT+=Time_Q;
		}
		if(remt[p_no]==0 && indicator==1)
		{
			RemProc--;
			WT+=CT-AT[p_no]-BT[p_no];
			TAT+=CT-AT[p_no];
			indicator=0;

		}
		if(p_no==no-1){
			x++;
			if(x==2){
				p_no=0;
				Time_Q=10;

				printf("\tTime Quantum for Second round is 10. \n");
			}
			else{
				break;
			}
		}
		else if(CT >= AT[p_no+1]){
			p_no++;
		}
		else{
			p_no=0;
		}
	}

	rrobin(no,remt,CT,AT,BT);

	return 0;
}


void rrobin(int no,int remt[10],int Cur_t,int AT[10], int BT[10]){

	float avg_WT,avg_TAT;
    int i,j,n=no,temp,b_time[20],p_no[20],w_time[20],TAT_t[20],total=0,loc;

    printf("\tThird round with Greater burst time.\n");

    for(i=0;i<n;i++)
    {
        b_time[i]=remt[i];
        w_time[i]=Cur_t-AT[i]-b_time[i];
		p_no[i]=i+1;
    }

    for(i=0;i<n;i++)
    {
        loc=i;
        for(j=i+1;j<n;j++)
        {
            if(b_time[j]>b_time[loc]){
            	loc=j;
            }
        }
        temp=b_time[i];
        b_time[i]=b_time[loc];
        b_time[loc]=temp;
        temp=p_no[i];
        p_no[i]=p_no[loc];
        p_no[loc]=temp;
    }

    for(i=1;i<n;i++)
    {
        for(j=0;j<i;j++){
        	w_time[i]+=b_time[j];
        }
        total+=w_time[i];
    }

    avg_WT=(float )total/n;
    total=0;
    printf("\nProcess\t\tBurst Time\t\tWaiting Time\t\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        TAT_t[i]=b_time[i]+w_time[i];
        total=total + TAT_t[i];
        printf("\nP%d\t\t\t%d\t\t\t%d\t\t\t%d",p_no[i],b_time[i],w_time[i],TAT_t[i]);
    }
    avg_TAT=(float)total/n;
    printf("\n\nAverage Waiting Time = %f",avg_WT);
    printf("\nAverage Turnaround Time = %f\n",avg_TAT);
	//by Neeraj

}



