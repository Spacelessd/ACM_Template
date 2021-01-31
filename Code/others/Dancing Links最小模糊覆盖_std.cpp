#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//矩阵的行与列的大小
#define R 56
#define C 56
#define INF (1<<30)
//定义节点，十字链表结构
struct Node
{
	int r, c;
	struct Node *left;
	struct Node *right;
	struct Node *up;
	struct Node *down;
} all[R *C], head, row[R], col[C];
int tot, cnt[C];
bool G[R][R];
//初始化函数
void Init(int Rnum, int Cnum)
{
	tot = 0;
	memset(cnt, 0, sizeof(cnt));
	head.left = head.right = head.up = head.down = &head;
	head.r = Rnum, head.c = Cnum;
	int i;
	for (i = 0; i < Cnum; i++)
	{
		col[i].r = Rnum, col[i].c = i;
		col[i].up = col[i].down = &col[i];
		col[i].right = &head, col[i].left = head.left;
		col[i].left->right = col[i].right->left = &col[i];
	}
	for (i = 0; i < Rnum; i++)
	{
		row[i].r = i, row[i].c = Cnum;
		row[i].left = row[i].right = &row[i];
		row[i].down = &head, row[i].up = head.up;
		row[i].down->up = row[i].up->down = &row[i];
	}
}
//连接函数
void Link(int r, int c)
{
	struct Node *t = &all[tot++];
	cnt[c]++;
	t->r = r, t->c = c;
	t->right = &row[r], t->left = row[r].left;
	t->right->left = t->left->right = t;
	t->down = &col[c], t->up = col[c].up;
	t->down->up = t->up->down = t;
}
//建图函数
void Build(int n)
{
	int i, j;
	Init(n, n);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (G[i][j])
				Link(i, j);
	for (i = 0; i < n; i++)
	{
		row[i].right->left = row[i].left;
		row[i].left->right = row[i].right;
	}
}
//删除函数，注意与精确覆盖的操作不同
void Remove(struct Node* &idx)
{
	struct Node *p;
	for (p = idx->down; p != idx; p = p->down)
	{
		cnt[p->c]--;
		p->right->left = p->left;
		p->left->right = p->right;
	}
}
//恢复函数
void Resume(struct Node* &idx)
{
	struct Node *p;
	for (p = idx->up; p != idx; p = p->up)
	{
		cnt[p->c]++;
		p->right->left = p;
		p->left->right = p;
	}
}
//IDA* 的估计函数
int H(void)
{
	int ret = 0, flag;
	bool used[C];
	struct Node *p, *q, *t;
	memset(used, false, sizeof(used));
	for (p = head.right; p != &head; p = p->right)
		if (!used[p->c])
		{
			used[p->c] = true;
			ret++, flag = 0;
			for (q = p->down; q != p; q = q->down)
			{
				flag = 1;
				for (t = q->right; t != q; t = t->right)
					if (!used[t->c]) used[t->c] = true;
			}
			if (!flag)return INF;
		}
	return ret;
}
//搜索函数, G 为当前深度， lim 为深度上限， G>lim 时不可行
bool Dfs(int G, int lim)
{
	int h = H();
	if (h == INF || G + h > lim) return false;
	if (head.right == &head)
		return true;
	struct Node *p, *q;
	int minc = INF, idx;
	for (p = head.right; p != &head; p = p->right)
		if (cnt[p->c] < minc)
		{
			idx = p->c;
			minc = cnt[idx];
			if (minc <= 1)break;
		}
	if (minc == 0) return false;
	for (p = col[idx].down; p != &col[idx]; p = p->down)
	{
		Remove(p);
		for (q = p->right; q != p; q = q->right)
			Remove(q);
		if (Dfs(G + 1, lim)) return true;
		for (q = p->left; q != p; q = q->left)
			Resume(q);
		Resume(p);
	}
	return false;
}
//通过二分来实现迭代加深
int Solve(int n)
{
	int head = 0, tail = n, mid, ans = n;
	while (head <= tail)
	{
		mid = (head + tail) >> 1;
		Build(n);
		if (Dfs(0, mid))
		{
			ans = mid;
			tail = mid - 1;
		}
		else head = mid + 1;
	}
	return ans;
}
int main(void)
{
	int i, n, m, x, y;
	while (scanf("%d %d", &n, &m) == 2)
	{
		memset(G, false, sizeof(G));
		for(i = 0; i < n; i++)G[i][i] = true;
		for (i = 0; i < m; i++)
		{
			scanf("%d %d", &x, &y);
			x--;
			y--;
			G[x][y] = G[y][x] = true;
		}
		printf("%d\n", Solve(n));
	}
	return 0;
}


