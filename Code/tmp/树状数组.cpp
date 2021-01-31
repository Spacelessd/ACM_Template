#include<stdio.h>
#define maxn 1000010
int c[maxn],a[maxn];
int n,i,tmp;
int lowbit(int x){return x& -x;}
void add(int x,int y)  //将点x的值加上y
{
	for (;x<=n;x+=lowbit(x)) c[x]+=y;
}

int sum(int x)  //统计1-x的总和
{
	int tmp=0;
	for (;x;x-=lowbit(x))tmp+=c[x];
	return tmp;
}

int findkth(int k)  //求第K小的值
{
	int ans=0,cnt=0,i;
	for (i=20;i>=0;i--)
	{
		ans+=(1<<i);
		if (ans>=n||cnt+c[ans]>=k)ans-=(1<<i);
		  else cnt+=c[ans];
	}
	return ans+1;
}

int Qmax(int l,int r)
{
	int x=r,ans=-100000;
	while (x>=l){tmp++;printf("%d\n",lowbit(x));
		  if (x-lowbit(x)>=l-1){
						   if (c[x]>ans)ans=c[x];
						   x-=lowbit(x);
						   }
						   else {
								if (a[x]>ans)ans=a[x];
								x--;
								}
		  }
	return ans;
}

int main()
{
	//scanf("%d",&n);
	n=1000000;
	for (i=1;i<=n;i++)a[i]=i;
	for (i=1;i<=n;i++){
		c[i]=-100000;
		for (int j=i;j>i-lowbit(i);j--)if (a[j]>c[i])c[i]=a[j];
		}
	printf("%d\n",Qmax(2542,600000));
	printf("%d\n",tmp);
	for(;;);
	
}

