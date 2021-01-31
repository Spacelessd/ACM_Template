#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
struct point
{
	double x, y;
} a, b, c, p[105], q, u, v;
const double pi=3.141592653589793;
double ans, r, d, la, lb, lc, mul, eps = 1e-12;
int n, i;

double dot(point a, point b)
{
	return a.x * b.x + a.y * b.y;
}
double cross(point a, point b)
{
	return a.x * b.y - a.y * b.x;
}
double len(point a)
{
	return sqrt(a.x * a.x + a.y * a.y);
}
double bet(point a, point u, point v)
{
	return a.x + eps > min(u.x, v.x) && a.x < eps + max(u.x, v.x) && a.y + eps > min(u.y, v.y) && a.y < eps + max(u.y, v.y);
}
double dist(point a, point b, point c, double lc)
{
	return fabs(cross(a, b) / lc);
}
double shan(point a, point b, double la, double lb)
{
	double f = dot(a, b) / la / lb;
	if(f > 1) f = 1;
	if(f < -1) f = -1;
	return fabs(r * r * acos(f) / 2);
}

point chuizu(point a, point b)
{
	point c, t;
	double t1, t2;
	c.x = b.y - a.y, c.y = a.x - b.x;
	t1 = cross(a, c);
	t2 = cross(c, b);
	t.x = (t1 * b.x + t2 * a.x) / (t1 + t2);
	t.y = (t1 * b.y + t2 * a.y) / (t1 + t2);
	return t;
}

void get(point a, point b, point &u, point &v)
{
	point c = chuizu(a, b), d;
	double q;
	d.x = a.x - b.x, d.y = a.y - b.y;
	q = sqrt((r * r - c.x * c.x - c.y * c.y) / (d.x * d.x + d.y * d.y));
	u.x = c.x + d.x * q, u.y = c.y + d.y * q;
	v.x = c.x - d.x * q, v.y = c.y - d.y * q;
}

int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	double xxx,yyy,x0,y0,v0,theta,tim,ga;
	while (scanf("%lf%lf%lf%lf%lf%lf%lf",&xxx,&yyy,&v0,&theta,&tim,&ga,&r)!=EOF)
	{
		if (fabs(xxx)<eps && fabs(yyy)<eps && fabs(v0)<eps && fabs(theta)<eps) break;
		//printf("%.3lf %.3lf %.3lf\n",v0,tim,sin(theta/180.0*pi));
		x0=xxx+v0*cos(theta/180.0*pi)*tim;
		y0=yyy-1.0/2*ga*tim*tim+v0*sin(theta/180.0*pi)*tim; 
		scanf("%d\n",&n);
		ans=0;
		//printf("%.3lf %.3lf\n",x0,y0);
		for(i = 1; i <= n; i++)
		{
			scanf("%lf%lf", &p[i].x, &p[i].y);
			p[i].x-=x0; p[i].y-=y0;
		}
		p[0] = p[n];
		ans = 0;
		for(i = 0; i < n; i++)
		{
			a = p[i], b = p[i+1], c.x = b.x - a.x, c.y = b.y - a.y;
			la = len(a), lb = len(b), lc = len(c), mul = cross(a, b);
			if(fabs(mul) < eps) continue;
			if(mul > 0) d = 1;
			else d = -1;
			if(la < r + eps && lb < r + eps) ans += mul / 2;
			else if(la + eps > r && lb + eps > r)
			{
				if(dist(a, b, c, lc) + eps > r) ans += d * shan(a, b, la, lb);
				else
				{
					q = chuizu(a, b);
					if(bet(q, a, b))
					{
						ans += d * shan(a, b, la, lb);
						get(a, b, u, v);
						ans -= d * shan(u, v, len(u), len(v));
						ans += d * fabs(cross(u, v) / 2);
					}
					else ans += d * shan(a, b, la, lb);
				}
			}
			else
			{
				get(a, b, u, v);
				if(!bet(u, a, b)) u = v;
				if(la > lb) ans += d * shan(a, u, la, len(u)) + cross(u, b) / 2;
				else ans += cross(a, u) / 2 + d * shan(u, b, len(u), lb);
			}
		}
		printf("%.2f\n", fabs(ans));
	}
	system("pause");for (;;);
	return 0;
}


