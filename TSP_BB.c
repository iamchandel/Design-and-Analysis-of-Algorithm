//5
//20 30 10 11
//15 16 4 2
//3 5 2 4
//19 6 18 3
//16 4 7 16
//5
//10 8 9 7
//10 10 5 6
//8 10 8 9
//9 5 8 6
//7 6 9 6
//
#include<stdio.h>
#include<malloc.h>
#define INFI 999999

struct node
{
	int cost;
	int **m;
	struct node *par;
	int k;
	int n;
};
typedef struct node node;

int **allocate(int x)
{
	int i,** a;
	a=(int **)calloc(x,sizeof(int *));
	for(i=0;i<x;i++)
		a[i]=(int *)calloc(x,sizeof(int));
	return a;
}

struct upper
{
	int value;
	node *data;
};
typedef struct upper upper;

void input(int **m, int n)
{
	int i,j;
	printf("\n\t ENTER MATRIX \n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n ;j++)
		{
			if(j != i)
			{
				printf(" enter m[%d][%d] : ",i+1,j+1);
				scanf("%d",&m[i][j]);
				if(m[i][j] <= 0)
				{
					printf("\n weight can't be negative or zero ");
					j-- ;
				}
			}
		}
		m[i][i] = INFI;
	}
}
void display(int **m, int n)
{
    int i,j;
    printf("\n\n");
    for (i=0 ; i<n ; i++) 
	{
        for (j=0 ; j<n ; j++) 
        {
        	if(m[i][j] == INFI)
        		printf(" NULL ");
        	else
        		printf("%5d ", m[i][j]);
		}
        printf("\n");
    }
    printf("\n");
}
void copy(int **m, int **n, int x)
{
	int i,j;
	for(i=0;i<x;i++)
		for(j=0;j<x;j++)
			m[i][j] = n[i][j];
}
int rcm(int **m, int n)
{
	int i,j,min, cnt = 0;
	for(i=0 ; i<n; i++)
	{
		min = INFI;
		for(j=0 ; j<n ; j++)
		{
			if(min> m[i][j])
				min = m[i][j];
		}
		if(min != INFI && min != 0)
		{
			cnt += min;
			for(j=0 ; j<n ; j++)
			{
				if(m[i][j] != INFI)
					m[i][j] = m[i][j] - min;
			}
		}
	}
	for(j=0 ; j<n ; j++)
	{
		min = INFI;
		for(i=0 ; i<n; i++)
		{
			if(min> m[i][j])
				min = m[i][j];
		}
		if(min != INFI && min != 0)
		{
			cnt += min;
			for(i=0 ; i<n; i++)
			{
				if(m[i][j] != INFI)
					m[i][j] = m[i][j] - min;
			}
		}
	}
	return cnt;
}

node * init_head(int n)
{
	node* p = (node*)malloc(sizeof(node));
	p->par = NULL;
	p->m = allocate(n);
	input(p->m,n);
	p->n = 0;
	p->k = 1;
	
	printf("\n\n\n Entered matrix ");
	display(p->m,n);
	
	int t = rcm(p->m,n);
	p->cost = t;
	printf("\n\n reduced cost matrix of ROOT node");
	printf("\n\t\t C^(.) : %d",p->cost);
	printf("\n\t\t upper : INFINITY ");	
	display(p->m,n);
	return p;
}
node * init_node(int n, int m, node *par, int *l, upper *up)
{
	int t,i;
	node* p = (node*)malloc(sizeof(node));
	p->par = par;
	p->m = allocate(n);
	p->n = m;
	
	copy(p->m,par->m,n);
	for(i=0;i<n;i++)
	{
		p->m[i][p->n] = INFI;
		p->m[par->n][i]  = INFI;
	}
	p->m[p->n][0] = INFI;
	
	t = rcm(p->m,n);
	p->k = par->k + 1;
	p->cost = t + par->cost + par->m[par->n][p->n];
	
	printf("\n\n reduced cost matrix %d",*l);
	printf("\n\t\t reduced cost : %d",t);
	if(up->value == INFI)
		printf("\n\t\t upper : INFINITY ");
	else
		printf("\n\t\t upper : %d",up->value);
	printf("\n\t\t total cost : %d + %d + %d ",par->cost,par->m[par->n][p->n],t);
	printf("\n\t\t C^(%d) : %d ",*l,p->cost);
	display(p->m,n);
	return p;
}

struct list
{
	node *data;
	struct list *next;
};
typedef struct list list;

void freeNode(list *n, int x)
{
	int i;
	for(i=0;i<x;i++)
		free(n->data->m[i]);
	free(n->data->m);
	free(n->data);
	free(n);
}
void memoryfree(list *head, int x)
{
	list *p,*q;
	p = head;
	while(p != NULL)
	{
		q = p;
		p = p->next;
		freeNode(q,x);
	}
}
void insert(list *head, list *temp, int n, int *x, upper *up)
{
	int i;
	if(temp->data->k == n)
	{
		if(temp->data->cost < up->value)
		{
			up->value = temp->data->cost;
			up->data = temp->data;
		}
	}	
	list *p = head;
	while(p->next != NULL && (temp->data->cost >= p->next->data->cost))
		p = p->next;

	temp->next = p->next;
	p->next = temp;
}
void expand(list *head, int n, int *x, int *l, upper *up)
{
	int i,j,pos=head->data->k;
	node *p = head->data;
	for(i = pos-1; i>0 ;i--)
	{
		x[i]=p->n;
		p=p->par;
	}
	printf(" \n\n");
	for(i=0;i<pos;i++)
		printf(" %d ----> ",x[i]);
	printf(" %d ",x[0]);
	
	list *p1=head;
	for(i=1 ; i<n ; i++)
	{
		for(j=1;j<pos;j++)
		{
			if(i == x[j])
				break;
		}
		if(j==pos)
		{
			list *temp = (list*)malloc(sizeof(list));
			temp->next = NULL;
			*l = *l + 1;
			temp->data = init_node(n,i,head->data,l,up);
			insert(head,temp,n,x,up);
		}
	}
}
void tsp()
{
	int n,i,j,num,t,l=0,s=1;
	int *x;

	printf("\n Enter the square matrix order : ");
	scanf("%d",&n);
	if(n < 2)
	{
		printf("\n nodes can't be less than 2 ");
		return ;
	}
	upper *up = (upper*)malloc(sizeof(upper));
	up->value = INFI;
	up->data = NULL;
	
	list *head,*dead,*dd;
	head = (list*)malloc(sizeof(list));
	head->next = NULL;

	x = (int*)calloc(n,sizeof(int));
	
	head->data = init_head(n);
	
	dead = dd = head;
	while(head != NULL)
	{
		if(head->data->cost <= up->value)
		{
			printf("\n\n\n Enode number : %d",s++);
			expand(head,n,x,&l,up);
			head = head->next;
			dd->next = head;
		}	
		else
		{
			list *t;
			t = head;
			head = head->next;
			printf("\n\n %d node is killed before exploring because %d(estimated cost) > %d(upper)",++l,t->data->cost,up->value);
			freeNode(t,n);
		}
	}
	dd->next = NULL;
	memoryfree(dead,n);
	
	printf(" \n\n final cost of root node : %d",up->value);
	printf(" \n final solution vector \n");
	int pos = n;
	node *q = up->data;
	for(i = pos-1; i>0 ;i--)
	{
		x[i] = q->n;
		q = q->par;
	}
	for(i=0;i<n;i++)
		printf(" %d ----> ",x[i]);
	printf(" %d ",x[0]);
	free(x);
	free(up);
}
int main()
{
	tsp();
	return 0;
}
