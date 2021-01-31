#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 200005
#define ll long long
#define oo (1LL<<60)
struct node{
	ll key;int size;
	node *l,*r,*p;
	void update(){
		size=l->size+r->size+1;
	}
};
node a[N],*null,*root[N],*stack[N],**stack1;
void clear(){
	null=new node;null->l=null->r=null;
	null->size=0;null->key=-oo;stack1=stack+N;
	for (int i=0;i<N;++i)stack[i]=a+i;
}
node *Newnode(ll key){
	node *p=*(--stack1);p->l=p->r=p->p=null;
	p->size=1;p->key=key;return p;
}
void zig(node *x){
	node *y=x->p,*z=y->p;
	if (z->l==y) z->l=x;else z->r=x;
	x->p=z;y->p=x;y->l=x->r;x->r=y;
	y->l->p=y;y->update();
}
void zag(node *x){
	node *y=x->p,*z=y->p;
	if (z->l==y) z->l=x;else z->r=x;
	x->p=z;y->p=x;y->r=x->l;x->l=y;
	y->r->p=y;y->update();
}
void splay(node *&root,node *x){
	if (x==null) return;
	node *y,*z,*fa=root->p;
	while (x->p!=fa){
		y=x->p;z=y->p;
		if (z==fa) if (x==y->l)zig(x);else zag(x);
		else
			if (y==z->l)
				if (x==y->l)zig(y),zig(x);
				else zag(x),zig(x);
			else
				if (x==y->r)zag(y),zag(x);
				else zig(x),zag(x);
	}
	x->update();root=x;
}
void insert(node *&root,ll key){
	node *x=root,*y=null,*z=Newnode(key);
	if (root==null){root=z;return;}
	while (x!=null){
		y=x;
		if (z->key<x->key)x=x->l;
			else x=x->r;
	}
	z->p=y;
	if (z->key<y->key)y->l=z;
		else y->r=z;
	splay(root,z);
}
int find(node *&root,ll y){
	int res=0;node *x=root,*last=null;
	while (x!=null){
		if (x->key<=y)res+=x->l->size+1,last=x,x=x->r;
		else last=x,x=x->l;
	}
	splay(root,last);return res;
}
void merge(node *x,node *&root){
	if (x==null)return;
	merge(x->l,root);merge(x->r,root);insert(root,x->key);*stack1++=x;
}
void print(node *x){
	if (x==null)return;
	print(x->l);
	printf("nie %d\n",x->key);
	print(x->r);
}
#define link Link
ll dist[N],cost[N*2];int size[N],q[N],dep[N],link[N*2],next[N*2],son[N],ans[N],l=0,n;
void addedge(int x,int y,ll z){link[++l]=y;next[l]=son[x];cost[l]=z;son[x]=l;}
void bfs(int S){
	int h=1,t=1; q[1]=S; dep[S]=1;
	while (h<=t){
		int i=q[h++];
		for (int p=son[i];p;p=next[p]){
			int j=link[p]; if (dep[j])continue;
			dist[j]=dist[i]+cost[p]; dep[j]=dep[i]+1; q[++t]=j;
		}
	}
	for (int i1=n;i1;--i1){
		int i=q[i1]; size[i]=1;
		for (int p=son[i];p;p=next[p])
			if (dep[link[p]]>dep[i])size[i]+=size[link[p]];
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1=clock();
	int x,y;ll z,len;clear();scanf("%d%I64d",&n,&len);
	for (int i=2;i<=n;++i)scanf("%d%I64d",&x,&z),addedge(x,i,z);
	bfs(1);
	for (int i1=n;i1;--i1){
		int i=q[i1],max=0,id=0;ans[i]=1;root[i]=null;
		for (int p=son[i];p;p=next[p]){
			int j=link[p];if (dep[j]<dep[i])continue;
			if (size[j]>max)max=size[j],id=j;
		}
		if (id)ans[i]+=find(root[id],dist[i]+len);
		else {insert(root[i],dist[i]);continue;}
		for (int p=son[i];p;p=next[p]){
			int j=link[p];if (dep[j]<dep[i]||j==id)continue;
			ans[i]+=find(root[j],dist[i]+len);merge(root[j],root[id]);
		}
		insert(root[i]=root[id],dist[i]);
	}
	for (int i=1;i<=n;++i)printf("%d\n",ans[i]);
	//printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


