#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void print(int sol[], int n, int ct)
{
	int i, j;
	printf("\n\n--------------------------------\n\n");
	printf("SOLUTION NO: %d\n", ct);
	for(j = 0; j < 2 * n + 1; j++) printf("-");
	printf("\n");
	for(i = 0; i < n; i++)
	{
		printf("|");
		for(j = 0; j < n; j++)
		{
			if(sol[i] == j) 
				printf("Q|");
			else 
				printf(" |");
		}
		printf("\n");
		for(j = 0; j < 2 * n + 1; j++) 
			printf("-");
		printf("\n");
	}
	printf("\n");
}

int check(int sol[],int row)
{
	int i;
	for(i=0;i<row;i++)
	{
		if(sol[i]==sol[row] || (abs(i-row) == abs(sol[i]-sol[row])))
		return 0;
	}
	return 1;
}

int nrecursive(int row,int limit,int sol[],int type,int *ct)
{
	int j;
	for(j=0;j<limit;j++)
	{
		sol[row]=j;
		if(check(sol,row))
		{
			if(row == limit-1)
			{
				(*ct)++;
				print(sol,limit,*ct);
				if(type==1)
					return 1;
				return 0;
			}
			int ok = nrecursive(row+1,limit,sol,type,ct);
			if(ok)
				return 1;
		}
	}
	return 0;
}

void niterative(int limit,int sol[],int type,int *ct)
{
	int k=0;
	while(k!=-1)
	{
		sol[k]++;
		if(sol[k] < limit)
		{
			if(check(sol,k))
			{
				if(k == limit-1)
				{
					(*ct)++;
					print(sol,limit,*ct);
					if(type==1)
						return;
				}
				else
				{
					k++;
					sol[k]=-1;
				}
			}
		}
		else
			k--;
	}
}

int main()
{
	int n,m,type,ct;
	printf("\nN-QUEEN PROBLEM");
	printf("\nEnter no. of queens: ");
	scanf("%d",&m);
	while(m<=3)
	{
		printf("\n---No. of Queens is less---\n");
		scanf("%d",&m);
	}
	int *solution = (int *)malloc(m*sizeof(int));
	while(1)
	{
		for(int i=0;i<m;i++)
		{
			solution[i] = -1;
		}
		printf("\nSelect one \n1)One Solution \n2)All Solution \n3)Exit\n");
		scanf("%d",&type);
		if(type==3)
			return 0;
		printf("\nSelect one:- \n1)Recursive \n2)Iterative\n");
		scanf("%d",&n);
		ct=0;
		if(n==1)
			nrecursive(0,m,solution,type,&ct);
		else
			niterative(m,solution,type,&ct);
		printf("Total No. of solutions: %d\n",ct);
		printf("---------------------------------------");
	}
}
