#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 5005
#define ll long long
int a[N][N],d[N];
ll prim(int n){
	const int oo=(1LL<<31)-1;ll ans=0;
	for (int i=1;i<=n;++i)d[i]=a[1][i];
	d[1]=-oo;
	for (int i1=1;i1<n;++i1){
		int min=oo,id;
		for (int i=1;i<=n;++i)
			if (d[i]!=-oo&&min>d[i])min=d[i],id=i;
		ans+=d[id];d[id]=-oo;
		for (int i=1;i<=n;++i)
			if (a[id][i]<d[i])d[i]=a[id][i];
	}
	return ans;
}
inline void read(int &x){
	char ch;int bo=0;x=0;
	for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
	for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
	if (bo)x=-x;
}
int main()
{
	freopen("mst.in","r",stdin);
	freopen("mst.out","w",stdout);
	int n,m;
	/*scanf("%d",&n);
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)scanf("%d",&a[i][j]);*/
	read(n);read(m);
	if (n>=N)return 0;
	memset(a,127,sizeof(a));
	for (int i=1;i<=m;++i){
		int x,y,z;read(x);read(y);read(z);
		if (z<a[x][y])a[x][y]=a[y][x]=z;
	}
	ll ans=prim(n);
	printf("%I64d\n",ans);
	//system("pause");for (;;);
	return 0;
}


