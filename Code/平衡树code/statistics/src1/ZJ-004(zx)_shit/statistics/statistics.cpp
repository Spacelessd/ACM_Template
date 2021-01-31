#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define MOD 1000000007
using namespace std;
const int MaxN = 200005;
int father[MaxN], lson[MaxN], rson[MaxN], size[MaxN], key[MaxN];
int N, A, B, C, root, node;
long long ANS;

inline void renew(int x) {
	size[x] = size[lson[x]] + size[rson[x]] + 1;
}

inline void lrot(int x) {
	int y = father[x], z = father[y];
	lson[y] = rson[x], father[rson[x]] = y;
	rson[x] = y, father[y] = x;
	y == lson[z] ? lson[z] = x : rson[z] = x;
	father[x] = z;
	renew(y);
}

inline void rrot(int x) {
	int y = father[x], z = father[y];
	rson[y] = lson[x], father[lson[x]] = y;
	lson[x] = y, father[y] = x;
	y == lson[z] ? lson[z] = x : rson[z] = x;
	father[x] = z;
	renew(y);
}

inline void splay(int x) {
	for (; father[x]; ) {
		int y = father[x], z = father[y];
		if (!z) {
			x == lson[y] ? lrot(x) : rrot(x);
			break;
		}
		if (y == lson[z]) {
			if (x == lson[y]) lrot(y), lrot(x);
			else rrot(x), lrot(x);
		}
		else {
			if (x == rson[y]) rrot(y), rrot(x);
			else lrot(x), rrot(x);
		}
	}
	renew(x);
	root = x;
}

inline void insert(int val) {
	if (!root){
		root=++node;
		father[node] =0;
		key[node] = val, size[node] = 1;
		return;
	}
	for (int p = root; ; ) {
		++size[p];
		if (val < key[p]) {
			if (!lson[p]) {
				lson[p] = ++ node, father[node] = p;
				key[node] = val, size[node] = 1;
				break;
			}
			p = lson[p];
		}
		else {
			if (!rson[p]) {
				rson[p] = ++ node, father[node] = p;
				key[node] = val, size[node] = 1;
				break;
			}
			p = rson[p];
		}
	}
	//root = node;
	//splay(node);
}

inline int findkth(int k) {
	int p = root;
	for (int lsize; ;) {
		lsize = size[lson[p]] + 1;
		if (lsize == k) break;
		else if (lsize > k) p = lson[p];
		else k -= lsize, p = rson[p];
	}
	//splay(p);
	return key[p];
}

int main() {
	freopen("statistics.in", "r", stdin);
	freopen("statistics.out", "w", stdout);
	scanf("%d%d%d", &A, &B, &C);
	scanf("%d", &N);
	root = node = 0;
	insert(1);
	ANS = 1;
	for (int i = 2; i <= N; ++ i) {
		int pre = findkth(i >> 1);
		int now = ((long long)A * pre + (long long)B * i + C) % MOD;
		insert(now);
		ANS += now;
	}
	cout << ANS << endl;
	return 0;
}


