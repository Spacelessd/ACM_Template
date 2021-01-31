#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=20000;
const int mod=1000000007;
long long a,b,c,n,tmp[maxn],f[maxn],ans;

int main()
{
	freopen("statistics.in","r",stdin);
	freopen("bl.out","w",stdout);
	cin>>a>>b>>c>>n;
	f[1]=1; ans=1;
	for (int i=2; i<=n; i++)
	{
		memcpy(tmp,f,sizeof(f));
		sort(tmp+1,tmp+i);
		f[i]+=(tmp[i/2]*a+b*i+c)%mod;
		ans+=f[i];
	}
	cout<<ans<<endl;
}
