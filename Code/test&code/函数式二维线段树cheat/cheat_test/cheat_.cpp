#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
using namespace std;
#define N 1005
int n,m;
int lly,rry,y;
struct node;
node *get();
struct node{
	int l,r;
	node *lson,*rson,*T;
	int sum;
	node *set(int _l,int _r,node *_lson,node *_rson){
		l=_l;r=_r;lson=_lson;rson=_rson;sum=0;
		if (lson!=NULL)sum+=lson->sum;
		if (rson!=NULL)sum+=rson->sum;
		return this;
	}
	node *set(int _lr,int _sum){
		l=r=_lr;sum=_sum;return this;
	}
	node *set(int _l,int _r,node *_lson,node *_rson,node *_T){
		l=_l;r=_r;lson=_lson;rson=_rson;T=_T;
		return this;
	}
	node *add1(int y){
		if (l==r&&l==y)return get()->set(l,1);
		int mid=(l+r)>>1;node *tmp;
		if (y<=mid){
			if (lson==NULL)tmp=get()->set(l,mid,NULL,NULL);
				else tmp=lson;
			return set(l,r,tmp->add1(y),rson);
		}
		else {
			if (rson==NULL)tmp=get()->set(mid+1,r,NULL,NULL);
				else tmp=rson;
			return set(l,r,lson,tmp->add1(y));
		}
	}
	node *add(int x){
		node *tmp;
		if (l==r&&l==x){
			if (T==NULL)tmp=get()->set(1,m,NULL,NULL);
				else tmp=T;
			return get()->set(l,r,lson,rson,tmp->add1(y));
		}
		int mid=(l+r)>>1;
		if (x<=mid){
			if (lson==NULL)tmp=get()->set(l,mid,NULL,NULL,NULL);
				else tmp=lson;
			return set(l,r,tmp->add(x),rson,T);
		}
		else {
			if (rson==NULL)tmp=get()->set(mid+1,r,NULL,NULL,NULL);
				else tmp=rson;
			return set(l,r,lson,tmp->add(x),T);
		}
	}
	int query1(int lly,int rry){
		if (lly==l&&rry==r)return sum;
		int mid=(l+r)>>1;
		if (rry<=mid)return lson!=NULL?lson->query1(lly,rry):0;
		else if (lly>mid)return rson!=NULL?rson->query1(lly,rry):0;
		else return (lson!=NULL?lson->query1(lly,mid):0)
			+(rson!=NULL?rson->query1(mid+1,rry):0);
	}
	int query(int llx,int rrx){
		if (llx==l&&rrx==r)return T!=NULL?T->query1(lly,rry):0;
		int mid=(l+r)>>1;
		if (rrx<=mid)return lson!=NULL?lson->query(llx,rrx):0;
		else if (llx>mid)return rson!=NULL?rson->query(llx,rrx):0;
		else return (lson!=NULL?lson->query(llx,mid):0)
			+(rson!=NULL?rson->query(mid+1,rrx):0);
	}
};
#define BUFFER_SIZE 10000
node *buffer=NULL,*cur;
node *get(){
	if (!buffer||cur==buffer+BUFFER_SIZE)
		cur=buffer=new node[BUFFER_SIZE];
	return cur++;
}
struct Query{
	int x,y,key;
};
Query Q[N*N];
bool cmp(const Query x,const Query y){
	return x.key<y.key;
}
node *root[N*N];
int a[N][N];
int p,q,l,ans;
int key[N*N];
#define M 3005
int pa,pb,pc;
long long paa[M],pbb[M],pcc[M];
int get(int x,int y,int p){
	return (paa[x%pa+1]+pbb[x%pb+1]+pcc[x%pc+1]
	+paa[y%pa+1]+pbb[y%pb+1]+pcc[y%pc+1])%p;
}
void init(){
	scanf("%d",&pa);
	for (int i=1;i<=pa;++i)scanf("%d",&paa[i]);
	scanf("%d",&pb);
	for (int i=1;i<=pb;++i)scanf("%d",&pbb[i]);
	scanf("%d",&pc);
	for (int i=1;i<=pc;++i)scanf("%d",&pcc[i]);
	scanf("%d%d%d",&n,&m,&p);l=0;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j){
			a[i][j]=get(i,j,p)+1;
			++l;Q[l].x=i;Q[l].y=j;Q[l].key=a[i][j];
			key[l]=a[i][j];
		}
	sort(Q+1,Q+l+1,cmp);sort(key+1,key+l+1);
	root[0]=get()->set(1,n,NULL,NULL,NULL);
	for (int i=1;i<=n*m;++i){
		y=Q[i].y;root[i]=root[i-1]->add(Q[i].x);
	}
}
int main(){
	freopen("cheat.in","r",stdin);
	//freopen("cheat.out","w",stdout);
	init();
	scanf("%d",&q);
	for (int i=1;i<=q;++i){
		int x1=get(i,1,n)+1,y1=get(i,2,m)+1,x2=get(i,3,n)+1,y2=get(i,4,m)+1,
		l=get(i,5,p)+1,r=get(i,6,p)+1;
		if (x1>x2)swap(x1,x2);
		if (y1>y2)swap(y1,y2);
		if (l>r)swap(l,r);
		lly=y1;rry=y2;
		int tmp=0;
		int L=1,R=l;
		while (L<R){
			int mid=(L+R+1)>>1;
			if (key[mid]<l)L=mid;
				else R=mid-1;
		}
		if (key[L]>=l)--L;
		tmp+=root[L]->query(x1,x2);
		printf("%d\n",L);
		L=1,R=l;
		while (L<R){
			int mid=(L+R+1)>>1;
			if (key[mid]<=l)L=mid;
				else R=mid-1;
		}
		tmp-=root[L]->query(x1,x2);
		ans^=tmp;
	}
	printf("%d\n",ans);
	system("pause");for (;;);
	return 0;
}


