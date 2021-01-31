#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
#include<math.h>
#define N 1000005
struct Query{int x,y;};
Query Q[N];
bool cmp1(Query x,Query y){return x.x+x.y<y.x+y.y;}
bool cmp2(Query x,Query y){return x.x<y.x;}
int n,Lim;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int x,y;
	scanf("%d",&n);Lim=(int)sqrt(n)+1;
	for (int i=1;i<=n;++i)scanf("%d%d",&x,&y),Q[i]=(Query){x,y};
	std::sort(Q+1,Q+1+n,cmp1);
	int start=1;
	while (start<=n){
		if (start+Lim<=n)std::sort(Q+start,Q+start+Lim,cmp2);
		else std::sort(Q+start,Q+n+1,cmp2);
		start+=Lim;
	}
	int ans=0;
	for (int i=2;i<=n;++i)ans+=abs(Q[i].x-Q[i-1].x)+abs(Q[i].y-Q[i-1].y);
	printf("%d\n",ans);
	system("pause");for (;;);
	return 0;
}


