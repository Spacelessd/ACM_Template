#include <cstdio>
#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
#define foreach(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
using namespace std;

const int MAX_L_STR = 200000 + 10;
const int SEED = 13331;
char str[MAX_L_STR], buf[MAX_L_STR];
int hash[MAX_L_STR] = { }, L;
int pow[MAX_L_STR];

void rebuild(int at) {
	for (int i = at; i < L; ++i) {
		hash[i + 1] = hash[i] * SEED + str[i];
	}
}

void initPow() {
	pow[0] = 1;
	for (int i = 1; i < MAX_L_STR; ++i) {
		pow[i] = pow[i - 1] * SEED;
	}
}

int ask(int l, int r) {
	return hash[r + 1] - hash[l] * pow[r - l + 1];
}

int lcp(int a, int b) {
	int L = 0, R = min(::L - a, ::L - b) + 1;
	while (L + 1 < R) {
		int M = L + R >> 1;
		if (ask(a, a + M - 1) == ask(b, b + M - 1))
			L = M;
		else
			R = M;
	}
	return L;
}

void add(int at, char buf[]) {
	int n = strlen(buf);
	memmove(str + at + n, str + at, sizeof(char) * (L - at));
	L += n;
	for (int i = 0; i < n; ++i) {
		str[at + i] = buf[i];
	}
	rebuild(at);
}

void replace(int l, int r, char buf[]) {
	for (int i = l; i <= r; ++i) {
		str[i] = buf[i - l];
	}
	rebuild(l);
}

void erase(int l, int r) {
	memmove(str + l, str + r + 1, sizeof(char) * (L - 1 - r));
	L -= r - l + 1;
	rebuild(l);
}

int main() {
	initPow();
	int nQ;
	scanf("%d%d", &L, &nQ);
	scanf("%s", str);
	rebuild(0);
	for (int i = 0; i < nQ; ++i) {
		char cmd;
		scanf(" ");
		scanf("%c", &cmd);
		switch (cmd) {
			case 'L': {
				int a, b;
				scanf("%d%d", &a, &b);
				printf("%d\n", lcp(--a, --b));
				break;
			}
			case 'A': {
				int at;
				scanf("%d%s", &at, buf);
				add(--at, buf);
				break;
			}
			case 'C': {
				int l, r;
				scanf("%d%d%s", &l, &r, buf);
				replace(--l, --r, buf);
				break;
			}
			case 'D': {
				int l, r;
				scanf("%d%d", &l, &r);
				erase(--l, --r);
				break;
			}
		}
	}
	system("pause");for (;;);
	return 0;
}


