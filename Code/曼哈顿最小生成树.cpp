#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
#include<math.h>
#define N 1000005
struct Query{int x,y,id,ans;}Q[N];
bool cmp1(Query x,Query y){return x.x+x.y<y.x+y.y;}
bool cmp2(Query x,Query y){return x.x<y.x;}
int color[N],out[N],sum[N],now;
inline void read(int &x){
	char ch;int bo=0;x=0;
	for (ch=getchar();!(ch>='0' && ch<='9');ch=getchar())if (ch=='-')bo=1;
	for (;ch>='0' && ch<='9';x=x*10+ch-'0',ch=getchar());
	if (bo)x=-x;
}
void insert(int x,int y){
	for (register int j=x;j<=y;++j)if (++sum[color[j]]==2)++now;
}
void del(int x,int y){
	for (register int j=x;j<=y;++j)if (--sum[color[j]]==1)--now;
}
int main()
{
	int t1=clock();
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n,m,c,Lim,x,y;
	scanf("%d%d%d",&n,&c,&m);Lim=(int)sqrt(m)+1;
	for (int i=1;i<=n;++i)read(color[i]);
	for (int i=1;i<=m;++i)read(x),read(y),Q[i]=(Query){x,y,i,0};
	std::sort(Q+1,Q+1+m,cmp1);
	int start=1;
	while (start<=m){
		if (start+Lim<=m)std::sort(Q+start,Q+start+Lim,cmp2);
		else std::sort(Q+start,Q+m+1,cmp2);
		start+=Lim;
	}
	int ans=0;
	for (int i=2;i<=m;++i)ans+=abs(Q[i].x-Q[i-1].x)+abs(Q[i].y-Q[i-1].y);
	//printf("ans=%d\n",ans);
	//printf("init time=%d\n",clock()-t1);
	now=0;Q[0].x=0;Q[0].y=-1;
	for (int i=1;i<=m;++i){
		if (Q[i-1].x<Q[i].x)del(Q[i-1].x,Q[i].x-1);
		if (Q[i].x<Q[i-1].x)insert(Q[i].x,Q[i-1].x-1);
		if (Q[i-1].y<Q[i].y)insert(Q[i-1].y+1,Q[i].y);
		if (Q[i].y<Q[i-1].y)del(Q[i].y+1,Q[i-1].y);
		Q[i].ans=now;
	}
	for (int i=1;i<=m;++i)out[Q[i].id]=Q[i].ans;
	for (int i=1;i<=m;++i)printf("%d\n",out[i]);
	//printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


