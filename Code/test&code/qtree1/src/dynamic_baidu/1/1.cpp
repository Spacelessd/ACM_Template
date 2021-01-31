#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;

const int oo=1000000;

struct node
{
    int cost,maxcost;
    bool isroot;
    node *c[2],*f;    
}P[100005],*null;

int n,m,t,dy[100005];

void update(node *p)
{
    p->maxcost=p->cost;
    if (p->c[0]->maxcost > p->maxcost) p->maxcost=p->c[0]->maxcost;
    if (p->c[1]->maxcost > p->maxcost) p->maxcost=p->c[1]->maxcost;
}

void rot(node *p,int o)
{
    node *q=p->f;
    q->c[o]=p->c[!o];
    p->c[!o]->f=q;
    p->c[!o]=q;
    p->f=q->f;
    if (p->f->c[o]==q) p->f->c[o]=p;
    if (p->f->c[!o]==q) p->f->c[!o]=p;
    q->f=p;
    update(q);
    p->isroot=q->isroot;
    q->isroot=false;
}

void splay(node *p)
{
    while (!p->isroot)
    {
        if (p->f->isroot)
        {
            if (p==p->f->c[0]) rot(p,0);
            else rot(p,1);
        }
        else
        {
            if (p->f->f->c[0]==p->f)
            {
                if (p->f->c[0]==p) rot(p->f,0),rot(p,0);
                else rot(p,1),rot(p,0);
            }
            else
            {
                if (p->f->c[1]==p) rot(p->f,1),rot(p,1);
                else rot(p,0),rot(p,1);
            }
        }
    }
    update(p);
}

void access(node *p)
{
    node *t=p;
    node *q=null;
    do
    {
        splay(p);
        p->c[1]->isroot=true;
        p->c[1]=q;
        q->isroot=false;
        update(p);
        q=p;
        p=p->f;
    }while (p!=null);
    splay(t);
}

int ansess(node *p)
{
    node *t=p;
    node *q=null;
    int re;
    do
    {
        splay(p);
        if (p->f==null)
        {
            if (t!=p)
            re=max(p->c[1]->maxcost,q->maxcost);
            else re=p->c[1]->maxcost;
        }
        p->c[1]->isroot=true;
        p->c[1]=q;
        q->isroot=false;
        update(p);
        q=p;
        p=p->f;
    }while (p!=null);
    splay(t);
    return re;
}

void change(int a,int b)
{
    node *p=P+dy[a];
    //access(p);
	splay(p);
    p->cost=b;
    update(p);
}

void query(int a,int b)
{
    access(P+a);
    printf("%d\n",ansess(P+b));
}

struct edge
{
    int t,c,id;
    edge *next;
}E[200010],*V[100005];
int eh;
inline void addedge(int id,int a,int b,int c)
{
    E[++eh].next=V[a];  V[a]=E+eh;  V[a]->t=b;  V[a]->c=c; V[a]->id=id;
    E[++eh].next=V[b];  V[b]=E+eh;  V[b]->t=a;  V[b]->c=c; V[b]->id=id;
}

void maketree(int u)
{
    for (edge *e=V[u];e;e=e->next)
    if ( P+e->t != P[u].f )
    {
        P[e->t].f=P+u;
        dy[e->id]=e->t;
        P[e->t].cost=P[e->t].maxcost=e->c;
        maketree(e->t);
    }
}

void init()
{
    null=P+100002;
    null->c[0]=null->c[1]=null->f=null;
    null->maxcost=null->cost=-oo;
    eh=0;
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        P[i].c[0]=P[i].c[1]=P[i].f=null;
        P[i].isroot=true;
        P[i].maxcost=-oo;P[i].cost=-oo;
    }
    int a,b,c;
    memset(V,0,sizeof(V));
    for (int i=1;i<=n-1;i++)
    {
        scanf("%d%d%d",&a,&b,&c);
        addedge(i,a,b,c);
    }
    maketree(rand()%n+1);
}

int main()
{
    freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
    srand(1108);
    int T;
    scanf("%d",&T);
    char st[10];
    int a,b;
    for (;T;--T)
    {
        init();
        while (true)
        {
            scanf("%s",st);
            if (st[0]=='Q')
            {
                scanf("%d%d",&a,&b);
                query(a,b);
            }
            else if (st[0]=='C')
            {
                scanf("%d%d",&a,&b);
                change(a,b);
            }
            else break;
        }
    }
    return 0;
}
