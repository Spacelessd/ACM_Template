#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
#define N 3000005
#define M 5000005
#define ll long long
struct edge{int x,y,z;}e[M];
bool cmp(const edge &x,const edge &y){return x.z<y.z;}
int f[N];
int find(int x){
	if (f[x]==x)return x;
	else return f[x]=find(f[x]);
}
inline void read(int &x){
	char ch;int bo=0;x=0;
	for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
	for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
	if (bo)x=-x;
}
//»ùÊýÅÅÐò n log W
void radix_sort(edge A[],int l,int r){
	#define base 65535
	#define W 16
	static edge B[M];
	static int s[base+1];
	A+=l-1;r-=l-1;l=1;
	edge *a=A,*b=B;int x=0;
	for (int i1=1;i1<=2;++i1){
		for (int i=0;i<=base;++i)s[i]=0;
		for (int i=1;i<=r;++i)++s[a[i].z>>x&base];
		for (int i=1;i<=base;++i)s[i]+=s[i-1];
		for (int i=r;i>=1;--i)b[s[a[i].z>>x&base]--]=a[i];
		edge *tmp=a;a=b;b=tmp;
		x+=W;
	}
	if (a!=A)for (int i=1;i<=r;++i)A[i]=a[i];
	#undef W
	#undef base
}
int main()
{
	freopen("mst.in","r",stdin);
	freopen("mst.out","w",stdout);
	int n,m;ll ans=0;read(n);read(m);
	for (int i=1;i<=m;++i)read(e[i].x),read(e[i].y),read(e[i].z);
	//std::sort(e+1,e+1+m,cmp);
	radix_sort(e,1,m);
	for (int i=1;i<=n;++i)f[i]=i;
	for (int i=1;i<=m;++i){
		int f1=find(e[i].x),f2=find(e[i].y);
		if (f1!=f2)f[f1]=f2,ans+=e[i].z;
	}
	printf("%I64d\n",ans);
	//for (int i=1;i<=m;++i)if (choose[i])printf("%d\n",i);
	//system("pause");for (;;);
	return 0;
}


