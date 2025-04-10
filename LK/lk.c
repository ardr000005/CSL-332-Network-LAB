#include<stdio.h>

int main()
{
	int bsize,bucket=0,in,out,rate,n,i=0;
	
	printf("Enter the size of the bucket\n");
	scanf("%d",&bsize);
	
	printf("Enter the rate of the bucket\n");
	scanf("%d",&rate);
	
	printf("Enter the no of entries\n");
	scanf("%d",&n);
	
	while(i!=n)
	{
		printf("Enter the %d token\n",i);
		scanf("%d",&in);
		
		if(in<=(bsize-bucket))
		{
			printf("Took the token %d of size %d\n",i,in);
			bucket+=in;
		}
		else
		{
			out=in-(bsize-bucket);
			printf("Dropped %d size from token %d\n",out,i);
			bucket+=in-out;
		}
		
		if(bucket<rate)
		{
			printf("Flowing out %d rate from bucket but it has %d so dropping all\n",rate,bucket);
			bucket=0;
		}
		else
		{
			printf("Flowing out %d rate from bucket dropped %d from bucket \n",rate,rate);
			bucket=bucket-rate;
		}
		i++;
	}
	
	
	return 0;
}
