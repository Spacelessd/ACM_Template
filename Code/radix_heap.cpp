#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000005,M=10000005;const ll C=1LL<<60;
struct Edge{
	int link[M],cost[M],next[M],son[N],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	Edge(){clear();}
	void addedge(int x,int y,int z){
		link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
	}
}e;
struct node{int x;ll d;node *pre,*next;};
struct bucket{
	ll l,r; bool exist; node *son;
	void insert(node *x){
		if (son)son->pre=x;
		x->pre=0;x->next=son;son=x;
	}
	void del(node *x){
		if (!x->pre){
			son=x->next;
			if (x->next)x->next->pre=0;
		}
		else {
			x->pre->next=x->next;
			if (x->next)x->next->pre=x->pre;
		}
	}
};
template<ll C>
struct radix_heap{
	bucket a[65],*now[N];node v[N];int nC;
	void clear(int n,int S){
		for (nC=0;;++nC){
			if (nC==0)a[nC].l=a[nC].r=0;
			else a[nC].l=1LL<<(nC-1),a[nC].r=(1LL<<nC)-1;
			a[nC].son=0;a[nC].exist=1;if (a[nC].r>=C)break;
		}
		for (int i=1;i<=n;++i)
			if (i!=S)v[i].x=i,v[i].d=C,a[nC].insert(v+i),now[i]=a+nC;
			else v[i].x=i,v[i].d=0,a[0].insert(v+i),now[i]=a+0;
	}
	node* find_min(){
		for (int i1=0;i1<=nC;++i1)
			if (a[i1].exist&&a[i1].son){
				ll mind=C+1;node *id;
				if (!i1){a[i1].del(id=a[i1].son);return id;}
				for (node *p=a[i1].son;p;p=p->next)if (p->d<mind)mind=p->d,id=p;
				for (int i=0;i<i1;++i){
					a[i].exist=1;
					if (i==0)a[i].l=a[i].r=mind;
					else a[i].l=mind+(1LL<<i-1),a[i].r=mind+(1LL<<i)-1;
				}
				a[i1-1].r=a[i1].r,a[i1].exist=0;
				for (node *p=a[i1].son,*next=p->next;p;p=next,next=p?p->next:0)if (p!=id)dec(p-v);
				a[i1].son=0;return id;
			}
		return 0;
	}
	void dec(int x){
		if (now[x]->exist&&v[x].d>=now[x]->l)return; now[x]->del(v+x);
		for (--now[x];!now[x]->exist||v[x].d<now[x]->l;--now[x]);
		now[x]->insert(v+x);
	}
	int SSSP(int S){
		while (1){
			node *p=find_min();if (!p)break; int x=p->x;
			for (int p=e.son[x];p;p=e.next[p]){
				int y=e.link[p];
				if (v[x].d+e.cost[p]<v[y].d)v[y].d=v[x].d+e.cost[p],dec(y);
			}
		}
	}
};
radix_heap<C> H;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1=clock();
	int n,m,x,y,z,S,T;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;++i)
		scanf("%d%d%d",&x,&y,&z),e.addedge(x,y,z);
	scanf("%d%d",&S,&T);
	//printf("read time=%d\n",clock()-t1);
	H.clear(n,S);H.SSSP(S);
	if (H.v[T].d<C)printf("%I64d\n",H.v[T].d);
	else printf("-1\n");
	//printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


