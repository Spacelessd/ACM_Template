#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<vector>
using namespace std;
#define rep(i,n) for(int i=1;i<=n;++i)
typedef vector<int>::iterator it;
#define tr(i,x) for(it i=x.begin();i!=x.end();++i)
#define maxn 30010
#define oo (1<<30)
int Lim,n,x,y,q;
int w[maxn],dep[maxn],fa[maxn],own[maxn],Max[maxn],Sum[maxn];
vector<int>e[maxn],et[maxn];
char str[100];
void Build(int x,int y,int deep){
    dep[x]=deep;fa[x]=y;
    if (own[x]==-1)own[x]=x,Sum[x]=1;
    int tmp=own[x];
    tr(i,e[x])if (*i!=y){
        if (Sum[tmp]<Lim){
            et[x].push_back(*i);
            own[*i]=tmp;Sum[tmp]++;
        }
        Build(*i,x,deep+1);
    }
}
void Dfs(int x,int s,int m){
    Sum[x]=s+=w[x];Max[x]=m=max(m,w[x]);
    tr(i,et[x])Dfs(*i,s,m);
}
void Change(int x,int key){
    w[x]=key;
    if (x==own[x])Dfs(x,0,-oo);
    else Dfs(x,Sum[fa[x]],Max[fa[x]]);
}
int Qsum(int x,int y){
    int s=0,tmp;
    while (x!=y){
        if (dep[x]<dep[y]){tmp=x;x=y;y=tmp;}
        if (own[x]==own[y]){s+=w[x];x=fa[x];}
        else {
            if (dep[own[x]]<dep[own[y]]){tmp=x;x=y;y=tmp;}
            s+=Sum[x];x=fa[own[x]];
        }
    }
    return s+w[x];
}
int Qmax(int x,int y){
    int m=-oo,tmp;
    while (x!=y){
        if (dep[x]<dep[y]){tmp=x;x=y;y=tmp;}
        if (own[x]==own[y]){m=max(m,w[x]);x=fa[x];}
        else {
            if (dep[own[x]]<dep[own[y]]){tmp=x;x=y;y=tmp;}
            m=max(m,w[x]);x=fa[own[x]];
        }
    }
    return max(m,w[x]);
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d",&n);Lim=(int)sqrt(n)+1;
	rep(i,n-1) scanf("%d%d",&x,&y),e[x].push_back(y),e[y].push_back(x);
	rep(i,n)scanf("%d",&w[i]);
	memset(own,-1,sizeof(int)*(n+5));
	Build(1,-1,0);
	rep(i,n)if (own[i]==i)Dfs(i,0,-oo);
	scanf("%d",&q);
	rep(i,q){
        gets(str);
        scanf("%s%d%d",str,&x,&y);
        if (str[1]=='H')Change(x,y);
        else if (str[1]=='S')printf("%d\n",Qsum(x,y));
        else if (str[1]=='M')printf("%d\n",Qmax(x,y));
    }
	system("pause");
	return 0;
}







