#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
#define N 100005
#define LL long long
struct Tree{
	struct tree{
		int key[N],num[N];
		LL sum[N];
	}T[21];
	int a[N];LL result;
	void build(int l,int r,int dep){
		T[dep].sum[l]=T[dep].key[l];
		for (int i=l+1;i<=r;++i)T[dep].sum[i]=T[dep].sum[i-1]+T[dep].key[i];
		if (l==r)return;
		int i,mid=(l+r)>>1,ll=l-1,rr=mid,sum=0,equal=0;
		for (i=l;i<=r;++i)if (T[dep].key[i]<a[mid])++equal;
		equal=mid-l+1-equal;
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
		if (l==r)return T[dep].key[l];
		int mid=(l+r)>>1,sx=l==ll?0:T[dep].num[ll-1],sy=T[dep].num[rr];
		if (sy-sx>=k){
			int tmp=Query(l,mid,l+sx,l+sy-1,k,dep+1);
			LL s=0;
			if (rr-l+1-sy)s+=T[dep+1].sum[mid+rr-l+1-sy];
			if (ll-l-sx)s-=T[dep+1].sum[mid+ll-l-sx];
			result+=s-(LL)(rr-ll+1-(sy-sx))*(LL)tmp;
			return tmp;
		}
		else {
			int tmp=Query(mid+1,r,mid+ll-l-sx+1,mid+rr-l+1-sy,k-(sy-sx),dep+1);
			LL s=0;
			if (sy)s+=T[dep+1].sum[l+sy-1];
			if (sx)s-=T[dep+1].sum[l+sx-1];
			result+=(LL)(sy-sx)*(LL)tmp-s;
			return tmp;
		}
	}
}zzy1,zzy2;
int A[N],B[N];
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n,m,x,y,z; scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i)scanf("%d",&A[i]);
	for (int i=1;i<=n;++i)scanf("%d",&B[i]);
	
	for (int i=1;i<=n;++i)zzy1.a[i]=A[i]+B[i];
	memcpy(zzy1.T[0].key,zzy1.a,sizeof(int)*(n+1));
	std::sort(zzy1.a+1,zzy1.a+1+n);
	zzy1.build(1,n,0);
	
	for (int i=1;i<=n;++i)zzy2.a[i]=A[i]-B[i];
	memcpy(zzy2.T[0].key,zzy2.a,sizeof(int)*(n+1));
	std::sort(zzy2.a+1,zzy2.a+1+n);
	zzy2.build(1,n,0);
	
	for (int i=1;i<=m;++i){
		scanf("%d%d",&x,&y);z=(y-x+1+1)/2;
		zzy1.result=0;zzy1.Query(1,n,x,y,z,0);
		zzy2.result=0;zzy2.Query(1,n,x,y,z,0);
		printf("%.2lf\n",double(zzy1.result+zzy2.result)/2.0);
	}
	system("pause");for (;;);
	return 0;
}


