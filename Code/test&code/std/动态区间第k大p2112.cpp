#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define inf 2000000000
using namespace std;
struct TreeT{
	int l,r,f,k,s;
};
const int maxN=50005;
TreeT T[1000000];
int S[maxN],P[maxN];
int Test,N,M,Tot,MIN,MAX;
char Opt;

inline int Min(int a,int b){if (a<b) return a;else return b;}
inline int Max(int a,int b){if (a>b) return a;else return b;}
inline int Lowbit(int x){return (x & -x);}
inline void Renew(int x){T[x].s=T[T[x].l].s+T[T[x].r].s+1;}

inline void LtoR(int x){
	int y=T[x].f,z=T[y].f;
	T[y].l=T[x].r;T[T[x].r].f=y;
	T[x].r=y;T[y].f=x;
	T[x].f=z;
	if (T[z].l==y) T[z].l=x;
	else T[z].r=x;
	Renew(y);
}

inline void RtoL(int x){
	int y=T[x].f,z=T[y].f;
	T[y].r=T[x].l;T[T[x].l].f=y;
	T[x].l=y;T[y].f=x;
	T[x].f=z;
	if (T[z].l==y) T[z].l=x;
	else T[z].r=x;
	Renew(y);
}

inline void Splay(int x,int &Root){
	for (;T[x].f;){
		int y=T[x].f,z=T[y].f;
		if (z==0){
			if (T[y].l==x) LtoR(x);
			else RtoL(x);
			break;
		}
		if (T[z].l==y){
			if (T[y].l==x) LtoR(y),LtoR(x);
			else RtoL(x),LtoR(x);
		}
		else{
			if (T[y].r==x) RtoL(y),RtoL(x);
			else LtoR(x),RtoL(x);
		}
	}
	Root=x;
	Renew(x);
}

inline void Insert(int x,int &Root){
	if (Root==0){
		Root=x;
		T[x].s=T[T[x].l].s+T[T[x].r].s+1;
		return;
	}
	int p=Root;
	for (;;){
		if (T[x].k<=T[p].k){
			if (T[p].l==0){T[p].l=x;break;}
			p=T[p].l;
		}
		else{
			if (T[p].r==0){T[p].r=x;break;}
			p=T[p].r;
		}
	}
	T[x].f=p;
	for (;p;){
		Renew(p);
		p=T[p].f;
	}
	Splay(x,Root);
	Renew(x);
}

inline void Add(int x,int k){
	for (;x<=N;){
		T[++Tot].k=k;
		Insert(Tot,P[x]);
		x+=Lowbit(x);
	}
}

inline int FindMax(int x){
	for (;T[x].r;) x=T[x].r;
	return x;
}

inline int Join(int x,int y){
	if (!x) return y;
	if (!y) return x;
	int z=FindMax(x);
	Splay(z,x);
	T[z].r=y;T[y].f=z;
	return z;
}

inline void Delete(int x,int &Root){
	Splay(x,Root);
	T[T[x].l].f=T[T[x].r].f=0;
	Root=Join(T[x].l,T[x].r);
	T[x].l=T[x].r=T[x].s=T[x].f=0;
}

inline int Find(int x,int &Root){
	int p=Root;
	for (;;){
        if (x==T[p].k) return p;
		if (x<T[p].k) p=T[p].l;
		else p=T[p].r;
	}
}

inline void Modify(int x,int k){
	int y=x;
	for (;x<=N;){
		int p=Find(S[y],P[x]);
		Delete(p,P[x]);
		T[p].k=k;
		Insert(p,P[x]);
		x+=Lowbit(x);
	}
	S[y]=k;
	if (k<MIN) MIN=k;if (k>MAX) MAX=k;
}

inline int GetSum(int k,int &Root){
	int p=Root,q=0;
	for (;p;){
		if (T[p].k<=k){
			q+=T[p].s-T[T[p].r].s;
			p=T[p].r;
		}
		else p=T[p].l;
	}
	return q;
}

inline int GetTot(int x,int k){
	int s=0;
	for (;x;){
		s+=GetSum(k,P[x]);
		x-=Lowbit(x);
	}
	return s;
}

inline int Query(int x,int y,int z){
	int p=MIN,q=MAX,ans=inf,u,v,mid;
	for (;p<=q;){
		mid=(p+q) >> 1;
		u=GetTot(x-1,mid);
		v=GetTot(y,mid);
		if (v-u>=z) ans=Min(ans,mid),q=mid-1;
		else p=mid+1;
	}
	return ans;
}//二分

void Work(){
	int t;
	scanf("%d%d\n",&N,&M);
	for (int i=1;i<=N;i++){
		scanf("%d",&t);
		if (t<MIN) MIN=t;if (t>MAX) MAX=t;
		S[i]=t;
		Add(i,t);
	}
	scanf("\n");
	for (int i=1;i<=M;i++){
		scanf("%c",&Opt);
		if (Opt=='C'){
            int p;
			scanf("%d%d\n",&p,&t);
			Modify(p,t);
		}
		else{
            int l,r,k;
			scanf("%d%d%d\n",&l,&r,&k);
			printf("%d\n",Query(l,r,k));
		}
	}
}

int main(){
//    freopen("1.in","r",stdin);
//    freopen("1.out","w",stdout);
    
	scanf("%d\n",&Test);
	for (int i=1;i<=Test;i++){
		memset(T,0,sizeof(T));
		memset(P,0,sizeof(P));
		MIN=inf;MAX=-inf;Tot=0;//记录最值
		Work();
	}
	return 0;
}


