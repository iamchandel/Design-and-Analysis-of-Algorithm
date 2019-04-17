#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct jobs
{
	int id;
	int size;
	char name[20];
	double rt;
};

void swap(int* a,int* b) 
{ 
	int t;
	t = *a; 
	*a = *b; 
	*b = t; 
}

int heapify(int arr[], int n, int i,struct jobs *jb) 
{ 
	int largest = i; 
	int l = 2*i + 1; 
	int r = 2*i + 2; 
	int cnt=0;

	if (l < n && jb[arr[l]].size > jb[arr[largest]].size) 
		largest = l; cnt++;
  
	if (r < n && jb[arr[r]].size > jb[arr[largest]].size) 
		largest = r; cnt++;
  
	if (largest != i) 
	{ 
		swap(&arr[i], &arr[largest]); 
		heapify(arr, n, largest,jb); 
	} 
	return cnt;
}

void heapSort(int arr[], int n,struct jobs *jb) 
{
	int cnt=0;
	for (int i = n / 2 - 1; i >= 0; i--)   /*Re-arrange array*/
		cnt += heapify(arr, n, i,jb); 
  
	for (int i=n-1; i>=0; i--) 			/*One by one extract element*/
	{
		swap(&arr[0], &arr[i]); 		/*Move current root to end*/
		cnt += heapify(arr, i, 0,jb); 	
	} 
}

void displayresult(struct jobs *jb,double ans,int n)
{
	printf("\n");
	printf("ID\tName\tSize\tRetrieval Time\n");
	for(int i=0;i<n;i++)
	{
		printf("%d\t%s\t%d\t%f\n",jb[i].id,jb[i].name,jb[i].size,jb[i].rt);
	}
	printf("\n");
	printf("                      --------------\n");
	printf("Minimum Retrieval Time : %f ",ans);
	printf("\n                    --------------");
	printf("\n");
}

void optimalstorage(struct jobs *jb,int n,int t)
{
	int *x,i,j;
	int sum=0;
	double ans;

	x = (int *)malloc(n*sizeof(int));

	for(i=0;i<n;i++)
	{
    	x[i] = jb[i].id;
	}

	heapSort(x,n,jb);
	
	int row = t,col=0;

	if(n%t == 0)
	{
		col = n/t;
	}
	else
	{
		col = (n/t)+1;
	}

	int *mat;
	mat = (int *)malloc(row*col*sizeof(int));

	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			*(mat + i*col +j)=-1;
		}
	}

	int k =0;
	for(i=0;;i++)
	{
		for(j=0;j<row;j++)
		{
			*(mat + (j)*col +i) = x[k];
			if(i==0)
			{
				jb[x[k]].rt = jb[x[k]].size;
				ans += jb[x[k]].rt;
			}
			else
			{	
				jb[x[k]].rt = jb[x[k]].size + jb[*(mat + (j)*col +i-1)].rt;
				ans += jb[x[k]].rt;
			}
			k++;
			if(k == n)
			{
				break;
			}
		}
		if(k == n)
		{
			break;
		}
	}

	printf("\nTape Storage\n");
	for(i=0;i<row;i++)
	{
		printf("\nTape:%d  : ",i) ;
		for(j=0;j<col;j++)
		{
			printf("%d  ",*(mat + i*col +j));
		}
		printf("\n");
	}
	displayresult(jb,ans,n);
	free(x);
	return ;
}

int main()
{
	int n,i,j,k,t;
	printf("Enter No. of Tapes:");
	scanf("%d",&t);
	printf("Enter No. of Jobs:");
	scanf("%d",&n);	
    
	struct jobs *jb;
	jb = (struct jobs *)malloc(n*sizeof(struct jobs));

	for(i=0;i<n;i++)
	{
		printf("Enter Job Size of %d :",i);
		scanf("%d",&jb[i].size);
		if(jb[i].size<=0)
		{
			printf("\nSize of job is Zero enter again....\n");
			i--;
		}
		else
		{
			jb[i].id = i;
			printf("Enter Job Name of %d :",i);
			scanf (" %[^\t\n]s",jb[i].name);
		}
	}
	
	if(n<=t)
	{
		int ans=0;
		for(i=0;i<n;i++)
		{
			jb[i].rt = jb[i].size;
			ans += jb[i].size;
		}
		printf("\nTape Storage\n");
		for(i=0;i<n;i++)
		{
			printf("\nTape %d :%d",i,jb[i].id);	
		}
		displayresult(jb,ans,n);
	}
	else
	{
		optimalstorage(jb,n,t);
	}
	free(jb);
	return 0;
}
