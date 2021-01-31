#include<cstdio>
#include<cstdlib>
#include<cstring>
const int maxn = 20010;
const int maxm = 500000;
const int max = 2147483647;
int n, m, k, x, y, z, ll, ans, flow, i, ss, tt, j;
int son[maxn+1], d[maxn+1], q[maxn+1];
int link[maxm+1], next[maxm+1], cap[maxm+1], opp[maxm+1];

inline int Min(int x, int y)
{
    if (x < y) return x;
    else return y;
}

inline bool build()
{
    int x, y, i, l, r;
    memset(d, 255, sizeof(d));
    l = 1;
    r = 1;
    q[1] = ss;
    d[ss] = 0;
    while (l <= r)
    {
        x = q[l];
        l++;
        i = son[x];
        while (i != -1)
        {
            y = link[i];
            if ((cap[i] != 0)&(d[y] == -1))
            {
                d[y] = d[x] + 1;
                if (y == tt) return 1;
                r++;
                q[r] = y;
            }
            i = next[i];
        }
    }
    return 0;
}


int find(int now, int low)
{
    int ret, i, y, w;
    if (now == tt) return(low);
    i = son[now];
    w = 0;
    while ((i != -1)&(w < low))
    {
        y = link[i];
        if ((cap[i] != 0)&(d[y] == d[now] + 1))
        {
            ret = find(y, Min(low - w, cap[i]));
            if (ret != 0)
            {
                cap[i] -= ret;
                cap[opp[i]] += ret;
                w += ret;
            }
        }
        i = next[i];
    }
    if (w == 0 ) d[now] = -1;
    return(w);
}


inline void addedge(int x, int y, int z)
{
    ll++;
    link[ll] = y;
    next[ll] = son[x];
    son[x] = ll;
    cap[ll] = z;
    opp[ll] = ll + 1;

    ll++;
    link[ll] = x;
    next[ll] = son[y];
    son[y] = ll;
    cap[ll] = 0;
    opp[ll] = ll - 1;
}

int costa[1000], costb[1000];
int ed[1000][1000];
int main()
{
    freopen("plan.in", "r", stdin);
    freopen("plan.out", "w", stdout);
    memset(son, 255, sizeof(son));
    ll = 0;
    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= n; i++)scanf("%d", &costa[i]);
    for (i = 1; i <= m; i++)scanf("%d", &costb[i]);
    for (i = 1; i <= n; i++)addedge(0, i, costa[i]);
    for (i = 1; i <= m; i++)addedge(n + i, n + m + 1, costb[i]);
    for (i = 1; i <= k; i++)
    {
        scanf("%d%d", &x, &y);
        ed[x][y] = 1;
    }
    for(i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
            if (ed[i][j] == 0)addedge(i, n + j, max);
    ss = 0;
    tt = n + m + 1;
    ans = 0;
    while (build())
        while (1)
        {
            flow = find(ss, max);
            if (flow == 0) break;
            ans = ans + flow;
        }
    ans = -ans;
    for (i = 1; i <= n; i++)ans += costa[i];
    for (i = 1; i <= m; i++)ans += costb[i];
    printf("%d\n", ans);
    return 0;
}

