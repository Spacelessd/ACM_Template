#include <cstdio>
#include <stdlib.h>
#include <ctime>
using namespace std;
template<class KEY, class DATA>
struct Tnode
{
	KEY key;
	DATA data;
	Tnode *rc, *lc;
	int sz;
	char b;
	Tnode **c(int a)
	{
		return a == 1 ? &rc : &lc;
	}
	Tnode()
	{
		rc = lc = NULL;
		sz = 1;
		b = 0;
	}
};
#define Rotate(y,x,d) *(y->c(d))=*(x->c(-(d)));*(x->c(-(d)))=y;if (d==-1)y->sz-=x->sz;else x->sz+=y->sz;
template<class KEY, class DATA>
struct AVL
{
	typedef Tnode<KEY, DATA> tNode;
	tNode root;
	int H;
	AVL()
	{
		root.rc = NULL;
		H = 0;
	}
	tNode *tIns(KEY k)
	{
		tNode *t, *s, *p, *q, *r;
		int a;
		if (!root.rc)
		{
			root.rc = new Tnode<KEY, DATA>;
			root.rc->key = k;
			H = 1;
			return root.rc;
		}
		t = &root;
		s = p = root.rc;
		while (1)
		{
			if (k < p->key)
			{
				q = p->lc;
				if (!q)
				{
					q = new Tnode<KEY, DATA>;
					p->lc = q;
					break;
				}
				if (q->b)
				{
					t = p;
					s = q;
				}
				p = q;
			}
			else if (k > p->key)
			{
				q = p->rc;
				if (!q)
				{
					q = new Tnode<KEY, DATA>;
					p->rc = q;
					break;
				}
				if (q->b)
				{
					t = p;
					s = q;
				}
				p = q;
			}
			else return p;
		}
		q->key = k;
		p = root.rc;
		while (p != q)
		{
			if (k < p->key)
			{
				p->sz++;
				p = p->lc;
			}
			else p = p->rc;
		}
		if (k < s->key)a = -1;
		else a = 1;
		r = p = *(s->c(a));
		while (p != q)
		{
			if (k < p->key)
			{
				p->b = -1;
				p = p->lc;
			}
			else
			{
				p->b = 1;
				p = p->rc;
			}
		}
		if (s->b == 0)
		{
			s->b = a;
			H++;
			return q;
		}
		else if (s->b == -a)
		{
			s->b = 0;
			return q;
		}
		else
		{
			if (r->b == a)
			{
				Rotate(s, r, a)
				s->b = r->b = 0;
				p = r;
			}
			else
			{
				p = *(r->c(-a));
				Rotate(r, p, -a) Rotate(s, p, a)
				if (p->b == a)
				{
					s->b = -a;
					r->b = 0;
				}
				else if (p->b == 0)s->b = r->b = 0;
				else
				{
					s->b = 0;
					r->b = a;
				}
				p->b = 0;
			}
			if (s == t->rc)t->rc = p;
			else t->lc = p;
		}
		return q;
	}
	tNode *tFind(KEY k)
	{
		tNode *p;
		p = root.rc;
		while (p && p->key != k)if (k < p->key)p = p->lc;
			else p = p->rc;
		return p;
	}
	tNode *tFind_index(int id)
	{
		tNode *p;
		p = root.rc;
		while (p && p->sz != id + 1)if (id >= p->sz)
			{
				id -= p->sz;
				p = p->rc;
			}
			else p = p->lc;
		return p;
	}
	void tDel(KEY key)
	{
		tNode *Stack[100], *p, *q, *r;
		int top, a, b;
		char dir[100];
		Stack[0] = &root;
		dir[0] = 0;
		Stack[1] = root.rc;
		dir[1] = 1;
		top = 2;
		p = root.rc;
		while (p && p->key != key)
		{
			if (key < p->key)p->sz--, dir[top] = -1, p = Stack[top++] = p->lc;
			else dir[top] = 1, p = Stack[top++] = p->rc;
		}
		if (!p)return;
		p->sz--;
		if (p->lc && p->rc)
		{
			q = p->lc;
			dir[top] = -1;
			Stack[top++] = q;
			while (q->rc)
			{
				q = q->rc;
				if (q)dir[top] = 1, Stack[top++] = q;
			}
			root.key = p->key;
			p->key = q->key;
			q->key = root.key;
			root.data = p->data;
			p->data = q->data;
			q->data = root.data;
		}
		if (Stack[top-1]->rc)*(Stack[top-2]->c(dir[top-1])) = Stack[top-1]->rc;
		else *(Stack[top-2]->c(dir[top-1])) = Stack[top-1]->lc;
		delete Stack[top-1];
		top--;
		while (top > 1)
		{
			p = Stack[top-1];
			b = dir[top];
			if (p->b == b)p->b = 0;
			else if (p->b == 0)
			{
				p->b = -b;
				break;
			}
			else
			{
				q = *(p->c(-b));
				if (q->b != b)
				{
					Rotate(p, q, -b)
					if (q->b == 0)q->b = b, p->b = -b;
					else q->b = p->b = 0;
					*(Stack[top-2]->c(dir[top-1])) = q;
					if (q->b)break;
				}
				else
				{
					r = *(q->c(b));
					Rotate(q, r, b) Rotate(p, r, -b)
					if (r->b == -b)q->b = 0, p->b = b;
					else if (r->b == 0)q->b = p->b = 0;
					else p->b = 0, q->b = -b;
					r->b = 0;
					*(Stack[top-2]->c(dir[top-1])) = r;
				}
			}
			top--;
		}
	}
};
typedef struct {} empty;
typedef AVL<int, empty> intAVL;
#define NMax 1000000
int dat[NMax];
int main()
{
	intAVL avl;
	int t1, N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)dat[i] = ((rand() << 14) | rand());
	t1 = clock();
	for (int i = 0; i < N; i++)avl.tIns(dat[i]);
	printf("inserting time %d\n", clock() - t1);
	t1 = clock();
	for (int i = 0; i < N; i++)avl.tFind(dat[i])->key;
	printf("finding(by key) time %d\n", clock() - t1);
	t1 = clock();
	for (int i = 0; i < N; i++)avl.tFind_index(i)->key;
	printf("finding(by index) time %d\n", clock() - t1);
	t1 = clock();
	for (int i = 0; i < N; i++)avl.tDel(dat[i]);
	printf("deleting time %d\n", clock() - t1);
	system("pause");
	return 0;
}
