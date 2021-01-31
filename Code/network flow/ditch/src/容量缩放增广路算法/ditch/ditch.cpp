#include <cstdio>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
#define INT_MAX (1<<30)
#define MAXN 20010
#define NIL INT_MAX

struct point { int u, have; bool operator <(const point it)const {return have < it.have; } };

int flow[MAXN][MAXN];
int have[MAXN];
int father[MAXN];
int mk[MAXN];

int min(int a, int b){ if(a > b)return b; else return a; }

int flow_dijk (int n, int u, int s)
{
       priority_queue<point> h;
       int maxflow, i, k=0;
       point pond;

       for(i=1; i<=n; i++)
       {
            mk[i] = 0;
            have[i] = 0;
            father[i] = -1;
       }

       pond.u = u; pond.have = NIL;
       h.push( pond );

       have[u]=NIL;
      
       while(k<n && !h.empty())
       {
            pond = h.top();
            h.pop();
            u = pond.u;
            maxflow = pond.have;
            if(mk[u])continue;
            k++;

            if(u == s)return have[s];

            mk[u] = 1;

            for(i=1; i<=n; i++)
            {
                     if(!mk[i] && have[i]<flow[u][i] && have[i]<maxflow )
                     {
                               have[i] = min (maxflow , flow[u][i]);
                               pond.u = i; pond.have = have[i];
                               h.push(pond);
                               father[i] = u;
                     }
            }
       }
       return 0;
}

int max_flow (int n, int u, int s)
{ 
       int maxflow = 0, ans, k;

       while ( ans = flow_dijk(n, u, s) )
       {
            maxflow += ans;

            k = s;
            while (father[k] != -1)
            {
                     flow[father[k]][k] -= ans;
                     flow[k][father[k]] += ans;

                     k = father[k];
            }
       }

       return maxflow;
}

int main()
{
       int n, m, i, j, a, b, c;
      freopen("ditch.in","r",stdin);
      freopen("ditch.out","w",stdout);
       while(scanf("%d%d", &m, &n)!=EOF)
       {
            for(i=1 ;i<=n; i++)
                     for(j=1; j<=n; j++)
                               flow[i][j] = 0;

            while ( m-- )
            {
                     scanf("%d %d %d", &a, &b, &c);

                     flow[a][b] += c;
            }

            printf ("%d\n", max_flow(n, 1, n));
       }

return 0;
}
