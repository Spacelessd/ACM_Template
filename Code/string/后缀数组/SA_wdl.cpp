#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int MaxN = 100005;
int N, rank[MaxN << 1], sa[MaxN << 1], tmp[MaxN << 1], cnt[MaxN << 1], height[MaxN << 1];
char s[MaxN << 1];

inline void	init()
{
	scanf("%s", s);
	N = strlen(s);
	for (int i = N; i; -- i) s[i] = s[i - 1];
	s[N + 1] = 1;
}

inline void	make_SA()
{
	for (int i = 0; i <= N; ++ i) cnt[i] = 0;
	for (int i = 1; i <= N; ++ i) cnt[s[i]] ++;
	for (int i = 1; i <= 256; ++ i) cnt[i] += cnt[i - 1];
	for (int i = N; i; -- i) sa[cnt[s[i]] --] = i;
	rank[sa[1]] = 1;
	for (int i = 2; i <= N; ++ i)
		rank[sa[i]] = rank[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
	
	for (int L = 1; L < N; L <<= 1)
	{
		for (int i = 0; i <= N; ++ i) cnt[i] = 0;
		for (int i = 1; i <= N; ++ i) cnt[rank[i + L]] ++;
		for (int i = 1; i <= N; ++ i) cnt[i] += cnt[i - 1];
		for (int i = N; i; -- i) tmp[cnt[rank[i + L]] --] = i;
		
		for (int i = 0; i <= N; ++ i) cnt[i] = 0;
		for (int i = 1; i <= N; ++ i) cnt[rank[tmp[i]]] ++;
		for (int i = 1; i <= N; ++ i) cnt[i] += cnt[i - 1];
		for (int i = N; i; -- i) sa[cnt[rank[tmp[i]]] --] = tmp[i];
		
		for (int i = 1; i <= N; ++ i) tmp[i] = rank[i];
		
		rank[sa[1]] = 1;
		for (int i = 2; i <= N; ++ i)
			rank[sa[i]] = rank[sa[i - 1]] + (tmp[sa[i]] != tmp[sa[i - 1]] || tmp[sa[i] + L] != tmp[sa[i - 1] + L]);
		
		if (rank[sa[N]] == N) break;
	}
	
	for (int i = 1, p = 0; i <= N; ++ i)
		if (rank[i] == 1) height[1] = 0; else
		{
			p = max(p - 1, 0);
			int j = sa[rank[i] - 1];
			while (s[i + p] == s[j + p]) p ++;
			height[rank[i]] = p;
		}
}

int main()
{
	init();
	make_SA();
}


