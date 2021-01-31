#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#define pi 2*asin(1)
using namespace std;

const int N = 1 << 20;

struct cpx
{
	double x, y;
};

cpx operator+(cpx a, cpx b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}
cpx operator-(cpx a, cpx b)
{
	a.x -= b.x;
	a.y -= b.y;
	return a;
}
cpx operator*(cpx a, cpx b)
{
	cpx ret;
	ret.x = a.x * b.x - a.y * b.y;
	ret.y = a.x * b.y + a.y * b.x;
	return ret;
}

int n;
int ans[N];
cpx aa[N];
string s;

cpx f[N];

void init(cpx a[])
{
	getline(cin, s);
	int j = s.size(), k = 0, l = 0, o = 0;
	int u[4] = {1, 10, 100, 1000};
	for (int i = j - 1; i >= 0; --i)
	{
		o += u[k++] * (s[i] - '0');
		if (k == 4) a[l++].x = o, k = o = 0;
	}
	if (k > 0) a[l++].x = o;
	if (l > n) n = l;
}

struct DFT
{
	cpx a[N];
	void cal(int n, int s, int t);
} o, p, q;

void DFT::cal(int n, int s, int t)
{
	if (n == 1)
	{
		return;
	}
	int j = n >> 1;
	cal(j, s, t + 1);
	cal(j, s + (1 << t), t + 1);
	for (int i = 0; i < j; ++i)
	{
		int p = s + (i << (t + 1));
		// W(i,n/(1<<t))=W(i<<t,n)
		cpx w = f[i<<t] * a[p+(1<<t)];
		aa[i] = a[p] + w;
		aa[i+j] = a[p] - w;
	}
	for (int i = 0; i < n; ++i) a[s+(i<<t)] = aa[i];
}

int main()
{
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	init(p.a);
	init(q.a);
	int i = 1;
	while (i < n) i *= 2;
	n = i * 2;
	for (int i = 0; i < n; ++i) f[i] = (cpx)
	{
		cos(2 * pi * i / n), sin(2 * pi * i / n)
	};
	p.cal(n, 0, 0);
	q.cal(n, 0, 0);
	for (int i = 0; i < n; ++i) o.a[i] = p.a[i] * q.a[i];
	for (int i = 0; i < n; ++i) f[i].y *= -1;
	o.cal(n, 0, 0);
	long long x = 0;
	for (int i = 0; i < n; ++i)
	{
		o.a[i].x /= n;
		//	printf("%lf\n",o.a[i].x+0.1);
		x += (long long)(o.a[i].x + 0.1);
		ans[i] = x % 10000;
		x /= 10000;
	}
	while (n && !ans[n]) --n;
	printf("%d", ans[n--]);
	for (int i = n; i >= 0; --i) printf("%04d", ans[i]);
	//for (;;);
	return 0;
}


