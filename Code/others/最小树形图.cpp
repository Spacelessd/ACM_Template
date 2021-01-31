#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int N = 510;
const int MAX = 1000;
int map[N][N], pre[N];
bool vis[N], flag[N];
int zhuliu(int n)
{
	int ans = 0;
	int t, i, j, k;
	memset(vis, false, sizeof(vis));
	memset(flag, false, sizeof(flag));
	pre[1] = 1; //1为根节点
	for(t = 0; t < n; t++)
	{
		for(i = 2; i <= n; i++)
		{
			if(flag[i]) continue;
			pre[i] = i;
			map[i][i] = MAX;
			for(j = 1; j <= n; j++)
			{
				if(i != j && !flag[j] && map[pre[i]][i] > map[j][i])
				{
					pre[i] = j;
				}
			}
		}
		for(i = 2; i <= n; i++)
		{
			j = i;
			if(flag[i]) continue;
			memset(vis, false, sizeof(vis));
			vis[1] = true;
			do vis[j] = true, j = pre[j];
			while(!vis[j]);
			if(j == 1) continue;
			i = j;
			ans += map[pre[i]][i];
			for(j = pre[i]; j != i; j = pre[j])
			{
				flag[j] = true;
				ans += map[pre[j]][j];
			}
			for(j = 1; j <= n; j++)
			{
				if(!flag[j] && map[j][i] < MAX)
				{
					map[j][i] -= map[pre[i]][i];
				}
			}
			for(k = 1; k <= n; k++)
				if(!flag[k])
				{
					for(j = pre[i]; j != i; j = pre[j])
					{
						if(map[j][k] < map[i][k]) map[i][k] = map[j][k];
						if(map[k][j] < MAX && map[k][j] - map[pre[j]][j] < map[k][i])
							map[k][i] = map[k][j] - map[pre[j]][j];
					}
				}
			break;
		}
		if(i == n + 1)
		{
			for(i = 2; i <= n; i++)
				if(!flag[i]) ans += map[pre[i]][i];
			break;
		}
	}
	return ans;
}
void dfs(int x, int n)
{
	vis[x] = true;
	for(int i = 2; i <= n; i++)
	{
		if(map[x][i] < MAX && !vis[i])
			dfs(i, n);
	}
}
int main()
{
	int n, m, x, y, d, i, j;
	while(scanf("%d%d", &n, &m) != EOF && (n || m))
	{
		memset(vis, false, sizeof(vis));
		for(i = 1; i <= n; i++)
			for(j = 1; j <= n; j++)
				map[i][j] = MAX;
		while(m--)
		{
			scanf("%d%d%d", &x, &y, &d);
			if(d < map[x][y])
				map[x][y] = d;
		}
		dfs(1, n);
		int temp = 0;
		for(int i = 2; i <= n; i++)
		{
			if(!vis[i])
			{
				printf("impossible\n");
				temp = 1;
				break;
			}
		}
		if(temp) continue;
		int ans = zhuliu(n);
		printf("%d\n", ans);
	}
}


