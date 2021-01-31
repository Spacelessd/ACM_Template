#include<cstdio>
#include<cstring>
#include<algorithm>
#define CH getchar()
const int oo = 1000000007, N = 20005, Q = 31;
struct note
{
    int v, size;
} c[N];
int fa[N], ed[N], son[N], next[N], v[N], l[N], r[N], B[N], a[N], f[N], sum[N];
int len, n;
long long ans, P[N];
void read(int &x)
{
    x = 0;
    char ch;
    for (ch = CH; ch < '0' || ch > '9'; ch = CH);
    for (; ch >= '0' && ch <= '9'; x = x * 10 + ch - 48, ch = CH);
}
bool cmp(const note i, const note j)
{
    return i.v < j.v;
}
void dfs(int x, int y)
{
    fa[x] = y;
    f[++len] = x;
    for (int p = son[x]; p; p = next[p])
        if (ed[p] != y) dfs(ed[p], x);
}
void work()
{
    for (int k = n; k; k--)
    {
        int i = f[k], l = 0, x = 1;
        v[i] = 0;
        sum[i] = 1;
        for (int p = son[i]; p; p = next[p])
        {
            int j = ed[p];
            if (fa[i] != j) c[l].v = v[j], c[l++].size = sum[j];
        }
        std::sort(c, c + l, cmp);
        for (int j = 1; j <= l; j++)
        {
            if (c[j].v != c[j-1].v || j == l) ans = ans * P[x] % oo, x = 1;
            else x++;
        }
        for (int j = 0; j < l; j++)
            v[i] = v[i] * B[c[j].size * 2] + c[j].v, sum[i] += c[j].size;
        v[i] = v[i] * Q + 1;
    }
}
int main()
{
	freopen("IOPC1200.in","r",stdin);
	freopen("std1.out","w",stdout);
    B[0] = 1;
    for (int i = 1; i <= 20000; i++) B[i] = B[i-1] * Q;
    P[0] = 1;
    for (int i = 1; i <= 11000; i++) P[i] = P[i-1] * i % oo;
    int t, x, y, l;
    read(t);
    while (t--)
    {
        read(n);
        l = 0;
        for (int i = 0; i < n; i++) son[i] = 0;
        for (int i = 1; i < n; i++)
        {
            read(x), read(y);
            ed[++l] = y;
            next[l] = son[x];
            son[x] = l;
            ed[++l] = x;
            next[l] = son[y];
            son[y] = l;
        }
        len = 0;
        dfs(0, -1);
        ans = 1;
        work();
        printf("%d\n", ans);
    }
    //system("pause");
    return 0;
}



