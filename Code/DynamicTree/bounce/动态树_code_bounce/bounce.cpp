/*
 * $File: bounce.cpp
 * $Date: Fri Jul 09 20:59:27 2010 +0800
 * $Author: Tim
 * $Solution: Dynamic Tree with Splay Tree implementation
 * $Time complexity: O(mlogn) , per operation amorized O(logn);
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

#define MAXN 200005

using namespace std;


class SplayNode
{
	public:
		int fa, lt, rt, size;
};
SplayNode node[MAXN + 1];

// functions below are belong to splay tree
// we can see that, this splay tree is quite
// simple, and just 'splay' function
// and size maintaining supported.
// but that what all we need to
// solve this problem

void Renew(int x)
{
	//if (!x)return;
	node[x].size = node[node[x].lt].size + node[node[x].rt].size + 1;
}
void RightRotate(int x)
{
	int lc = node[x].lt, fa = node[x].fa;
	node[x].lt = node[lc].rt; node[node[x].lt].fa = x;
	node[lc].rt = x; node[x].fa = lc;
	node[lc].fa = fa;
	if (x == node[fa].lt)
		node[fa].lt = lc;
	else
		node[fa].rt = lc;
	Renew(x);
	Renew(lc);
}


void LeftRotate(int x)
{
	int rc = node[x].rt, fa = node[x].fa;
	node[x].rt = node[rc].lt; node[node[x].rt].fa = x;
	node[rc].lt = x; node[x].fa = rc;
	node[rc].fa = fa;
	if (x == node[fa].lt)
		node[fa].lt = rc;
	else
		node[fa].rt = rc;
	Renew(x);
	Renew(rc);
}

void splay(int x, int FA = 0)
{
	int fa, Fa;
	while ((fa = node[x].fa) != FA)
	{
		if ((Fa = node[fa].fa) == FA)
		{
			if (x == node[fa].lt)
				RightRotate(fa);
			else
				LeftRotate(fa);
		}
		else
		{
			if (x == node[fa].lt)
			{
				if (fa == node[Fa].lt)
				{
					RightRotate(Fa);
					RightRotate(fa);
				}
				else
				{
					RightRotate(fa);
					LeftRotate(Fa);
				}
			}
			else
			{
				if (fa == node[Fa].rt)
				{
					LeftRotate(Fa);
					LeftRotate(fa);
				}
				else
				{
					LeftRotate(fa);
					RightRotate(Fa);
				}
			}
		}
	}
}

// end splay

int query_rank(int id)
{
	splay(id);
	return node[node[id].lt].size + 1;
}
int father[MAXN + 1];
int n;
void Init()
{
	scanf("%d", &n);
	for (int i = 1, k; i <= n; i ++)
	{
		scanf("%d", &k);
		k += i;
		if (k > n + 1)
			k = n + 1;
		father[i] = k;
		node[i].size = 1;
	}
	node[n + 1].size = 1;
}

int split(int id) 
	// isolate id and the node right after it on the solid path 
	// and return that node
{
	splay(id);
	if (node[id].rt)
	{
		int rc = node[id].rt;
		node[id].rt = node[rc].fa = 0;
		node[id].size -= node[rc].size;
		return rc;
	}
	else
		return 0;
}

void Link(int id, int fa) 
	// let fa be the father of id, 
	// we assume that before this, 
	// id is the head of a solid path,
	// and fa is the tail of a solid path,
	// this was done by function 'cut' and 'split'
{
	splay(id);
	//assert(!node[id].lt);
	splay(fa);
	//assert(!node[fa].rt);
	node[fa].rt = id;
	node[fa].size += node[id].size;
	node[id].fa = fa;
}

int get_head(int x)
	// get the head of the solid path which x is in.
{
	while (node[x].fa)
		x = node[x].fa;
	while (node[x].lt)
		x = node[x].lt;
	splay(x);
	return x;
}

void expose(int id) 
	// turn the edges between id and the root of the tree id is in
	// all into solid edges. with this operation, we can query what
	// we want conveniently in a splay tree.
{
	while (true)
	{
		id = get_head(id);
				printf("*%d\n",id);
		if (!father[id])
			break;
		split(father[id]);
		Link(id, father[id]);
	}
}

int query_depth(int id)
{
	expose(id);
	return query_rank(id) - 1;
}

void cut(int id)
	// this function isolated the subtree rooted id
{
	expose(id);
	split(father[id]);
}

void modify_father(int id, int fa)
{
	cut(id);
	split(fa);
	father[id] = fa;
	Link(id, fa);
}

void Solve()
{
	int m, cmd, id, k;
	scanf("%d", &m);
	while (m --)
	{
		scanf("%d%d", &cmd, &id);
		id ++;
		if (cmd == 1)
			printf("%d\n", query_depth(id));
		else
		{
			scanf("%d", &k);
			k += id;
			if (k > n + 1)
				k = n + 1;
			modify_father(id, k);
		}
	}
}

int main()
{
	freopen("c:\\bounce.in", "r", stdin);
	//freopen("bounce.out", "w", stdout);
	Init();
	Solve();
	for(;;);
	return 0;
}


