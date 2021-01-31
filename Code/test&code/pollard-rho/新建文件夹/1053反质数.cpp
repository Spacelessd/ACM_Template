#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<cstring>
#define rep(i,n) for(int i=0;i<n;i++)
#define pb push_back
using namespace std;
const int inf=~0U>>1,maxp=1000;
int Ps[maxp],pnt=0,N;
typedef long long ll;
bool IsPrime(int p)
{
	if(p==2)return true;
	if(p%2==0) return false;
	for(int i=3;i*i<=p;i+=2)if(p%i==0) return false;
	return true;
}
struct Answer
{
	int ans,num;
	Answer(){ans=1;num=1;}
	void Update(const Answer&a)
	{
		if(a.ans>ans||(a.ans==ans&&a.num<num)) *this=a;
	}
	Answer Mul(int x,int c)
	{
		Answer ret;
		ret.ans=ans*(c+1);
		ret.num=num*x;
		return ret;
	}
}Ans;
void GetPrime()
{
	for(int i=2;i<maxp&&pnt<9;i++) if(IsPrime(i)) Ps[pnt++]=i;
}
void dfs(int now,int pre,ll N,Answer a)
{
	if(N<Ps[now]||now>=pnt||!pre){Ans.Update(a);return;}
	ll s=1;rep(i,pre) s*=Ps[now];
	for(int i=pre;i>=0;--i)
	{
		if(s<=N)dfs(now+1,i,N/s,a.Mul(s,i));
		s/=Ps[now];
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	cin>>N;
	GetPrime();
	dfs(0,15,N,Answer());
	long long k=1;
	cout<<Ans.num<<" "<<Ans.ans<<endl;
	ll rp=Ans.num;
	for (int i=2;i*i<=rp;++i)if (rp%i==0){
		int c=0;while (rp%i==0)rp/=i,++c;
		printf("%d^%d*",i,c);
	}
	if (rp>1)printf("%d^%d\n",(int)rp,1);
	system("pause");for (;;);
	return 0;
}


