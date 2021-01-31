#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<deque>
using namespace std;
#define N 55
#define oo (1<<30)
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
char str[N][N];
int d[N*N],n,m;
struct Edge{
	int link[N*N*4],next[N*N*4],cost[N*N*4],son[N*N],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y,int z){
		link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
	}
}e;
inline int get(int x,int y){return (x-1)*m+y;}
int spfa(int S){  //for edge cost=0 or 1
	for (int i=1;i<=n*m;++i)d[i]=oo;
	static deque<int> Q;Q.clear();
	d[S]=0;Q.push_back(S);
	while (!Q.empty()){
		int x=Q.front();Q.pop_front();
		for (int i=e.son[x];i;i=e.next[i]){
			int y=e.link[i];
			if (d[x]+e.cost[i]<d[y]){
				d[y]=d[x]+e.cost[i];
				if (!e.cost[i])Q.push_front(y);
				else Q.push_back(y);
			}
		}
	}
	int ans=0;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			if (str[i][j]=='B')ans=max(ans,d[get(i,j)]);
	return ans+1;
}
int main()
{
	int t1=clock();
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i)
		scanf("%s",str[i]+1);
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			for (int k=0;k<4;++k){
				int xx=i+dx[k],yy=j+dy[k];
				if (xx<1||xx>n||yy<1||yy>m)continue;
				if (str[i][j]!=str[xx][yy])
					e.addedge(get(i,j),get(xx,yy),1);
				else
					e.addedge(get(i,j),get(xx,yy),0);
			}
	int ans=oo;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			ans=min(ans,spfa(get(i,j)));
	printf("%d\n",ans);
	//printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


