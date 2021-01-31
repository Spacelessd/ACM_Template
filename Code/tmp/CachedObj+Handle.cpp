#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 1000005
int sum=0;
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
template<class T> const size_t CachedObj<T>::SIZE=10000;
template<class T> class Handle/*:public CachedObj<size_t>CachedObj<Handle<T> >*/{
	public:
	Handle(T *p=0):ptr(p),use(new size_t(1)){}
	Handle(const Handle &h):ptr(h.ptr),use(h.use){++*use;}
	Handle& operator =(const Handle &h){
		++*h.use;rem_ref();ptr=h.ptr;use=h.use;return *this;
	}
	T& operator *(){return *ptr;}
	const T& operator *()const{return *ptr;}
	T* operator ->(){return ptr;}
	const T* operator ->()const{return ptr;}
	T& operator [](int x){return *(ptr+x);}
	const T& operator [](int x)const{return *(ptr+x);}
	bool operator ==(const Handle &h)const{return ptr==h.ptr;}
	bool operator !=(const Handle &h)const{return ptr!=h.ptr;}
	bool operator <(const Handle &h)const{return ptr<h.ptr;}
	bool operator >(const Handle &h)const{return ptr>h.ptr;}
	operator T*()const{return ptr;}
	~Handle(){rem_ref();}
	private:
	T *ptr;size_t *use;
	void rem_ref(){if (--*use==0){delete ptr;delete use;}}
};
struct node{int i;};
//Handle<int> a[N];
int main()
{
	//freopen((name+in).c_str(),"r",stdin);
	//freopen((name+out).c_str(),"w",stdout);
#ifndef ONLINE_JUDGE
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1=clock();
#endif
	Handle<int> *a=new Handle<int>[N];
	printf("sum=%d\n",sum);
#ifndef ONLINE_JUDGE	
	printf("time=%d\n",clock()-t1);
	system("pause");//for (;;);
#endif
	return 0;
}


