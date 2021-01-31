#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxn 10010
#define maxm 1000010
int son[maxn];
int next[maxm],link[maxm];
int n,m,i,ll,x,y;
void addedge(int x,int y){
	link[++ll]=y;next[ll]=son[x];son[x]=ll;
}
void Hopcroft_Karp(){
	int i;
	while (bfs()){
		for (i=1;i<=nx;i++)
int main(){
	scanf("%d%d",&n,&m);
	for (i=1;i<=m;i++)scanf("%d%d",&x,&y),addedge(x,y);
	system("pause");
}
