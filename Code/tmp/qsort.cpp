#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 100010
int a[N];
void Q(int s,int t){
	int p,i=s,j=t,m=a[(i+j)>>1];
	do {
		while (a[i]<m) ++i;
		while (a[j]>m) --j;
		if (i<=j){
			p=a[i]; a[i]=a[j]; a[j]=p;
			++i; --j;
		}
	}while (i<=j);
	if (i<t) Q(i,t);
	if (s<j) Q(s,j);
}
int main()
{
	int n;
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	//std::sort(a,a+n);
	Q(1,n);
	for (int i=0;i<n;i++)
		printf("%d ",a[i]);
	//system("pause");
	return 0;
}	   




