#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;


const int MaxN = 100005;

struct	Node	{	int x, y;	}	tmp[MaxN];
struct	Node1	{	int l, r, k, mid, ans, LCA;	}	query[MaxN];
int N, M, Q, E, weight[MaxN], change_back[MaxN], Link[MaxN << 2], next[MaxN << 2], list[MaxN << 1], len[MaxN << 2], 
	num[MaxN << 1], go_in[MaxN], go_out[MaxN], T[MaxN], fa[MaxN][20], depth[MaxN];
bool	visit[MaxN];

inline int	read()
{
	char ch = getchar(); int x = 0; bool flag = 0;
	for (; ch != '-' && (ch < '0' || ch > '9'); ch = getchar());
	if (ch == '-')
	{
		flag = 1;
		ch = getchar();
	}
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
	if (flag) return -x; return x;
}

bool	cmp(const Node a, const Node b)
{	return a.x < b.x;	}

inline	void	add_edge(int x, int y)
{
	Link[++ E] = y; next[E] = list[x]; list[x] = E;
	Link[++ E] = x; next[E] = list[y]; list[y] = E;
}

void	dfs(int x)
{
	visit[x] = 1; go_in[x] = ++ E; num[E] = x;
	for (int i = list[x]; i; i = next[i])
	{
		int j = Link[i];
		if (!visit[j])
		{
			fa[j][0] = x;
			depth[j] = depth[x] + 1;
			dfs(j);
		}
	}
	go_out[x] = ++ E; num[E] = - x;
}

inline int	lowbit(int x)
{	return	x & (- x);	} 

inline void	add(int x, int y)
{
	for (; x <= M; x += lowbit(x)) T[x] += y;
}

inline int	get_LCA(int x, int y)
{
	if (depth[x] < depth[y])
	{
		int tmp = x; x = y; y = tmp;
	}
	for (int i = 0, j = depth[x] - depth[y]; j; j /= 2, ++ i)
		if (j % 2)	x = fa[x][i];
	if (x == y) return x;
	for (int i = 19; i >= 0; -- i)
		if (fa[x][i] != fa[y][i])
		{
			x = fa[x][i];
			y = fa[y][i];
		}
	return fa[x][0];
}

inline int	get(int x)
{
	int ans = 0;
	for (; x; x -= lowbit(x)) ans += T[x];
	return ans;
}

int main()
{
	double	___time = clock();
	freopen("COT.in", "r", stdin);
	freopen("ydl.out", "w", stdout);
	N = read(); Q = read();
	for (int i = 1; i <= N; ++ i)
	{
		tmp[i].x = read(); 
		tmp[i].y = i;
	}
	sort(tmp + 1, tmp + N + 1, cmp);
	M = 0;
	for (int i = 1; i <= N; ++ i)
	{
		if (i == 1 || tmp[i].x != tmp[i - 1].x) change_back[++ M] = tmp[i].x;
		weight[tmp[i].y] = M;
	}
	E = 0;
	for (int i = 1; i < N; ++ i)
	{
		int x = read(), y = read();
		add_edge(x, y);
	}
	E = 0;
	fa[1][0] = 0; depth[1] = 1;
	dfs(1);
	for (int i = 1; i < 20; ++ i)
		for (int x = 1; x <= N; ++ x)
			fa[x][i] = fa[fa[x][i - 1]][i -1];
	memset(list, 0, sizeof(list)); E = 0;
	for (int i = 1; i <= Q; ++ i)
	{
		int l = read(), r = read(); query[i].k = read();
		query[i].l = 0; query[i].r = M + 2;
		Link[++ E] = i; next[E] = list[go_in[l]]; list[go_in[l]] = E; len[E] = 1;
		Link[++ E] = i; next[E] = list[go_in[r]]; list[go_in[r]] = E; len[E] = 1;
		int LCA = get_LCA(l, r);
		Link[++ E] = i; next[E] = list[go_in[LCA] - 1]; list[go_in[LCA] - 1] = E; len[E] = -2;
		query[i].LCA = LCA;
	}
	for (int k = M; k; k /= 2)
	{
		for (int i = 1; i <= Q; ++ i)
		{
			query[i].mid = (query[i].l + query[i].r) >> 1;
			query[i].ans = -(weight[query[i].LCA] < query[i].mid);
		}
		memset(T, 0, sizeof(T));
		for (int i = 1; i <= N << 1; ++ i)
		{
			add(weight[abs(num[i])], num[i] > 0 ? 1 : -1);
			for (int j = list[i]; j; j = next[j])
			{
				int q = Link[j];
				if (query[q].l + 1 == query[q].r) continue;
				query[q].ans += get(query[q].mid - 1) * len[j];
			}
		}
		for (int i = 1; i <= Q; ++ i)
		{
			if (query[i].l + 1 == query[i].r) continue;
			if (query[i].ans < query[i].k) query[i].l = query[i].mid; else query[i].r = query[i].mid;
		}
	}
	for (int i = 1; i <= Q; ++ i) printf("%d\n", change_back[query[i].l]);
	printf("%lf\n", clock() - ___time);
	return 0;
}
