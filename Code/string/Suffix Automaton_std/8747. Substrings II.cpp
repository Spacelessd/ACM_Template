/*
 * 8747. Substrings II.cpp
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

const int MAX_N = 40000 + 10;
const int MAX_LEN = MAX_N * 2;
const int MAX_N_NODES = MAX_LEN * 2;
const int ALPHABET = 26;
namespace DT {
	struct Node {
		Node*ch[2], *par;
		Node*pathFa;
		int cnt, add;
		bool isRoot;
		Node() :
				par(0), cnt(0), add(0), pathFa(0), isRoot(false) {
			memset(ch, 0, sizeof ch);
		}
		void setCh(Node*c, bool d) {
			ch[d] = c;
			c->par = this;
		}
		bool dir() {
			return this == par->ch[1];
		}
		void setRoot(Node*_pathFa);
		void apply(int a) {
			add += a;
			cnt += a;
		}
		void relax() {
			if (add) {
				for (int c = 0; c < 2; ++c) {
					ch[c]->apply(add);
				}
				add = 0;
			}
		}
	};

	Node nodePool[MAX_N_NODES], *cur, *null;
	Node*newNode() {
		Node*t = cur++;
		t->ch[0] = t->ch[1] = t->par = t->pathFa = null;
		t->isRoot = true;
		return t;
	}

	void Node::setRoot(Node*_pathFa) {
		pathFa = _pathFa;
		par = null;
		isRoot = true;
	}

	void rotate(Node*t) {
		Node*p = t->par;
		p->relax();
		t->relax();
		bool d = t->dir();
		p->par->setCh(t, p->dir());
		p->setCh(t->ch[!d], d);
		t->setCh(p, !d);
		if (p->isRoot) {
			t->setRoot(p->pathFa);
			p->isRoot = false;
		}
	}

	void splay(Node*t) {
		while (!t->isRoot) {
			if (t->par->isRoot)
				rotate(t);
			else {
				if (t->dir() == t->par->dir())
					rotate(t->par), rotate(t);
				else
					rotate(t), rotate(t);
			}
		}
		t->relax();
	}

	Node* expose(Node*t) {
		Node*u, *v;
		for (u = t, v = null; u != null; v = u, u = u->pathFa) {
			splay(u);
			u->ch[1]->setRoot(u);
			v->isRoot = false;
			u->setCh(v, 1);
		}
		return v;
	}

	void cut(Node*u) { //cut u and it's father
		splay(u);
		if (u->ch[0] == null) //already cutted
			return;
		Node*f = u->ch[0];
		while (f->ch[1] != null)
			f = f->ch[1];
		splay(f);
		f->ch[1]->setRoot(f);
		f->ch[1] = null;
		splay(u);
	}

	void addToRoot(Node*t, int add) { //don't include itself
		expose(t);
		splay(t);
		t->ch[0]->apply(add);
	}

	void init() {
		cur = nodePool;
		null = cur++;
	}
} // namespace DT

using DT::Node;

struct State {
	State*go[ALPHABET], *suf;
	bool inner;
	int val;
	Node*node;
	State() :
			suf(0), val(0), inner(false) {
		memset(go, 0, sizeof go);
	}
}*root, *last;

State statePool[MAX_N_NODES], *cur;

State* newState() {
	cur->node = DT::newNode();
	return cur++;
}

void init() {
	DT::init();
	cur = statePool;
	root = last = newState();
}

void extend(int w) {
//	cout << w << endl;
	State*p = last, *np = newState();
	np->val = p->val + 1;
	np->inner = true;
	DT::Node*nd = np->node;
	nd->cnt = 1;
	while (p && !p->go[w])
		p->go[w] = np, p = p->suf;
	if (!p) {
		np->suf = root;
		nd->pathFa = root->node;
	} else {
		State*q = p->go[w];
		if (p->val + 1 == q->val) {
			np->suf = q;
			nd->pathFa = q->node;
		} else {
			State*nq = newState();
			memcpy(nq->go, q->go, sizeof q->go);
//			cout << "CUT" << endl;
			DT::cut(q->node);
//			cout << "DONE" << endl;

			nq->node->cnt = q->node->cnt;
			nq->suf = q->suf;
			nq->node->pathFa = q->suf->node;

			q->suf = nq;
			q->node->pathFa = nq->node;

			np->suf = nq;
			nd->pathFa = nq->node;

			while (p && p->go[w] == q)
				p->go[w] = nq, p = p->suf;
		}
	}
	DT::addToRoot(nd, 1);
//	cout << "DONE" << endl;
	last = np;
}

char buf[MAX_N];

int ask(char*pt) {
	State*s = root;
	for (; *pt; ++pt) {
		int w = *pt - 'a';
		if (!s->go[w])
			return 0;
		s = s->go[w];
	}
	DT::splay(s->node);
	return s->node->cnt;
}

int main() {
	scanf("%s", buf);
	init();
	for (char*pt = buf; *pt; ++pt)
		extend(*pt - 'a');
	int Q, A, B;
	cin >> Q >> A >> B;
	for (int i = 0; i < Q; ++i) {
		scanf("%s", buf);
		int ret = ask(buf);
		printf("%d\n", ret);
		extend((A * ret + B) % 26);
	}
}
