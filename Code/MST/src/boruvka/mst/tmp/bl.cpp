#include <cstring>
#include <cstdio>
#include <ctime>
#include <algorithm>
using namespace std;

const int maxn=5000010;
int n,m;
int a[maxn],f[maxn];

struct node
{
	int x,y,z;
}p[maxn];

bool cmp(const node &i, const node &j)
{
	return i.z<j.z;
}

int findset(int x)
{
	if (f[x]==x) return x;
	return f[x]=findset(f[x]);
}
inline void read(int &x){
	char ch;int bo=0;x=0;
	for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
	for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
	if (ch=='.'){
		double tmp=1;
		for (ch=getchar();ch>='0' && ch<='9';tmp/=10.0,x+=tmp*(ch-'0'),ch=getchar());
	}
	if (bo)x=-x;
}
int main()
{
	freopen("road9.in","r",stdin);
	//freopen("bl.out","w",stdout);
	double t1=clock();
	scanf("%d%d",&n,&m);
	for (int i=1; i<=n; i++) 
		read(a[i]);
	for (int i=1; i<=m; i++) 
	{
		read(p[i].x); read(p[i].y); read(p[i].z);
		p[i].z=p[i].z-a[p[i].x]-a[p[i].y];
	}
	
	sort(p+1,p+m+1,cmp);
	
	int ans=0;
	for (int i=1; i<=n; i++) f[i]=i;
	for (int i=1; i<=m; i++)
	{
		int f1=findset(f[p[i].x]), f2=findset(f[p[i].y]);
		if (f1==f2) continue;
		ans+=p[i].z; f[f1]=f2;
	}
	printf("%d\n",ans);
	printf("%.6lf\n",clock()-t1);
	for (;;);
	return 0;
}
