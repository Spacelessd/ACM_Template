#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 30000005
int f[N],p[N],len;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n;scanf("%d",&n);
	//O(n)
	int t1=clock();len=0;
	memset(f+1,0,sizeof(int)*n);
	for (int i=2;i<=n;++i){
		if (!f[i])f[i]=p[++len]=i;
		for (int j=1;j<=len&&p[j]<=f[i]&&i*p[j]<=n;++j)
			f[i*p[j]]=p[j];
	}
	printf("%d\n",len);
	//for (int i=1;i<=len;++i)printf("%d%c",p[i],i==len?'\n':' ');
	//for (int i=1;i<=n;++i)printf("%d %d\n",i,f[i]);
	printf("time=%d\n",clock()-t1);
	//n log log n
	t1=clock();len=0;
	memset(f+1,0,sizeof(int)*n);
	for (int i=2;i<=n;++i)if (!f[i]){
		p[++len]=i;for (int j=i+i;j<=n;j+=i)f[j]=1;
	}
	printf("%d\n",len);
	//for (int i=1;i<=len;++i)printf("%d%c",p[i],i==len?'\n':' ');
	//for (int i=1;i<=n;++i)printf("%d %d\n",i,f[i]);
	printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


