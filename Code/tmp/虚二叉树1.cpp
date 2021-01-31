#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 10000005
int sum[N],cnt[N];
int Qsum(int x){
	int l=0,r=N,res=0;
	for (;;){
		int mid=(l+r)>>1;
		if (x<=mid)++sum[mid];
		if (x>=mid)res+=sum[mid];
		if (x==mid)break;
		if (x<mid)r=mid-1;else l=mid+1;
	}
	return res;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	srand(time(0));
	int n;scanf("%d",&n);
	int t1=clock();
	for (int i=1;i<=n;++i){
		int x,y;scanf("%d%d",&x,&y);
		//x=rand()*rand()%N;y=rand()*rand()%N;
		++cnt[Qsum(x)];
	}
	for (int i=1;i<=n;++i)printf("%d\n",cnt[i]);
	printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


