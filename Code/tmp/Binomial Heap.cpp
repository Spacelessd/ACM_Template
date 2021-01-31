#include<stdio.h>
#include<stdlib.h>
#define maxn 50
#define duilen 25
int empty[maxn+5];
int empty1;
int duitmp[duilen+2];
class node{
	public:
	int p,next,son,key,d;
};
node dui[maxn+5];
void make()
{
	for (int i=1;i<=maxn;i++)empty[i]=i;
	empty1=maxn;
}

int insnode(int key){
	int x=empty[empty1--];
	a[x].p=a[x].
	return x;
}

void delnode(int x){empty[++empty1]=x;}

class Heap{
	public:
	int head;
	Heap(){head=0;}
};
void insert(Heap &a,int key)
{
	int tmp=newnode(key);
	memset(duitmp,0,sizeof(duitmp));
	for (int x=a.head;x=a[x].next;x++)duitmp;
}

Heap merge(Heap a,Heap b)
{
	int x,i;
	for (x=a.head;x;x=a[x].next)duitmp[a[x].d]=x;
	for (x=b.head;x;x=a[x].next)duitmp[a[x].d]=x;
	Heap tmp;
	for (i=1;i<=duilen;i++)if (duitmp[i])break;
	return tmp;
}

Heap a;

int main()
{
	make();
	srand(time(0));
	for (i=1;i<=maxn;i++)insert(a,i);
	system("pause");
}	



