#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
#define INT_MAX (1<<30)
const int MAX_N = 40000 + 10;
const int MAX_LIMIT = 400 + 10;
const int MAX_SQRT = 200 + 10;
const int MAX_LOG = 17;
vector<int> E[MAX_N];
int n, nQ;
inline int nextInt()
{
    int x = 0;
    char ch;
    while (ch = getchar(), ch < '0' || ch > '9')
        ;
    x = ch - '0';
    while (ch = getchar(), ch >= '0' && ch <= '9')
        x = x * 10 + ch - '0';
    return x;
}
int anc[MAX_N][MAX_LOG];
int father[MAX_N];
int dep[MAX_N], cur;
int sqrtN;
int getLca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    int need = dep[u] - dep[v];
    for (int i = 0; i < MAX_LOG; ++i)
    {
        if (need >> i & 1)
            u = anc[u][i];
    }
    if (u == v)
        return u;
    for (int i = MAX_LOG - 1; i >= 0; --i)
    {
        int nu = anc[u][i], nv = anc[v][i];
        if (nu != nv)
            u = nu, v = nv;
    }
    return anc[u][0];
}

int id[MAX_N], nId;
map<int, int> idmap;
int LIMIT;

int specialId[MAX_N], nSpecialId;
int cnt[MAX_N];
int ans[MAX_LIMIT][MAX_N];

int *adj[MAX_N], deg[MAX_N];
int mem[MAX_N * 2];

int specialAnc[MAX_N];

int blockPool[MAX_N][MAX_SQRT];
int blockCur = 0;
int at[MAX_N], idx[MAX_N];

struct BlockList
{
    int *blocks[MAX_SQRT];
    void set(int all)
    {
        int *b = blockPool[blockCur++];
        fill(b, b + sqrtN, -1);
        fill(blocks, blocks + sqrtN, b);
    }
    void set(BlockList &src, int i, int w)
    {
        memcpy(blocks, src.blocks, sizeof(int *) * sqrtN);
        int *b = blockPool[blockCur++];
        memcpy(b, src.blocks[at[i]], sizeof(int) * sqrtN);
        b[idx[i]] = w;
        blocks[at[i]] = b;
    }
    inline int operator[](int i)
    {
        return blocks[at[i]][idx[i]];
    }
};
BlockList firstAnc[MAX_N];

int getSpecial(int u, int par)
{
    int maxNeed = 0;
    for (vector<int>::iterator e = E[u].begin(); e != E[u].end(); ++e)
    {
        if (*e != par)
        {
            int need = getSpecial(*e, u);
            maxNeed = max(maxNeed, need);
        }
    }
    if (maxNeed >= LIMIT)
    {
        specialId[u] = nSpecialId++;
        return 0;
    }
    return maxNeed + 1;
}

void dfs(int u, int par, int d, int sanc)
{
    father[u] = anc[u][0] = par;
    dep[u] = d;
    if (specialId[u] != -1)
        sanc = u;
    specialAnc[u] = sanc;
    for (int i = 1; i < MAX_LOG; ++i)
    {
        int go = anc[u][i - 1];
        if (go == -1)
            anc[u][i] = -1;
        else
            anc[u][i] = anc[go][i - 1];
    }
    for (vector<int>::iterator e = E[u].begin(); e != E[u].end(); ++e)
    {
        if (*e != par)
        {
            firstAnc[*e].set(firstAnc[u], id[*e], d + 1);
            dfs(*e, u, d + 1, sanc);
        }
    }
}

void dfs(int u, int par, int result, int ans[])
{
    //while (1)printf("nie\n");
	int me = id[u];
    if (cnt[me] == 0)
        ++result;
    cnt[me]++;
    ans[u] = result;

    int *end = adj[u] + deg[u];
    for (int *e = adj[u]; e != end; ++e)
    {
        if (*e != par)
            dfs(*e, u, result, ans);
    }

    cnt[me]--;
}

int mark[MAX_N], markCur = 1;

int bf(register int a, register int b, register int lca)
{
    ++markCur;
    int ret = 0;
    while (a != lca)
    {
        register int me = id[a];
        if (mark[me] != markCur)
        {
            mark[me] = markCur;++ret;
        }
        a = father[a];
    }
    while (b != lca)
    {
        register int me = id[b];
        if (mark[me] != markCur)
        {
            mark[me] = markCur;
            ++ret;
        }
        b = father[b];
    }
    int me = id[lca];
    if (mark[me] != markCur)
    {
        mark[me] = markCur;
        ++ret;
    }
    return ret;
}

