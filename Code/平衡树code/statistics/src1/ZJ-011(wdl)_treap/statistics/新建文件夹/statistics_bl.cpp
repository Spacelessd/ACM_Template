#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;


typedef long long LL;
const LL P = 1000000007;
int N;
LL	f[200005], ans, A, B, C;

int main()
{
	freopen("statistics.in", "r", stdin);
	freopen("statistics_bl.out", "w", stdout);
	cin >> A >> B >> C >> N;
	f[1] = 1; ans = 1;
	for (int i = 2; i <= N; ++ i)
	{
		sort(f + 1, f + i);
		f[i] = (A * f[i / 2] + B * i + C) % P;
		ans += f[i];
	}
	cout << ans << endl;
	return 0;
}
		
