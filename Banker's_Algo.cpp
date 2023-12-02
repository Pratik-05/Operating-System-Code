#include<iostream>

using namespace std;

int main()
{
	int n;
	int m;
	int i,j,k;
	cout<<"Enter the number processes that you want: ";
	cin>>n;
	cout<<"Enter the number of resources that you want: ";
	cin>>m;
	
	cout<<"\n Allocation matrix is: "<<endl;
	int allocation[n][m];
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			cout<<"Enter the resource "<<j+1<<" for the process "<<i<<" th allocated:  ";
			cin>>allocation[i][j];
		}
	}
	cout<<"\nMaximum matrix is: "<<endl;
	int max[n][m];
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			cout<<"Enter the max resource "<<j+1<<" for the process "<<i<<" th allocated:  ";
			cin>>max[i][j];
			if(max[i][j]<allocation[i][j])
			{
				cout<<"Please enter maximum resource --->"<<allocation[i][j]<<": ";
				cin>>max[i][j];
			}
		}
	}
	
	cout<<"\n Available Array is: "<<endl;
	int avail[m];
	for(i=0;i<m;i++)
	{
		cout<<"Enter the available instance for resources "<<i+1<<" ";
		cin>>avail[i];

	}
	cout<<"\n ||---Available Array is: ---||"<<endl;
	for(i=0;i<m;i++)
	{
		cout<<avail[i]<<" ";

	}
	
	int f[n];
	for(k=0;k<n;k++)
	{
		f[k]=0;
		
	}
	
	int need[n][m];
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			need[i][j]=max[i][j]-allocation[i][j];
		}
	}
	int y=0;
	int ans[n],ind=0;
	for(k=0;k<n;k++)
	{
		for(i=0;i<n;i++)
		{
			if(f[i]==0)
			{
				int flag=0;
				for(j=0;j<m;j++)
				{
					if(need[i][j]>avail[j])
					{
						flag=1;
						break;		
					}
				}
				if(flag==0)
				{
					ans[ind++]=i;
					for(y=0;y<m;y++)
					{
						avail[y]+=allocation[i][y];
                        f[i] = 1;
					}
				}
			}
		}
	}
	
	int flag=1;
	for(int i=0;i<n;i++)
	{
		if(f[i]==0)
		{
			flag=0;
			cout<<"The given sequence is not safe!";
			break;
		}
	}
	
	cout<<"\n ||---Allocation matrix is: ---||"<<endl;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			cout<<allocation[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"\n ||---Maximum matrix is: ---||"<<endl;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			cout<<max[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"\n ||---Final Available Array is: ---||"<<endl;
	for(i=0;i<m;i++)
	{
		cout<<avail[i]<<" ";

	}
	
	cout<<"\n ||---The BANKER'S ALGORITHM IS : ---||"<<endl;
	if(flag==1)
	{
		cout<<"*****Following is the Safe Sequence: *****"<<endl;
		for(i=0;i<n-1;i++)
		{
			cout<<"P"<<ans[i]<<"---->";
		}
		cout<<"P"<<ans[n-1]<<endl;
	}
	
	return 0;	
}
