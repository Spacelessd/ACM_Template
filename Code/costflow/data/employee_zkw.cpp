#include <cstdio>
#include <cstring>
using namespace std;
const int maxint=~0U>>1;

int n,m,dis[1100]={0},cost=0;
bool v[1100];
struct etype{int t,c,u;etype *next,*pair;} *e[1100];

void addedge(int s,int t,int c,int u=maxint)
{
	etype es={t,c,u,e[s],0},et={s,-c,0,e[t],0};
	e[s]=new etype(es);
	e[t]=new etype(et);
	e[s]->pair=e[t];
	e[t]->pair=e[s];
}

int aug(int no,int m)
{
	if(!no)return cost+=dis[n+1]*m,m;
	v[no]=true;
	for(etype *i=e[no];i;i=i->next)
		if(i->u && !v[i->t] && dis[i->t]+i->c==dis[no])
			if(int d=aug(i->t,m<i->u?m:i->u))
				return i->u-=d,i->pair->u+=d,d;
	return 0;
}

bool modlabel()
{
	int d=maxint,c;
	for(int i=0;i<=n+1;++i)if(v[i])
		for(etype *j=e[i];j;j=j->next)if(j->u && !v[j->t])
			if((c=j->c-dis[i]+dis[j->t])<d)d=c;
	if(d==maxint)return false;
	for(int i=0;i<=n+1;++i)if(v[i])dis[i]+=d;
	return true;
}

int main()
{
	freopen("employee.in","r",stdin);
	freopen("employee.out","w",stdout);
	scanf("%d %d",&n,&m);++n;
	for(int i=1;i<n;++i)
	{
		int t;
		scanf("%d",&t);
		addedge(n+1,i,0,t);
		addedge(i+1,0,0,t);
	}
	while(m--)
	{
		int s,t,c;
		scanf("%d %d %d",&s,&t,&c);
		addedge(s,t+1,c);
	}
	for(int i=1;i<n;++i)addedge(i+1,i,0);
	do do memset(v,0,sizeof(v));
	while(aug(n+1,maxint));
	while(modlabel());
	printf("%d\n",cost);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
