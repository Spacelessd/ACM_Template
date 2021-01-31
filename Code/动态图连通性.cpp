#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
template<class T>
struct Gethash{
	size_t operator ()(const T &x)const{return x;}
};
template<> size_t Gethash<int>::operator ()(const int &x)const{return x;}
template<> size_t Gethash<long long>::operator ()(const long long &x)const{return x;}
template<> size_t Gethash<char*>::operator ()(char *const &_str)const{
	const size_t seed=131;size_t hash=0;char *str=_str;
	while (*str)hash=hash*seed+*str++;
	return hash;
}
template<> size_t Gethash<string>::operator ()(const string &s)const{
	size_t hash=5381;
	for (string::const_iterator i=s.begin();i!=s.end();++i)hash+=(hash<<5)+*i;
	return hash;
}
template<> size_t Gethash<pair<int,int> >::operator ()(const pair<int,int> &x)const{return (x.first<<15)+(x.first>>8)+x.second;}
template<class Tkey,class Tvalue=bool,class _Hash=Gethash<Tkey> >
struct Hash{
	_Hash gethash;
	struct node{
		Tkey first;Tvalue second;node *next;
		node():next(0){}
		node(const Tkey &x,const Tvalue &y,node *_next=0):first(x),second(y),next(_next){}
	};
	node **v,*key;size_t len,P,max_size;
	struct iterator{
		size_t i;node *j;Hash<Tkey,Tvalue,_Hash> *H;
		iterator(){}
		iterator(size_t _i,node *_j,Hash<Tkey,Tvalue,_Hash> *_H):i(_i),j(_j),H(_H){go();}
		void go(){
			if (i<H->P&&!j){
				for (++i;i<H->P&&!H->v[i];++i);
				if (i==H->P)j=0;else j=H->v[i];
			}
		}
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
		inline friend bool operator !=(const iterator &x,const iterator &y){return x.i!=y.i||x.j!=y.j;}
		bool operator !(){return i==H->P;}
		operator bool(){return i!=H->P;}
	};
	iterator begin(){return iterator(0,v[0],this);}
	iterator end(){return iterator(P,0,this);}
	//void operator =(const Hash &y){}
	void Grow(){
		static double rate=1.7;Hash<Tkey,Tvalue,_Hash> res(max_size*2,size_t(rate*max_size*2));
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
	//void clear(){free();build(3,5);}
	Tvalue& insert(const Tkey &x,const Tvalue &y=0){
		//if (&find(x)){Tvalue *null=NULL;return *null;}
		if (len==max_size)Grow();size_t x1=gethash(x)%P;
		key[++len]=node(x,y,v[x1]);v[x1]=key+len;
		return key[len].second;
	}
	Tvalue& insert(const pair<Tkey,Tvalue> &p){return insert(p.first,p.second);}
	void erase(const Tkey &x){
		size_t x1=gethash(x)%P;
		for (node *i=v[x1],*pre=0;i;pre=i,i=i->next)if (i->first==x){
			if (!pre)v[x1]=i->next;else pre->next=i->next;
			return;  //multimap
		}
	}
	void erase(iterator x){
		if (x.j==v[x.i])v[x.i]=x->next;
		else {node *y=x->next;--x;x->next=y;}
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
	size_t count(const Tkey &x){return &find_(x)?1:0;}
	void free(){delete[] key;delete[] v;}
	~Hash(){}
	/*void print(){
		for (size_t i=0;i<P;++i)
			for (node *j=v[i];j;j=j->next)printf("H[%d]=%d\n",j->first,j->second);
	}*/
};
const int N=200005,D=18;
struct dynamic_graph{
	typedef long long ll;
	struct Edge{
		int link[N*2],next[N*2],son[N],l;
		void addedge(int x,int y){
			link[++l]=y;next[l]=son[x];son[x]=l;
			link[++l]=x;next[l]=son[y];son[y]=l;
		}
	}e;
	struct Ins{int x,y;}ins[N*4];
	struct node:Ins{
		int type,ans;  //0=query 1=ins 2=del
	}a[N];
	int id[N],visit[N],q[N],m,c1;
	void set(int n){m=0;c1=0;for (int i=1;i<=n;++i)visit[i]=0;}
	void add(int x,int y,int z){if (x>y)swap(x,y);++m;a[m].x=x;a[m].y=y;a[m].type=z;}
	ll mp(int x,int y){return (ll)x*N+y;}
	void bfs(int S){
		if (visit[S]==c1)return;
		visit[S]=c1;id[S]=S;int h=1,t=1;q[h]=S;
		while (h<=t){
			int x=q[h++];
			for (int p=e.son[x];p;p=e.next[p]){
				int j=e.link[p];if (visit[j]!=c1)visit[j]=c1,q[++t]=j,id[j]=S;
			}
		}
	}
	void calc(int l,int r,int dep,int insl,int insr){
		if (l==r){
			if (a[l].type==0)a[l].ans=(a[l].x==a[l].y);
			return;
		}
		int mid=(l+r)>>1,*idx=new int[r-l+1]-l,*idy=new int[r-l+1]-l,ins1;Hash<ll,int> H,H1;
		Ins *I=ins;e.l=0;++c1;ins1=insr;
		for (int i=insl;i<=insr;++i)e.son[I[i].x]=e.son[I[i].y]=0;
		for (int i=l;i<=mid;++i)e.son[a[i].x]=e.son[a[i].y]=0;
		for (int i=l;i<=mid;++i)if (a[i].type==2)H.insert(mp(a[i].x,a[i].y));
		for (int i=insl;i<=insr;++i)
			if (!&H.find_(mp(I[i].x,I[i].y)))e.addedge(I[i].x,I[i].y);
			else H.erase(mp(I[i].x,I[i].y)),ins[++ins1]=I[i];
		for (int i=l;i<=mid;++i)idx[i]=a[i].x,idy[i]=a[i].y;
		for (int i=insr+1;i<=ins1;++i)
			bfs(ins[i].x),ins[i].x=id[ins[i].x],bfs(ins[i].y),ins[i].y=id[ins[i].y];
		for (int i=l;i<=mid;++i)bfs(a[i].x),a[i].x=id[a[i].x],bfs(a[i].y),a[i].y=id[a[i].y];
		calc(l,mid,dep+1,insr+1,ins1);
		for (int i=l;i<=mid;++i)a[i].x=idx[i],a[i].y=idy[i];
		H.clear();e.l=0;++c1;ins1=insr;
		for (int i=insl;i<=insr;++i)e.son[I[i].x]=e.son[I[i].y]=0;
		for (int i=l;i<=r;++i)e.son[a[i].x]=e.son[a[i].y]=0;
		for (int i=l;i<=mid;++i)if (a[i].type==2)H.insert(mp(a[i].x,a[i].y));
		for (int i=mid+1;i<=r;++i)if (a[i].type==2)H1.insert(mp(a[i].x,a[i].y));
		for (int i=insl;i<=insr;++i){
			ll pr=mp(I[i].x,I[i].y);
			if (&H.find_(pr))H.erase(pr);
			else if (&H1.find_(pr))H1.erase(pr),ins[++ins1]=I[i];
			else e.addedge(I[i].x,I[i].y);
		}
		for (int i=l;i<=mid;++i)if (a[i].type==1){
			ll pr=mp(a[i].x,a[i].y);
			if (&H.find_(pr))H.erase(pr);
			else if (&H1.find_(pr))H1.erase(pr),ins[++ins1]=a[i];
			else e.addedge(a[i].x,a[i].y);
		}
		for (int i=mid+1;i<=r;++i)idx[i]=a[i].x,idy[i]=a[i].y;
		for (int i=insr+1;i<=ins1;++i)
			bfs(ins[i].x),ins[i].x=id[ins[i].x],bfs(ins[i].y),ins[i].y=id[ins[i].y];
		for (int i=mid+1;i<=r;++i)bfs(a[i].x),a[i].x=id[a[i].x],bfs(a[i].y),a[i].y=id[a[i].y];
		calc(mid+1,r,dep+1,insr+1,ins1);
		for (int i=mid+1;i<=r;++i)a[i].x=idx[i],a[i].y=idy[i];
		delete[] (idx+l);delete[] (idy+l);H.free();H1.free();
	}
};
dynamic_graph G;
inline void read(int &x){
	char ch;int bo=0;x=0;
	for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
	for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
	if (bo)x=-x;
}
int C;char str[105];
inline int getid(int x,int y){return (x-1)*C+y;}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1=clock();
	read(C);G.set(C*2);
	while (1){
		scanf("%s",str);
		if (str[0]=='E')break;
		int x,y,x1,y1,x2,y2;read(x1);read(y1);read(x2);read(y2);
		x=getid(x1,y1);y=getid(x2,y2);
		if (str[0]=='A')G.add(x,y,0);
		if (str[0]=='O')G.add(x,y,1);
		if (str[0]=='C')G.add(x,y,2);
	}
	G.calc(1,G.m,0,1,0);
	for (int i=1;i<=G.m;++i)if (G.a[i].type==0)printf("%c\n",G.a[i].ans?'Y':'N');
	//printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


