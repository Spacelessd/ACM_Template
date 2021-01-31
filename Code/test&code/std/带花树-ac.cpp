#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<string>
#include<iostream>
using namespace std;
char read_line[20];

//用每朵花的根作为这朵花的根

const int maxn = 222;

typedef int tindex;
typedef bool tgraph [maxn+1][maxn+1];
typedef bool texist [maxn+1];
typedef tindex tlink [maxn+1];
typedef tindex tqueue [maxn+1];

tindex n;
tgraph graph;
tlink match;
texist inqueue, inpath, inblossom;

tindex head, tail;
tqueue queue;

tindex start, finish;
tindex newbase;
tlink father, base;
tindex Count;
int result;
void creategraph()
{
    tindex u, v;
    memset(graph, false, sizeof(graph));
    cin >> n, gets(read_line);
    while (cin >> u >> v)
    {
        gets(read_line);
        graph[u][ v] = true;
        graph[v][ u] = true;
    }
}
void push(tindex u)
{
    queue[tail] = u;
    tail++;
    inqueue[u] = true;
}

tindex pop()
{
    result = queue[head];
    head++;
    return result;
}

tindex findcommonancestor(tindex u, tindex v)
{
    memset(inpath, false, sizeof(inpath));
    while (true)
    {
        u = base[u];
        inpath[u] = true;
        if (u == start ) break;
        u = father[match[u]];
    }
    while (true)
    {
        v = base[v];
        if (inpath[v]) break;
        v = father[match[v]];
    }
    result = v;
    return result;
}

void resettrace(tindex u)
{
    tindex v;
    while (base[u] != newbase)
    {
        v = match[u];
        inblossom[base[u]] = true;
        inblossom[base[v]] = true;
        u = father[v];
        if (base[u] != newbase ) father[u] = v;
    }
}

void blossomcontract(tindex u, tindex v)
{
    newbase = findcommonancestor(u, v);
    memset(inblossom, false, sizeof(inblossom));
    resettrace(u);
    resettrace(v);
    if (base[u] != newbase ) father[u] = v;
    if (base[v] != newbase ) father[v] = u;
    for (u = 1 ; u <= n ; u ++)
        if (inblossom[base[u]] )
        {
            base[u] = newbase;
            if (! (inqueue[u]) ) push(u);
        }
}

void findaugmentingpath()
{
    tindex u, v;
    memset(inqueue, false, sizeof(inqueue));
    memset(father, 0, sizeof(father));
    for (u = 1 ; u <= n ; u ++)
        base[u] = u;
    head = 1;
    tail = 1;
    push(start);
    finish = 0;

    while (head < tail)
    {
        u = pop();
        for (v = 1 ; v <= n ; v ++)
            if (graph[u][ v] & (base[u] != base[v]) & (match[u] != v) )
                if ((v == start) | ((match[v] > 0) & (father[match[v]] > 0)) )
                    blossomcontract(u, v);
                else if (father[v] == 0 )
                {
                    father[v] = u;
                    if (match[v] > 0 )
                        push(match[v]);
                    else
                    {
                        finish = v;
                        return;
                    }
                }
    }
}

void augmentpath()
{
    tindex u, v, w;
    u = finish;
    while (u > 0)
    {
        v = father[u];
        w = match[v];
        match[v] = u;
        match[u] = v;
        u = w;
    }
}

void edmonds()
{
    tindex u;
    memset(match, 0, sizeof(match));
    for (u = 1 ; u <= n ; u ++)
        if (match[u] == 0 )
        {
            start = u;
            findaugmentingpath();
            if (finish > 0 ) augmentpath();
        }
}

void printmatch()
{
    tindex u;
    for (u = 1 ; u <= n ; u ++)
        if (match[u] > 0 )
            Count++;
    cout << Count << endl;
    for (u = 1 ; u <= n ; u ++)
        if (u < match[u] )
            cout << u << ' ' << match[u] << endl;
}

void main1()
{
    creategraph();
    edmonds();
    printmatch();
}

int main()
{
    main1();
    return 0;
}






