#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
template<class Tkey> inline size_t Gethash(const Tkey &x){return x;}
template<class Tkey,class Tvalue,size_t (*gethash)(const Tkey&)=Gethash>
struct hash{
	Tkey *key; Tvalue *value;
	int *v,*next,len,P,size;
	void build(int Len=9,int p=11){  //len¸öÊý  hashsize=p
		P=p;len=0;size=Len;++Len; key=new Tkey[Len];
		v=new int[p];memset(v,0,sizeof(int)*p);
		value=new Tvalue[Len];memset(value,0,sizeof(Tvalue)*Len);
		next=new int[Len];memset(next,0,sizeof(int)*Len);
	}
	hash(int Len=0,int p=11){if (Len==0)return;build(Len,p);}
	void clear(){len=0;memset(v,0,sizeof(int)*P);}
	void insert(const Tkey &x,const Tvalue &y=0){
		size_t x1=gethash(x)%P;
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
	Tvalue operator [](const Tkey &x){return find(x);}
	Tvalue& id(const Tkey &x){
		Tvalue& tmp=find_r(x);
		if (&tmp==0)insert(x);return find_r(x);
	}
};
inline size_t get(const string &x){return 1;}
hash<int,int> a(100,200);
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	a.insert(1,3);//a[1]=3;
	a.insert(3,0);
	if (a[1]!=-1)printf("%d\n",a[1]);else printf("not exist\n");
	if (a[2]!=-1)printf("%d\n",a[2]);else printf("not exist\n");
	if (a[3]!=-1)printf("%d\n",a[3]);else printf("not exist\n");
	a.del(1);
	if (a[1]!=-1)printf("%d\n",a[1]);else printf("not exist\n");
	system("pause");for (;;);
	return 0;
}


