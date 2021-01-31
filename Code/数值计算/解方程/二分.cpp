#include<stdio.h>
#include<math.h>
const double eps=1e-10;
int T;
double A,B,C,l,r,mid,f1,f2,f3;
double Get(double x)
{
	return A*x+B*sin(x)-C;
}
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	scanf("%d",&T);
	for(;T--;)
	{
		double a1,a2,a3;
		scanf("%lf%lf%lf",&a1,&a2,&a3);
		A=a1;B=a2;C=a3;
		for(l=(C-B)/A,r=(C+B)/A;l+eps<r;)
		{
			mid=(l+r)/2;
			f1=Get(l);
			f2=Get(mid);
			f3=Get(r);
			if(f1*f2<0) r=mid;
			else if(f2*f3<0) l=mid;
				else if(f2<0) r=mid;
					else l=mid;
		}
		printf("%.18lf\n",l);
	}
	system("pause");
	return 0;
}
