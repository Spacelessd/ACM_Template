#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
#define N 25005
struct result{
	int lmax,rmax,sum;
	result(int _lmax,int _rmax,int _sum):lmax(_lmax),rmax(_rmax),sum(_sum){}
	inline int max(int x,int y){return x>y?x:y;}
	result update(result x,result y){
		sum=lmax=rmax=0;
		sum+=x.sum;
		lmax=max(lmax,x.lmax);
		sum+=y.sum;
		rmax=max(rmax,y.rmax);
		lmax=max(lmax,x.sum+y.lmax);
		rmax=max(rmax,y.sum+x.rmax);
		return *this;
	}
};
result Tmp(0,0,0);
struct node;
node *get();
struct node{
	int l,r;int lmax,rmax,sum;
	node *lson,*rson;
	inline int max(int x,int y){return x>y?x:y;}
	node *update(){
		sum=lmax=rmax=0;
		if (lson!=NULL){
			sum+=lson->sum;
			lmax=max(lmax,lson->lmax);
		}
		if (rson!=NULL){
			sum+=rson->sum;
			rmax=max(rmax,rson->rmax);
		}
		if (lson!=NULL&&rson!=NULL){
			lmax=max(lmax,lson->sum+rson->lmax);
			rmax=max(rmax,rson->sum+lson->rmax);
		}
		return this;
	}
	node *set(int _l,int _r,node *_lson,node *_rson,int _lmax,int _rmax,int _sum){
		l=_l;r=_r;lson=_lson;rson=_rson;lmax=_lmax;rmax=_rmax;sum=_sum;
		return this;
	}
	node *Change(int x,int y){
		if (l==r)return get()->set(l,r,NULL,NULL,y>0?y:0,y>0?y:0,y);
		int mid=(l+r)>>1;node *tmp;
		if (x<=mid){
			if (lson==NULL)tmp=get()->set(l,mid,NULL,NULL,0,0,0);
				else tmp=lson;
			return get()->set(l,r,tmp->Change(x,y),rson,0,0,0)->update();
		}
		else {
			if (rson==NULL)tmp=get()->set(mid+1,r,NULL,NULL,0,0,0);
				else tmp=rson;
			return get()->set(l,r,lson,tmp->Change(x,y),0,0,0)->update();
		}
	}
	result Query(int ll,int rr){
		if (l==ll&&r==rr)return result(lmax,rmax,sum);
		int mid=(l+r)>>1;
		if (rr<=mid)return lson!=NULL?lson->Query(ll,rr):result(0,0,0);
		else if (ll>mid)return rson!=NULL?rson->Query(ll,rr):result(0,0,0);
		else {
			result tmp1=lson!=NULL?lson->Query(ll,mid):result(0,0,0),
			tmp2=rson!=NULL?rson->Query(mid+1,rr):result(0,0,0);
			return Tmp.update(tmp1,tmp2);
		}
	}
	void print(){
		printf("%d %d %d %d %d\n",l,r,lmax,rmax,sum);
		if (l==r)return;
		if (lson!=NULL)lson->print();
		if (rson!=NULL)rson->print();
	}
};
#define BUFFER_SIZE 10000
node *buffer=NULL,*cur;
inline node *get(){
	if (!buffer||cur==buffer+BUFFER_SIZE)
		buffer=new node[BUFFER_SIZE],cur=buffer;
	return cur++;
}
node *root[N];
int a[N],pred[N],visit[N];
int n,q,pre;
struct Node{
	int key,id;
};
bool cmp(const Node x,const Node y){
	return x.key<y.key;
}
Node A[N];
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;++i)scanf("%d",&a[i]);
	for (int i=1;i<=n;++i)A[i].key=a[i],A[i].id=i;
	std::sort(A+1,A+1+n,cmp);
	for (int i=1;i<=n;++i)if (i==1||A[i].key==A[i-1].key)pred[i]=pred[i-1];
		else pred[i]=i-1;
	root[1]=get()->set(1,n,NULL,NULL,0,0,0);
	for (int i=1;i<=n;++i)root[1]=root[1]->Change(i,1);
	for (int i=2;i<=n;++i){
		int j=pred[i];
		root[i]=root[i-1];
		while (j&&!visit[j]){
			visit[j]=1;
			root[i]=root[i]->Change(A[j].id,-1);
			--j;
		}
	}
	scanf("%d",&q);pre=0;
	while (q--){
		int tmp[5];
		for (int i=1;i<=4;++i)scanf("%d",&tmp[i]),tmp[i]=((tmp[i]+pre)%n+n)%n;
		for (int i=1;i<=4;++i)++tmp[i];
		std::sort(tmp+1,tmp+1+4);
		int l=1,r=n,mid;
		while (l<r){
			mid=(l+r+1)>>1;
			int ans1=tmp[1]<=tmp[2]-1?root[mid]->Query(tmp[1],tmp[2]-1).rmax:0,
				ans2=tmp[3]+1<=tmp[4]?root[mid]->Query(tmp[3]+1,tmp[4]).lmax:0,
				ans3=root[mid]->Query(tmp[2],tmp[3]).sum;
			int ans=ans1+ans2+ans3;
			if (ans>=0)l=mid;
				else r=mid-1;
		}
		printf("%d\n",A[l].key);
		pre=A[l].key;
	}
	system("pause");for (;;);
	return 0;
}


