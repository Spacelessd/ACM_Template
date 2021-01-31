#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 1005
#define P 1000000009
struct Polynomial{
	typedef long long value;
	value a[N];int len;
	Polynomial(){memset(a,0,sizeof(a));len=0;}
	inline friend Polynomial operator *(const Polynomial &x,const Polynomial &y){
		Polynomial c;
		for (int i=0;i<=x.len;++i)
			for (int j=0;j<=y.len;++j)
				c.a[i+j]=(c.a[i+j]+x.a[i]*y.a[j])%P;
		c.len=x.len+y.len;
		while (c.len&&!c.a[c.len])--c.len;
		return c;
	}
};
int n,k;
inline int get(int x,int y){return (x-1)*k+y;}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	
	system("pause");for (;;);
	return 0;
}


