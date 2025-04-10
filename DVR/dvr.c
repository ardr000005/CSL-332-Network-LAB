#include<stdio.h>

struct
{
	int dist[10],from[10];
}r[10];

void main()
{
	int costmat[30][30],n,i,j,k,min;
	
	printf("Enter the number of nodes\n");
	scanf("%d",&n);
	
	printf("Enter the costmatrix\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&costmat[i][j]);
			costmat[i][i]=0;
			r[i].dist[j]=costmat[i][j];
			r[i].from[j]=j;
		}
	}
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			for(k=0;k<n;k++)
			{
				min=costmat[i][k]+r[k].dist[j];
				if(r[i].dist[j]>min)
				{
					r[i].dist[j]=min;
					 r[i].from[j] = k; 
				}
			}
		}
	}
	printf("\n---------------------------------------------------------------------------------\n");
		for(i=0;i<n;i++)
		{
			printf("Route Table %d\n",i);
			for(j=0;j<n;j++)
			{
				printf("node %d distance %d via %d\n",j,r[i].dist[j],r[i].from[j]);
			}
			printf("\n");
		}
	printf("\n---------------------------------------------------------------------------------\n");
	
	printf("\n---------------------------------------------------------------------------------\n");
	printf("cost matrix \n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("\t %d \t",costmat[i][j]);
		}
		printf("\n");
	}
	printf("\n---------------------------------------------------------------------------------\n");
	
	
}
