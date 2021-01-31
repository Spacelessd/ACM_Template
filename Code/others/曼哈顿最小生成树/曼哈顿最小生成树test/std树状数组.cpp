#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#define lowbit(x) x&-x
const int maxn = 2000005;
int N, M, C;
int last[maxn], c[maxn], ans[maxn], pre[maxn];
struct rec
{
	int n, x, y;
} a[maxn];

inline bool cmp(const rec &a, const rec &b)
{
	return a.y < b.y;
}
inline void upd(int *a, int x, int w)
{
	for(; x <= N; x += lowbit(x))a[x] += w;
}
inline int sum(int *a, int x)
{
	int s = 0;
	for(; x; x -= lowbit(x))s += a[x];
	return s;
}

int main()
{
	int i, u, w;
	//freopen("flower.in","r",stdin);
	//freopen("flower.out","w",stdout);
	scanf("%d%d%d", &N, &C, &M);
	for(i = 1; i <= N; ++i)
	{
		scanf("%d", &w);
		pre[i] = last[w];
		last[w] = i;
	}
	for(i = 0; i < M; ++i)
	{
		scanf("%d%d", &a[i].x, &a[i].y);
		a[i].n = i;
	}
	std::sort(a, a + M, cmp);
	u = 0;
	for(i = 1; i <= N; ++i)
	{
		upd(c, pre[pre[i]] + 1, 1);
		upd(c, pre[i] + 1, -1);
		while(u < M && a[u].y == i)
		{
			ans[a[u].n] = sum(c, a[u].x);
			++u;
		}
	}
	for(i = 0; i < M; ++i)printf("%d\n", ans[i]);
	return 0;
}


