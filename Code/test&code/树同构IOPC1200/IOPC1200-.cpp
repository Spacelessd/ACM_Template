#include<cstdio>
#include<cstring>
#include<algorithm>
#define CH getchar()
const int oo = 1000000007, N = 20005, Q = 365464577;
struct note
{
    int v;
} c[N];
int fa[N], ed[N], son[N], next[N], v[N], l[N], r[N], B[N], a[N], f[N];
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
struct hash{
	const static int N=50005;
	static int p;
	int v[N],next[N],key[N],l;
	void clear(int len){
		for (int i=0;i<len;++i)v[i]=0;
		l=0;p=len;
	}
	void insert(int x){
		int x1=x%p;
		key[++l]=x;next[l]=v[x1];v[x1]=l;
	}
};int hash::p;
hash H;
void work()
{
    for (int k = n; k; k--)
    {
        int i = f[k], l = 0, x = 1;
        v[i] = 0;
        for (int p = son[i]; p; p = next[p])
        {
            int j = ed[p];
            if (fa[i] != j) c[l++].v = v[j];
        }
        std::sort(c, c + l, cmp);
        for (int j = 1; j <= l; j++)
        {
            if (c[j].v != c[j-1].v || j == l) ans = ans * P[x] % oo, x = 1;
            else x++;
        }
        /*v[i]=196546757;
        for (int j = 0; j < l; j++)
            v[i] =v[i]^c[j].v;
        v[i] = v[i] * Q ^7654321 + 1645789;*/
        //printf("%d\n",v[i]);
        H.clear(l*2);
        for (int j = 0; j < l; j++)H.insert(v[j]);
        v[i]=196546757;
        for (int j = 0; j < H.p; j++)
        	{
				for (int i1=H.v[j];i1;i1=H.next[i1])
					v[i]^=H.key[i1];
				v[i]=v[i]*Q+164578895;
			}
		v[i] = v[i] * Q ^7654321 + 1645789;
		//printf("%d\n",v[i]);
    }
}
int main()
{
	freopen("IOPC1200.in","r",stdin);
	freopen("D.out","w",stdout);
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



