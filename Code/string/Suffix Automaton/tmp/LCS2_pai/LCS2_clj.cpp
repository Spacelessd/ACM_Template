/*
 * 1812. Longest Common Substring II.cpp
 *
 *  Created on: 2011-11-7
 *      Author: mac
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <climits>
#include <numeric>
#define foreach(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
#define REP(i,n) for(int i=0;i<n;++i)
using namespace std;
const int MAX_M = 9;

struct State {
	State*suf, *go[26], *next;
	int val;
	int l[MAX_M];
	State() :
			suf(0), next(0) {
		memset(go, 0, sizeof go);
		memset(l, 0, sizeof l);
	}
};

const int MAX_N = 100000 + 10;
State statePool[MAX_N * 2], *cur,*root,*last;
State*firstVal[MAX_N] = { };

State*newState(int val) {
	cur->val = val;
	cur->next = firstVal[val];
	firstVal[val] = cur;
	return cur++;
}

void init() {
	cur = statePool;
	root = last = newState(0);
}

void extend(int w) {
	State*p = last;
	State*np = newState(p->val + 1);
	while (p && !p->go[w])
		p->go[w] = np, p = p->suf;
	if (!p)
		np->suf = root;
	else {
		State*q = p->go[w];
		if (p->val + 1 == q->val) {
			np->suf = q;
		} else {
			State*nq = newState(p->val + 1);
			memcpy(nq->go, q->go, sizeof q->go);
			nq->suf = q->suf;
			q->suf = nq;
			np->suf = nq;
			while (p && p->go[w] == q)
				p->go[w] = nq, p = p->suf;
		}
	}
	last = np;
}

char buf[MAX_N];
int main() {
	freopen("1.in", "r", stdin);
	freopen("2.out", "w", stdout);
	init();
	int L;
	scanf("%s", buf);
	L = strlen(buf);
	for (char*pt = buf; *pt; ++pt)
		extend(*pt - 'a');

	int id;
	for (id = 0; scanf("%s", buf) != EOF; ++id) {
		int l = 0;
		State*t = root;
		for (char*pt = buf; *pt; ++pt) {
			int w = *pt - 'a';
			while (t && !t->go[w]) {
				t = t->suf;
				l = t ? t->val : 0;
			}
			if (!t) {
				t = root;
				l = 0;
			} else {
				t = t->go[w];
				t->l[id] = max(t->l[id], ++l);
			}
		}
	}

	int ans = 0;
	for (int i = L; i >= 0; --i) {
		for (State*p = firstVal[i]; p; p = p->next) {
			int ret = p->val;
			for (int j = 0; j < id; ++j) {
				ret = min(ret, p->l[j]);
				if (p->suf)
					p->suf->l[j] = max(p->suf->l[j], p->l[j]);
			}
			ans = max(ans, ret);
		}
	}

	printf("%d\n", ans);
	//for (;;);
	return 0;
}
