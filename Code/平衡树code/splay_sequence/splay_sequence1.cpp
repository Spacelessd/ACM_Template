#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define CH getchar()
#define max(a,b) ((a)<(b)?(b):(a))
inline void swap(int &x, int &y)
{
	int tmp = x;
	x = y;
	y = tmp;
}
inline void read(int &x)
{
	char ch;
	int bo = 0;
	x = 0;
	for (ch = getchar(); !(ch >= '0' && ch <= '9'); ch = getchar())if (ch == '-')bo = 1;
	for (; ch >= '0' && ch <= '9'; x = x * 10 + ch - '0', ch = getchar());
	if (bo)x = -x;
}

const int maxn = 500015;
struct node
{
	int l, r, p, sum, size, key, cover, rev, ml, mr, mm;
};
node a[maxn];
int stack[maxn], can[maxn], e[maxn];
int root = 0, stack1, can1;
const int null = 999999;

inline void update(int x)
{
	int L = a[x].l, R = a[x].r;
	a[x].size = a[L].size + a[R].size + 1;
	a[x].sum = a[L].sum + a[R].sum + a[x].key;
	a[x].ml = max(a[L].ml, a[L].sum + a[x].key + a[R].ml);
	a[x].mr = max(a[R].mr, a[R].sum + a[x].key + a[L].mr);
	a[x].mm = a[L].mr + a[x].key + a[R].ml;
	if (L) a[x].mm = max(a[x].mm, a[L].mm);
	if (R) a[x].mm = max(a[x].mm, a[R].mm);
}

void build(int l, int r)
{
	int mid = (l + r) / 2, tmp;
	a[e[mid]].cover = null;
	if (l < mid)
	{
		build(l, mid - 1);
		tmp = (l + mid - 1) >> 1;
		a[e[mid]].l = e[tmp];
		a[e[tmp]].p = e[mid];
	}
	if (r > mid)
	{
		build(mid + 1, r);
		tmp = (mid + 1 + r) >> 1;
		a[e[mid]].r = e[tmp];
		a[e[tmp]].p = e[mid];
	}
	update(e[mid]);
}

inline int paint(int x, int y)
{
	a[x].key = a[x].cover = y;
	a[x].sum = a[x].size * y;
	if (y > 0)a[x].ml = a[x].mr = a[x].mm = a[x].sum;
	else a[x].ml = a[x].mr = 0, a[x].mm = y;
}

inline void downnode(int x)
{
	int L = a[x].l, R = a[x].r, C = a[x].cover, rev = a[x].rev, tmp;
	if (C != null)
	{
		if (L)paint(L, C);
		if (R)paint(R, C);
		a[x].cover = null;
	}
	if (rev)
	{
		if (L)
		{
			a[L].rev ^= 1;
			swap(a[L].l, a[L].r);
			swap(a[L].ml, a[L].mr);
		}
		if (R)
		{
			a[R].rev ^= 1;
			swap(a[R].l, a[R].r);
			swap(a[R].ml, a[R].mr);
		}
		a[x].rev = 0;
	}
	update(x);
}

inline void down(int root, int x)
{
	stack1 = 0;
	for (; x != a[root].p; x = a[x].p)stack[++stack1] = x;
	for (; stack1; stack1--)downnode(stack[stack1]);
}

inline void zig(int x)
{
	int y = a[x].p, z = a[y].p;
	if (a[z].l == y) a[z].l = x;
	else a[z].r = x;
	a[x].p = z;
	a[y].p = x;
	a[y].l = a[x].r;
	a[x].r = y;
	a[a[y].l].p = y;
	update(y);
}

inline void zag(int x)
{
	int y = a[x].p, z = a[y].p;
	if (a[z].l == y) a[z].l = x;
	else a[z].r = x;
	a[x].p = z;
	a[y].p = x;
	a[y].r = a[x].l;
	a[x].l = y;
	a[a[y].r].p = y;
	update(y);
}

inline void splay(int &root, int x)
{
	int y, z, fa = a[root].p;
	if (x == 0) return;
	down(root, x);
	while (a[x].p != fa)
	{
		y = a[x].p;
		z = a[y].p;
		if (z == fa)
		{
			if (x == a[y].l)zig(x);
			else zag(x);
		}
		else if (y == a[z].l)
			if (x == a[y].l)
			{
				zig(y);
				zig(x);
			}
			else
			{
				zag(x);
				zig(x);
			}
		else if (x == a[y].r)
		{
			zag(y);
			zag(x);
		}
		else
		{
			zig(x);
			zag(x);
		}
	}
	update(x);
	root = x;
}

inline int getmin(int &root)
{
	int x = root;
	for(; a[x].l; x = a[x].l)downnode(x);
	splay(root, x);
	return x;
}

inline int getmax(int &root)
{
	int x = root;
	for(; a[x].r; x = a[x].r)downnode(x);
	splay(root, x);
	return x;
}

