#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long __int64;

const int P = 131, Q = 1000003;
inline int Q_abs (int a) { if (a < 0) a += Q; return a; }
const int rope_size = 4010;
const int allowed_rope = 110;
const int rope_cr = 510;
const int array_size = 8100;
int bitpwr[array_size];
struct rope_node { int length, next; };
rope_node rope[rope_cr];
char ori[rope_cr][array_size]; int hash[rope_cr][array_size];
int entrance, ropemr, mem_stack[rope_cr], mem_stack_top;
void database_init (void)
{
	ropemr = mem_stack_top = 0;
	entrance = -1, bitpwr[0] = 1;
	for (int i = 1; i < array_size; i++) bitpwr[i] = (bitpwr[i - 1] * P) % Q;
}
inline int alloc (void)
{
	int idx; if (mem_stack_top) idx = mem_stack[--mem_stack_top];
	else idx = ropemr++;
	rope[idx].next = -1; return idx;
}
inline int rope_count (void) { return ropemr - mem_stack_top; }
inline void collect (int x) { mem_stack[mem_stack_top++] = x; }
inline int make_rope (const char* str, int len)
{
	int sr = alloc(), lh = 0;
	rope[sr].length = len;
	for (int i = 0; i < len; i++)
	{
		ori[sr][i] = str[i];
		hash[sr][i] = ((lh * P) + str[i]) % Q;
		lh = hash[sr][i];
	} return sr;
}
pair<int, int> string_alloc (const char* str)
{
	int len = strlen(str);
	int last = -1, first;
	for (int p = 0; p < len; p += rope_size)
	{
		int lb = min(len, p + rope_size);
		int sr = make_rope(&str[p], lb - p);
		if (last == -1) last = first = sr;
		else rope[last].next = sr, last = sr;
	} return make_pair(first, last);
}
int split (int a, int place)
{
	int sr = make_rope(ori[a] + place, rope[a].length - place);
	rope[sr].next = rope[a].next;
	rope[a].next = sr, rope[a].length = place;
	return sr;
}
pair<int, int> select (int place)
{
	int now, forw;
	for (now = entrance, forw = -1; now != -1 && place >= rope[now].length;
		 place -= rope[now].length, forw = now, now = rope[now].next);
	if (now == -1 || place == 0) return make_pair(forw, now);
	else
	{
		int sr = split(now, place);
		return make_pair(now, sr);
	}
}
void merge (int a)
{
	int nxt = rope[a].next, base = rope[a].length, lh = hash[a][base - 1];
	for (int i = 0; i < rope[nxt].length; i++)
	{
		ori[a][base + i] = ori[nxt][i];
		hash[a][base + i] = ((lh * P) + ori[nxt][i]) % Q;
		lh = hash[a][base + i];
	}
	rope[a].length += rope[nxt].length;
	rope[a].next = rope[nxt].next;
	collect(nxt);
}
void add (int place, const char *str)
{
	pair<int, int> spl = select(place), res = string_alloc(str);
	if (spl.first == -1) entrance = res.first;
	else rope[spl.first].next = res.first;
	rope[res.second].next = spl.second;
}
void del (int a, int b)
{
	pair<int, int> splb = select(b), spla = select(a);
	if (spla.first == -1) entrance = splb.second;
	else rope[spla.first].next = splb.second;
	for (int i = spla.second; i != splb.second; i = rope[i].next) collect(i);
}
void chg (int a, int b, const char *str) { del(a, b), add(a, str); }
void maintain (void)
{
	for (int i = entrance; i != -1; i = rope[i].next)
		while (rope[i].length <= (rope_size >> 1) && rope[i].next != -1) merge(i);
}
inline int get_hash (int x, int remain, int len)
{
	int f = rope[x].length - remain - 1, l = f + len;
	int res = hash[x][l];
	if (f >= 0) res -= (__int64)hash[x][f] * bitpwr[len] % Q;
	return Q_abs(res);
}
inline int query (int a, int b)
{
	int na, nb, la, lb, res = 0;
	for (na = entrance; na != -1 && a >= rope[na].length; a -= rope[na].length, na = rope[na].next);
	la = rope[na].length - a;
	for (nb = entrance; nb != -1 && b >= rope[nb].length; b -= rope[nb].length, nb = rope[nb].next);
	lb = rope[nb].length - b;
	while (na != -1 && nb != -1)
	{
		int tl = min(la, lb);
		int tha = get_hash(na, la, tl), thb = get_hash(nb, lb, tl);
		if (tha == thb)
		{
			la -= tl, lb -= tl, res += tl;
			if (la == 0) { na = rope[na].next; if (na != -1) la = rope[na].length; }
			if (lb == 0) { nb = rope[nb].next; if (nb != -1) lb = rope[nb].length; }
		}
		else
		{
			int st = 0, ed = tl;
			while (ed - st > 1)
			{
				int mid = (st + ed) >> 1;
				tha = get_hash(na, la, mid), thb = get_hash(nb, lb, mid);
				if (tha == thb) st = mid;
				else ed = mid;
			}
			return res + st;
		}
	} return res;
}
char opt[100010];
int main ()
{
	int n, q, x, y; char ar[12];
	database_init();
	scanf("%d %d", &n, &q);
	scanf("%s", opt);
	entrance = string_alloc(opt).first;
	for (; q; --q)
	{
		scanf("%s", ar);
		if (ar[0] == 'L')
		{
			scanf("%d %d", &x, &y);
			printf("%d\n", query(x - 1, y - 1));
		}
		else if (ar[0] == 'A')
		{
			scanf("%d %s", &x, opt);
			add(x - 1, opt);
		}
		else if (ar[0] == 'C')
		{
			scanf("%d %d %s", &x, &y, opt);
			chg(x - 1, y, opt);
		}
		else if (ar[0] == 'D')
		{
			scanf("%d %d", &x, &y);
			del(x - 1, y);
		}
		if (rope_count() > allowed_rope) maintain();
	}
	system("pause");for (;;);
	return 0;
}