int calc(int a, int b)
{
    int lca = getLca(a, b);
    int dlca = dep[lca];
    int distA, distB, sa = specialAnc[a], sb = specialAnc[b];
    if (sa == -1 || dep[sa] < dlca)
        distA = INT_MAX;
    else
        distA = dep[a] - dep[sa];
    if (sb == -1 || dep[sb] < dlca)
        distB = INT_MAX;
    else
        distB = dep[b] - dep[sb];
    if (distA > distB)
    {
        swap(distA, distB), swap(sa, sb), swap(a, b);
    }
    if (distA == INT_MAX)
        return bf(a, b, lca);
    int ret = ans[specialId[sa]][b];
    ++markCur;
    BlockList &bsa = firstAnc[sa], &bb = firstAnc[b];
    while (a != sa)
    {
        int me = id[a];
        if (mark[me] != markCur)
        {
            mark[me] = markCur;
            int x = at[me], y = idx[me];
            if (bsa.blocks[x][y] < dlca && bb.blocks[x][y] < dlca)
                ++ret;
        }
        a = father[a];
    }
    return ret;
}

void print(int x)
{
    int ps[20];
    int n = 0;
    if (!x)
        puts("0");
    else
    {
        while (x)
            ps[n++] = x % 10, x /= 10;
        for (int i = n - 1; i >= 0; --i)
        {
            putchar('0' + ps[i]);
        }
        putchar('\n');
    }
}

int maxd;
void dfs2(int u, int par, int d)
{
    maxd = max(maxd, d);
    father[u] = par;
    for (vector<int>::iterator e = E[u].begin(); e != E[u].end(); ++e)
    {
        if (*e != par)
            dfs2(*e, u, d + 1);
    }
}

int ROOT;

int main()
{
	freopen("cot2.in","r",stdin);
	freopen("cot2.out","w",stdout);
    n = nextInt();
    nQ = nextInt();
    ROOT = rand() % n;
    for (int i = 0; i < n; ++i)
    {
        int w = nextInt();
        if (idmap.count(w))
            id[i] = idmap[w];
        else
            id[i] = idmap[w] = nId++;
    }
    for (int i = 0; i < n - 1; ++i)
    {
        int a = nextInt() - 1, b = nextInt() - 1;
        E[a].push_back(b), E[b].push_back(a);
    }
    int *memCur = mem;
    for (int i = 0; i < n; ++i)
    {
        adj[i] = memCur;
        for (vector<int>::iterator e = E[i].begin(); e != E[i].end(); ++e)
        {
            adj[i][deg[i]++] = *e;
        }
        memCur += deg[i];
    }

    dfs2(ROOT, -1, 0);
    if (0){
	if (maxd <= 800)
    {
        dfs(ROOT, -1, 0, -1);
        for (int i = 0; i < nQ; ++i)
        {
            int a = nextInt()/* ^ last*/, b = nextInt();
            --a, --b;
            int ret = bf(a, b, getLca(a, b));
            print(ret);
        }
        return 0;
    }
	}
    LIMIT = (int) sqrt(n / 2) + 1;
    memset(specialId, -1, sizeof specialId);
    nSpecialId = 0;
    getSpecial(ROOT, -1);
    for (int i = 0; i < n; ++i)
    {
        if (specialId[i] != -1)
        {
            dfs(i, -1, 0, ans[specialId[i]]);
        }
    }
    sqrtN = 0;
    while (sqrtN *sqrtN <= n)
        ++sqrtN;
    for (int i = 0; i < n; ++i)
    {
        at[i] = i / sqrtN;
        idx[i] = i % sqrtN;
    }
    firstAnc[n].set(-1);
    firstAnc[ROOT].set(firstAnc[n], id[ROOT], 0);
    dfs(ROOT, -1, 0, -1);
    for (int i = 0; i < nQ; ++i)
    {
        int a = nextInt()/* ^ last*/, b = nextInt();
        --a, --b;
        int ret = calc(a, b);
        print(ret);
    }
    return 0;
}

