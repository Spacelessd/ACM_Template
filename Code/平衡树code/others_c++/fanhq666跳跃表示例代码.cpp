#include <cstdio>
#include <stdlib.h>
#include <ctime>
using namespace std;
template<class KEY, class DATA>
struct Lnode
{
	KEY key;
	DATA data;
	Lnode *son, *next;
	Lnode()
	{
		son = next = NULL;
	}
};
template<class KEY, class DATA>
struct JTable
{
	typedef Lnode<KEY, DATA> jNode;
	jNode *head[16];
	int H;
	JTable(KEY low, KEY up)
	{
		H = 0;
		jNode *p;
		for (int i = 0; i < 15; i++)
		{
			head[i] = p = new jNode;
			if (i)p->son = head[i-1];
			p = p->next = new jNode;
			if (i)p->son = head[i-1]->next;
			head[i]->key = low;
			p->key = up;
		}
	}
	jNode *jIns(KEY key)
	{
		int f, i;
		jNode *p, *q, *l;
		f = (rand() & 16383) + 1;
		f &= -f;
		while ((1 << H) < f)H++;
		p = head[i=H];
		l = NULL;
		while (i >= 0)
		{
			while (p->next->key <= key)p = p->next;
			if ((1 << i) <= f)
			{
				q = new jNode;
				q->key = key;
				q->next = p->next;
				p->next = q;
				if (l)l->son = q;
				l = q;
			}
			p = p->son;
			i--;
		}
		return l;
	}
	jNode *jFind(KEY key)
	{
		int i;
		jNode *p;
		for (p = head[i=H]; i >= 0; i--)
		{
			while (p->next->key <= key)p = p->next;
			if (i)p = p->son;
		}
		return (p->key == key) ? p : NULL;
	}
	void jDel(KEY key)
	{
		int i;
		jNode *p, *q;
		for (p = head[i=H]; i >= 0; i--)
		{
			while (p->next->key < key)p = p->next;
			if (p->next->key == key)
			{
				q = p->next;
				p->next = q->next;
				delete q;
			}
			p = p->son;
			i--;
		}
	}
	~JTable()
	{
		jNode *p, *q;
		for (int i = 0; i < 15; i++)
		{
			p = head[i];
			while (p)
			{
				q = p;
				p = p->next;
				delete q;
			}
		}
	}
};
typedef struct {} empty;
typedef JTable<int, empty> intJtable;
#define NMax 1000000
int dat[NMax];
int main()
{
	int t1, N;
	scanf("%d", &N);
	intJtable J(-2100000000, 2100000000);
	for (int i = 0; i < N; i++)dat[i] = ((rand() << 14) | rand());
	srand(1325);
	t1 = clock();
	for (int i = 0; i < N; i++)J.jIns(dat[i]);
	printf("inserting time %d\n", clock() - t1);
	srand(1325);
	t1 = clock();
	for (int i = 0; i < N; i++)J.jFind(dat[i])->key;
	printf("finding time %d\n", clock() - t1);
	srand(1325);
	t1 = clock();
	for (int i = 0; i < N; i++)J.jDel(dat[i]);
	printf("deleting time %d\n", clock() - t1);
	system("pause");
	return 0;
}


