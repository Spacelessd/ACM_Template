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
	node **v,*key;size_t len,P,max_size;
	struct iterator{
		size_t i;node *j;Hash<Tkey,Tvalue,gethash> *H;
		iterator(){}
		iterator(size_t _i,node *_j,Hash<Tkey,Tvalue,gethash> *_H):i(_i),j(_j),H(_H){go();}
		void go(){while (i<H->P&&!j)++i,j=H->v[i];if (i==H->P)j=0;}
		node operator *(){return *j;}
		iterator& operator ++(){j=j->next;go();}
		iterator operator ++(int){iterator res=*this;++*this;return res;}
		iterator& operator --(){
			if (j==H->v[i]){for (--i;!H->v[i];--i);for (j=H->v[i];j->next;j=j->next);}
			else {node *k=j;for (j=H->v[i];j->next!=k;j=j->next);}
		}
		iterator operator --(int){iterator res=*this;--*this;return res;}
		node* operator ->(){return j;}
		inline friend bool operator ==(const iterator &x,const iterator &y){return x.i==y.i&&x.j==y.j;}
		inline friend bool operator !=(const iterator &x,const iterator &y){return x.i!=y.i&&x.j!=y.j;}
		bool operator !(){return i==H->P;}
		operator bool(){return i!=H->P;}
	};
	iterator begin(){return iterator(0,v[0],this);}
	iterator end(){return iterator(P,0,this);}
	void Grow(){
		static double rate=2.0;Hash<Tkey,Tvalue,gethash> res(max_size*2,size_t(rate*max_size*2));
		for (size_t i=0;i<P;++i)
			for (node *j=v[i];j;j=j->next)res.insert(j->first,j->second);
		free();*this=res;
	}
	void build(size_t L,size_t p){
		P=p;len=0;max_size=L;++L;key=new node[L];
		v=new node*[p];memset(v,0,sizeof(node*)*p);
	}
	Hash(size_t len=3,size_t p=5){build(len,p);}
	void clear(){len=0;memset(v,0,sizeof(node*)*P);}
	Tvalue& insert(const Tkey &x,const Tvalue &y=0){
		//if (&find(x)){Tvalue *null=NULL;return *null;}
		if (len==max_size)Grow();size_t x1=gethash(x)%P;
		key[++len]=node(x,y,v[x1]);v[x1]=key+len;
		return key[len].second;
	}
	void erase(const Tkey &x){
		size_t x1=gethash(x)%P;
		for (node *i=v[x1],*pre=0;i;pre=i,i=i->next)if (i->key==x)
			if (!pre)v[x1]=i->next;else pre->next=i->next;
	}
	void erase(iterator x){
		printf("%d %d %d\n",x.j,v[x.i],int(x.j==v[x.i]));
		if (x.j==v[x.i]){
			v[x.i]=x.j->next,puts("zzy");
			printf("v=%d\n",v[1]);
		}
		else {puts("rp");
			iterator y=x;--y;
			y->next=x.j->next;
			puts("wei");
		}
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
			if (i->first==x)return iterator(x1,i,this);
		return end();
	}
	Tvalue& operator [](const Tkey &x){
		Tvalue &res=find_(x);if (&res==0)return insert(x);return res;
	}
	bool empty(){return len==0;}
	size_t size(){return len;}
	void free(){delete[] key;delete[] v;}
	/*void print(){
		for (size_t i=0;i<P;++i)
			for (node *j=v[i];j;j=j->next)printf("H[%d]=%d\n",j->first,j->second);
	}*/
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
	A[1]=10;printf("1st:%d\n",A[1]);i=A.find(1);
	printf("%d\n",i->next);
	A.erase(i);
	printf("2nd:%d\n",A[1]);
	printf("%d\n",A.empty());
	i=A.begin();
	if (i)puts("zzy");
	/*i=A.end();*/if (!i)puts("zzy1");
	for (int i=1;i<=n;++i){
		int x=rand()*rand(),y=rand()*rand();//A.insert(x,y);
		A[x]=y;
	}
	/*for (int i1=1;i1<=1;++i1)
	for (Hash<int,int>::iterator i=A.begin();i!=A.end();++i) 
		printf("%d %d\n",i->first,i->second);*/
	//A.print();
	printf("%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


