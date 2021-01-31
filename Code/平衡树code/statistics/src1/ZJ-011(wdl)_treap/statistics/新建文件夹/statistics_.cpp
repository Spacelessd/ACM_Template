#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <unistd.h>
using namespace std;


typedef long long LL;
const LL P = 1000000007;
int N, root, l[200005], r[200005], value[200005], size[200005];
LL	f[200005], ans, A, B, C;


inline void	Updata(int x)
{
	size[x] = size[l[x]] + size[r[x]] + 1;
}

inline void	Right_Rotate(int &x)
{
	int k = l[x];
	l[x] = r[k];
	r[k] = x;
	Updata(x); Updata(k);
	x = k;
}

inline void	Left_Rotate(int &x)
{
	int k = r[x];
	r[x] = l[k];
	l[k] = x;
	Updata(x); Updata(k);
	x = k;
}

void	Ins(int &x, int y)
{
	if (x == 0)
	{
		x = y;
		value[y] = rand();
		size[y] = 1;
		l[y] = r[y] = 0;
		return;
	}
	if (f[y] < f[x])
	{
		Ins(l[x], y); Updata(x);
		if (value[l[x]] < value[x]) Right_Rotate(x);
	} else
	{
		Ins(r[x], y); Updata(x);
		if (value[r[x]] < value[x]) Left_Rotate(x);
	}
}

int	Search(int x, int y)
{
	if (size[l[x]] + 1 == y) return x;
	if (y <= size[l[x]]) return Search(l[x], y);
	return Search(r[x], y - size[l[x]] - 1);
}

int main()
{
	srand(getpid());
	freopen("statistics.in", "r", stdin);
	freopen("statistics.out", "w", stdout);
	int tmp1, tmp2, tmp3;
	scanf("%d%d%d%d", &tmp1, &tmp2, &tmp3, &N);
	if (N == 0)
	{
		cout << 0 << endl;
		return 0;
	}
	A = tmp1; B = tmp2; C = tmp3; ans = 1;
	f[1] = 1; root = 0; size[0] = 0; value[0] = 1000000000; Ins(root, 1);
	for (int i = 2; i <= N; ++ i)
	{
		f[i] = (f[Search(root, i >> 1)] * A + i * B + C) % P;
		ans += f[i];
		Ins(root, i);
	}
	cout << ans << endl;
	return 0;
}
