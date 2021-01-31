#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<queue>
using namespace std;
#define N 3005
struct Edge{
	#define Mx 20005
	int link[Mx],next[Mx],son[N],l;
	double cost[Mx];
	void clear(){l=0;memset(son,0,sizeof(son));}
	Edge(){clear();}
	void addedge(int x,int y,double z){
		link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
	}
};
Edge e;
double d[N];int q[N],inq[N],cnt[N],n,m;
bool spfa(){
	int h=0,t=n;
	for (int i=1;i<=n;++i)d[i]=0;
	for (int i=1;i<=n;++i)inq[i]=1;
	for (int i=1;i<=n;++i)cnt[i]=1;
	for (int i=1;i<=n;++i)q[i]=i;
	while (h!=t){
		h=h<n?h+1:1;int i=q[h];inq[i]=0;
		for (int p=e.son[i];p;p=e.next[p]){
			int j=e.link[p];
			if (d[i]+e.cost[p]<d[j]){
				d[j]=d[i]+e.cost[p];
				if (!inq[j]){
					if (++cnt[j]>15)return 1;
					t=t<n?t+1:1,q[t]=j,inq[j]=1;
				}
			}
		}
	}
	return 0;
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int x,y;double z;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;++i)
		scanf("%d%d%lf",&x,&y,&z),e.addedge(x,y,z);
	double l=-1e7,r=1e7,mid;
	while (l+1e-9<r){
		mid=(l+r)/2;
		for (int i=1;i<=e.l;++i)e.cost[i]-=mid;
		bool can=spfa();
		for (int i=1;i<=e.l;++i)e.cost[i]+=mid;
		if (can)r=mid;else l=mid;
	}
	printf("%.8lf\n",l);
	system("pause");for (;;);
	return 0;
}


