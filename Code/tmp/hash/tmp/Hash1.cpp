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
	Tkey *key; Tvalue *value;
	int *v,*next,len,P,size;
	void Grow(){
		Hash<Tkey,Tvalue,gethash> res(size*2,P*2);
		for (int i=0;i<P;++i)
			for (int j=v[i];j;j=next[j])res.insert(key[j],value[j]);
		free();*this=res;
	}
	void build(int L,int p){  //len¸öÊý  hashsize=p
		P=p;len=0;size=L;++L; key=new Tkey[L];
		v=new int[p];memset(v,0,sizeof(int)*p);
		value=new Tvalue[L];memset(value,0,sizeof(Tvalue)*L);
		next=new int[L];memset(next,0,sizeof(int)*L);
	}
	Hash(int len=3,int p=7){build(len,p);}
	void clear(){len=0;memset(v,0,sizeof(int)*P);}
	void insert(const Tkey &x,const Tvalue &y=0){
		if (len==size)Grow();size_t x1=gethash(x)%P;
		key[++len]=x;value[len]=y;
		next[len]=v[x1];v[x1]=len;
	}
	void del(const Tkey &x){
		size_t x1=gethash(x)%P;
		for (int i=v[x1],pre=0;i;pre=i,i=next[i])
			if (key[i]==x)
				if (pre==0)v[x1]=next[i];
				else next[pre]=next[i];
	}
	Tvalue find(const Tkey &x){
		size_t x1=gethash(x)%P;
		for (int i=v[x1];i;i=next[i])
			if (key[i]==x)return value[i];
		return -1;
	}
	Tvalue& find_r(const Tkey &x){
		size_t x1=gethash(x)%P;
		for (int i=v[x1];i;i=next[i])
			if (key[i]==x)return value[i];
		Tvalue *null=NULL;return *null;
	}
	void inc(const Tkey &x,const Tvalue &y=1){
		size_t x1=gethash(x)%P;
		for (int i=v[x1];i;i=next[i])
			if (key[i]==x){value[i]+=y;return;}
	}
	Tvalue& operator [](const Tkey &x){
		Tvalue& tmp=find_r(x);
		if (&tmp==0)insert(x);return find_r(x);
	}
	Tvalue id(const Tkey &x){return find(x);}
	/*void print(){
		for (int i=0;i<P;++i)
			for (int j=v[i];j;j=next[j])printf("H[%d]=%d\n",key[j],value[j]);
	}*/
	void free(){delete[] key;delete[] value;delete[] v;delete[] next;}
	//~Hash(){free();}
};
Hash<int,int> A;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1=clock();srand(time(0));
	for (int i=1;i<=1000000;++i){
		int x=rand()*rand(),y=rand()*rand();A.insert(x,y);
	}
	//A.print();
	printf("%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


