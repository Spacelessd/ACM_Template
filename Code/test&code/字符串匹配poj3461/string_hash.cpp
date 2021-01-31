#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define mo 199997
#define cp freopen
#define M(x) x%=mo
#define MAX 1000010
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;
int n;
char s1[MAX],s2[MAX];

struct hash_table
{
	int s,k,l;
	int e[10010];
	void update(int x,int y)
	{
		s-=x*e[l+1],s*=k;
		s=(s%mo+mo)%mo;
		s+=e[2]*y,M(s);
	}
	void pre()
	{
		e[0]=1;
		rep(i,1,10005)
			e[i]=e[i-1]*k,M(e[i]);
	}
	void calc(int L,char *S)
	{
		s=0;
		l=L;
		rep(i,0,l-1)
			s+=e[l-i+1]*S[i],M(s);
	}
}a;

void solve()
{
	gets(s1);
	gets(s2);
	int l1=strlen(s1);
	a.calc(l1,s1);
	int a1=a.s;
	int l2=strlen(s2);
	a.calc(l1,s2);
	int ans=a1==a.s;
	rep(i,1,l2-l1)
	{
		a.update(s2[i-1],s2[l1-1+i]);
		ans+=a1==a.s;
	}
	cout<<ans<<endl;
}

int main()
{
	a.k=47;
	a.pre();
	cin>>n;
	gets(s1);
	rep(i,1,n)solve();
	return 0;
}


