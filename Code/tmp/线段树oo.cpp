#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct Tree{
	#define N 100005
	struct node{
		int L,R,sum;
	};
	node a[N*32];int tree;
	int Newnode(){
		++tree;a[tree].L=a[tree].R=0;a[tree].sum=0;
		return tree;
	}
	void clear(){tree=0;Newnode();}
	Tree(){clear();}
	void add(int t,int l,int r,int x){
		if (l==r){
			++a[t].sum;return;
		}
		int mid=(l+r)>>1;
		if (x<=mid){
			if (!a[t].L)a[t].L=Newnode();
			add(a[t].L,l,mid,x);
		}
		else {
			if (!a[t].R)a[t].R=Newnode();
			add(a[t].R,mid+1,r,x);
		}
		a[t].sum=0;
		if (a[t].L)a[t].sum+=a[a[t].L].sum;
		if (a[t].R)a[t].sum+=a[a[t].R].sum;
	}
	int Qsum(int t,int l,int r,int ll,int rr){
		if (l==ll&&r==rr)return a[t].sum;
		int mid=(l+r)>>1;
		if (rr<=mid)return a[t].L?Qsum(a[t].L,l,mid,ll,rr):0;
			else if (ll>mid)return a[t].R?Qsum(a[t].R,mid+1,r,ll,rr):0;
			else return (a[t].L?Qsum(a[t].L,l,mid,ll,mid):0)+(a[t].R?Qsum(a[t].R,mid+1,r,mid+1,rr):0);
	}
};
Tree T;

struct Tree1{
	#define N 100005
	#define oo 1000000000
	struct node{
		int L,R,max;
	};
	node a[N*32];int tree;
	int Newnode(){
		++tree;a[tree].L=a[tree].R=0;a[tree].max=-oo;
		return tree;
	}
	void clear(){tree=0;Newnode();}
	Tree1(){clear();}
	inline int max(int x,int y){return x>y?x:y;}
	void insert(int t,int l,int r,int x,int y){
		if (l==r){
			a[t].max=y;return;
		}
		int mid=(l+r)>>1;
		if (x<=mid){
			if (!a[t].L)a[t].L=Newnode();
			insert(a[t].L,l,mid,x,y);
		}
		else {
			if (!a[t].R)a[t].R=Newnode();
			insert(a[t].R,mid+1,r,x,y);
		}
		a[t].max=-oo;
		if (a[t].L)a[t].max=max(a[t].max,a[a[t].L].max);
		if (a[t].R)a[t].max=max(a[t].max,a[a[t].R].max);
	}
	int Qmax(int t,int l,int r,int ll,int rr){
		if (l==ll&&r==rr)return a[t].max;
		int mid=(l+r)>>1;
		if (rr<=mid)return a[t].L?Qmax(a[t].L,l,mid,ll,rr):-oo;
			else if (ll>mid)return a[t].R?Qmax(a[t].R,mid+1,r,ll,rr):-oo;
			else return max((a[t].L?Qmax(a[t].L,l,mid,ll,mid):-oo),(a[t].R?Qmax(a[t].R,mid+1,r,mid+1,rr):-oo));
	}
};
Tree1 T1;
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	
	system("pause");
	return 0;
}


