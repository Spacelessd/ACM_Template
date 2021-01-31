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
#define maxn 10010
#define oo (1<<30)
int Lim,n,x,y,z,q,test;
int w[maxn],dep[maxn],fa[maxn],own[maxn],Max[maxn],Sum[maxn];
vector<int>e[maxn],et[maxn],cost[maxn];
pair<int,int>edge[maxn];
char str[100];
void Build(int x,int y,int deep){
    dep[x]=deep;fa[x]=y;
    if (own[x]==-1)own[x]=x,Sum[x]++;
    int tmp=own[x];
    tr(i,e[x])if (*i!=y){
        if (Sum[tmp]<Lim){
            et[x].push_back(*i);
            own[*i]=tmp;Sum[tmp]++;
        }
        w[*i]=*(i-e[x].begin()+cost[x].begin());
        Build(*i,x,deep+1);
    }
}
void Dfs(int x,int m){
    Max[x]=m=max(m,w[x]);
    tr(i,et[x])Dfs(*i,m);
}
void Change(int x,int key){
    w[x]=key;
    if (x==own[x])Dfs(x,-oo);
    else Dfs(x,Max[fa[x]]);
}
int Qmax(int x,int y){
    int m=-oo,tmp;
    while (x!=y){
        if (dep[x]<dep[y]){tmp=x;x=y;y=tmp;}
        if (own[x]==own[y]){m=max(m,w[x]);x=fa[x];}
        else {
            if (dep[own[x]]<dep[own[y]]){tmp=x;x=y;y=tmp;}
            m=max(m,Max[x]);x=fa[own[x]];
        }
    }
    return m;
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	scanf("%d",&test);
	while (test--){
	scanf("%d",&n);Lim=(int)sqrt(n)+1;
	rep(i,n)e[i].clear();rep(i,n)et[i].clear();
	rep(i,n-1)scanf("%d%d%d",&x,&y,&z),e[x].push_back(y),e[y].push_back(x),cost[x].push_back(z),cost[y].push_back(z),edge[i]=make_pair(x,y);
	memset(own,-1,sizeof(int)*(n+5));
	memset(Sum,0,sizeof(int)*(n+5));
	Build(1,-1,0);
	rep(i,n)if (own[i]==i)Dfs(i,-oo);
	int tmp;
	while (1){
        gets(str);
        scanf("%s",str);
        if (str[0]=='D')break;
        scanf("%d%d",&x,&y);
        if (str[1]=='H'){
                         if (dep[edge[x].first]>dep[edge[x].second])tmp=edge[x].first;
                         else tmp=edge[x].second;
                         Change(tmp,y);
                         }
        else if (str[1]=='U')printf("%d\n",Qmax(x,y));
    }
    }
	//system("pause");
	//for (;;);
	return 0;
}







