#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define MOD 1000000007
using namespace std;
const int MaxN = 200005;
//int father[MaxN], lson[MaxN], rson[MaxN], size[MaxN], key[MaxN];
int N, A, B, C, root, node;
long long ANS;

struct NODE {
	int key, size;
	NODE *lson, *rson, *father;
};
NODE T[MaxN];

inline void renew(int x) {
	T[x].size = T[x] -> lson.size + T[x] -> rson.size + 1;
}

inline void lrot(int x) {
	int *y = T[x] -> father, *z = T[y] -> father;
	T[y] -> lson = x -> rson, T[x] -> rson -> father = x;
	T[x] -> rson = y, T[y] -> father = x;
	y == T[z] -> lson ? T[z] -> lson = x : T[z] -> rson = x;
	T[x] -> father = z;
	renew(y);
}

inline void rrot(int x) {
	int *y = T[x] -> father, *z = T[y] -> father;
	T[y] -> rson = x -> lson, T[x] -> lson -> father = x;
	T[x] -> lson = y, T[y] -> father = x;
	y == T[z] -> lson ? T[z] -> lson = x : T[z] -> rson = x;
	T[x] -> father = z;
	renew(y);
}

inline void splay(int x) {
	for (; T[x] -> father; ) {
		int *y = T[x] -> father, *z = T[y] -> father;
		if (!z) {
			x == T[y] -> lson ? lrot(x) : rrot(x);
			break;
		}
		if (y == T[z] -> lson) {
			if (x == T[y] -> lson) lrot(y), lrot(x);
			else rrot(x), lrot(x);
		}
		else {
			if (x == T[y] -> rson) rrot(y), rrot(x);
			else lrot(x), rrot(x);
		}
	}
	renew(x);
	root = x;
}

inline void insert(int val) {
	for (int p = root; ; ) {
		if (val < T[p] -> key) {
			if (!T[p] -> lson) {
				T[p] -> lson = ++ node, T[node] -> father = p;
				T[node].key = val, T[node].size = 1;
				break;
			}
			p = T[p] -> lson;
		}
		else {
			if (!T[p] -> rson) {
				T[p] -> rson = ++ node, T[node] -> father = p;
				T[node].key = val, T[node].size = 1;
				break;
			}
			p = T[p] -> rson;
		}
	}
	splay(node);
}

inline int findkth(int k) {
	int p = root;
	for (int lsize; ;) {
		lsize = T[p] -> lson.size + 1;
		if (lsize == k) break;
		else if (lsize > k) p = T[p] -> lson;
		else k -= lsize, p = T[p] -> rson;
	}
	splay(p);
	return T[p].key;
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
