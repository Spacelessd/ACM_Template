#include<vector>
#include<stack>
#include<set>
#include<map>
#include<queue>
#include<deque>
#include<string>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cassert>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<string>
//#include<debugger>

using namespace std;

#define s(n)					scanf("%d",&n)
#define sl(n) 					scanf("%lld",&n)
#define sf(n) 					scanf("%lf",&n)
#define ss(n) 					scanf("%s",n)
#define INF						(int)1e9
#define LINF					(long long)1e18
#define EPS						1e-9
#define maX(a,b)				((a)>(b)?(a):(b))
#define miN(a,b)				((a)<(b)?(a):(b))
#define abS(x)					((x)<0?-(x):(x))
#define FOR(i,a,b)				for(int i=a;i<b;i++)
#define REP(i,n)				FOR(i,0,n)
#define foreach(v,c)            for( typeof((c).begin()) v = (c).begin();  v != (c).end(); ++v)
#define mp						make_pair
#define FF						first
#define SS						second
#define tri(a,b,c)				mp(a,mp(b,c))
#define XX						first
#define YY						second.first
#define ZZ						second.second
#define pb						push_back
#define fill(a,v) 				memset(a,v,sizeof a)
#define all(x)					x.begin(),x.end()
#define SZ(v)					((int)(v.size()))
#define DREP(a)					sort(all(a)); a.erase(unique(all(a)),a.end())
#define INDEX(arr,ind)			(lower_bound(all(arr),ind)-arr.begin())
#define debug(args...)			{dbg,args; cerr<<endl;}
#define dline					cerr<<endl	
 
void sc(char &c){
	char temp[4];	ss(temp);	
	c=temp[0];
}
 
struct debugger
{
	template<typename T> debugger& operator , (const T& v)
	{	
		cerr<<v<<" ";	
		return *this;	
	}
} dbg;
 
 
 
 
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef pair<int,PII> TRI;
 
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VII;
typedef vector<PLL> VLL;
typedef vector<TRI> VT;
 
typedef vector<VI> VVI;
typedef vector<VL> VVL;
typedef vector<VII> VVII;
typedef vector<VLL> VVLL;
typedef vector<VT> VVT;
 
 
/*Main code begins now */
 
int testnum;
LL fact[10005];
const LL mod = 1000000007;
int N;
VI adj[10005];
 
const LL A=1002107;
const LL B=10456037;
const LL C=1015669;
 
const LL P = mod;
 
LL getHash(VL &h)
{
	LL ans=37;
	int n=h.size();
	for(int i=0;i<n;i++)
	{
		ans = (ans*(h[i]+i+2))%mod;
		//ans = ((ans<<2)+2)%mod;
		//ans = ((ans<<30) + h[i])%mod;
		//ans = ((ans<<2)+3)%mod;
	}
	
	return ans+1;
}
 
void preprocess()
{
	fact[0]=1;
	for(int i=1;i<=10000;i++)
		fact[i] = (fact[i-1]*i)%mod;
}
 
bool done[10005];
PLL dfs(int u)
{
	done[u]=true;
	int n=adj[u].size();
	VL h;
	LL ans=1;
	
	for(int i=0;i<n;i++)
	{
		int v=adj[u][i];
		if(!done[v])
		{
			PLL ret = dfs(v);
			ans = (ans*ret.FF) % mod;
			h.pb(ret.SS);
		}
	}
	
	sort(all(h));
	LL hash = getHash(h);
	
	for(int i=0;i<h.size();i++)
	{
		LL H=h[i];
		int cnt=1;
		while(i+1<h.size() && h[i+1]==H)
		{
			cnt++;
			i++;
		}
		//debug(u,H,cnt);
		ans = (ans*fact[cnt])%mod;
	}
		
		
	
	return mp(ans,hash);
}
		
 
void solve()
{
	fill(done,false);
	PLL ret = dfs(0);
	printf("%lld\n",ret.FF);
		
}
 
 
 
bool input()
{
	s(N);
	for(int i=0;i<N;i++)
		adj[i].clear();
	for(int i=0;i<N-1;i++)
	{
		int a,b;
		s(a); s(b);
		adj[a].pb(b);
		adj[b].pb(a);
	}
	return true;
}
 
 
int main()
{
	freopen("IOPC1200.in","r",stdin);
	freopen("std.out","w",stdout);
	preprocess();
	int T; s(T);
	for(testnum=1;testnum<=T;testnum++)
	{
		if(!input()) break;
		solve();
	}
}


