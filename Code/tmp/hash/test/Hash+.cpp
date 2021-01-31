#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
template<class Tkey> inline size_t Gethash(const Tkey &x){return x;}
template<class Tkey,class Tvalue,size_t (*gethash)(const Tkey&)=Gethash>
struct Hash{
	struct node{
		Tkey first;Tvalue second;node *next;
		node():next(0){}
		node(const Tkey &x,const Tvalue &y,node *_next=0):first(x),second(y),next(_next){}
	};
	node **v,*key;size_t len,P,size;
	struct iterator{
		size_t i;node *j;Hash<Tkey,Tvalue,gethash> *H;
		iterator(){}
		iterator(size_t _i,node *_j,Hash<Tkey,Tvalue,gethash> *_H):i(_i),j(_j),H(_H){go();}
		void go(){while (i+1<H->P&&!j)++i,j=H->v[i];if (i==H->P)j=0;}
		node operator *(){return *j;}
		iterator& operator ++(){j=j->next;go();}
		iterator operator ++(int){iterator res=*this;++*this;return res;}
		iterator& operator --(){
			if (j==H->v[i]){
				for (--i;!H->v[i];--i);for (j=H->v[i];j->next;j=j->next);
			}
			else {
				node *k=j;for (j=H->v[i];j->next!=k;j=j->next);
			}
		}
		iterator operator --(int){iterator res=*this;--*this;return res;}
		node* operator ->(){return j;}
		inline friend bool operator ==(const iterator &x,const iterator &y){return x.i==y.i&&x.j==y.j;}
		inline friend bool operator !=(const iterator &x,const iterator &y){return x.i!=y.i&&x.j!=y.j;}
	};
	iterator begin(){return iterator(0,v[0],this);}
	iterator end(){return iterator(P,0,this);}
	void Grow(){
		Hash<Tkey,Tvalue,gethash> res(size*2,P*2);
		for (size_t i=0;i<P;++i)
			for (node *j=v[i];j;j=j->next)res.insert(j->first,j->second);
		free();*this=res;
	}
	void build(size_t L,size_t p){  //len¸öÊý  hashsize=p
		P=p;len=0;size=L;++L;key=new node[L];
		v=new node*[p];memset(v,0,sizeof(node*)*p);
	}
	Hash(size_t len=3,size_t p=5){build(len,p);}
	void clear(){len=0;memset(v,0,sizeof(node*)*P);}
	Tvalue& insert(const Tkey &x,const Tvalue &y=0){
		//if (&find(x)){Tvalue *null=NULL;return *null;} 
		if (len==size)Grow();size_t x1=gethash(x)%P;
		key[++len]=node(x,y,v[x1]);v[x1]=key+len;
		return key[len].second; 
	}
	void del(const Tkey &x){
		size_t x1=gethash(x)%P;
		for (node *i=v[x1],*pre=0;i;pre=i,i=i->next)if (i->key==x)
			if (!pre)v[x1]=i->next;else pre->next=i->next;
	}
	Tvalue& find_(const Tkey &x){
		size_t x1=gethash(x)%P;
		for (node *i=v[x1];i;i=i->next)
			if (i->first==x)return i->second;
		Tvalue *null=NULL;return *null;
	}
	iterator find(const Tkey &x){
		size_t x1=gethash(x)%P;
		for (node *i=v[x1];i;i=i->next)
			if (i->first==x)return iterator(x1,i,*this);
		return end();
	}
	Tvalue& operator [](const Tkey &x){
		Tvalue &res=find_(x);if (&res==0)return insert(x);return res;
	}
	/*void print(){
		for (size_t i=0;i<P;++i)
			for (node *j=v[i];j;j=j->next)printf("H[%d]=%d\n",j->first,j->second);
	}*/ 
	void free(){delete[] key;delete[] v;}
};
Hash<int,int> A;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n=1000000;
	int t1=clock();srand(time(0));
	//for (int i=1;i<=n;++i)A.insert(i,i*i);
	//for (int i=1;i<=n;++i){int x=A[i];/*printf("%d\n",x);*/} 
	///*A[i]=1,*/printf("%d %d\n",i,A[i]);
	//A.print();
	//printf("%d\n",clock()-t1);
	Hash<int,int>::iterator i;//=A.begin();
	A[1]=10;printf("%d\n",A[1]);
	for (int i=1;i<=n;++i){
		int x=rand()*rand(),y=rand()*rand();A.insert(x,y);
	}
	/*for (int i1=1;i1<=1;++i1)
	for (Hash<int,int>::iterator i=A.begin();i!=A.end();++i) 
		printf("%d %d\n",i->first,i->second);*/ 
	//A.print();
	printf("%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


