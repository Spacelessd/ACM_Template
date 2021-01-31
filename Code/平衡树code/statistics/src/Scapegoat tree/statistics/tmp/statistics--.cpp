#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define maxn 200010
#define oo (1<<30)
struct adjust{
    struct node{
		int key,size;
		node *l,*r,*p;
		void update(){
             size=l->size+r->size+1;
		}
    };
    node a[maxn];
    node *stack[maxn];
	node *null,*root;
	int len,s1;
	void clear(){
		null=new node;null->l=null->r=null;
		null->size=0;null->key=-oo;
		len=0;root=null;
    }
    adjust(int n=5){
        n+=5;clear();
	}
    node* newnode(int key){
        node *p=a+(++len);
		p->l=p->r=p->p=null;
        p->size=1;p->key=key;
        return p;
    }
	void build(int l,int r){
        int mid=(l+r)>>1,tmp;
        if (l<mid){
            build(l,mid-1);tmp=(l+mid-1)>>1;
            stack[mid]->l=stack[tmp];stack[tmp]->p=stack[mid];
        }else stack[mid]->l=null;
        if (r>mid){
            build(mid+1,r);tmp=(mid+1+r)>>1;
            stack[mid]->r=stack[tmp];stack[tmp]->p=stack[mid];
        }else stack[mid]->r=null;
        stack[mid]->update();
    }
    void dfs(node *x){
        if (x->l!=null)dfs(x->l);
        stack[++s1]=x;
        if (x->r!=null)dfs(x->r);
    }
    void insert(node *from,node *&x,int key){
        if (x==null){x=newnode(key);x->p=from;return;}
        if (key<x->key){
            insert(x,x->l,key);
            if (x->l->size*2<x->r->size){
                s1=0;dfs(x);build(1,s1);
                node *fa=x->p;
                (x=stack[(1+s1)>>1])->p=fa;
            }
            else ++(x->size);
        }
        else {
            insert(x,x->r,key);
            if (x->r->size*2<x->l->size){
                s1=0;dfs(x);build(1,s1);
                node *fa=x->p;
                (x=stack[(1+s1)>>1])->p=fa;
            }
            else ++(x->size);
        }
    }
	node* findkth(node *root,int k){
        node *x=root;
        while (k){
              if (k==x->l->size+1) break;
		      if (k<=x->l->size) x=x->l;
			     else {k-=x->l->size+1;x=x->r;}			
        }
	    return x;
    }
};
adjust a;
void print(adjust::node *x){
	if (x==a.null) return;
	print(x->l);
	printf("nie %d\n",x->key);
	print(x->r);
}
int main()
{
    long long n,A,b,c,m,i,tmp,key,ans=1;
    freopen("statistics.in","r",stdin);
	freopen("statistics.out","w",stdout);
    scanf("%I64d%I64d%I64d%I64d",&A,&b,&c,&n);
    a.insert(a.null,a.root,1);a.null->size=0;
    for (i=2;i<=n;++i){
        if ((i-1)&1)tmp=((i-1)>>1)+1;else tmp=(i-1)>>1;
        m=a.findkth(a.root,tmp)->key;
        key=(A*m+b*i+c)%1000000007;
        a.insert(a.null,a.root,(int)key);
        //printf("%I64d %I64d %I64d\n",i,m,key);
        ans+=key;
        }
    printf("%I64d\n",ans);
    //system("pause");
    //for (;;);
}










