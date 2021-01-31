#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int W=18; ll ans0=0,ans1=0,ans=0;
template<class T> class CachedObj{
	public:
	void *operator new(size_t s){
		if (!head){
			T *a=new T[SIZE];
			for (size_t i=0;i<SIZE;++i)add(a+i);
		}
		T *p=head;head=head->CachedObj<T>::next;return p;
	}
	void operator delete(void *p,size_t){if (p)add(static_cast<T*>(p));}
	virtual ~CachedObj(){}
	protected:T *next;
	private:
	static T *head;static const size_t SIZE;
	static void add(T *p){p->CachedObj<T>::next=head;head=p;}
};
template<class T> T *CachedObj<T>::head=0;
template<class T> const size_t CachedObj<T>::SIZE=100000;
struct node:CachedObj<node>{
	node *l,*r;int cnt;
	node(node *_l=0,node *_r=0,int _cnt=0):l(_l),r(_r),cnt(_cnt){}
};
node* merge(node *x,node *y){
	if (!x||!y)return x?x:y;
	if (x->l&&y->r)ans0+=(ll)x->l->cnt*y->r->cnt;
	if (y->l&&x->r)ans1+=(ll)y->l->cnt*x->r->cnt;
	x->l=merge(x->l,y->l);x->r=merge(x->r,y->r);x->cnt=x->cnt+y->cnt;
	delete y;return x;
}
node *insert(int key){
	node *x=new node,*res=x;x->cnt=1;
	for (int i=W-1;i>=0;--i,x->cnt=1)
		key>>i&1?(x->r=new node,x=x->r):(x->l=new node,x=x->l);
	return res;
}
void print(node *x,int key){
	if (!x)return;
	if (!x->l&&!x->r)printf("%d\n",key);
	else print(x->l,key*2),print(x->r,key*2+1);
}
node* build(){
	int key;scanf("%d",&key);
	if (!key){
		node *x=merge(build(),build());ans+=min(ans0,ans1);
		ans0=ans1=0;return x;
	}
	else return insert(key);
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1=clock();
	int n;scanf("%d",&n);build();
	printf("%I64d\n",ans);
	//printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


