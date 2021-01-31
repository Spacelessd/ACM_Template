#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=15,M=60005,inf=1<<30;
struct point{
	int x,y;
	point(int _x=0,int _y=0):x(_x),y(_y){}
}p[N],ansp;int p1;
char map[N][N];bool visit[N][N];
int dx[]={1,-1,0,0},dy[]={0,0,1,-1};
int f[M],pw3[N],n,best,id[M];
int dfs(int x,int y){
	int res=1;visit[x][y]=1;
	for (int i=0;i<4;++i){
		int x1=x+dx[i],y1=y+dy[i];
		if (x1&&y1&&x1<=n&&y1<=n&&map[x1][y1]==map[x][y]
			&&!visit[x1][y1])res+=dfs(x1,y1);
	}
	return res;
}
int get_score(){
	memset(visit,0,sizeof(visit));
	int s1=0,s2=0;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)if (!visit[i][j]){
			if (map[i][j]=='0')s1=max(s1,dfs(i,j));
			else s2=max(s2,dfs(i,j));
		}
	return s1-s2;
}
int MinSearch(int,int,int,int);
int MaxSearch(int state,int dep,int now,int alpha){
	if (state==0)return get_score();
	if (f[now]!=-inf)return f[now];
	int ans=-inf,st=state;
	while (st){
		int lowbit=st&-st,pos=id[lowbit];
		map[p[pos].x][p[pos].y]='0';
		int tmp=MinSearch(state-lowbit,dep+1,now+pw3[pos],ans);
		map[p[pos].x][p[pos].y]='.';
		ans=max(ans,tmp);
		if (tmp>=alpha)return tmp;
		if (dep==0)
			if (ans>best||ans==best&&(p[pos].x<ansp.x||
				p[pos].x==ansp.x&&p[pos].y<ansp.y))best=ans,ansp=p[pos];
		st-=lowbit;
	}
	return f[now]=ans;
}
int MinSearch(int state,int dep,int now,int beta){
	if (state==0)return get_score();
	if (f[now]!=-inf)return f[now];
	int ans=inf,st=state;
	while (st){
		int lowbit=st&-st,pos=id[lowbit];
		map[p[pos].x][p[pos].y]='1';
		int tmp=MaxSearch(state-lowbit,dep+1,now+2*pw3[pos],ans);
		map[p[pos].x][p[pos].y]='.';
		ans=min(ans,tmp);
		if (tmp<=beta)return tmp;
		st-=lowbit;
	}
	return f[now]=ans;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	pw3[0]=1;for (int i=1;i<N;++i)pw3[i]=pw3[i-1]*3;
	for (int i=0;i<N;++i)id[1<<i]=i;
	while (scanf("%d",&n)!=EOF&&n){
		int s1=0,s2=0;p1=0;
		for (int i=1;i<=n;++i){
			scanf("%s",map[i]+1);
			for (int j=1;j<=n;++j)
				if (map[i][j]=='.')p[p1++]=point(i,j);
				else if (map[i][j]=='0')++s1;
				else ++s2;
		}
		if (s1>s2)
			for (int i=1;i<=n;++i)
				for (int j=1;j<=n;++j)
					if (map[i][j]=='0')map[i][j]='1';else map[i][j]='0';
		best=-inf;
		for (int i=0;i<pw3[p1];++i)f[i]=-inf;
		MaxSearch((1<<p1)-1,0,0,inf);
		printf("(%d,%d) %d\n",ansp.x-1,ansp.y-1,best);
	}
	system("pause");for (;;);
	return 0;
}


