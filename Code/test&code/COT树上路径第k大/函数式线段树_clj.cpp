#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <climits>
#include <numeric>
#include <vector>
#define foreach(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
#define REP(i,n) for(int i=0;i<n;++i)
using namespace std;

const int MAX_N = 100000 + 10;
vector<int> E[MAX_N];
int n, nQ;
int w[MAX_N];
int sortW[MAX_N];
int nId;

inline int nextInt() {
	int x = 0;
	char ch;
	while (ch = getchar(), ch < '0' || ch > '9')
		;
	x = ch - '0';
	while (ch = getchar(), ch >= '0' && ch <= '9')
		x = x * 10 + ch - '0';
	return x;
}

struct Tree;
Tree*get();

struct Tree {
	int l, r, sum;
	Tree*pl, *pr;
	Tree*set(int _l, int _r, Tree*_pl, Tree*_pr) {
		l = _l, r = _r, pl = _pl, pr = _pr;
		sum = pl->sum + pr->sum;
		return this;
	}
	Tree* set(int _l, int _r, int all) {
		l = _l, r = _r;
		if (l + 1 == r) {
			sum = all;
			return this;
		}
		pl = get()->set(l, l + r >> 1, all);
		pr = get()->set(l + r >> 1, r, all);
		sum = pl->sum + pr->sum;
		return this;
	}
	Tree*add(int at, int d) {
		if (l + 1 == r) {
			return get()->set(l, r, sum + d);
		}
		int m = l + r >> 1;
		if (at < m)
			return get()->set(l, r, pl->add(at, d), pr);
		else
			return get()->set(l, r, pl, pr->add(at, d));
	}
};

const int BUFFER_SIZE = 10000;
Tree*buffer = 0, *cur;
Tree*get() {
	if (!buffer || cur == buffer + BUFFER_SIZE)
		buffer = new Tree[BUFFER_SIZE], cur = buffer;
	return cur++;
}

Tree*my[MAX_N];

const int MAX_LOG = 20;
int anc[MAX_N][MAX_LOG];
int dep[MAX_N];

void dfs(int u, int par, Tree*t, int d) {
	t = t->add(w[u], 1);
	my[u] = t;
	dep[u] = d;
	anc[u][0] = par;
	for (int i = 1; i < MAX_LOG; ++i) {
		int go = anc[u][i - 1];
		if (go == -1)
			anc[u][i] = -1;
		else
			anc[u][i] = anc[go][i - 1];
	}
	for (vector<int>::iterator e = E[u].begin(); e != E[u].end(); ++e) {
		if (*e != par)
			dfs(*e, u, t, d + 1);
	}
}

int getLca(int u, int v) {
	if (dep[u] < dep[v])
		swap(u, v);
	int need = dep[u] - dep[v];
	for (int i = MAX_LOG - 1; i >= 0; --i) {
		if (need >> i & 1)
			u = anc[u][i];
	}
	if (u == v)
		return u;
	for (int i = MAX_LOG - 1; i >= 0; --i) {
		int nu = anc[u][i], nv = anc[v][i];
		if (nu != nv)
			u = nu, v = nv;
	}
	return anc[u][0];
}

int main() {
	n = nextInt(), nQ = nextInt();
	for (int i = 0; i < n; ++i) {
		sortW[i] = w[i] = nextInt();
	}
	for (int i = 0; i < n - 1; ++i) {
		int a = nextInt() - 1, b = nextInt() - 1;
		E[a].push_back(b), E[b].push_back(a);
	}
	sort(sortW, sortW + n);
	nId = unique(sortW, sortW + n) - sortW;
	for (int i = 0; i < n; ++i) {
		w[i] = lower_bound(sortW, sortW + nId, w[i]) - sortW;
	}

	dfs(0, -1, get()->set(0, nId, 0), 0);
	int last = 0;
	for (int i = 0; i < nQ; ++i) {
		int a = nextInt() ^ last, b = nextInt(), k = nextInt() - 1;
		--a, --b;
		int lca = getLca(a, b);
		Tree*ta = my[a], *tb = my[b], *tl = my[lca];
		while (ta->l + 1 != ta->r) {
			int cnt = ta->pl->sum + tb->pl->sum - tl->pl->sum * 2
					+ (w[lca] >= ta->pl->l && w[lca] < ta->pl->r);
			if (cnt <= k) {
				k -= cnt;
				ta = ta->pr, tb = tb->pr, tl = tl->pr;
			} else {
				ta = ta->pl, tb = tb->pl, tl = tl->pl;
			}
		}
		printf("%d\n", sortW[ta->l]);
		last = sortW[ta->l];
	}
	return 0;
}

