/*
ID:hqztrue1
LANG:C++
TASK:ditch
*/
#include <cstdio>
#define rep(i,l,r) for(int i = l; i <= r; i++)
const int MAXN = 210, MAXM = 610, inf = (~0U)>>2;
int n, m, a[MAXM][MAXN], next[MAXN];
inline void orz(int l, int e) {
    a[l][e] = -1;int t = MAXN - 1;
    rep(i,0,m) if (a[l][i]) next[t] = i, t = i; next[t] = -1;
    rep(i,0,n) if (i!=l && (t = a[i][e])) {
        a[i][e] = 0;
        for (int j = next[MAXN - 1]; j != -1; j = next[j])
            a[i][j] += a[l][j] * t;
    }
}
int solve(void) {
    for(;;) {
        int min = inf, l = 0, e = 0;
        rep(i,1,m) if (a[0][i] > 0) {e = i; break;}
        if (!e) return a[0][0];
        rep(i,1,n) if (a[i][e] < 0 && a[i][0] < min) min = a[i][0], l = i;
        orz(l, e);
    }
}
int main() {
	freopen("ditch.in","r",stdin);
	freopen("ditch.out","w",stdout);
    int v, e, x, y, z; scanf("%d%d", &e, &v);
    rep(i,1,e) {
        scanf("%d%d%d", &x, &y, &z);
        a[x - 1][i] = 1, a[y - 1][i] = -1;
        a[v*2-4+i][i] = -1, a[v*2-4+i][0] = z;
    }
    rep(i,1,v-2) rep(j,1,e) a[i + v - 2][j] = -a[i][j];
    n = v*2-4+e, m = e; printf("%d\n", solve());
}
