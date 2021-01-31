// Program : USACO 4.2.1 ditch (Max Flow)
#include <iostream>
#include <climits>
#include <cstring>
const int maxn = 20010, maxm = 1000010;
using namespace std;
struct node
{
    int data, weight;
    node *next, *anti;
} *ge[maxn+1], *di[maxn+1], *path[maxn+1], data[maxm+1];
int dist[maxn+1], count_dist[maxn+1], his[maxn+1], pre[maxn+1], n;
int top = 0;
node *Add_Edge(int a, int b, int w)
{
    node *p = &data[++ top];
    p->data = b;
    p->weight = w;
    p->next = ge[a];
    ge[a] = p;
    return p;
}
void Ins_Edge(int a, int b, int w)
{
    node *p1 = Add_Edge(a, b, w), *p2 = Add_Edge(b, a, 0);
    p1->anti = p2;
    p2->anti = p1;
}
int Max_Flow(int s, int t)
{
    int i, now_flow, total, min_dist;
    node *p, *locate;
    bool flag;
    //memset(dist, 0, sizeof(dist));
    //memset(count_dist, 0, sizeof(count_dist));
    count_dist[0] = n;
    for (i = 1; i <= n; i ++) di[i] = ge[i];
    for (total = 0, now_flow = INT_MAX, i = s; dist[s] < n; )
    {
        his[i] = now_flow;
        for (flag = false, p = di[i]; p != NULL; p = p->next)
            if ((p->weight > 0) && (dist[i] == dist[p->data] + 1))
            {
                if (p->weight < now_flow) now_flow = p->weight;
                pre[p->data] = i;
                path[p->data] = p;
                di[i] = p;
                i = p->data;
                if (i == t)
                {
                    for (total += now_flow; i != s; i = pre[i])
                    {
                        path[i]->weight -= now_flow;
                        path[i]->anti->weight += now_flow;
                    }
                    now_flow = INT_MAX;
                }
                flag = true;
                break;
            }
        if (! flag)
        {
            for (min_dist = n - 1, p = ge[i]; p != NULL; p = p->next)
                if ((p->weight > 0) && (dist[p->data] < min_dist))
                {
                    min_dist = dist[p->data];
                    locate = p;
                }
            di[i] = locate;
            count_dist[dist[i]] --;
            if (count_dist[dist[i]] == 0) break;
            dist[i] = min_dist + 1;
            count_dist[dist[i]] ++;
            if (i != s)
            {
                i = pre[i];
                now_flow = his[i];
            }
        }
    }
    return total;
}
int main()
{
    int i, m, a, b, w;
    freopen("ditch.in", "r", stdin);
    freopen("ditch.out", "w", stdout);
    scanf("%d%d", &m, &n);
    //for (i = 1; i <= n; i ++) ge[i] = NULL;
    for (i = 1; i <= m; i ++)
    {
        scanf("%d%d%d", &a, &b, &w);
        Ins_Edge(a, b, w);
    }
    printf("%d\n", Max_Flow(1, n));
    return 0;
}
