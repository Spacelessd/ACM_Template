#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

const int n=10000000;
int s[n+5],p[n+5];

inline void Qsort(int l,int r){
	int i,j,mid;
	i=l;j=r;mid=p[(l+r) >> 1];
	for (;;){
		while (p[i]<mid) i++;
		while (p[j]>mid) j--;
		if (i<=j){
			int tmp=p[i];p[i]=p[j];p[j]=tmp;
			i++;j--;
		}
		else break;
	}
	if (i<r) Qsort(i,r);
	if (l<j) Qsort(l,j);
}

int main(){
	srand(time(0));
	for (int i=1;i<=n;i++) s[i]=p[i]=rand();
	double t0=(double)clock()/CLOCKS_PER_SEC;
	sort(s+1,s+n+1);
	double t1=(double)clock()/CLOCKS_PER_SEC;
	Qsort(1,n);
	double t2=(double)clock()/CLOCKS_PER_SEC;
	printf("%.9lf\n",t1-t0);
	printf("%.9lf\n",t2-t1);
	system("pause");
	return 0;
}
