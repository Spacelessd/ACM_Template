#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#define rep(i,n) for(int i=0;i<n;i++)
#define pb push_back
#define tr(i,x) for(eit i=x.begin();i!=x.end();i++)
const int inf=~0U>>1,maxn=3000;
using namespace std;
int n,m;
struct Edge
{
	int t;
	double c,oc;
	Edge(int _t,double _c):t(_t),oc(_c){}
};
typedef vector<Edge>::iterator eit;
vector<Edge> E[maxn];
double D;
bool vis[maxn]={0},Find;
double Dist[maxn];
void dfs(int x)
{
	vis[x]=true;double cost=Dist[x],ncost;
	tr(e,E[x])if((ncost=cost+e->c)>Dist[e->t])
	{
		if(!vis[e->t]){Dist[e->t]=ncost;dfs(e->t);}
		else Find=true;
		if(Find)break;
	}
	vis[x]=false;
}
bool Check(double _D)
{
	D=_D;
	rep(i,n)tr(e,E[i])e->c=D-e->oc;
	Find=false;
	rep(i,n)Dist[i]=0;
	rep(i,n){dfs(i);if(Find)return true;}
	return false;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	cin>>n>>m;
	int s,t;double c;
	rep(i,m)scanf("%d %d %lf",&s,&t,&c),--s,--t,E[s].pb(Edge(t,c));
	double r=1e7,l=-r;
	while(r-l>1e-9)
	{
		double m=(l+r)/2;
		if(Check(m))r=m;
		else l=m;
	}
	printf("%0.8lf\n",l);
	system("pause");for (;;);
	return 0;
}


