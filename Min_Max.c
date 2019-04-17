#include<stdio.h> 
#include<stdlib.h>
struct pair 
{ 
	int min; 
	int max; 
}; 

struct pair getelement(int arr[], int low, int high) 
{
	struct pair mml, mmr;	 
	int mid; 
	
	if (low == high) 
	{
		mml.max = arr[low]; 
		mml.min = arr[low];	 
		return mml; 
	} 
	
	mid = (low + high)/2; 
	mml = getelement(arr, low, mid);
	mmr = getelement(arr, mid+1, high);
	
	if (mml.min < mmr.min) 
		mml.min = mml.min; 
	else
		mml.min = mmr.min;	 

	if (mml.max > mmr.max) 
		mml.max = mml.max; 
	else
		mml.max = mmr.max;	 
	
	return mml;
}

int main() 
{
	int arr_size,i,*arr;

	printf("\nEnter number of elements in an array:-");
  	scanf("%d", &arr_size);

	printf("\nEnter an array:-\n");
  	arr=(int *)malloc(sizeof(int)*arr_size);

	for(i=0;i<arr_size;i++)
	{
 		scanf("%d", &arr[i]);
  	}
	struct pair element = getelement(arr, 0, arr_size-1);
	printf("\nElements in an array:-\n");
	for(i=0;i<arr_size;i++)
		printf("%d ",arr[i]);
	free(arr);
	printf("\n");
	printf("Minimum element is :- %d\n", element.min); 
	printf("Maximum element is :- %d\n", element.max);
	return 0;
} 

