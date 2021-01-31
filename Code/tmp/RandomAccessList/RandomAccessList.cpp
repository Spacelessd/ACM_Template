#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
template<class T>
class RAL{
	private:
	struct node; struct root_node;
	#define SIZE 10000
	static node* Newnode(const T& key,node *l,node *r){
		static node *A=NULL,*A1;
		if (A==NULL||A1==A+SIZE)A=new node[SIZE],A1=A;
		A1->key=key;A1->l=l;A1->r=r;return A1++;
	}
	static root_node* Newroot_node(const T& key,node *l,node *r,root_node *next,size_t size){
		static root_node *A=NULL,*A1;
		if (A==NULL||A1==A+SIZE)A=new root_node[SIZE],A1=A;
		A1->key=key;A1->l=l;A1->r=r;A1->next=next;A1->size=size;
		return A1++;
	}
	#undef SIZE
	struct node{
		node *l,*r;T key;
		node* modify(size_t x,const T& new_key,size_t size)const{
			if (!x)return Newnode(new_key,l,r);
			else if (x<=size)return Newnode(key,l->modify(x-1,new_key,size>>1),r);
			else return Newnode(key,l,r->modify(x-size-1,new_key,size>>1));
		}
	};
	struct root_node:public node{
		root_node *next;size_t size;
		root_node* modify(const T& new_key,size_t x)const{
			if (x<size){
				node *tmp=node::modify(x,new_key,size>>1);
				return Newroot_node(tmp->key,tmp->l,tmp->r,next,size);
			}
			else return Newroot_node(node::key,node::l,node::r,next->modify(new_key,x-size),size);
		}
	};
	struct reference{
		RAL *A;size_t x;
		reference(RAL *_A,size_t _x):A(_A),x(_x){}
		void operator =(reference key){A->modify(x,key);}
		void operator =(const T& key){A->modify(x,key);}
		operator const T&(){return A->find(x);}
	};
	root_node *first; size_t cnt;
	RAL(root_node *_first,size_t _cnt):first(_first),cnt(_cnt){}
	void show_error()const{printf("error\n");system("pause");for (;;);}
	public:
	RAL():first(NULL),cnt(0){}
	RAL(const RAL &x){*this=x;}
	RAL(size_t size){resize(size);}
	RAL(size_t size,const T& key){resize(size,key);}
	~RAL(){}
	const RAL& operator =(const RAL &x){
		first=x.first;cnt=x.cnt;return *this;
	}
	void push_front(const T& key){
		if (first==NULL||first->next==NULL||first->size!=first->next->size)
			first=Newroot_node(key,NULL,NULL,first,1),++cnt;
		else first=Newroot_node(key,first,first->next,first->next->next,first->size*2+1),++cnt;
	}
	void pop_front(){
		if (!cnt)show_error();
		if (first->size==1)first=first->next,--cnt;
		else {
			node *L=first->l,*R=first->r;
			first=Newroot_node(L->key,L->l,L->r,
				Newroot_node(R->key,R->l,R->r,first->next,first->size>>1),
				first->size>>1),--cnt;
		}
	}
	const T& find(size_t x)const{
		if (x>=cnt)show_error();
		for (root_node *now=first;now;x-=now->size,now=now->next)if (x<now->size){
			node *y=now;size_t size=now->size>>1;
			for (;;size>>=1)
				if (!x)return y->key;
				else if (x<=size)--x,y=y->l;else y=y->r,x-=size+1;
		}
	}
	void modify(size_t x,const T& key){
		if (x>=cnt)show_error();
		first=first->modify(key,x);
	}
	//const T& operator [](size_t x)const{return find(x);}
	reference operator [](size_t x){return reference(this,x);}
	bool empty()const{return cnt==0;}
	size_t size(){return cnt;}
	void clear(){first=NULL;cnt=0;}
	void resize(size_t size,const T& key=*(new T)){
		clear();while (size--)push_front(key);
	}
};
RAL<int> A;
void Qsort(int s,int t){
	int i=s,j=t;int tmp,tmp1,m=A[(i+j)>>1];
	do {
		while (A[i]<m) ++i;
		while (A[j]>m) --j;
		if (i<=j){
			tmp=A[i];
			A[i]=A[j];
			//tmp1=A[j]; A[i]=tmp1;
			A[j]=tmp;
			++i; --j;
		}
	}while (i<=j);
	if (i<t) Qsort(i,t);
	if (s<j) Qsort(s,j);
}
void sort(){
	srand(time(0));int t1=clock();
	int n=50000;A.resize(n+1);
	for (int i=1;i<=n;++i)A[i]=((rand()<<16)+rand())%10;
	//for (int i=1;i<=n;++i)printf("%d\n",int(A[i]));
	Qsort(1,n);
	//printf("-----------\n");
	//for (int i=1;i<=n;++i)printf("%d\n",int(A[i]));
	printf("sort time=%d\n",clock()-t1);
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	sort();
	srand(time(0));int t1=clock();
	int n=5000000;
	for (int i=n*2;i;--i)A.push_front(i);
	for (int i=n;i;--i)A.pop_front();
	printf("build time=%d\n",clock()-t1);
	t1=clock();
	for (int i=0,x=rand()*rand()%n;i<n;++i){
		int key=A[x];if ((i&-i)==128)x=rand()*rand()%n;
	}
	//for (int i=0;i<n;++i)printf("%d\n",A.find(i));
	printf("find time=%d\n",clock()-t1);
	n=1000000;
	t1=clock();
	for (int i=0,x=rand()*rand()%n,y=rand()*rand();i<n;++i){
		A.modify(x,y);//printf("%d %d\n",A[x],y);
		if ((i&-i)==128)x=rand()*rand()%n,y=rand()*rand();
	}
	printf("modify time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


