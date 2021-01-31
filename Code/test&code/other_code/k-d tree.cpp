#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
using namespace std;
#define N 50005
#define K 5
#define M 10
struct P{int x[K],id;}a[N];
struct T{int x[K],min[K],max[K],id,split;T *l,*r;}f[N];T *f1;
int n,k,cmp_k,p[K],s;
pair<int,T*> A[M+1];
inline bool cmp(const P &a,const P &b){return a.x[cmp_k]<b.x[cmp_k];}
inline void update(T *x,T *son){
	if (!son)return;
	for (int i=0;i<k;++i)
		x->min[i]=min(x->min[i],son->min[i]),
		x->max[i]=max(x->max[i],son->max[i]);
}
void build(T *&root,int l,int r){
	if (l>r){root=0;return;}root=++f1;
	int d;double max=-1;
	for (int i=0;i<k;++i){
		double ave=0,sum=0;
		for (int j=l;j<=r;++j)ave+=a[j].x[i];
		ave/=r-l+1;
		for (int j=l;j<=r;++j)sum+=(a[j].x[i]-ave)*(a[j].x[i]-ave);
		if (sum>max)max=sum,d=i;
	}
	root->split=cmp_k=d;sort(a+l,a+r+1,cmp);
	int mid=(l+r)>>1; root->id=a[mid].id;
	for (int i=0;i<k;++i)root->min[i]=root->max[i]=root->x[i]=a[mid].x[i];
	if (l==r)return;
	if (l<=mid-1)build(root->l,l,mid-1),update(root,root->l);
	if (mid+1<=r)build(root->r,mid+1,r),update(root,root->r);
}
inline void upd(const pair<int,T*> &x){
	if (A[s].first<x.first||A[s].first==x.first&&A[s].second<x.second)return;
	for (int i=1;i<=s;++i)
		if (x.first<A[i].first||x.first==A[i].first&&x.second<A[i].second)
			{for (int j=s;j>i;--j)A[j]=A[j-1];A[i]=x;return;}
}
inline int sqr(int x){return x*x;}
inline int dist(int *x1,int *x2){
	int res=0;
	for (int i=0;i<k;++i)res+=sqr(x1[i]-x2[i]);
	return res;
}
inline int dist(int *x1,int *x2,int *x3){
	int res=0;
	for (int i=0;i<k;++i)
		if (x1[i]<x2[i])res+=sqr(x2[i]-x1[i]);
		else if (x1[i]>x3[i])res+=sqr(x1[i]-x3[i]);
	return res;
}
void ask(T *root,int l,int r){
	if (l>r)return; int d=root->split;
	upd(make_pair(dist(root->x,p),root));
	if (l==r||dist(p,root->min,root->max)>A[s].first)return;
	int mid=(l+r)>>1;
	if (p[d]<root->x[d])ask(root->l,l,mid-1),ask(root->r,mid+1,r);
	else ask(root->r,mid+1,r),ask(root->l,l,mid-1);
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1=clock();
	while (scanf("%d%d",&n,&k)!=EOF){
		for (int i=1;i<=n;++i)
			for (int j=0;j<k;++j)scanf("%d",&a[i].x[j]);
		for (int i=1;i<=n;++i)a[i].id=i;
		f1=f;T *root;build(root,1,n);
		int q;scanf("%d",&q);
		while (q--){
			for (int i=0;i<k;++i)scanf("%d",&p[i]);
			scanf("%d",&s);
			for(int i=1;i<=s;++i)A[i]=make_pair(1<<30,(T*)NULL);
			ask(root,1,n);
			printf("the closest %d points are:\n",s);
			for (int i=1;i<=s;++i)
				for (int j=0;j<k;++j)printf("%d%c",A[i].second->x[j],j==k-1?'\n':' ');
		}
	}
	//printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


