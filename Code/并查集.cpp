#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 10000005
int f[N],rank[N];
int find(int x){
	if (f[x]==x)return x;
	else return f[x]=find(f[x]);
}
inline void link(int x,int y){f[find(x)]=find(y);}
inline void _link(int x,int y){
	int f1=find(x),f2=find(y);
	if (f1==f2)return;
	if (rank[f1]>rank[f2])f[f2]=f1;
		else if (rank[f1]<rank[f2])f[f1]=f2;
			else f[f2]=f1,++rank[f1];
}
inline int Rand(){return (rand()<<15)+rand();}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n;scanf("%d",&n);
	{
		int t1=clock();
		for (int i=1;i<=n;++i)f[i]=i;
		for (int i=1;i<=n;++i)rank[i]=0;
		for (int i=1;i<=n;++i){
			int x=Rand()%n+1,y=Rand()%n+1;
			_link(x,y); 
		}
		printf("without rank:time=%d\n",clock()-t1);
	}
	{
		int t1=clock();
		for (int i=1;i<=n;++i)f[i]=i;
		for (int i=1;i<=n;++i)rank[i]=0;
		for (int i=1;i<=n;++i){
			int x=Rand()%n+1,y=Rand()%n+1;
			link(x,y); 
		}
		printf("with rank:time=%d\n",clock()-t1);
	}
	system("pause");for (;;);
	return 0;
}


