#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>

#define MAXN 30000

using namespace std;

struct dijk_p
{
		int dist, p;
};

bool operator< ( const dijk_p& p1, const dijk_p& p2 )
{
		return p1.dist > p2.dist;
}

vector< pair<int,int> > road[MAXN];
int v[ MAXN ];
priority_queue<dijk_p> que;

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int n, m, t, x, y, z;
	dijk_p tt;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++ )
	{
		int x, y, c;
		scanf("%d %d %d", &x, &y, &c);
				road[--x].push_back(make_pair(--y, c));
	}
	priority_queue< dijk_p > que;
	que.push( (dijk_p){ 0, 0 } );
	memset( v, 0xff, sizeof(v) );
	v[ 0 ] = 0;
	while ( !que.empty() )
	{
		x = que.top().p; y = que.top().dist; que.pop();
		if ( v[ x ] != y ) continue;
		for (int i = 0; i < road[ x ].size(); i++)
		{
			y = road[ x ][ i ].first;
			z = road[ x ][ i ].second;
			if ( v[ y ] == -1 || v[ y ] > v[ x ] + z )
			{
				v[ y ] = v[ x ] + z;
				que.push( (dijk_p){ v[ x ] + z, y } );
			}
		}
	}
	printf("%d\n",v[ n - 1 ] - v[ 0 ]);
	return 0;
}


