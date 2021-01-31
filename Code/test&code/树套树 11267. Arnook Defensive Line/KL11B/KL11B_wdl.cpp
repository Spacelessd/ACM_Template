#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

const int MaxN = 500005;
struct  Node
{
	int x, y, t;
} A[MaxN], B[MaxN], C[MaxN];

struct	POINT
{
	int x, y;
}	tmp[MaxN];

int T, N, M, K, Ans[MaxN], Tree[MaxN];
bool	opt[MaxN];

inline int	read()
{
	char ch = getchar(); int x = 0; bool flag = 0;
	for (; ch != '-' && (ch < '0' || ch > '9'); ch = getchar());
	if (ch == '-')	{
		flag = 1;	ch = getchar();	
	}
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
	if (flag) return - x; return x;
}

bool	cmp(const POINT A, const POINT B)
{	return A.x < B.x;	}

bool	cmp2(const Node A, const Node B)
{	return A.y > B.y;	}

inline int	lowbit(int x)
{	return x & -x;	}

inline void	add(int x)
{
	for (; x <= K; x += lowbit(x))	Tree[x] ++;
}

inline int	get(int x)
{
	int ans = 0;
	for (; x; x -= lowbit(x))	ans += Tree[x];
	return ans;
}

inline void	clear(int x)
{
	if (!Tree[x]) return;
	for (; x <= K; x += lowbit(x))	Tree[x] = 0;
}

inline void	get_ans(int al, int ar, int bl, int br)
{
	if (al > ar)	return;
	if (bl > br)	return;
	for (int i = bl, j = al; i <= br; ++ i)
	{
		for (; j <= ar && A[j].y >= B[i].y; ++ j) add(A[j].x);
		Ans[B[i].t] += get(B[i].x);
	}
	for (int i = al; i <= ar; ++ i)	clear(A[i].x);
}

inline void	merge(Node	A[], int l, int mid, int r)
{
	if (l > mid)	return;
	if (mid + 1 > r)	return;
	for (int i = l, j = mid + 1, k = l; k <= r; ++ k)
	{
		if (j > r || i <= mid && A[i].y > A[j].y)
		{
			C[k] = A[i];
			++ i;
		}	else
		{
			C[k] = A[j];
			++ j;
		}
	}
	for (int i = l; i <= r; ++ i)	A[i] = C[i];
}

void	work(int tl, int tr, int al, int ar, int bl, int br)
{
	if (al > ar)
	{
		sort(B + bl, B + br + 1, cmp2);
		return;
	}
	if (bl > br)
	{
		sort(A + al, A + ar + 1, cmp2);
		return;
	}
	int tmid = (tl + tr) >> 1, amid = al - 1, bmid = bl - 1;
	while (amid < ar && A[amid + 1].t <= tmid) ++ amid;
	while (bmid < br && B[bmid + 1].t <= tmid) ++ bmid;
	work(tl, tmid, al, amid, bl, bmid);
	work(tmid + 1, tr, amid + 1, ar, bmid + 1, br);
	get_ans(al, amid, bmid + 1, br);
	merge(A, al, amid, ar);
	merge(B, bl, bmid, br);
}

int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	T = read(); N = 0; M = 0;
	for (int i = 1; i <= T; ++ i)
	{
		char ch = getchar();
		if (ch == '+')
		{
			A[++ N].x = read();
			A[N].y = read();
			A[N].t = i;
			opt[i] = 0;
		}	else
		if (ch == '?')
		{
			B[++ M].x = read();
			B[M].y = read();
			B[M].t = i;
			opt[i] = 1;
		}	else
		{	-- i;	continue;	}
	}
	for (int i = 1; i <= N; ++ i)
	{
		tmp[i].x = A[i].x;	tmp[i].y = i;
	}
	for (int i = N + 1; i <= T; ++ i)
	{
		tmp[i].x = B[i - N].x;	tmp[i].y = i;
	}
	for (int i = 1; i <= T; ++ i) Ans[i] = 0;
	sort(tmp + 1, tmp + T + 1, cmp);
	K = 0;
	for (int i = 1; i <= T; ++ i)
	{
		if (i == 1 || tmp[i].x != tmp[i - 1].x) ++ K;
		if (tmp[i].y <= N)	A[tmp[i].y].x = K;
		else				B[tmp[i].y - N].x = K;
	}
	work(1, T, 1, N, 1, M);
	for (int i = 1; i <= T; ++ i)
		if (opt[i])	printf("%d\n", Ans[i]);
	return 0;
}
