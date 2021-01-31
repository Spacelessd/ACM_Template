#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<queue>
#include<algorithm>
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
double d[N];int vis[N],id[N],n,m,Find;
void dfs(int x){
	vis[x]=1;double dist=d[x];
	for (int p=e.son[x];p;p=e.next[p]){
		int y=e.link[p];
		if (dist+e.cost[p]<d[y]){
			if (!vis[y])d[y]=dist+e.cost[p],dfs(y);
			else Find=1;
			if (Find)break;
		}
	}
	vis[x]=0;
}
bool check(double x){
	for (int i=1;i<=e.l;++i)e.cost[i]-=x;
	Find=0; for (int i=1;i<=n;++i)d[i]=0;
	for (int i=1;i<=n;++i){dfs(i);if (Find)return 1;}
	return 0;
}
char str[300005],*p=str;
inline void read(int &x){
	int bo=0;x=0;
	while(*p<'0'||*p>'9')if (*p++=='-')bo=1;
	while(*p>='0'&&*p<='9')x=x*10+*p++-'0';
	if (bo)x=-x;
}
inline void read(double &x){
	int bo=0;x=0;
	while (*p<'0'||*p>'9')if (*p++=='-')bo=1;
	while(*p>='0'&&*p<='9')x=x*10+*p++-'0';
	if (*p=='.'){
		p++;double tmp=1;
		while(*p>='0'&&*p<='9')tmp/=10.0,x+=tmp*(*p++-'0');
	}
	if (bo)x=-x;
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	fread(str,1,300000,stdin);
	int x,y,z;
	read(n);read(m);
	for (int i=1;i<=n;++i)id[i]=i;
	random_shuffle(id+1,id+1+n);
	for (int i=1;i<=m;++i)
		read(x),read(y),read(z),e.addedge(id[x],id[y],z);
	double l=-1e7,r=1e7,mid;
	while (l+1e-9<r){
		if (check(mid=(l+r)/2))r=mid;else l=mid;
		for (int i=1;i<=e.l;++i)e.cost[i]+=mid;
	}
	printf("%.8lf\n",l);
	system("pause");for (;;);
	return 0;
}


