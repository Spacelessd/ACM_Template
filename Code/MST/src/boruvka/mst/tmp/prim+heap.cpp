#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

const int inf=10000000;

const int maxn=100010;
const int maxm=2000010*2;

int tot,l,n,m,heap[maxn],rankin[maxn],rankout[maxn],a[maxn];
int son[maxn],len[maxm],next[maxm],point[maxm];
bool use[maxn];

void addedge(int x, int y, int z)
{
	point[++tot]=y; next[tot]=son[x]; 
	son[x]=tot; len[tot]=z;
}

void swap(int x, int y)
{
	int tmp;
	tmp=heap[x]; heap[x]=heap[y]; heap[y]=tmp;
	tmp=rankout[x]; rankout[x]=rankout[y]; rankout[y]=tmp;
	rankin[rankout[x]]=x; rankin[rankout[y]]=y;
}


void up(int x)
{
	while (x && heap[x]<heap[x>>1]) swap(x,x>>1),x=x>>=1;
}

void down(int x)
{
	while (x*2<=l)
	{
		int y=x;
		if (heap[x+x]<heap[y]) y=x+x;
		if (heap[x+x+1]<heap[y] && x+x+1<=l) y=x+x+1;
		if (x==y) break;
		swap(x,y); x=y;
	}
}

void add(int x, int y)
{
	heap[++l]=y; rankin[x]=l; rankout[l]=x;
}

int main()
{
	//freopen("road.in","r",stdin);
	//freopen("road.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1; i<=n; i++) scanf("%d",&a[i]);
	for (int i=1; i<=m; i++) 
	{
		int x,y,z; scanf("%d%d%d",&x,&y,&z);
		z=z-a[x]-a[y]; addedge(x,y,z); addedge(y,x,z);
	}
	
	double ans=0;
	
	add(1,0);
	for (int i=2; i<=n; i++) add(i,inf);
	
	for (int i=1; i<=n; i++)
	{
		int x,y;
		ans+=heap[1]; x=rankout[1]; use[x]=1;
		swap(1,l); l--; down(1);
		
		for (int p=son[x]; p; p=next[p])
		{
			y=point[p];
			if (!use[y])
			{
				if (len[p]<heap[rankin[y]]) heap[rankin[y]]=len[p];
				up(rankin[y]);
			}
		}
	}
	printf("%d\n",ans);
	for (;;);
	return 0;
}
