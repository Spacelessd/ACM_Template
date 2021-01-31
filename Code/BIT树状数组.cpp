#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 10000005
int n,c[N],a[N];
inline int lowbit(int x){return x&-x;}
void add(int x,int y){
	for (;x<=n;x+=lowbit(x))c[x]+=y;
}
int sum(int x){
	int tmp=0;
	for (;x;x-=lowbit(x))tmp+=c[x];
	return tmp;
}
int findkth(int k){
	int ans=0,cnt=0;
	for (int i=20;i>=0;--i){
		ans+=1<<i;
		if (ans>=n||cnt+c[ans]>=k)ans-=1<<i;
			else cnt+=c[ans];
	}
	return ans+1;
}
int Qmax(int l,int r){
	int x=r,ans=-(1<<30);
	while (x>=l){
		if (x-lowbit(x)>=l-1){
			if (c[x]>ans)ans=c[x];
			x-=lowbit(x);
		}
		else {
			if (a[x]>ans)ans=a[x];
			--x;
		}
	}
	return ans;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	//scanf("%d",&n);
	int t1=clock();
	n=10000000;
	for (int i=1;i<=n;++i)a[i]=i;
	for (int i=1;i<=n;++i){
		int k=i-lowbit(i),max=-(1<<30);
		for (int j=i;j>k;--j)if (a[j]>max)max=a[j];
		c[i]=max;
	}
	printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


