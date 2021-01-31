/*
 * 1811. Longest Common Substring.cpp
 *
 *  Created on: 2011-11-7
 *  Author: mac
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

const int MAX_N = 250000 + 10;
char buf[MAX_N];
struct State {
	State*suf, *go[26];
	int val;
	State() :
			suf(0), val(0) {
		memset(go, 0, sizeof go);
	}
}*root, *last;
State statePool[MAX_N * 2], *cur;

void init() {
	cur = statePool;
	root = last = cur++;
}

void extend(int w) {
	State*p = last, *np = cur++;
	np->val = p->val + 1;
	while (p && !p->go[w])
		p->go[w] = np, p = p->suf;
	if (!p)
		np->suf = root;
	else {
		State*q = p->go[w];
		if (p->val + 1 == q->val) {
			np->suf = q;
		} else {
			State*nq = cur++;
			memcpy(nq->go, q->go, sizeof q->go);
			nq->val = p->val + 1;
			nq->suf = q->suf;
			q->suf = nq;
			np->suf = nq;
			while (p && p->go[w] == q)
				p->go[w] = nq, p = p->suf;
		}
	}
	last = np;
}

int main() {
	scanf("%s", buf);
	init();
	for (char*pt = buf; *pt; ++pt)
		extend(*pt - 'a');
	scanf("%s", buf);
	State*t = root;
	int l = 0, ans = 0;
	for (char*pt = buf; *pt; ++pt) {
		int w = *pt - 'a';
		if (t->go[w]) {
			t = t->go[w];
			++l;
		} else {
			while (t && !t->go[w])
				t = t->suf;
			if (!t)
				l = 0, t = root;
			else {
				l = t->val + 1;
				t = t->go[w];
			}
		}
		ans = max(ans, l);
	}
	printf("%d\n", ans);
	return 0;
}


