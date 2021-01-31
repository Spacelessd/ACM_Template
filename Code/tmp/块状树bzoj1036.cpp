#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
#define rep(i,n) for(int i=0;i<n;i++)
#define tr(e,x) for(it e=x.begin();e!=x.end();e++)
#define pb push_back
const int inf=~0U>>1,maxn=30000;
using namespace std;
vector<int> E[maxn],Et[maxn];
typedef vector<int>::iterator it;
int n,q,w[maxn],Lim,dep[maxn],Fa[maxn];
int own[maxn],Max[maxn],Sum[maxn]={};
void Build(int t,int f,int d)
{
    dep[t]=d;Fa[t]=f;int tmp=own[t];
    tr(e,E[t])if(*e!=f)
    {
        if(Sum[tmp]++<Lim)
        {
            Et[t].pb(*e);
            own[*e]=tmp;
        }
        Build(*e,t,d+1);
    }
}
void Dfs(int t,int s,int m)
{
    Sum[t]=s+=w[t];Max[t]=m>?=w[t];
    tr(e,Et[t])Dfs(*e,s,m);
}
void Change(int t,int u)
{
    w[t]=u;
    if(t==own[t])Dfs(t,0,-inf);
    else Dfs(t,Sum[Fa[t]],Max[Fa[t]]);
}
int QSum(int a,int b)
{
    int s=0;
    while(a!=b)
    {
        if(dep[a]<dep[b])swap(a,b);
        if(own[a]==own[b])
            s+=w[a],a=Fa[a];
        else
        {
            if(dep[own[a]]<dep[own[b]])swap(a,b);
            s+=Sum[a],a=Fa[own[a]];
        }
    }
    return s+w[a];
}
int QMax(int a,int b)
{
    int m=-inf;
    while(a!=b)
    {
        if(dep[a]<dep[b])swap(a,b);
        if(own[a]==own[b])
            m>?=w[a],a=Fa[a];
        else
        {
            if(dep[own[a]]<dep[own[b]])swap(a,b);
            m>?=Max[a],a=Fa[own[a]];
        }
    }
    return m>?=w[a];
}
inline int nextInt()
{
    char c;c=getchar();
    while(c!='-'&&(c<'0'||c>'9'))c=getchar();
    int n=0,s=1;if(c=='-')s=-1,c=getchar();
    while(c>='0'&&c<='9')n*=10,n+=c-'0',c=getchar();
    return n*s;
}
int main()
{
    n=nextInt();int s,t;Lim=sqrt(n)+1;
    rep(i,n-1)s=nextInt(),t=nextInt(),--s,--t,E[s].pb(t),E[t].pb(s);
    rep(i,n)w[i]=nextInt(),own[i]=i;
    Build(0,-1,0);
    rep(i,n)if(own[i]==i)Dfs(i,0,-inf);
    q=nextInt();
    char cmd[100];
    rep(i,q)
    {
        scanf(" ");
        scanf("%s",cmd);s=nextInt();t=nextInt();
        if(cmd[0]=='C')Change(s-1,t);
        else if(cmd[1]=='S')printf("%d\n",QSum(s-1,t-1));
        else printf("%d\n",QMax(s-1,t-1));
    }
    for(;;);
}
