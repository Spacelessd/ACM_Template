#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 21111, M = 51111;
const long long INF = 1LL << 40;
int n, m, q, x[M], y[M], zz[M], num[M], to[M], f[N], ord[M];
long long z[M], base_ans;

struct recover
{
	int cnt;
	int a[M*5], b[M*5];
	inline int find(int v)
	{
		if (!f[v]) return v;
		int ret = v;
		while (f[ret]) ret = f[ret];
		while (f[v] != ret)
		{
			++cnt;
			b[cnt] = f[a[cnt] = v];
			f[v] = ret;
			v = b[cnt];
		}
		return ret;
	}
	inline void merge(int u, int v)
	{
		u = find(u);
		v = find(v);
		a[++cnt] = u;
		b[cnt] = f[u];
		f[u] = v;
	}
	inline void action(int top = 0)
	{
		for (; cnt != top; --cnt)
			f[a[cnt]] = b[cnt];
	}
} re[18];
int opt[M];

void qs(int l, int r)
{
	long long md = z[ord[l + r >> 1]];
	int i = l, j = r;
	while (i < j)
	{
		while (z[ord[i]] < md) ++i;
		while (z[ord[j]] > md) --j;
		if (i <= j)
			swap(ord[i++], ord[j--]);
	}
	if (l < j) qs(l, j);
	if (i < r) qs(i, r);
}

void work(int dep, int l, int r)
{
	recover &e = re[dep];
	e.cnt = 0;
	if (l == r)
	{
		z[num[l]] = zz[num[l]] = to[l];
		qs(1, m);
		long long ans = base_ans;
		for (int i = 1; i <= m; ++i)
			if (e.find(x[ord[i]]) != e.find(y[ord[i]]))
			{
				ans += z[ord[i]];
				e.merge(x[ord[i]], y[ord[i]]);
			}
		printf("%I64d\n", ans);
		e.action();
		return;
	}
	int m_rem = m;
	long long base_rem = base_ans;
	// Start Contraction
	for (int i = l; i <= r; ++i)
		z[num[i]] = -INF;
	qs(1, m);
	opt[0] = 0;
	
	for (int i = 1; i <= m; ++i)
		if (e.find(x[ord[i]]) != e.find(y[ord[i]]))
		{
			if (z[ord[i]] != -INF)
				opt[++opt[0]] = ord[i];
			e.merge(x[ord[i]], y[ord[i]]);
		}
	e.action();
	for (int i = 1; i <= opt[0]; ++i)
	{
		base_ans += z[opt[i]];
		e.merge(x[opt[i]], y[opt[i]]);
	}
	int cnt_rem = e.cnt;
	// Start Reduction
	
	for (int i = l; i <= r; ++i)
		z[num[i]] = INF;
	qs(1, m);
	opt[0] = 0;
	for (int i = 1; i <= m; ++i)
		if (e.find(x[ord[i]]) != e.find(y[ord[i]]))
			e.merge(x[ord[i]], y[ord[i]]);
		else if (z[ord[i]] != INF)
			opt[++opt[0]] = i;
	sort(opt + 1, opt + 1 + opt[0]);
	for (int i = opt[0]; i; --i)
		swap(ord[opt[i]], ord[m--]);
	e.action(cnt_rem);
	// Recover edge costs
	for (int i = l; i <= r; ++i)
		z[num[i]] = zz[num[i]];

	work(dep + 1, l, (l + r) / 2);
	work(dep + 1, (l + r) / 2 + 1, r);
	// Recover All
	e.action();
	m = m_rem;
	base_ans = base_rem;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= m; ++i)
		scanf("%d%d%d", x + i, y + i, zz + i), ord[i] = i, z[i] = zz[i];
	for (int i = 1; i <= q; ++i)
		scanf("%d%d", num + i, to + i);
	if (q) work(0, 1, q);
	//fclose(stdin);
	//fclose(stdout);
	//for (;;);
	return 0;
}


