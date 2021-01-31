#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#define RT return
#define N 1000005
int cnt[N],key[N],ran[N],L[N],R[N],size[N],root=0;
inline void zig(int x,int y)
{
	L[y]=R[x]; R[x]=y;
	size[y]=size[L[y]]+size[R[y]]+1;
	size[x]=size[L[x]]+size[R[x]]+1;
}
inline void zag(int x,int y)
{	
	R[y]=L[x]; L[x]=y;
	size[y]=size[L[y]]+size[R[y]]+1;
	size[x]=size[L[x]]+size[R[x]]+1;
}
inline void ins(int x,int &y)
{
	if (!y) {ran[x]=rand(); L[x]=R[x]=0; size[x]=1; y=x; RT;}
	if (key[x]<=key[y]){
		ins(x,L[y]); size[y]++;
		if (ran[x]<ran[y]) zig(x,y),y=x;
		}
	else{
		ins(x,R[y]); size[y]++;
		if (ran[x]<ran[y]) zag(x,y),y=x;
		}
}
double t1;
int main()
{
	srand(time(0));
	int n,x=1;
	t1=clock();
	for (int i=1;i<=500000;i++) key[i]=rand()*32768+rand();
	for (int i=1;i<=500000;i++) ins(i,root);
	printf("%.4f\n",(clock()-t1)/CLOCKS_PER_SEC);
	system("pause");
}
