#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;
#define N 1000005
struct A{
	int x,y;
	int a[14];  //10-14:fast 15:slow
};
A a[N],*aa[N];
int n;
bool cmp(const A x,const A y){return x.x<y.x;}
bool cmp1(const A *x,const A *y){return x->x<y->x;}
int main(){
	{
		srand(time(0));
		n=1000000;
		for (int i=1;i<=n;++i)a[i].x=rand(),a[i].y=rand();
		int t1=clock();
		sort(a+1,a+1+n,cmp);
		printf("%d\n",clock()-t1);
	}
	{
		srand(time(0));
		n=100000;
		for (int i=1;i<=n;++i)a[i].x=rand(),a[i].y=rand(),aa[i]=a+i;
		int t1=clock();
		sort(aa+1,aa+1+n,cmp1);
		printf("%d\n",clock()-t1);
	}
	system("pause");
	return 0;
}


