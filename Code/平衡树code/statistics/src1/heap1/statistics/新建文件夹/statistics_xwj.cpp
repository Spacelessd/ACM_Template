#include<cstdio>
const int oo=1000000007;
int i,T,N,Num1,Num2,t;
long long A,B,C,Ans;
int f[200005],g1[200005],g2[200005];
inline void swap1(int i,int j)
{
	int t;
	t=g1[i];
	g1[i]=g1[j];
	g1[j]=t;
}
inline void swap2(int i,int j)
{
	int t;
	t=g2[i];
	g2[i]=g2[j];
	g2[j]=t;
}
inline void Up1(int i)
{
	for(;i>1&&g1[i]>g1[i/2];)
	{
		swap1(i,i/2);
		i/=2;
	}
}
inline void Up2(int i)
{
	for(;i>1&&g2[i]<g2[i/2];)
	{
		swap2(i,i/2);
		i/=2;
	}
}
inline void Down1(int i)
{
	int j;
	for(;2*i<=Num1;)
	{
		j=i;
		if(g1[2*i]>g1[j])
			j=2*i;
		if(2*i+1<=Num1&&g1[2*i+1]>g1[j])
			j=2*i+1;
		if(i==j)
			return;
		swap1(i,j);
		i=j;
	}
}
inline void Down2(int i)
{
	int j;
	for(;2*i<=Num2;)
	{
		j=i;
		if(g2[2*i]<g2[j])
			j=2*i;
		if(2*i+1<=Num2&&g2[2*i+1]<g2[j])
			j=2*i+1;
		if(i==j)
			return;
		swap2(i,j);
		i=j;
	}
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld%lld%lld%d",&A,&B,&C,&N);
		f[1]=1;
		Num1=1,Num2=0;
		g1[1]=1;
		for(i=2;i<=N;++i)
		{
			f[i]=(A*g1[1]+B*i+C)%oo;
			if(i&1)
			{
				g1[++Num1]=f[i];
				Up1(Num1);
			}
			else
			{
				g2[++Num2]=f[i];
				Up2(Num2);
			}
			for(;g1[1]>g2[1];)
			{
				t=g1[1];
				g1[1]=g2[1];
				g2[1]=t;
				Down1(1);
				Down2(1);
			}
		}
		Ans=0;
		for(i=1;i<=N;++i)
			Ans+=f[i];
		printf("%lld\n",Ans);
	}
	return 0;
}


