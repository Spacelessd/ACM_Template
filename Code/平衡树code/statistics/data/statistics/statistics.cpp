#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#define int64 long long

using namespace std;

const int64 mo=1000000007;

int l[210000],r[210000];
int64 a,b,c,now,ans;
int n,m,x,y,z,Test,n1,n2,mid;

void Up_l(int y)
{
	int x=l[y];
	while ((y>1)&&(l[y >> 1]<x))
	{
		l[y]=l[y >> 1];
		y=y >> 1;
	}
	l[y]=x;
}

void Down_l(int y)
{
	int x=l[y];
	while (((y*2<=n1)&&(x<l[y*2]))||((y*2+1<=n1)&&(x<l[y*2+1])))
	{
		if ((y*2+1<=n1)&&(l[y*2+1]>l[y*2]))
			z=y*2+1;
		else z=y*2;
		l[y]=l[z];
		y=z;
	}
	l[y]=x;
}

void Up_r(int y)
{
	int x=r[y];
	while ((y>1)&&(r[y >> 1]>x))
	{
		r[y]=r[y >> 1];
		y=y >> 1;
	}
	r[y]=x;
}

void Down_r(int y)
{
	int x=r[y];
	while (((y*2<=n2)&&(x>r[y*2]))||((y*2+1<=n2)&&(x>r[y*2+1])))
	{
		if ((y*2+1<=n2)&&(r[y*2+1]<r[y*2]))
			z=y*2+1;
		else z=y*2;
		r[y]=r[z];
		y=z;
	}
	r[y]=x;
}

void Add_l(int x)
{
	l[++n1]=x;
	Up_l(n1);
}

void Del_l()
{
	mid=l[1];
	if (n1>1)
	{
		l[1]=l[n1];
		--n1;
		Down_l(1);
	}
	else --n1;
}
	
void Add_r(int x)
{
	r[++n2]=x;
	Up_r(n2);
}

void Del_r()
{
	mid=r[1];
	if (n2>1)
	{
		r[1]=r[n2];
		--n2;
		Down_r(1);
	}
	else --n2;
}

int main()
{
	freopen("statistics.in","r",stdin);
	freopen("statistics.out","w",stdout);
	Test=1;
	for (int ii=1;ii<=Test;++ii)
	{
		scanf("%d%d%d%d",&a,&b,&c,&n);
		n1=0;n2=0;
		mid=1;ans=1;
		for (int i=2;i<=n;++i)
		{
			now=((int64)a*mid+(int64)b*i+c) % mo;
			ans+=now;
			if (now<=mid)
				Add_l(now);
			if (now>mid)
				Add_r(now);
			if (n1<(i-1)/2)
			{
				Add_l(mid);
				Del_r();
			}
			else
				if (n1>(i-1)/2)
				{
					Add_r(mid);
					Del_l();
				}
		}
		printf("%lld\n",ans);
	}
}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		