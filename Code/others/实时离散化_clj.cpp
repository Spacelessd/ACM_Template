#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>
#include<algorithm>
#include<utility>
#include<map>
#define rep(i,n) for(int i=0;i<n;i++)
#define pb push_back
#define All(x) x.begin(),x.end()
const int inf=2e9,maxn=50000+10;
using namespace std;
map<int,int> Pre,Next;
int n,m,Ans[maxn];
int pre(int x){return Pre.count(x)?Pre[x]:x-1;}
int next(int x){return Next.count(x)?Next[x]:x+1;}
typedef pair<int,int> ii;
typedef vector<ii>::iterator it;
vector<ii> L,P;
void init()
{
	scanf("%d",&n);int a,b;
	rep(i,n)
	{
		scanf("%d%d",&a,&b);
		Next[pre(a)]=next(a);
		Pre[next(a)]=pre(a);
		Next[pre(b)]=a;
		Pre[a]=pre(b);
		Next[a]=b;
		Pre[b]=a;
	}
	Next[inf]=inf+1;
	char c;scanf("%d",&m);
	rep(i,m)
	{
		scanf(" %c %d",&c,&a);
		if(c=='P')P.pb(ii(a,i));
		else L.pb(ii(a,i));
	}
	L.pb(ii(inf,m));P.pb(ii(inf,m));
	sort(All(L));sort(All(P));
}
void Solve()
{
	int now=0,Min,pos=0;
	while(now<inf)
	{
		int a=Next.lower_bound(now)->first-now;
		int b=lower_bound(All(L),ii(pos,0))->first-pos;
		int c=lower_bound(All(P),ii(now,0))->first-now;
		Min=a<?b<?c;
		now+=Min;pos+=Min;
		if(Min==b)
		{
			it l=lower_bound(All(L),ii(pos,0)),r=lower_bound(All(L),ii(pos+1,0));
			for(it i=l;i!=r;i++)
				Ans[i->second]=now;
		}
		if(Min==c)
		{
			it l=lower_bound(All(P),ii(now,0)),r=lower_bound(All(P),ii(now+1,0));
			for(it i=l;i!=r;i++)
				Ans[i->second]=pos;
		}
		now=next(now);
		++pos;
	}
	rep(i,m)printf("%d\n",Ans[i]);
}
int main()
{
	init();Solve();
	system("pause");
}


