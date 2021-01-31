#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<map>
using namespace std;
struct Trie{
	static const int L=2000005,CH=26;
	struct node{
		node *son[CH];int sum;
		node *clear(){memset(son,0,sizeof(son));sum=0;return this;}
	};
	node a[L];int l;
	void clear(){l=0;a[0].clear();}
	Trie(){clear();}
	int get(char ch){return ch-'a';}
	void insert(char s[],int len){
		int c;node *x=a;
		for (int i=0;i<len;++i){
			c=get(s[i]);
			if (!x->son[c])x->son[c]=(a+(++l))->clear();
			x=x->son[c];
		}
		++x->sum;
	}
	node *find(char s[],int len){
		node *x=a;
		for (int i=0;i<len;++i)
			if (!(x=x->son[get(s[i])]))return NULL;
		return x;
	}
}T;

struct Trie_list{
	static const int L=2000005,CH=26;
	static int son[L],next[L],key[L],sum[L],l;
	void clear(int x){son[x]=0;sum[x]=0;}
	void init(){l=0;clear(0);}
	Trie_list(){init();}
	int get(char ch){return ch-'a';}
	void insert(char s[],int len){
		int x=0,c,flag;
		for (int i=0;i<len;++i){
			c=get(s[i]);flag=0;
			for (int p=son[x];p;p=next[p])
				if (key[p]==c){x=p;flag=1;break;}
			if (!flag)++l,clear(l),
			key[l]=c,next[l]=son[x],son[x]=l,x=l;
		}
		++sum[x];
	}
	int find(char s[],int len){
		int x=0,c,flag;
		for (int i=0;i<len;++i){
			c=get(s[i]);flag=0;
			for (int p=son[x];p;p=next[p])
				if (key[p]==c){x=p;flag=1;break;}
			if (!flag)return 0;
		}
		return x;
	}
}T1;int Trie_list::son[Trie::L],Trie_list::next[Trie::L],
	Trie_list::key[Trie::L],Trie_list::sum[Trie::L],Trie_list::l;

struct Trie_map{
	static const int L=2000005,CH=26;
	struct node{
		map<int,node*> son;int sum;
		node *clear(){son.clear();sum=0;return this;}
	};
	node a[L];int l;
	void clear(){l=0;a[0].clear();}
	Trie_map(){clear();}
	int get(char ch){return ch-'a';}
	void insert(char s[],int len){
		int c;node *x=a;map<int,node*>::iterator y;
		for (int i=0;i<len;++i){
			c=get(s[i]);y=x->son.find(c);
			if (y==x->son.end())x->son[c]=(a+(++l))->clear(),x=a+l;
			else x=y->second;
		}
		++x->sum;
	}
	node *find(char s[],int len){
		node *x=a;
		for (int i=0;i<len;++i)
			if (!(x=x->son[get(s[i])]))return NULL;
		return x;
	}
}T2;

template <class T>
struct Block{
	static const int L=2000005;
	static T Pool[L*4],*cur;
	T *NewT(int len){cur+=len;return cur-len;}
	T *son[7];
	void clear(){memset(son,0,sizeof(son));}
	Block(){clear();}
	T &operator [](int x){
		if (!son[x>>2])son[x>>2]=NewT(4);
		return son[x>>2][x&3];
	}
};
template <class T>T Block<T>::Pool[Block<T>::L*4];
template <class T>T* Block<T>::cur=Block<T>::Pool;
struct Trie_Block{
	static const int L=2000005,CH=26;
	struct node{
		Block<node*> son;int sum;
		node *clear(){son.clear();sum=0;return this;}
	};
	node a[L];int l;
	void clear(){l=0;a[0].clear();}
	Trie_Block(){clear();}
	int get(char ch){return ch-'a';}
	void insert(char s[],int len){
		int c;node *x=a;
		for (int i=0;i<len;++i){
			c=get(s[i]);
			if (!x->son[c])x->son[c]=(a+(++l))->clear();
			x=x->son[c];
		}
		++x->sum;
	}
	node *find(char s[],int len){
		node *x=a;
		for (int i=0;i<len;++i)
			if (!(x=x->son[get(s[i])]))return NULL;
		return x;
	}
}T3;
int main(){
	T.insert("zzy",3);
	printf("%d\n",T.find("zzy",2));
	printf("%d\n",T.find("zy",2));
	system("pause");for (;;);
	return 0;
}


