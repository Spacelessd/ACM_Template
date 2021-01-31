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

int main()
{
	freopen("road9.in","r",stdin);
	freopen("bl.out","w",stdout);
	double t1=clock();
	scanf("%d%d",&n,&m);
	for (int i=1; i<=n; i++) scanf("%d",&a[i]);
	for (int i=1; i<=m; i++) 
	{
		scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].z);
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
	//for (;;);
	return 0;
}
