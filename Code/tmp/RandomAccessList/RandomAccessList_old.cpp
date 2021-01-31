#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 100005
template<class T>
class RandomAccessList{
	private:
	struct node{
		node *l,*r;T key;
		node(){}
		node(const T& _key,node *_l,node *_r):key(_key),l(_l),r(_r){}
	};
	struct root_node:public node{
		root_node *next;size_t size;
		root_node(){}
		root_node(const T& _key,node *_l,node *_r,root_node *_next,size_t _size):node(_key,_l,_r),next(_next),size(_size){}
	};
	root_node *first; size_t cnt;
	RandomAccessList(root_node *_first,size_t _cnt):first(_first),cnt(_cnt){}
	void show_error()const{printf("error\n");system("pause");for (;;);}
	public:
	RandomAccessList():first(NULL),cnt(0){}
	RandomAccessList(const RandomAccessList &x){*this=x;}
	~RandomAccessList(){}
	RandomAccessList& operator =(const RandomAccessList &x){
		first=x.first;cnt=x.cnt;return *this;
	}
	#define SIZE 1000
	root_node* Newroot_node()const{
		static root_node *Pool=NULL,*Pool1;
		if (Pool==NULL||Pool1==Pool+SIZE)
			Pool=new root_node[SIZE],Pool1=Pool;
		return Pool1++;
	}
	root_node* Newroot_node(const T& key,node *l,node *r,root_node *next,size_t size)const{
		static root_node *Pool=NULL,*Pool1;
		if (Pool==NULL||Pool1==Pool+SIZE)
			Pool=new root_node[SIZE],Pool1=Pool;
		*Pool1=root_node(key,l,r,next,size);
		//Pool1->key=key;Pool1->l=l;Pool1->r=r;Pool1->next=next;Pool1->size=size;
		return Pool1++;
	}
	/*node* Newnode()const{
		static node *Pool=NULL,*Pool1;
		if (Pool==NULL||Pool1==Pool+SIZE)
			Pool=new node[SIZE],Pool1=Pool;
		return Pool1++;
	}
	node* Newnode(const T& key,node *l,node *r)const{
		static node *Pool=NULL,*Pool1;
		if (Pool==NULL||Pool1==Pool+SIZE)
			Pool=new node[SIZE],Pool1=Pool;
		*Pool1=node(key,l,r);return Pool1++;
	}*/
	#undef SIZE
	RandomAccessList push_front(const T& key)const{
		if (first==NULL||first->next==NULL||first->size!=first->next->size)
			return RandomAccessList(Newroot_node(key,NULL,NULL,first,1),cnt+1);
		else return RandomAccessList(Newroot_node(key,first,first->next,first->next->next,first->size*2+1),cnt+1);
	}
	RandomAccessList pop_front()const{
		if (!cnt)show_error();
		if (first->size==1)return RandomAccessList(first->next,cnt-1);
		else {
			node *L=first->l,*R=first->r;
			return RandomAccessList(Newroot_node(L->key,L->l,L->r,
				Newroot_node(R->key,R->l,R->r,first->next,first->size>>1),
				first->size>>1),cnt-1);
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
	const T& operator [](size_t x)const{return find(x);}
	bool empty()const{return cnt==0;}
};
RandomAccessList<int> A;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	srand(time(0));int t1=clock();
	const int n=1000000;
	for (int i=n*2;i;--i)A=A.push_front(i);
	//for (int i=n;i;--i)A=A.pop_front();
	printf("time=%d\n",clock()-t1);
	for (int i=0;i<n;++i)A[rand()*rand()%n];
	//for (int i=0;i<n;++i)printf("%d\n",A.find(i));
	printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


