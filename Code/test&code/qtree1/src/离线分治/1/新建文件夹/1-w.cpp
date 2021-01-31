#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 100005
#define Q 100005
#define M 3000005
#define Mdep 25
#define oo (1<<29)
inline int min(int x,int y){return x<y?x:y;}
struct node{
	int min;
	node *New;
};
struct edge;
struct Tnode{
	int count,deep;
	node *T;
	Tnode *Tnew;
	edge *p,*son;
};
struct Query{
	char ch;
	Tnode *x,*y;
	int z;
};
/*
1=Change a node's weight
2=Query the min weight of a path
*/
struct edge{
	node *T;
	Tnode *from,*link;
	edge *next;
};
struct Dfsdata{
	int old1,e1,T1,N1;
	Tnode *root;
};
Dfsdata data[Mdep];
node nodes[M];int N1;
edge e[M];int e1;
Tnode T[M];int T1;
Query query[Q],old[M];int old1;
int n,q,Ans[Q];
Tnode *Newnode(){
	++T1;T[T1].son=NULL;
	return T+T1;
}
void addedge(Tnode *x,Tnode *y,node *z){
	++e1;e[e1].from=x;e[e1].link=y;e[e1].T=z;
	e[e1].next=x->son;x->son=y->p=e+e1;
}
Tnode *queue[N];int h,t;
void Bfs(Tnode *root){
	h=1;t=1;queue[1]=root;root->deep=1;
	while (h<=t){
		Tnode *x=queue[h++];
		for (edge *i=x->son;i!=NULL;i=i->next){
			queue[++t]=i->link;i->link->deep=x->deep+1;
		}
	}
}
void contract(int L,int R,int dep){
	static Tnode *a[N],*Tmp[N];
	data[dep].T1=T1;data[dep].e1=e1;data[dep].old1=old1;data[dep].N1=N1;
	Bfs(data[dep].root);
	{	//mark
		for (int i=1;i<=t;++i)queue[i]->count=0;
		for (int i=L;i<=R;++i){
			if (query[i].ch==1)query[i].x->count=2;
			if (query[i].ch==2)query[i].x->count=2,query[i].y->count=2;
		}
	}
	/*for (int i=1;i<=t;++i)
		printf("nie %d %d %d %d\n",queue[i],queue[i]->p!=NULL?queue[i]->p->from:0,queue[i]->T->min,queue[i]->count);
	printf("\n\n");*/
	int top=0,Tmp1;
	for (int i=1;i<=t;++i)
		if (queue[i]->count>1)a[++top]=queue[i];
	while (top>1){
		int D=a[top]->deep;
		int i,j;
		for (i=top;i&&a[i]->deep==D;--i)a[i]=a[i]->p->from;
		j=i;Tmp1=0;
		for (i=top;i>j;--i){
			if (!a[i]->count)Tmp[++Tmp1]=a[i];
			++a[i]->count;
		}
		top=j;
		for (int i=1;i<=Tmp1;++i)a[++top]=Tmp[i];
	}
	for (int i1=1;i1<=t;++i1){
		Tnode *i=queue[i1];
		if (i->count>1){
			i->Tnew=Newnode();i->Tnew->T=&nodes[++N1];
			i->Tnew->T->min=i->T->min;i->T->New=i->Tnew->T;
		}
	}
	for (int i1=1;i1<=t;++i1){
		Tnode *i=queue[i1];
		if (i->count>1&&i!=a[1]){
			node *tmp=&nodes[++N1];tmp->min=oo;
			Tnode *j=i->p->from;
			while (j->count<=1){
				tmp->min=min(tmp->min,j->T->min);
				j=j->p->from;
			}
			j=i;
			do{
				if (j->p->T!=NULL)tmp->min=min(tmp->min,j->p->T->min);
				j=j->p->from;
			}while (j->count<=1);
			if (tmp->min!=oo)addedge(j->Tnew,i->Tnew,tmp);
				else addedge(j->Tnew,i->Tnew,NULL);
		}
	}
	data[dep+1].root=a[1]->Tnew;
	a[1]->Tnew->p=NULL;
	for (int i=L;i<=R;++i){
		old[++old1]=query[i];
		if (query[i].ch==1)query[i].x=query[i].x->Tnew;
		if (query[i].ch==2)query[i].x=query[i].x->Tnew,query[i].y=query[i].y->Tnew;
	}
	/*for (int i=L;i<=R;++i){
		old[++old1]=query[i];
		if (query[i].ch==1)printf("rp %d\n",query[i].x);
		if (query[i].ch==2)printf("rp %d %d\n",query[i].x,query[i].y);
	}
	printf("\n\n");*/
}
void release(int L,int R,int dep){
	Bfs(data[dep].root);
	for (int i1=1;i1<=t;++i1){
		Tnode *i=queue[i1];
		if (i->count>1)i->T->min=i->T->New->min;
	}
	old1=data[dep].old1;
	for (int i=L;i<=R;++i)
		query[i]=old[++old1];
	T1=data[dep].T1;e1=data[dep].e1;old1=data[dep].old1;N1=data[dep].N1;
}
void Answer(int l,int r,int dep){
	if (l==r){
		if (query[l].ch==1){
			query[l].x->T->min=query[l].z;
		}
		if (query[l].ch==2){
			int tmp;
			if (query[l].x->p!=NULL&&query[l].x->p->from==query[l].y)
				if (query[l].x->p->T!=NULL)
					tmp=min(query[l].x->T->min,query[l].x->p->T->min);
				else tmp=query[l].x->T->min;
			else if (query[l].y->p!=NULL&&query[l].y->p->from==query[l].x)
				if (query[l].y->p->T!=NULL)
					tmp=min(query[l].y->T->min,query[l].y->p->T->min);
				else tmp=query[l].y->T->min;
			else {
				tmp=min(query[l].x->T->min,query[l].y->T->min);
				if (query[l].x->p->T!=NULL)tmp=min(tmp,query[l].x->p->T->min);
				if (query[l].y->p->T!=NULL)tmp=min(tmp,query[l].y->p->T->min);
			}
			Ans[l]=tmp;
		}
		return;
	}
	int mid=(l+r)>>1;
	{
		contract(l,mid,dep);
		Answer(l,mid,dep+1);
		release(l,mid,dep);
	}
	{
		contract(mid+1,r,dep);
		Answer(mid+1,r,dep+1);
		release(mid+1,r,dep);
	}
}
struct Edge{
	int link[N*2],cost[N*2],next[N*2],son[N],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y,int z){
		link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
	}
};
Edge Te;
int deep[N];
Tnode *Link[N];
void maketree(int x,int dep,int cost){
	deep[x]=dep;Link[x]=Newnode();Link[x]->T=&nodes[++N1];
	Link[x]->T->min=cost;
	for (int i=Te.son[x];i;i=Te.next[i]){
		int j=Te.link[i];
		if (!deep[j])maketree(j,dep+1,Te.cost[i]),
		addedge(Link[x],Link[j],NULL);
	}
}
void init(){
	static char str[110];
	static int edgex[N],edgey[N];
	int x,y,z,tmp;
	T1=e1=old1=N1=0;q=0;Te.clear();
	scanf("%d",&n);
	for (int i=1;i<=n-1;++i)
		scanf("%d%d%d",&x,&y,&z),
		Te.addedge(x,y,z),Te.addedge(y,x,z),
		edgex[i]=x,edgey[i]=y;
	maketree(1,1,oo);Link[1]->p=NULL;
	while (1){
		scanf("%s",&str);
		if (str[0]=='D')break;++q;
		scanf("%d%d",&x,&y);
		if (str[0]=='C'){
			if (deep[edgex[x]]>deep[edgey[x]])tmp=edgex[x];
				else tmp=edgey[x];
			query[q].ch=1;query[q].x=Link[tmp];query[q].z=y;
		}
		else if (str[0]=='Q'){
			query[q].ch=2;query[q].x=Link[x];query[q].y=Link[y];
		}
	}
}
int main(){
	freopen("1.in","r",stdin);
	//freopen("1.out","w",stfout);
	int T;scanf("%d",&T);
	while (T--){
		init();
		data[0].root=Link[1];
		contract(1,q,0);
		Answer(1,q,1);
		for (int i=1;i<=q;++i)
			if (query[i].ch==2)printf("%d\n",Ans[i]);
	}
	system("pause");for (;;);
	return 0;
}




