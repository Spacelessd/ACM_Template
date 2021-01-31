#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define FAIL -1
#define Init 0
#define N 2000005
#define M 105
#define ML 211111
#define AS 128
#define INF (int)((unsigned int)(-1)>>2)
#define _max(a,b) (a>b?a:b)
#define _min(a,b) (a<b?a:b)

long lrs[N] = {0};
long  bk[N] = {0};
long belong[N] = {0};
int cac[ML][M] = {0};
int  trans[AS][ML];
long m, n, ml0;
char p[N];

inline int LengthCommonSuffix(int p1, int p2)
{
	if (p2 == bk[p1]) return lrs[p1];
	while (bk[p1] != bk[p2])
		p2 = bk[p2];
	return _min(lrs[p1], lrs[p2]);
}
inline int LengthRepeatedSuffix(int p1, int s)
{
	if (s == Init) return 0;
	return LengthCommonSuffix(p1, s - 1) + 1;
}
void Oracle_on_line(char *p, int n)
{
	void Analy(int, int, int);
	int k, s, j, u;
	char c;
	for(j = 0; j < AS; j++)
		for(k = 0; k < ML; k++)
			trans[j][k] = FAIL;
	//memset(cac, 0, sizeof cac);
	//memset(lrs, 0, sizeof lrs);
	//memset( bk, 0, sizeof  bk);

	bk[Init] = FAIL;
	for (j = 0; j <  n; j++)
	{
		c = p[j];
		if(belong[j] == 0)
			trans[c][j] = j + 1;
		u = j;
		k = bk[j];
		//assert(k<ml0);
		while (k > FAIL && trans[c][k] == FAIL)
		{
			if(belong[j] == 0)
				trans[c][k] = j + 1;
			u = k;
			k = bk[k];
		}
		if (k == FAIL) s = Init;
		else s = trans[c][k];
		bk[j+1] = s;
		lrs[j+1] = LengthRepeatedSuffix(u, bk[j+1]);
		Analy(bk[j+1] - 1, j, lrs[j+1]);
	}
}
void Analy(int p1, int p2, int lr)
{
	if (lr == 0)return;
	if (belong[p2] == 0)return;
	//assert(p1!=-1);
	if (cac[p1][belong[p2]] == 0) cac[p1][0]++;
	cac[p1][belong[p2]] = _max(cac[p1][belong[p2]], lr);
}
void solve()
{
	int _max = 0;
	int _min = INF;
	int I = 0;
	for(int i = 0; i < ml0; i++)
		if(cac[i][0] == m - 1)
		{
			_min = INF;
			for(int j = 1; j < m; j++)
				_min = _min(_min, cac[i][j]);
			if(_max < _min)
			{
				_max = _min;
				I = i;
			}
		}
	printf("%d\n",_max);
	/*for(int k = I - _max + 1; k <= I; k++)
	{
		printf("%c", p[k]);
	}
	printf("\n");*/
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int i;
	m=0;//scanf("%d", &m);
	for(i = n = 0;; i++, n++)
	{
		if (scanf("%s", p + n)==EOF)break;
		++m;
		while(p[n])belong[n] = i, n++;
		if(i == 0)p[n] = 91; //'['
		else p[n] = 123 + (i & 0x3); //'{'
		belong[n] = i;
		if(i == 0)ml0 = n + 1;
	}
	p[n] = 0;
	Oracle_on_line(p, n);
	solve();
	system("pause");for (;;);
	return 0;
}


