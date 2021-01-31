#include<iostream>
#include<stdio.h>
#include<cstring>
#define rep(i,n) for(int i=0;i<n;i++)
#define pb push_back
using namespace std;
const int inf = ~0U >> 1;
int n, m;
const int V = 50010;
struct Edge
{
    int t, c;
    Edge *next, *op;
    Edge(int _t, int _c, Edge *_n): t(_t), c(_c), next(_n) {}}*E[V] = {0};
int vs, vt, v;
void AddEdge(int s, int t, int c)
{
    E[s] = new Edge(t, c, E[s]);
    E[t] = new Edge(s, 0, E[t]);
    E[s]->op = E[t];
    E[t]->op = E[s];
}
int k = 0;
bool vis[V] = {0};
bool dfs(int no)
{
    if(no == vt)return true;
    vis[no] = true;
    for(Edge *e = E[no]; e; e = e->next)if(!vis[e->t] && e->c >= k && dfs(e->t))
        {
            e->c -= k;
            e->op->c += k;
            return true;
        }
    return false;
}
int main()
{
    freopen("ditch.in","r",stdin);
    freopen("ditch.out","w",stdout);
    cin >> m >> n;
    v = n;
    int s, t, c;
    vs = 0;
    vt = n - 1;
    while(m--)
    {
        cin >> s >> t >> c;
        --s;
        --t;
        AddEdge(s, t, c);
        k = c > k ? c : k;
    }
    long long ans = 0;
    while(k)
    {
        while(memset(vis, 0, sizeof(vis)), dfs(vs))ans += k;
        k >>= 1;
    }
    cout << ans << endl;
}


