#include<iostream>
using namespace std;

int n,nf;
int p[50],in[100];
int hit=0,pgfaultcnt=0,hitcnt=0;
int i,j,k;

void intialize()
{
	pgfaultcnt=0;
	for(int k=0;k<nf;k++)
	{
		p[k]=9999;
	}
}

void dispages()
{
	for(int k=0;k<nf;k++)
	{
		if(p[k]!=9999)
		{
			cout<<p[k]<<" ";
		}
	}
}


int isHit(int data)
{
	hit=0;
	for(int j=0;j<nf;j++)
	{
		if(p[j]==data)
		{
			hit=1;
			break;
		}
	}
	return hit;
}
void dispgfault()
{
	cout<<"\nTotal No. of Page Faults: "<<pgfaultcnt;
}
void dispghit()
{
	for(int i=0;i<n;i++)
	{
		hitcnt = n - pgfaultcnt;
	}
	cout<<"\nTotal No. of Page Hits: "<<hitcnt;
}

void fifo()
{
	intialize();
	for(int i=0;i<n;i++)
	{
		cout<<"\nFor "<<in[i]<<": ";
		
		if(isHit(in[i])==0)
		{
		    for(k=0;k<nf-1;k++)
		    {
			    p[k]=p[k+1];
		    }
		p[k]=in[i];
		pgfaultcnt++;
		dispages();
		cout<<" ";	
		}
		else
		{
			cout<<"No Page Fault!";
		}	
	}
	dispgfault();
	dispghit();
	
}
void optimal()
{
	intialize();
	int near[50];
	for(int i=0;i<n;i++)
	{
		cout<<"\nFor "<<in[i]<<": ";
		
		if(isHit(in[i])==0)
		{
			for(int j=0;j<nf;j++)
			{
				int pg=p[j];
				int found=0;
				for(int k=i;k<n;k++)
				{
					if(pg==in[k])
					{
						near[j]=k;
						found=1;
						break;
					}
					else
					{
						found=0;
					}
				}
				if(!found)
				{
					near[j]=9999;
				}
				
			}
			int max=-9999;
			int repindex;
			for(int j=0;j<nf;j++)
			{
				if(near[j]>max)
				{
					max=near[j];
					repindex=j;
				}
			}
			p[repindex]=in[i];
			pgfaultcnt++;
			dispages();
			cout<<" ";
		}
		else{
			cout<<"No Page Fault!";
		}
	}
	dispgfault();
	dispghit();	
}

void LRU()
{
	intialize();
	int least[50];
	
	for(int i=0;i<n;i++)
	{
		cout<<"\nFor "<<in[i]<<": ";
		
		if(isHit(in[i])==0)
		{
			for(int j=0;j<nf;j++)
			{
				int pg=p[j];
				int found=0;
				for(int k=i-1;k>=0;k--)
				{
					if(pg==in[k])
					{
						least[j]=k;
						found=1;
						break;
					}
					else
					{
						found=0;
					}
				}
				if(!found)
				{
					least[j]=-9999;
				}
			}
			int min=9999;
			int repindex;
			for(int j=0;j<nf;j++)
			{
				if(least[j]<min)
				{
					min=least[j];
					repindex=j;
				}
			}
			p[repindex]=in[i];
			pgfaultcnt++;
			dispages();
			cout<<" ";
		}
		else
		{
			cout<<"No Page Fault!";
		}
	}
	dispgfault();
	dispghit();	
}
int main()
{
	cout<<"\nEnter the Length of the referenced string: ";
	cin>>n;
	cout<<"\nEnter the Referenced string elements: ";
	for(int i=0;i<n;i++)
	{
		cin>>in[i];
	}
	cout<<"\nEnter the number of frames: ";
	cin>>nf;
	int choice;
	while(true)
	{
		cout<<"\n||*****Page Replacement Algorithms*****||\n1.FIFO\n2.Optimal\n3.LRU\n4.Exit";
	    cout<<"\nEnter Your Choice: ";
	    cin>>choice;
	    switch(choice)
	    {
	        case 1: fifo();
		            break;
		        
		    case 2:optimal();
		            break;
		       
		    case 3: LRU();
		            break;
	    
	        default:return 0;
		            break;	   	           
	    }
	}
}
/*
Output:

Enter the Length of the referenced string: 22

Enter the Referenced string elements: 7
0
1
2
0
3
0
4
2
3
0
3
0
3
2
1
2
0
1
7
0
1

Enter the number of frames: 3

||*****Page Replacement Algorithms*****||
1.FIFO
2.Optimal
3.LRU
4.Exit
Enter Your Choice: 1

For 7: 7
For 0: 7 0
For 1: 7 0 1
For 2: 0 1 2
For 0: No Page Fault!
For 3: 1 2 3
For 0: 2 3 0
For 4: 3 0 4
For 2: 0 4 2
For 3: 4 2 3
For 0: 2 3 0
For 3: No Page Fault!
For 0: No Page Fault!
For 3: No Page Fault!
For 2: No Page Fault!
For 1: 3 0 1
For 2: 0 1 2
For 0: No Page Fault!
For 1: No Page Fault!
For 7: 1 2 7
For 0: 2 7 0
For 1: 7 0 1
Total No. of Page Faults: 15
Total No. of Page Hits: 7
||*****Page Replacement Algorithms*****||
1.FIFO
2.Optimal
3.LRU
4.Exit
Enter Your Choice: 2

For 7: 7
For 0: 7 0
For 1: 7 0 1
For 2: 2 0 1
For 0: No Page Fault!
For 3: 2 0 3
For 0: No Page Fault!
For 4: 2 4 3
For 2: No Page Fault!
For 3: No Page Fault!
For 0: 2 0 3
For 3: No Page Fault!
For 0: No Page Fault!
For 3: No Page Fault!
For 2: No Page Fault!
For 1: 2 0 1
For 2: No Page Fault!
For 0: No Page Fault!
For 1: No Page Fault!
For 7: 7 0 1
For 0: No Page Fault!
For 1: No Page Fault!
Total No. of Page Faults: 9
Total No. of Page Hits: 13
||*****Page Replacement Algorithms*****||
1.FIFO
2.Optimal
3.LRU
4.Exit
Enter Your Choice: 3

For 7: 7
For 0: 7 0
For 1: 7 0 1
For 2: 2 0 1
For 0: No Page Fault!
For 3: 2 0 3
For 0: No Page Fault!
For 4: 4 0 3
For 2: 4 0 2
For 3: 4 3 2
For 0: 0 3 2
For 3: No Page Fault!
For 0: No Page Fault!
For 3: No Page Fault!
For 2: No Page Fault!
For 1: 1 3 2
For 2: No Page Fault!
For 0: 1 0 2
For 1: No Page Fault!
For 7: 1 0 7
For 0: No Page Fault!
For 1: No Page Fault!
Total No. of Page Faults: 12
Total No. of Page Hits: 10
||*****Page Replacement Algorithms*****||
1.FIFO
2.Optimal
3.LRU
4.Exit
Enter Your Choice: 4

*/
