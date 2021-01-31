#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 100005
#define null 2147483647
struct node{
	int m,cover,add;
};
struct tree{
	node *a;
	int *e;
	inline int max(int x,int y){return x>y?x:y;}
	tree(){}
	void make(int len=10){
		a=new node[(len+1)*4];
		e=new int[len+2];
	}
	void build(int t,int l,int r){
		a[t].cover=null;
		if (l==r) {a[t].m=e[l];return;}
		int mid=(l+r)>>1;
		build(t*2,l,mid);
		build(t*2+1,mid+1,r);
		a[t].m=max(a[t*2].m,a[t*2+1].m);
	}
	void down(int t){
		if (a[t].cover<null){
			a[t*2+1].cover=a[t*2+1].m=a[t*2].cover=a[t*2].m=a[t].cover;
			a[t*2].add=a[t*2+1].add=0;
			a[t].cover=null;
		}
		if (a[t].add){
			a[t*2].m+=a[t].add; a[t*2+1].m+=a[t].add;
			if (a[t*2].cover<null) a[t*2].cover+=a[t].add;
				else a[t*2].add+=a[t].add;
			if (a[t*2+1].cover<null) a[t*2+1].cover+=a[t].add;
				else a[t*2+1].add+=a[t].add;
			a[t].add=0;
		}
	}
	void change(int t,int l,int r,int y,int v){
		if (l==r) {a[t].m=v; return;}
		int mid=(l+r)>>1; down(t);
		if (y<=mid) change(t*2,l,mid,y,v);
		else change(t*2+1,mid+1,r,y,v);
		a[t].m=max(a[t*2].m,a[t*2+1].m);
	}
	void cover(int t,int l,int r,int ll,int rr,int v){
		if (l==ll && r==rr){
			a[t].m=a[t].cover=v; a[t].add=0; return;
		}
		int mid=(l+r)>>1; down(t);
		if (rr<=mid) cover(t*2,l,mid,ll,rr,v);
			else if (ll>mid) cover(t*2+1,mid+1,r,ll,rr,v);
				else cover(t*2,l,mid,ll,mid,v),cover(t*2+1,mid+1,r,mid+1,rr,v);
		a[t].m=max(a[t*2].m,a[t*2+1].m);
	}
	void add(int t,int l,int r,int ll,int rr,int v){
		if (l==ll && r==rr){
			if (a[t].cover<null) a[t].cover+=v;
			else a[t].add+=v;
			a[t].m+=v; return;
		}
		int mid=(l+r)>>1; down(t);
		if (rr<=mid) add(t*2,l,mid,ll,rr,v);
			else if (ll>mid) add(t*2+1,mid+1,r,ll,rr,v);
			  else add(t*2,l,mid,ll,mid,v),add(t*2+1,mid+1,r,mid+1,rr,v);
		a[t].m=max(a[t*2].m,a[t*2+1].m);
	}
	int query(int t,int l,int r,int ll,int rr){
		if (l==ll && r==rr) return a[t].m;
		int mid=(l+r)>>1; down(t);
		if (rr<=mid) return query(t*2,l,mid,ll,rr);
		if (ll>mid) return query(t*2+1,mid+1,r,ll,rr);
		return max(query(t*2,l,mid,ll,mid),query(t*2+1,mid+1,r,mid+1,rr));
	}
};
tree a;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	
	system("pause");for (;;);
	return 0;
}


