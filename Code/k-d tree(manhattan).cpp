#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
using namespace std;
const int N=1000005,K=2,k=2;
struct P{int x[K];}a[N];
struct T{int x[K],min[K],max[K],split;T *l,*r;}f[N];T *f1;
int n,m,cmp_k,p[K],ans;
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
		for (int j=l;j<=r;++j)ave+=a[j].x[i];ave/=r-l+1;
		for (int j=l;j<=r;++j)sum+=(a[j].x[i]-ave)*(a[j].x[i]-ave);
		if (sum>max)max=sum,d=i;
	}
	root->split=cmp_k=d;int mid=(l+r)>>1;nth_element(a+l,a+mid+1,a+r+1,cmp);
	for (int i=0;i<k;++i)root->min[i]=root->max[i]=root->x[i]=a[mid].x[i];
	build(root->l,l,mid-1),update(root,root->l);
	build(root->r,mid+1,r),update(root,root->r);
}
void insert(T *&root,int fd=0){
	if (!root){
		root=++f1;root->split=fd+1==k?0:fd+1;
		for (int i=0;i<k;++i)root->min[i]=root->max[i]=root->x[i]=p[i];
		return;
	}
	for (int i=0;i<k;++i)
		root->min[i]=min(root->min[i],p[i]),
		root->max[i]=max(root->max[i],p[i]);
	int d=root->split;
	if (p[d]<root->x[d])insert(root->l,d);else insert(root->r,d);
}
inline void upd(int x){if (x<ans)ans=x;}
inline int dist(int *x1,int *x2){
	int res=0;
	for (int i=0;i<k;++i)res+=abs(x1[i]-x2[i]);
	return res;
}
inline int dist(int *x1,int *x2,int *x3){
	int res=0;
	for (int i=0;i<k;++i)
		if (x1[i]<x2[i])res+=x2[i]-x1[i];
		else if (x1[i]>x3[i])res+=x1[i]-x3[i];
	return res;
}
void ask(T *root){
	if (!root||dist(p,root->min,root->max)>=ans)return;
	upd(dist(root->x,p));int d=root->split;
	if (p[d]<root->x[d])ask(root->l),ask(root->r);
	else ask(root->r),ask(root->l);
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1=clock();
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i)
		for (int j=0;j<k;++j)scanf("%d",&a[i].x[j]);
	f1=f;T *root=0;build(root,1,n);
	while (m--){
		int ch;scanf("%d",&ch);
		for (int i=0;i<k;++i)scanf("%d",&p[i]);
		if (ch==1)insert(root);
		else ans=1<<30,ask(root),printf("%d\n",ans);
	}
	//printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


