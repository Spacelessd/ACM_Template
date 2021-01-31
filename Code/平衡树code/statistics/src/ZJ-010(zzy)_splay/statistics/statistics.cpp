#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn=1000005;
const int mod=1000000007;
int Size[maxn],Left[maxn],Right[maxn],Father[maxn],root;
long long f[maxn],Key[maxn],a,b,c,n,ans;

inline void update(int x){ Size[x]=Size[Left[x]]+Size[Right[x]]+1; }
inline void zig(int x)
{
	int y=Father[x],z=Father[y];
	Father[Right[x]]=y; Left[y]=Right[x];
	Right[x]=y; Father[y]=x;
	Father[x]=z;
	if (y==Left[z]) Left[z]=x; else Right[z]=x;
	update(y);
}

inline void zag(int x)
{
	int y=Father[x],z=Father[y];
	Father[Left[x]]=y; Right[y]=Left[x];
	Left[x]=y; Father[y]=x;
	Father[x]=z;
	if (y==Left[z]) Left[z]=x; else Right[z]=x;
	update(y);
}

inline void splay(int x,int &root)
{
	int y,z;
	while (Father[x]!=0)
	{
		y=Father[x]; z=Father[y];
		if (z==0)
			{if (x==Left[y]) zig(x); else zag(x);}
		else
		{
			if (Left[z]==y)
				{if (Left[y]==x) zig(y),zig(x); else zag(x),zig(x);}
			else
				{if (Left[y]==x) zig(x),zag(x); else zag(y),zag(x);}
		}
	}
	root=x;
	update(x);
}

void insert(int &root,int x,int k)
{
	if (root==0){ Key[x]=k; root=x; Size[x]=0; return;}
	int q=root;
	while (q)
	{
		if (k<Key[q])
		{
			if (Left[q]==0) {Key[x]=k; Left[q]=x; Father[x]=q; break;}
				else q=Left[q];
		}
		else
		{
			if (Right[q]==0) {Key[x]=k; Right[q]=x; Father[x]=q; break;}
				else q=Right[q];
		}
	}
	splay(x,root);
}

int findkth(int k)
{
	int p=root;
	while (k)
	{
		if (k==Size[Left[p]]+1) {splay(p,root);return p;}
		else
		{
			if (k<Size[Left[p]]+1) p=Left[p];
			else k-=Size[Left[p]]+1,p=Right[p];
		}
	}
}

int main()
{
	freopen("statistics.in","r",stdin);
	freopen("statistics.out","w",stdout);
	cin>>a>>b>>c>>n;
	root=0;
	f[1]=1; ans=1; insert(root,1,1);
	for (int i=2; i<=n; i++)
	{
		int p=findkth(i/2);
		f[i]=(a*Key[p]+b*i+c)%mod;
		ans+=f[i];
		insert(root,i,f[i]);
	}
	cout<<ans<<endl;
	return 0;
}


