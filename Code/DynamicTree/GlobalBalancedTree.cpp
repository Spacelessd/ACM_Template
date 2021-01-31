#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=30005;
struct GBT{
	static const int oo=1<<29;
	struct edge{
		edge *next;int link;
	}e[N*2],*e1,*son[N];
	struct rec{
		int a[2][2],b[2][2];
		static rec ini(char *s){
			rec res;
			for (int i=0;i<2;++i)
				for (int j=0;j<2;++j)
					if (s[i]!='#'&&s[j]!='#')res.a[i][j]=1+(i!=j);
					else res.a[i][j]=-oo;
			for (int i=0;i<2;++i)
				for (int j=0;j<2;++j)
					if (s[j]=='#')res.b[i][j]=0;
					else res.b[i][j]=(s[1-j]!='#')+1;
			return res;
		}
		static rec empty(){
			rec res;
			for (int i=0;i<2;++i)
				for (int j=0;j<2;++j)
					res.a[i][j]=i==j?0:-oo,res.b[i][j]=0;
			return res;
		}
		rec operator +(const rec &y)const{
			rec res;
			for (int i=0;i<2;++i)
				for (int j=0;j<2;++j){
					int s=a[i][0]+y.a[0][j],t=a[i][1]+y.a[1][j];
					if (t>s)s=t;if (-oo>s)s=-oo;
					res.a[i][j]=s;
				}
			for (int i=0;i<2;++i){
				int s=b[0][i];
				for (int j=0;j<2;++j){
					int t=a[i][j]+y.b[0][j];
					if (t>s)s=t;
				}
				res.b[0][i]=s;
				s=y.b[1][i];
				for (int j=0;j<2;++j){
					int t=y.a[j][i]+b[1][j];
					if (t>s)s=t;
				}
				res.b[1][i]=s;
			}
			return res;
		}
		rec rev()const{
			rec res;
			for (int i=0;i<2;++i)
				for (int j=0;j<2;++j)
					res.a[i][j]=a[j][i],res.b[1-i][j]=b[i][j];
			return res;
		}
		void print(){
			printf("start:\n");
			for (int i=0;i<2;++i){
				for (int j=0;j<2;++j)printf("%d ",a[i][j]);
				printf("\n");
			}
			for (int i=0;i<2;++i){
				for (int j=0;j<2;++j)printf("%d ",b[i][j]);
				printf("\n");
			}
			printf("end\n");
		}
	};
	struct node{
		node *l,*r,*p,*head;int dep;
		rec key,sum;
		void update(){
			sum=key;
			if (l!=NULL)sum=sum+l->sum;
			if (r!=NULL)sum=r->sum+sum;
		}
	}a[N];
	int dep[N],size[N],fa[N],heavy[N]; char Map[N][2];
	void clear(){
		for (int i=0;i<N*2;++i)e[i].next=NULL;
		for (int i=0;i<N;++i)son[i]=NULL;
		e1=e;size[0]=0;dep[0]=0;
	}
	GBT(){clear();}
	node *getnode(int x){return a+x;}
	int getid(node *x){return x-a;}
	bool istop(node *x){return x->p==NULL||x->p->l!=x&&x->p->r!=x;}
	void addedge(int x,int y){
		e1->link=y;e1->next=son[x];son[x]=e1++;
		e1->link=x;e1->next=son[y];son[y]=e1++;
	}
	node *build(int start,int siz,node *head,int dep){
		if (!siz)return NULL;
		int mid,s=size[start]-size[heavy[start]],now=start;
		while (s+s<siz)now=heavy[now],s+=size[now]-size[heavy[now]];
		node *x=getnode(now);x->head=head;x->dep=dep;
		if ((x->l=build(start,s-size[now]+size[heavy[now]],head,dep+1))!=NULL)x->l->p=x;
		if ((x->r=build(heavy[now],siz-s,head,dep+1))!=NULL)x->r->p=x;
		x->update();return x;
	}
	void bfs(int root,int n){
		static int Q[N];int t=1;Q[1]=root;
		for (int i=1;i<=n;++i)dep[i]=0;
		dep[root]=1;fa[root]=0;
		for (int h=1;h<=t;++h){
			int x=Q[h];
			for (edge *i=son[x];i;i=i->next){
				int j=i->link;if (dep[j])continue;
				dep[j]=dep[x]+1;fa[j]=x;Q[++t]=j;
			}
		}
		for (int i1=t;i1;--i1){
			int x=Q[i1],max=0;heavy[x]=0;size[x]=1;
			for (edge *i=son[x];i;i=i->next)if (i->link!=fa[x]){
				int s=size[i->link];size[x]+=s;
				if (s>max)max=s,heavy[x]=i->link;
			}
		}
		for (int i=1;i<=n;++i)getnode(i)->key=rec::ini(Map[i]);
		for (int i1=1;i1<=n;++i1){
			int i=Q[i1];
			if (!fa[i]||heavy[fa[i]]!=i){
				node *x=build(i,size[i],getnode(i),getnode(fa[i])->dep+1);
				if (fa[i])x->p=getnode(fa[i]);
				else x->p=NULL;
			}
		}
	}
	void Change(node *x){
		x->key=rec::ini(Map[getid(x)]);
		for (;;x=x->p){x->update();if (istop(x))break;}
	}
	void Change(int x){Change(getnode(x));}
	int Query(node *x,node *y){
		rec left=rec::empty(),right=rec::empty();
		while (x->head!=y->head)
			if (dep[getid(x->head)]>dep[getid(y->head)]){
				for (node *pre=x->r,*now=x;pre==now->l||pre==now->r;pre=now,now=now->p)
					if (pre==now->r){
						left=left+now->key;
						if (now->l!=NULL)left=left+now->l->sum;
					}
				x=getnode(fa[getid(x->head)]);
			}
			else {
				for (node *pre=y->r,*now=y;pre==now->l||pre==now->r;pre=now,now=now->p)
					if (pre==now->r){
						right=right+now->key;
						if (now->l!=NULL)right=right+now->l->sum;
					}
				y=getnode(fa[getid(y->head)]);
			}
		bool flag=dep[getid(x)]<dep[getid(y)]; node *prex,*prey;
		if (flag)prex=x->l,prey=y->r;
		else prex=x->r,prey=y->l;
		while (x!=y)
			if (x->dep>y->dep){
				if (flag&&prex==x->l){
					left=left+x->key;
					if (x->r!=NULL)left=left+x->r->sum.rev();
				}
				else if (!flag&&prex==x->r){
					left=left+x->key;
					if (x->l!=NULL)left=left+x->l->sum;
				}
				prex=x;x=x->p;
			}
			else {
				if (!flag&&prey==y->l){
					right=right+y->key;
					if (y->r!=NULL)right=right+y->r->sum.rev();
				}
				else if (flag&&prey==y->r){
					right=right+y->key;
					if (y->l!=NULL)right=right+y->l->sum;
				}
				prey=y;y=y->p;
			}
		rec ans=left+x->key+right.rev();
		return max(ans.b[0][0],ans.b[0][1]);
	}
	int Query(int x,int y){return Query(getnode(x),getnode(y));}
	void print(int n){
		printf("start\n");
		for (int i=1;i<=n;++i){
			printf("id=%d:l=%d r=%d p=%d head=%d dep=%d\n",i,getid(getnode(i)->l),getid(getnode(i)->r),
				getid(getnode(i)->p),getid(getnode(i)->head),getnode(i)->dep);
		}
		printf("end\n");
	}
};
GBT T;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n,q;scanf("%d%d",&n,&q);
	for (int i=1;i<n;++i){
		int x,y;scanf("%d%d",&x,&y);
		T.addedge(x,y);
	}
	for (int i=1;i<=n;++i)scanf("%s",T.Map[i]);
	T.bfs(1,n);
	while (q--){
		char zzy[15];int x,y;
		scanf("%s",zzy);
		if (zzy[0]=='Q'){
			scanf("%d%d",&x,&y);
			printf("%d\n",T.Query(x,y));
		}
		else {
			scanf("%d",&x);scanf("%s",T.Map[x]);
			T.Change(x);
		}
	}
	system("pause");for (;;);
	return 0;
}


