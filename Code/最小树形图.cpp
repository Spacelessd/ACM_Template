#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define type int
const int mm=11111;
const int mn=111;
const int oo=(1<<29);
int s[mm],t[mm];
int id[mn],pre[mn],q[mn],vis[mn];
type c[mm],in[mn],w[mn];
type Directed_MST(int root,int NV,int NE)
{
	type ret=0,sum=0,tmpw;
	int i,j,u,v,r;
	bool huan=1;
	for(i=0;i<=NV;++i)in[i]=0,id[i]=i,pre[i]=-1;
	while(huan)
	{
		for(i=0;i<=NV;++i)
			if(pre[j=id[i]]>=0)
			{
				if(pre[i]<0)in[i]+=w[j],id[i]=id[j];
				else in[i]+=w[i],ret+=w[i];
			}
		for(i=0;i<=NV;++i)pre[i]=-1,vis[i]=0;
		for(i=0;i<NE;++i)
			if((u=id[s[i]])!=(v=id[t[i]])&&(w[v]>(tmpw=c[i]-in[t[i]])||pre[v]<0))
				pre[v]=u,w[v]=tmpw;
		for(i=1;i<=NV;++i)
			if(i!=root&&id[i]==i&&pre[i]<0)return -1;
		for(pre[root]=-1,sum=i=0;i<=NV;++i)
			if(pre[i]>=0)sum+=w[i];
		for(huan=i=0;i<=NV;++i)
			if(!vis[i])
			{
				r=0,j=i;
				while(j>=0&&vis[j]>=0)
				{
					if(vis[j]>0)
					{
						while(q[--r]!=j)id[q[r]]=j,vis[q[r]]=-1;
						huan=1,vis[j]=-1;
					}
					else vis[q[r++]=j]=1,j=pre[j];
				}
				while(r--)vis[q[r]]=pre[q[r]]=-1;
			}
	}
	return ret+sum;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int i,n,m;
	while(scanf("%d%d",&n,&m),n+m)
	{
		for(i=0;i<m;++i)scanf("%d%d%d",&s[i],&t[i],&c[i]);
		type ans=Directed_MST(1,n,m);
		if(ans<0)printf("impossible\n");
		else printf("%d\n",ans);
	}
	system("pause");for (;;);
	return 0;
}


