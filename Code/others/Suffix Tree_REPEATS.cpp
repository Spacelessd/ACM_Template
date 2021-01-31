#include<cstdio>
#include<cstring>
#define MAXN 51000
#define C(Now,i) c[Now][Str[i+d[Now]]]

int t, c[2*MAXN][3], d[2*MAXN], f[2*MAXN], Link[2*MAXN], Str[MAXN], Case, n, N, Ans, F[2*MAXN], bl[2*MAXN], Pos[2*MAXN],
	Fac[2*MAXN], Beg[2*MAXN], End[2*MAXN], Pre[2*MAXN], Suc[2*MAXN], _x[4*MAXN], _y[4*MAXN], _f[2*MAXN], _T, T;

char Chr;

void read(int &x)
{
	for(; (Chr = getchar()) < '0';);
	for(x = Chr - '0'; (Chr = getchar()) >= '0'; x = x * 10 + Chr - '0');
}

void readc(int &x)
{
	for(; (Chr = getchar()) < '0';);
	x = Chr - 'a';
}

void Cut(int &x, int Len, int i)
{
	if(!Len)return;
	d[++t] = d[x] + Len;
	f[t] = f[C(x, i)] - d[C(x, i)] + d[t];
	c[t][Str[f[t]]] = C(x, i);
	x = C(x, i) = t;
}

void Build_Suffix_Tree()
{
	int i, Now(1), Len(0), Far, j, k;
	Link[1] = 1;
	for(i = 0; i < n; i++, Now = Link[Far])
	{
		for(Len = 0; C(Now, i) && Str[f[C(Now, i)] - d[C(Now, i)] + d[Now] + Len] == Str[i+d[Now] + Len];)
			if(d[Now] + (++Len) == d[C(Now, i)])
			{
				Now = C(Now, i);
				Len = 0;
			}
		Cut(Far = Now, Len, i);
		f[C(Far, i)=++t] = n;
		d[Pos[i] = t] = n - i;
		for(k = Far, j = i + 1; !Link[k]; k = Link[k])
		{
			for(Link[k] = Link[Now]; C(Link[k], j) && d[C(Link[k], j)] + 1 <= d[k]; Link[k] = C(Link[k], j));
			Now = Link[k];
			Cut(Link[k], d[k] - d[Link[k]] - 1, j++);
		}
		Fac[i] = d[Far] ? d[Far] : 1;
	}
}

void String_Factorization()
{
	int i, j, k;
	T = 0;
	for(i = j = 0; i < N; i += Fac[j=i])
		for(k = (j - Fac[i] + 1) > 0 ? (j - Fac[i] + 1) : 0; k < i; k++)if(Str[k] == Str[i])
			{
				Beg[++T] = k;
				End[T] = i;
			}
}

void IN(int a, int b)
{
	_x[_T] = _f[Pos[a]];
	_y[_T] = Pos[b];
	_f[Pos[a]] = _T++;
}

int Find(int x)
{
	return F[x] == x ? x : F[x] = Find(F[x]);
}

void Tarjan(int *P, int l)
{
	bl[F[l] = l] = 1;
	int i;
	for(i = 0; i < 3; i++)
		if(c[l][i])
		{
			Tarjan(P, c[l][i]);
			F[c[l][i]] = l;
		}
	for(i = _f[l]; i; i = _x[i])
		if(bl[_y[i]])
			P[i>>1] = d[Find(_y[i])];
}

int main()
{
	int i, j;
	//freopen("REPEATS.in", "rb", stdin);
	//freopen("REPEATS.out", "wb", stdout);
	for(read(Case); Case--;)
	{
		read(N);
		for(i = 0; i < N; i++)readc(Str[i]);
		n = N + 1;
		Str[N] = 2;
		memset(c, 0, (t + 1)*sizeof c[0]);
		memset(bl, 0, (t + 1)*sizeof(int));
		memset(_f, 0, (t + 1)*sizeof(int));
		memset(Link, 0, (t + 1)*sizeof(int));
		t = 1;
		Build_Suffix_Tree();
		String_Factorization();
		_T = 2;
		for(i = 1; i <= T; i++)
		{
			IN(Beg[i], End[i]);
			IN(End[i], Beg[i]);
		}
		Tarjan(Pre, 1);
		for(i = 0; 2 * i < N; i++)
		{
			j = Str[i];
			Str[i] = Str[N-i-1];
			Str[N-i-1] = j;
		}
		n = N + 1;
		Str[N] = 2;
		memset(c, 0, (t + 1)*sizeof c[0]);
		memset(bl, 0, (t + 1)*sizeof(int));
		memset(_f, 0, (t + 1)*sizeof(int));
		memset(Link, 0, (t + 1)*sizeof(int));
		t = 1;
		Build_Suffix_Tree();
		_T = 2;
		for(i = 1; i <= T; i++)
		{
			IN(N - Beg[i] - 1, N - End[i] - 1);
			IN(N - End[i] - 1, N - Beg[i] - 1);
		}
		Tarjan(Suc, 1);
		Ans = 0;
		for(i = 1; i <= T; i++)
			if(Ans < (Pre[i] + Suc[i] - 1) / (End[i] - Beg[i]))
				Ans = (Pre[i] + Suc[i] - 1) / (End[i] - Beg[i]);
		printf("%d\n", Ans + 1);
	}
	return 0;
}


