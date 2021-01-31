#include<cstdio>
#include<cstdlib>
#include<math.h>
#include<string>
#include<iostream>
using namespace std;
#define maxlongint 2147483647
char read_line[20];
#define sqr(a) ((a)*(a))
const int maxn = 522;
const double eps = 1e-6;

int i, j, k, m, n;
double r[maxn+1], x [maxn+1];
double a, t, kk, ll, rr, x1, Y1, x2, y2;
double cal(double t)
{
	double s;
	double tmp = 0;
	for (i = 1 ; i <= n ; i++)
	{
		if (fabs(x[i] - t) < r[i] )
		{
			s = sqrt(double(sqr(r[i]) - sqr(x[i] - t)));
			if (s > tmp ) tmp = s;
		}
		if (x[i+1] - x[i] > fabs(r[i+1] - r[i]) )
		{
			x1 = x[i] + r[i] * (r[i] - r[i+1]) / (double)(x[i+1] - x[i]);
			Y1 = sqrt(double(sqr(r[i]) - sqr(x1 - x[i])));
			x2 = x[i+1] + r[i+1] * (r[i] - r[i+1]) / (double)(x[i+1] - x[i]);
			y2 = sqrt(double(sqr(r[i+1]) - sqr(x2 - x[i+1])));
			if ((t > x1)&(t < x2) )
			{
				s = (y2 - Y1) / (double)(x2 - x1) * (t - x1) + Y1;
				if (s > tmp) tmp = s;
			}
		}
	}
	return tmp;
}

double sim(double k1, double k2, double k3, double len)
{
	return (k1 + 4 * k2 + k3) * len / (double)(6);
}

double rsim(double ll, double rr, double t1, double t2, double t3)
{
	double mid, k1, k2, len;
	double tmp;
	mid = (ll + rr) / (double)2;
	k1 = cal((mid + ll) / (double)2);
	k2 = cal((mid + rr) / (double)2);
	len = rr - ll;
	if (fabs(sim(t1, t2, t3, len) - sim(t1, k1, t2, len / (double)2) - sim(t2, k2, t3, len / (double)2)) < eps )
		return(sim(t1, t2, t3, len));
	else tmp = rsim(ll, mid, t1, k1, t2) + rsim(mid, rr, t2, k2, t3);
	return tmp;
}

int main()
{
	cin >> n >> a;
	a = 1 / (double)tan(a);
	for (i = 1 ; i <= n + 1 ; i++)
	{
		cin >> kk;
		t = t + kk;
		x[i] = t * a;
	}
	rr = x[n+1];
	ll = x[n+1];
	for (i = 1 ; i <= n ; i++)
	{
		cin >> r[i];
		if (x[i] + r[i] > rr ) rr = x[i] + r[i];
		if (x[i] - r[i] < ll ) ll = x[i] - r[i];
	}
	printf("%.2lf\n", 2 * rsim(ll, rr, 0, cal((ll + rr) / (double)2), 0));
	system("pause");
	return 0;
}


