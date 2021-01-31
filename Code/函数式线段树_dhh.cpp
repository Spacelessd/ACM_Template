#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
using namespace std;
const int N=20005,S=1000005,oo=2000000000;
int n,m,ans=0;
int a[N],p[N],c[5],root[N];
struct func_segment_tree{
	int L[S],R[S],Min[S],Max[S],add[S],tot;
	func_segment_tree(){tot=0;}
	void build(int &t,int l,int r){
		if (!t) t=++tot; Min[t]=-r; Max[t]=-l; add[t]=0;
		if (l==r) return; int mid=(l+r)>>1;
		build(L[t],l,mid); build(R[t],mid+1,r);
	}
	void update(int t){
		Min[t]=add[t]+min(Min[L[t]],Min[R[t]]);
		Max[t]=add[t]+max(Max[L[t]],Max[R[t]]);
	}
	void modify(int t,int &t1,int l,int r,int ll,int rr){
		t1=++tot; add[t1]=add[t];
		if (l==ll && r==rr){
			L[t1]=L[t]; R[t1]=R[t];
			Min[t1]=Min[t]+2; Max[t1]=Max[t]+2;
			add[t1]=add[t]+2; return;
		}
		int mid=(l+r)>>1;
		if (rr<=mid) modify(L[t],L[t1],l,mid,ll,rr),R[t1]=R[t];
		else if (ll>mid) modify(R[t],R[t1],mid+1,r,ll,rr),L[t1]=L[t];
			else modify(L[t],L[t1],l,mid,ll,mid)
				,modify(R[t],R[t1],mid+1,r,mid+1,rr);
		update(t1);
	}
	int query_Min(int t,int l,int r,int ll,int rr){
		if (l==ll && r==rr) return Min[t]; int mid=(l+r)>>1;
		if (rr<=mid) return add[t]+query_Min(L[t],l,mid,ll,rr);
		if (ll>mid) return add[t]+query_Min(R[t],mid+1,r,ll,rr);
		return add[t]+min(query_Min(L[t],l,mid,ll,mid)
					,query_Min(R[t],mid+1,r,mid+1,rr));
	}
	int query_Max(int t,int l,int r,int ll,int rr){
		if (l==ll && r==rr) return Max[t]; int mid=(l+r)>>1;
		if (rr<=mid) return add[t]+query_Max(L[t],l,mid,ll,rr);
		if (ll>mid) return add[t]+query_Max(R[t],mid+1,r,ll,rr);
		return add[t]+max(query_Max(L[t],l,mid,ll,mid)
					,query_Max(R[t],mid+1,r,mid+1,rr));
	}
};
func_segment_tree T;
bool cmp(const int i,const int j){return a[i]<a[j];}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d",&n); for (int i=1;i<=n;++i) scanf("%d",&a[i]),p[i]=i;
	sort(p+1,p+n+1,cmp); T.Min[0]=oo; T.Max[0]=-oo; T.build(root[0],1,n);
	for (int i=1;i<=n;++i) T.modify(root[i-1],root[i],1,n,p[i],n);
	scanf("%d",&m);
	while (m--){
		for (int i=0;i<4;++i) scanf("%d",&c[i]),c[i]=(c[i]+ans)%n;
		sort(c,c+4); int A=c[0],B=c[1],C=c[2]+1,D=c[3]+1;
		int l=1,r=n,mid,z1,z2;
		while (l<r){
			mid=(l+r)>>1; z1=T.query_Min(root[mid],1,n,C,D);
			if (A) z2=T.query_Max(root[mid],1,n,A,B);
			else if (B) z2=max(0,T.query_Max(root[mid],1,n,1,B)); else z2=0;
			if (z1-z2<=0) l=mid+1; else r=mid;
		}
		printf("%d\n",ans=a[p[l]]);
	}
	system("pause");for (;;); 
	return 0;
}


