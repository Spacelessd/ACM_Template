#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 3005
int graph[N][N],match[N],inqueue[N],inpath[N],
	inblossom[N],queue[N],father[N],base[N];
int n,head,tail,start,finish,newbase;
void Create(){
	int n1,n2,m,x,y;
	memset(graph,0,sizeof(graph));
	scanf("%d%d%d",&n1,&n2,&m);
	n=n1+n2;
	for (int i=1;i<=m;++i)scanf("%d%d",&x,&y),graph[x][n1+y]=1;
}
void push(int x){
	queue[++tail]=x;
	inqueue[x]=1;
}
int pop(){return queue[head++];}
int ancestor(int u,int v){
	memset(inpath,0,sizeof(inpath));
	while (1){
		u=base[u];inpath[u]=1;
		if (u==start)break;
		u=father[match[u]];
	}
	while (1){
		v=base[v];
		if (inpath[v])return v;
		v=father[match[v]];
	}
}
void reset(int u){
	int v;
	while (base[u]!=newbase){
		v=match[u];
		inblossom[base[u]]=inblossom[base[v]]=1;
		u=father[v];
		if (base[u]!=newbase)father[u]=v;
	}
}
void contract(int u,int v){
	newbase=ancestor(u,v);
	memset(inblossom,0,sizeof(inblossom));
	reset(u);reset(v);
	if (base[u]!=newbase)father[u]=v;
	if (base[v]!=newbase)father[v]=u;
	for (u=1;u<=n;u++)
		if (inblossom[base[u]]){
			base[u]=newbase;
			if (!inqueue[u])push(u);
		}
}
void findpath(){
	int u,v,i;
	memset(inqueue,0,sizeof(inqueue));
	memset(father,0,sizeof(father));
	for (i=1;i<=n;++i)base[i]=i;
	head=1;tail=0;push(start);finish=0;
	while (head<=tail)
	{
		u=pop();
		for (v=1;v<=n;v++)
			if (graph[u][v]&&(base[u]!=base[v])&&(match[u]!=v))
				if ((v==start)||match[v]&&father[match[v]])contract(u,v);
				else if (!father[v]){
					father[v]=u;
					if (match[v])push(match[v]);
						else {finish=v;return;}
				}
	}
}
void updatepath(){
	int u=finish,v,w;
	while (u){
		v=father[u];w=match[v];
		match[v]=u;match[u]=v;
		u=w;
	}
}
void Edmonds(){
	memset(match,0,sizeof(match));
	for (int i=1;i<=n;++i)
		if (!match[i]){
			start=i;
			findpath();
			if (finish)updatepath();
		}
}
void Print(){
	int i,count=0;
	for (i=1;i<=n;++i)if (match[i])count++;
	printf("%d\n",count/2);
	//for (i=1;i<=n;++i)
	//	if (i<match[i])printf("%d %d\n",i,match[i]);
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("6.out","w",stdout);
	Create();
	Edmonds();
	Print();
	//system("pause");for(;;);
	return 0;
}