int findkth(int &root, int k)
{
	int x = root;
	while (k)
	{
		downnode(x);
		if (k == a[a[x].l].size + 1) break;
		if (k <= a[a[x].l].size) x = a[x].l;
		else
		{
			k -= a[a[x].l].size + 1;
			x = a[x].r;
		}
	}
	splay(root, x);
	return x;
}

inline int merge(int y, int x, int z)
{
	int L, R;
	if (x == 0)
	{
		if (y == 0)return z;
		if (z == 0)return y;
		R = getmax(y);
		a[z].p = R;
		a[R].r = z;
		update(R);
		return R;
	}
	L = getmin(x);
	a[y].p = L;
	a[L].l = y;
	update(L);
	R = getmax(x);
	a[z].p = R;
	a[R].r = z;
	update(R);
	return R;
}

inline void ins(int &root, int p, int x)
{
	int y, z;
	if (!p)
	{
		y = getmin(root);
		a[y].l = x;
		a[x].p = y;
		update(y);
		return;
	}
	y = findkth(root, p);
	z = a[y].r;
	a[z].p = a[y].r = 0;
	update(y);
	root = merge(y, x, z);
}

inline void del(int &root, int L, int R)
{
	can[++can1] = a[a[root].r].l;
	a[a[root].r].l = 0;
	update(a[root].r);
	update(root);
}

inline void modify(int &root, int L, int R, int C)
{
	int tmp = a[a[root].r].l;
	a[tmp].key = a[tmp].cover = C;
	a[tmp].sum = C * a[tmp].size;
	if (C) a[tmp].ml = a[tmp].mr = a[tmp].mm = a[tmp].sum;
	else a[tmp].ml = a[tmp].mr = 0, a[tmp].mm = C;
	downnode(tmp);
	update(a[root].r);
	update(root);
}


inline void turn(int &root, int L, int R)
{
	int tmp = a[a[root].r].l;
	a[tmp].rev ^= 1;
	swap(a[tmp].l, a[tmp].r);
	swap(a[tmp].ml, a[tmp].mr);
	update(a[root].r);
	update(root);
}

inline int sum(int &root, int L, int R)
{
	int y, z;
	return a[a[a[root].r].l].sum;
}

void print(int x)
{
	if (x == 0)return;
	down(x, x);
	print(a[x].l);
	printf("%d\n", a[x].key);
	print(a[x].r);
}

void test(int x)
{
	printf("start\n");
	print(x);
	printf("end\n");
	printf("\n");
}

int makenull(int x)
{
	a[x].l = a[x].r = a[x].p = a[x].sum = a[x].size = 0;
	a[x].ml = a[x].mr = 0;
	a[x].mm = -100000000;
	a[x].key = -100000;
	a[x].cover = null;
}

char ch, ch1, read_line[100];
int n, m, i, ans, x, y, tmp, v, l, r, L, R;

int main()
{
	const int lnode = 500001, rnode = 500002;
	makenull(0);
	makenull(lnode);
	makenull(rnode);
	a[lnode].size = a[rnode].size = 1;
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	read(n);
	read(m);
	can1 = 500000;
	for (i = 1; i <= 500000; i++)can[i] = 500000 - i + 1;
	for (i = 1; i <= n; i++)
	{
		e[i] = can[can1--];
		read(a[e[i]].key);
	}
	build(1, n);
	root = e[(1+n)>>1];
	getmax(root);
	a[root].r = rnode;
	a[rnode].p = root;
	update(root);
	getmin(root);
	a[root].l = lnode;
	a[lnode].p = root;
	update(root);
	while (m--)
	{
		ch = CH;
		ch = CH;
		ch = CH;
		ch1 = CH;
		ch1 = CH;
		if (ch == 'X')
		{
			gets(read_line);
			printf("%d\n", a[root].mm);
			continue;
		}
		read(x);
		x++;
		read(y);
		if (ch == 'S')
		{
			for (i = 1; i <= y; i++)
			{
				e[i] = can[can1--];
				if (a[e[i]].l)can[++can1] = a[e[i]].l;
				if (a[e[i]].r)can[++can1] = a[e[i]].r;
				read(a[e[i]].key);
				a[e[i]].l = a[e[i]].r = a[e[i]].p = a[e[i]].rev = 0;
				a[e[i]].cover = null;
			}
			build(1, y);
			tmp = (1 + y) >> 1;
			ins(root, x, e[tmp]);
			continue;
		}
		L = findkth(root, x - 1);
		R = findkth(a[root].r, x + y - a[a[root].l].size - 1);
		if (ch == 'L') del(root, L, R);
		if (ch == 'K')
		{
			read(v);
			modify(root, L, R, v);
		}
		if (ch == 'V')
		{
			turn(root, L, R);
		}
		if (ch == 'T')
		{
			if (!y)
			{
				printf("0\n");
				continue;
			}
			printf("%d\n", sum(root, L, R));
		}
	}
	//system("pause");for(;;);
	return 0;
}


