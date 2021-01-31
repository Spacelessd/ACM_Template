#define INF 100000000
#define MAXSIZE 3010
#define min(a, b) ((a)<(b)? (a): (b))
#include <stdio.h>
void INITIALIZE_PREFLOW();
long PUSH_RELABEL();
int RELABEL(long u);
void PUSH(long u, long v);
long N, M, s, t, ans,
     map[MAXSIZE][MAXSIZE], F[MAXSIZE][MAXSIZE], E[MAXSIZE], H[MAXSIZE]; 
int main()
{
    long i, a, b, c;
    freopen("ditch.in", "r", stdin);
    freopen("ditch.out", "w", stdout);
    scanf("%ld %ld", &N, &M);
    s=1, t=M;
    for(i=1; i<=N; ++i)
    {
             scanf("%ld %ld %ld", &a, &b, &c);
             map[a][b]+=c;
    }
    ans=PUSH_RELABEL();
    printf("%ld\n", ans);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
 
void INITIALIZE_PREFLOW()
{
     long i, j;
     for(i=1; i<=M; ++i)
              H[i]=E[i]=0;
     for(i=1; i<=M; ++i)
              for(j=1; j<=M; ++j)
                       F[i][j]=0;
     H[s]=M;
     for(i=1; i<=M; ++i)
     {
              if(map[s][i]!=0)
              {
                       F[s][i]=map[s][i];
                       F[i][s]=-map[s][i];
                       E[i]=map[s][i];
                       E[s]-=map[s][i];
              }
     }
}       
 
long PUSH_RELABEL()
{
    int flag=1; 
    long i;
    INITIALIZE_PREFLOW();
    while(flag)
    {
        flag=0;
        for(i=2; i<M; ++i)
            if(E[i]>0) 
               flag=RELABEL(i)||flag;
    }
    return E[t];
}
 
int RELABEL(long u)
{
    long minh=INF, i;
    for(i=1; i<=M; ++i)
             if(map[u][i]>F[u][i]) minh=min(minh, H[i]);
    if(minh==INF) return 0;
    H[u]=minh+1;
    for(i=1; i<=M; ++i)
    {
             if(E[u]==0) break;
             if(H[i]==minh && map[u][i]>F[u][i])
                           PUSH(u, i);
    }
    return 1;
}
 
void PUSH(long u, long v)
{
     long d;
     d=min(E[u], map[u][v]-F[u][v]);
     F[u][v]+=d;
     F[v][u]=-F[u][v];
     E[u]-=d;
     E[v]+=d;
}
