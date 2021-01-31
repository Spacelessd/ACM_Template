#include <cstdio>
#include <cstring>
#define MAXX 1010
#define MAXY 1010
int sum;
int n,t;
bool tree[3*MAXX][3*MAXY];
void sub_update(int paroot,int root,int ld,int rd,int y1,int y2)
{
	if(ld == y1 && rd == y2)
	{
		tree[paroot][root] ^= 1;
		return ;
	}
	int mid = (ld + rd)>>1;
	if(y2 <= mid)
		sub_update(paroot,root<<1,ld,mid,y1,y2);
	else if(y1 > mid)
		sub_update(paroot,root<<1|1,mid+1,rd,y1,y2);
	else
	{
		sub_update(paroot,root<<1,ld,mid,y1,mid);
		sub_update(paroot,root<<1|1,mid+1,rd,mid+1,y2);
	}
}

void update(int root,int ld,int rd,int x1,int y1,int x2,int y2)
{
	if(ld == x1 && rd == x2)
	{
		sub_update(root,1,1,n,y1,y2);
		return ;
	}
	int mid = (ld + rd) >>1;
	if(x2 <= mid)
		update(root<<1,ld,mid,x1,y1,x2,y2);
	else if(x1 > mid)
		update(root<<1|1,mid+1,rd,x1,y1,x2,y2);
	else
	{
		update(root<<1,ld,mid,x1,y1,mid,y2);
		update(root<<1|1,mid+1,rd,mid+1,y1,x2,y2);
	}
}

void sub_query(int paroot,int root,int ld,int rd,int y)
{
	sum ^= tree[paroot][root];
	if(ld == rd)  return ;
	int mid = (ld + rd)>>1;
	if(y <= mid)
		sub_query(paroot,root<<1,ld,mid,y);
	else
		sub_query(paroot,root<<1|1,mid+1,rd,y);
}

void query(int root,int ld,int rd,int x,int y)
{
	sub_query(root,1,1,n,y);
	if(ld == rd)  return ;
	int mid = (ld + rd)>>1;
	if(x <= mid)
		query(root<<1,ld,mid,x,y);
	else
		query(root<<1|1,mid+1,rd,x,y);
}

int main()
{
	int totcase,x1,x2,y1,y2;
	char op[5];
	char op2;
	scanf("%d",&totcase);
	while(totcase--)
	{
		scanf("%d%d",&n,&t);
		memset(tree,0,sizeof(tree));
		while(t--)
		{
			//scanf("%s",op);
			getchar();
			op2 = getchar();
			//if(op[0] == 'C')
			if(op2=='C')
			{
				scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
				update(1,1,n,x1,y1,x2,y2);
			}
			else
			{
				scanf("%d%d",&x1,&y1);
				sum = 0;
				query(1,1,n,x1,y1);
				printf("%d\n",sum);
			}
		}
			printf("\n");
	}
	return 0;
}


