#include<stdio.h>
#include<string.h>
#include<math.h>
int task,n,b,i,j,l,r,p,x,y,z,ans,s[10010],q[10010],son[10010],f[10010],tr[10010],d[10010],deep[10010],dis[10010],o[10010],ed[20010],w[20010],id[20010],next[20010];
char str[10];
void build(int i,int j,int k,int l)
{
	ed[++p]=j;
	w[p]=k;
	id[p]=l;
	next[p]=son[i];
	son[i]=p;
}
int main()
{
    freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	scanf("%d",&task);
	while(task--)
	{
		scanf("%d",&n);
		b=(int)(sqrt(n));
		p=0;
		memset(son,0,sizeof(son));
		for(i=1;i<n;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			build(x,y,z,i);
			build(y,x,z,i);
		}
		memset(f,0,sizeof(f));
		memset(tr,0,sizeof(tr));
		memset(deep,0,sizeof(deep));
		memset(dis,0,sizeof(dis));
		memset(d,0,sizeof(d));
		memset(o,0,sizeof(o));
		memset(s,0,sizeof(s));
		f[1]=0;
		tr[1]=1;
		deep[1]=1;
		dis[1]=0;
		s[1]=1;
		d[1]=0;
		q[1]=1;
		l=0;
		r=1;
		while(l<r)
		{
			i=q[++l];
			for(j=son[i];j;j=next[j])
				if(f[i]!=ed[j])
				{
					f[ed[j]]=i;
					deep[ed[j]]=deep[i]+1;
					d[ed[j]]=w[j];
					o[id[j]]=ed[j];
					if(s[tr[i]]<b)
					{
						s[tr[i]]++;
						tr[ed[j]]=tr[i];
						dis[ed[j]]=dis[i];
						if(w[j]>dis[ed[j]])
							dis[ed[j]]=w[j];
					}
					else
					{
						s[ed[j]]=1;
						tr[ed[j]]=ed[j];
						dis[ed[j]]=0;
					}
					q[++r]=ed[j];
				}
		}
		while(scanf("%s",str))
		{
			if(str[0]=='D')
				break;
			if(str[0]=='C')
			{
				scanf("%d%d",&x,&y);
				x=o[x];
				d[x]=y;
				//if(tr[x]==x)
					//continue;
				dis[x]=y;
				if(dis[f[x]]>y)
					dis[x]=dis[f[x]];
				q[1]=x;
				l=0;
				r=1;
				while(l<r)
				{
					i=q[++l];
					for(j=son[i];j;j=next[j])
						if(ed[j]!=f[i]&&tr[ed[j]]==tr[i])
						{
							dis[ed[j]]=dis[i];
							if(d[ed[j]]>dis[ed[j]])
								dis[ed[j]]=d[ed[j]];
							q[++r]=ed[j];
						}
				}
			}
			if(str[0]=='Q')
			{
				scanf("%d%d",&x,&y);
				ans=0;
				while(x!=y)
				{
					if(tr[x]!=tr[y]&&deep[x]!=deep[y])
					{
						if(deep[x]>deep[y])
						{
							if(dis[x]>ans)
								ans=dis[x];
							if(d[tr[x]]>ans)
								ans=d[tr[x]];
							x=f[tr[x]];
						}
						else
						{
							if(dis[y]>ans)
								ans=dis[y];
							if(d[tr[y]]>ans)
								ans=d[tr[y]];
							y=f[tr[y]];
						}
					}
					else
					{
						if(deep[x]>deep[y])
						{
							if(d[x]>ans)
								ans=d[x];
							x=f[x];
						}
						else
						{
							if(d[y]>ans)
								ans=d[y];
							y=f[y];
						}
					}
				}
				printf("%d\n",ans);
			}
		}
	}
	return 0;
}
