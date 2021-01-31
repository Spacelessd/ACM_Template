#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<map>
using namespace std;
#define ll long long
#define N 15
#define maxn 1594323
struct node{
	ll state,sum;
}Q_pool[2][maxn],*Q,*Q1;
template<class Tkey,class Tvalue>
struct Hash{
	Tkey *key; Tvalue *value;
	int *v,*next,len,P,size;
	void build(int Len=9,int p=11)  //len¸öÊý  hashsize=p
	{
		P=p;len=0;size=Len;++Len;
		v=new int[p];memset(v,0,sizeof(int)*p);
		value=new Tvalue[Len];memset(value,0,sizeof(Tvalue)*Len);
		next=new int[Len];memset(next,0,sizeof(int)*Len);
		key=new Tkey[Len];memset(key,0,sizeof(Tkey)*Len);
	}
	Hash(int Len=0,int p=11){
		if (Len==0)return;build(Len,p);
	}
	void clear(){len=0;memset(v,0,sizeof(int)*P);}
	Tkey gethash(Tkey x){return x%P;}
	void insert(Tkey x,Tvalue y=0){
		Tkey x1=gethash(x);
		key[++len]=x;value[len]=y;
		next[len]=v[x1];v[x1]=len;
	}
	void del(Tkey x){
		Tkey x1=gethash(x);int i=v[x1],pre=0;
		while(i){
			if (key[i]==x){
				if (pre==0)v[x1]=next[i];
					else next[pre]=next[i];
			}
			pre=i;i=next[i];
		}
	 }
	int find(Tkey x){
		Tkey x1=gethash(x);int i=v[x1];
		while(i){
			if (key[i]==x)return value[i];
			i=next[i];
		}
		return -1;
	}
	void inc(Tkey x,Tvalue y=1){
		Tkey x1=gethash(x);int i=v[x1];
		while(i){
			if (key[i]==x){value[i]+=y;return;}
			i=next[i];
		}
	}
	int operator [](Tkey x){return find(x);}
};
Hash<ll,int> pos(300000,30007);
int code[N+1],visit[N+1],n,m,tail,tail1,last,place;
char a[N][N];
inline void decode(ll state){
	for (int i=m+1;i;--i)code[i]=state&7,state>>=3;
}
inline ll encode(){
	int cnt=0;ll state=0;
	memset(visit,-1,sizeof(visit));
	visit[0]=0;
	for (int i=1;i<=m+1;++i){
		if (visit[code[i]]==-1)visit[code[i]]=++cnt;
		state<<=3;state|=visit[code[i]];
	}
	return state;
}
void insert(ll sum){
	if (place==m&&code[m+1])return;
	ll state=encode();int tmp=pos.find(state);
	if (tmp!=-1)Q[tmp].sum+=sum;
	else {
		pos.insert(state,++tail);
		Q[tail].state=state;
		Q[tail].sum=sum;
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j){
			while (scanf("%c",&a[i][j]),(a[i][j]!='*'&&a[i][j]!='.'));
			if (a[i][j]=='.')last=i*m+j;
		}
	pos.clear();
	Q=Q_pool[0];Q1=Q_pool[1];
	tail=0;memset(code,0,sizeof(code));insert(1);
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j){
			place=j;pos.clear();
			node *tmp=Q;Q=Q1,Q1=tmp;
			tail1=tail;tail=0;
			for (int head=1;head<=tail1;++head){
				ll state=Q1[head].state,sum=Q1[head].sum;
				decode(state);
				int up=code[j],left=code[m+1];
				if (!left&&!up){  //Case 1
					if (a[i][j]!='*')code[j]=code[m+1]=N;
					insert(sum);
				}
				else if (a[i][j]=='*')continue;
				else if (left&&up){  //Case 2
					if (left==up&&i*m+j==last){
						code[j]=0;code[m+1]=0;
						insert(sum);
					}
					else if (left!=up){
						for (int i=1;i<=m+1;++i)
							if (code[i]==left)code[i]=up;
						code[j]=0;code[m+1]=0;
						insert(sum);
					}
				}
				else if (!left||!up){  //Case 3
					code[j]=0;code[m+1]=up+left;
					insert(sum);
					code[j]=up+left;code[m+1]=0;
					insert(sum);
				}
			}
		}
	printf("%I64d\n",Q[pos[0]].sum);
	system("pause");for (;;);
	return 0;
}


