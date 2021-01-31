#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define rep(i,n) for(int i=0;i<n;++i)
#define ll long long
#define N 10005
int F[N],w[N],visit[N],is[N],time1=0,n,m;
void Clear_List(){rep(i,n)F[i]=i;}
int Find_Root(int u){
	while(u!=F[u])u=F[u];
	return u;
}
bool Query(int u,int v){
	return Find_Root(u)==Find_Root(v);
}
void Mark_Root(int u){
	int v=F[u],t;F[u]=u;
	while(u!=v){
		t=F[v];F[v]=u;
		u=v;v=t;
	}
}
void Connect(int u,int v){
	Mark_Root(v);F[v]=u;
}
void Destroy(int u,int v){
	Mark_Root(u);F[v]=v;
}
int get(int x,int root){
	if (x==0)return 0;
	if (visit[x]==time1)return is[x];
	visit[x]=time1;
	return is[x]=get(F[x],root);
}
void add(int x,int y){
	++time1;visit[x]=time1;is[x]=1;
	for (int i=1;i<=n;++i)if (get(i,x))w[i]+=y;
}
ll Query(int x){
	++time1;visit[x]=time1;is[x]=1;
	ll res=0;
	for (int i=1;i<=n;++i)if (get(i,x))res+=w[i];
	return res;
}
char c[105];
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d%d",&n,&m);
	Clear_List();
	rep(i,m){
		int u,v;int x,y;
		scanf("%s%d%d",c,&u,&v);
		u--;v--;
		switch(c[0]){
			case 'Q':Query(u,v)?puts("Yes"):puts("No");break;
			case 'C':Connect(u,v);break;
			case 'D':Destroy(u,v);break;
			/*case 'C':{
				scanf("%d",&x);
				Mark_Root(x);break;
			}
			case 'A':{
				scanf("%d%d",&x,&y);
				Add(x,y);break;
			}
			case 'Q':{
				scanf("%d",&x);
				printf("%I64d\n",Query(x));break;
			}*/
		}
	}
	system("pause");for (;;);
	return 0;
}


