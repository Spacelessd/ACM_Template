#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<ext/rope>
using namespace std;
using namespace __gnu_cxx;
//if (/*_RopeRep*/_Rope_constants::_S_leaf == __right->_M_tag)
#define N 1000005
#define CH 128
char str[N];
struct Suffix{
	int id;
	rope<char> s;
	friend bool operator <(const Suffix &x,const Suffix &y){
		return x.s<y.s;
	}
}a[N];
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	srand(time(0));
	int n;scanf("%d",&n);
	int t1=clock();
	for (int i=0;i<n;++i)str[i]=rand()%(CH-1)+1;
	for (int i=0;i<n;++i)a[i].id=i;
	a[n].s="";
	for (int i=n-1;i>=0;--i)a[i].s=rope<char>(str[i])+a[i+1].s;
    sort(a,a+n);
	//for (int i=0;i<n;++i)printf("%d\n",a[i].id);
	printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


