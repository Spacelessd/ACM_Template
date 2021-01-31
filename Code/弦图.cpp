#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 10005
#define M 1000005
int R[N*2],L[N*2],label[N],visit[N],
	son[N],Link[M*2],next[M*2],l;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n,m,x,y,ans=0,max;
	scanf("%d%d",&n,&m);
	for (int i=1;i<n;++i)R[i]=i+1;R[n]=0;
	for (int i=2;i<=n;++i)L[i]=i-1;L[1]=n+1;
	R[n+1]=1;max=n+1;l=0;
	for (int i=1;i<=m;++i){
		scanf("%d%d",&x,&y);
		Link[++l]=y;next[l]=son[x];son[x]=l;
		Link[++l]=x;next[l]=son[y];son[y]=l;
	}
	for (int i=1;i<=n;++i)label[i]=0;
	for (int i=n;i;--i){
		int x=R[max],cnt=1;visit[x]=1;
		R[L[x]]=R[x];L[R[x]]=L[x];
		for (int p=son[x];p;p=next[p])
			if (visit[Link[p]])++cnt;
			else {
				int j=Link[p],lbl=++label[j]+n+1;
				R[L[j]]=R[j];L[R[j]]=L[j];
				L[R[lbl]]=j;R[j]=R[lbl];L[j]=lbl;R[lbl]=j;
			}
		while (R[max+1])++max;while (max>n+1&&!R[max])--max;
		if (cnt>ans)ans=cnt;
	}
	printf("%d\n",ans);
	system("pause");for (;;);
	return 0;
}


