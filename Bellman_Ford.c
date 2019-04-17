#include<stdio.h>
#include<stdlib.h>
#define INF 999

struct edge
{
	int source;
	int destination;
	int weight;
};

int Bellmanford(struct edge *E,int v,int e,int source_vertex)
{
	int *Distance = (int*)malloc(v*(sizeof(int)));
	int i,j,k;
	for(i=0;i<v;i++)
	{
		Distance[i]=INF;
	}
	Distance[source_vertex]=0;
	for(i=1;i<=v-1;i++)
	{
		k=0;
		for(j=0;j<e;j++)
		{
			int u = E[j].source;
			int v = E[j].destination;
			int w = E[j].weight;

			if((Distance[u]!=INF) && ((Distance[u]+w)<Distance[v]))
			{
				Distance[v] = Distance[u] + w;
				k=1;
			}
		}
		if(k==0)
			break;
	}
	if(k==1)
	{
		for(j=0;j<e;j++)
		{
			int u = E[j].source;
			int v = E[j].destination;
			int w = E[j].weight;

			if((Distance[u]!=INF) && ((Distance[u]+w)<Distance[v]))
			{
				printf("\n---Negative Cycle---\n");
				return 0;
			}
		}		
	}
	printf("\nNumber of Iterations are:- %d \n",i);
	printf("Source\tDestination\tDistance\n");
	for( j=0;j<v;j++)
	{
		if(Distance[j]==INF)
			printf("  %d Path Not Possible\n",j+1);
		else
			printf("%d\t%d\t%d\n",source_vertex+1,j+1,Distance[j]);
	}
	return 0;
}

int check(int s,int d,struct edge *E , int v,int i)
{
	if(s<0 || s>=v || d<0 || d>=v)
	{
		printf("\nEnter Proper Source or Destination");	
		return 1;
	}

	for(int j=0;j<i;j++)
	{
		if(E[i].source==s && E[i].destination==d)
		{
			printf("\n Duplicate Egde... Enter new edge");
			return 1;
		}
	}
	return 0;
}

int main()
{
	int e,v;
	do
	{
		printf("\nEnter the number of Edges and Vertices:- ");
		scanf("%d %d",&e,&v);
		if(e<=0 || v<=0 || e>(v*(v-1)))
			printf("\nGraph not Possible\n");
		else
			break;
	}while(1);
	int s,d,w,i;
	struct edge *E = (struct Edge*)malloc(e*(sizeof(struct edge)));

	for(i=0;i<e;i++)
	{
		printf("\n Enter Source , Destination and Weight of an %d Edge :- ",i+1);
		scanf("%d %d %d",&s,&d,&w);
		s--;
		d--;
		if((check(s,d,E,v,i)&&(s==v)))				// checks self loop and multiple edges
		{
			i--;
		}
		else
		{
			E[i].source = s;
			E[i].destination = d;
			E[i].weight = w;
		}
	}
	int source_vertex;
	do
	{
		printf("\nEnter Source Vertex:- ");
		scanf("%d",&source_vertex);
		source_vertex--;
		if(source_vertex < 0 || source_vertex >= v)
		{
			printf("\nSource Vertex Not Possible\n");
		}
		else
			break;
	}while(1);

	Bellmanford(E,v,e,source_vertex);
	return 0;
}
