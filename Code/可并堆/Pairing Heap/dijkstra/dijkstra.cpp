#include "pairingheap.h"
#include "edge.h"
#include <conio.h>
#define maxint 0x0fffffff
int v[1001];
pairingheap h(1000);
int n,m;
edge e[1001];
int dist[1001];
bool used[1001];
void dijkstra(void);
int main(void)
{
	scanf("%d %d",&n,&m);
	for(int i=0;i<m;i++)
	{
		int f,t,w;
		scanf("%d %d %d",&f,&t,&w);
		e[f].insert(t,w);
		e[t].insert(f,w);
	}
	int s;
	scanf("%d",&s);
	for(int i=1;i<=n;i++)
		h.insert(i,maxint);
	h.decreasekey(s,0);
	dijkstra();
	for(int i=1;i<=n;i++)
		printf("Dist from %d to %d is:%d\n",s,i,dist[i]);
	return 0;
}
void dijkstra(void)
{
	while(!h.isempty())
	{
		int key=h.findmin();
		int v=h.findminpos();
		while(used[v]&&!h.isempty())
		{
			dist[v]=key;
			h.delmin();
			key=h.findmin();
			v=h.findminpos();
		}
		if(h.isempty())break;
		used[v]=true;
		e[v].repos();
		while(!e[v].isrear())
		{
			h.decreasekey(e[v]->to,key+e[v]->w);
			e[v]++;
		}
	}
}
			
