#include <iostream>
using namespace std;
const int MAXN = 20012, MAXE =1000010;
const int BIG = 999999999;
int n, m, l, s, t, c, cost, u;
int dis[MAXN];
bool v[MAXN];
int e_n[MAXE],e_t[MAXE], e_c[MAXE];
int e_u[MAXE],e_p[MAXE], e_x[MAXE];

void addedge(int s,int t, int c, int u, int k)
{
    l++;
    e_n[l] = e_n[s];
    e_n[s] = l;     //下一条边
    e_t[l] = t;     //边的另一端
    e_c[l] = c;     //边的费用
    e_u[l] = u;     //边的容量
    e_p[l] = l+k;   //对应的边
}

void build(int s,int t,int c,int u)
{
    addedge(s,t,c,u,1);     //正向边
    addedge(t,s,-c,0,-1);   //反向边
}

int aug(int no, int m)
{
    int i,d;

    if ( no==n )
    {
        cost += m*dis[1];
        return m;
    }
    v[no] = true;
    i = e_x[no];
    while (i!=0)
    {
       if ( (e_u[i]>0) && !v[e_t[i]] && (dis[e_t[i]]+e_c[i]==dis[no]))
       {
          d = aug(e_t[i],min(m,e_u[i]));
          if (d > 0)
          {
              e_u[i] -= d;
              e_u[e_p[i]] += d;
              e_x[no] = i;
              return d;
          }
       }
       i = e_n[i];
    }
    e_x[no] = i;
    return 0;
}

bool modlabel()
{
  int d,i,j;

  d = BIG;
  for (i=1; i<=n; i++)
    if (v[i])
    {
       j = e_n[i];
       while (j!=0)
       {
           if ( (e_u[j]>0) && !v[e_t[j]] && (e_c[j]-dis[i]+dis[e_t[j]]<d))
             d = e_c[j]-dis[i]+dis[e_t[j]];
           j = e_n[j];
       }
    }
    if (d == BIG)
        return false;
    for (i=1; i<=n; i++)
      if (v[i])
      {
          v[i] = false;
          dis[i] += d;
      }
    return true;
}
void init()
{
  int i;
  scanf("%d%d", &n, &m);
  l = n;
  for (i=1; i<=m; i++)
  {
     scanf("%d%d%d%d", &s,&t,&u,&c);
     build(s,t,c,u);
  }
}

int main()
{
    int i;
    freopen("costflow.in","r",stdin);
    freopen("costflow.out","w",stdout);
    init();
    do
    {
        for (i=1; i<=n; i++)
          e_x[i] = e_n[i];
        while (aug(1, BIG) > 0)
          memset(v, 0, sizeof(v));
    }while(modlabel());
    printf("%d\n", cost);
    return 0;
}
