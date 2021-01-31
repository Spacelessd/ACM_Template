#include<stdio.h>
#define maxn 200010
struct node{
	int sum,key;
	node *l,*r,*p;
	void update(){
		sum=l->sum+r->sum+key;  
	}
};
struct Splay{
	node a[maxn*2],*null;
	void clear(){
		null=new node;null->l=null->r=null;   
		null->sum=0;
	}
	void zig(node *x){
		node *y=x->p,*z=y->p;
		if (z->l==y) z->l=x;else z->r=x;   
		x->p=z;y->p=x;   
		y->l=x->r;x->r=y;   
		y->l->p=y;   
		y->update();   
	}   
	void zag(node *x){   
		node *y=x->p,*z=y->p;
		if (z->l==y) z->l=x;else z->r=x;   
		x->p=z;y->p=x;   
		y->r=x->l;x->l=y;   
		y->r->p=y;   
		y->update();   
	}   
	void splay(node *x)   
	{   
		node *y,*z;   
		if (x==null) return; 
		while (x->p!=null){
			y=x->p;z=y->p;
			if (z==null) {if (x==y->l)zig(x);else zag(x);}   
			else
				if (y==z->l)   
					if (x==y->l){zig(y);zig(x);} 
					else{zag(x);zig(x);}   
				else 
					if (x==y->r){zag(y);zag(x);}   
					else{zig(x);zag(x);}   
		}   
		x->update();   
	} 
	void build(int l,int r){
		int mid=(l+r)>>1,tmp;
		if (l<mid){
				build(l,mid-1);tmp=(l+mid-1)>>1;
				a[mid].l=a+tmp;a[tmp].p=a+mid;
				}
		if (r>mid){
				build(mid+1,r);tmp=(mid+1+r)>>1;
				a[mid].r=a+tmp;a[tmp].p=a+mid;
				}
		(a+mid)->update();
	}
	void merge(node *x,node *y){
		node *p;
		for (p=x;p->r!=null;p=p->r);
		splay(p);p->r=y;y->p=p;p->update();
	}  
void print(node *x)
{
	if (x==null)return;
	print(x->l);
	printf("%d\n",x->key);
	print(x->r);
}
void test(int y)
{
	 printf("start\n");
	 node *x=a+y;
	 while (x->p!=null)x=x->p;
	 print(x);
	 printf("end\n");
	 printf("\n");
}
};
Splay a;
struct Edge{
	int link[maxn],next[maxn],son[maxn],l;
	Edge(){l=0;}
	void addedge(int x,int y){
		link[++l]=y;next[l]=son[x];son[x]=l;
		}
}e;
node *in[maxn],*out[maxn];
int len;
void Build(int x){
	node *p=a.a+ ++len;
	in[x]=p;p->l=p->r=a.null;p->sum=p->key=1;
	for (int i=e.son[x];i;i=e.next[i])Build(e.link[i]);
	p=a.a+ ++len;
	out[x]=p;p->l=p->r=a.null;p->sum=p->key=-1;
}
int main(){
	//freopen("bounce.in","r",stdin);   
	//freopen("bounce.out","w",stdout); 
	int n,m,i,x,y,ch,tmp;
	node *p,*q;
	a.clear();scanf("%d",&n);
	for (i=1;i<=n;++i){
		scanf("%d",&x);
		tmp=i+x>n?n+1:i+x;
		e.addedge(tmp,i);
	}
	Build(n+1);
	a.build(1,len);
	a.a[(1+len)>>1].p=a.null;scanf("%d",&m);//printf("nie\n");
	for (i=0;i<m;++i){
		scanf("%d",&ch);scanf("%d",&x);
		++x;
		if (ch==1){
			a.splay(out[x]);
			printf("%d\n",out[x]->l->sum-1);
		}
		else {
			scanf("%d",&y);y=x+y>n?n+1:x+y;
			a.splay(in[x]);p=in[x]->l;in[x]->l=a.null;p->p=a.null;in[x]->update();
			a.splay(out[x]);q=out[x]->r;out[x]->r=a.null;q->p=a.null;out[x]->update();
			a.merge(p,q);
			a.splay(out[y]);p=out[y]->l;p->p=a.null;out[y]->l=out[x];out[x]->p=out[y];out[y]->update();
			a.merge(p,out[y]);
		}
	}
	//printf("endll\n");
	//for (;;);
}


