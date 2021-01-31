#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
#define N 200005
struct tree{
	int key[N],num[N];
}T[21];
int a[N];
void build(int l,int r,int dep){
	if (l==r)return;
	int i,mid=(l+r)>>1,ll=l-1,rr=mid,sum=0,equal=0;
	for (i=l;i<=r;++i)if (T[dep].key[i]<a[mid])++equal;
	equal=mid-l-1-equal;
	for (i=l;i<=r;++i)
		if (T[dep].key[i]<a[mid]){
			T[dep+1].key[++ll]=T[dep].key[i];T[dep].num[i]=++sum;
		}
		else if (T[dep].key[i]==a[mid]&&equal){
			--equal;T[dep+1].key[++ll]=T[dep].key[i];T[dep].num[i]=++sum;
		}
		else {
			T[dep+1].key[++rr]=T[dep].key[i];T[dep].num[i]=sum;
		}
	build(l,mid,dep+1);
	build(mid+1,r,dep+1);
}
int Query(int l,int r,int ll,int rr,int k,int dep){
	if (l==ll&&r==rr)return a[l+k-1];
	int mid=(l+r)>>1,sx=l==ll?0:T[dep].num[ll-1],sy=T[dep].num[rr];
	if (sy-sx>=k)return Query(l,mid,l+sx,l+sy-1,k,dep+1);
		else return Query(mid+1,r,mid+ll-l-sx+1,mid+rr-l+1-sy,k-(sy-sx),dep+1);
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	int n,m,x,y,z; scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i)scanf("%d",&a[i]);
	memcpy(T[0].key,a,sizeof(int)*(n+1));
	std::sort(a+1,a+1+n);
	build(1,n,0);
	for (int i=1;i<=m;++i){
		scanf("%d%d%d",&x,&y,&z);
		if (x>y){int tmp=x;x=y;y=tmp;}
		printf("%d\n",Query(1,n,x,y,z,0));
	}
	//system("pause");
	return 0;
}


