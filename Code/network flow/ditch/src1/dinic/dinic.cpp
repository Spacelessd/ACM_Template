#include<stdio.h>
#include<string.h>
#include<iostream>
 
using namespace std;
 
const int maxn=1100;
const int maxm=110000;
const int INF=2000000000;
 
int n,m;
int S,T;
 
int tot=0;
int d[maxn];
int first[maxn];
int next[maxm];
int opp[maxm];
int line[maxm];
int value[maxm];
int work[maxn];
 
int link(int x,int y,int p)
{
    tot++; line[tot]=y; value[tot]=p; opp[tot]=tot+1; next[tot]=first[x]; first[x]=tot;
    tot++; line[tot]=x; value[tot]=0; opp[tot]=tot-1; next[tot]=first[y]; first[y]=tot;
}
 
void init()
{
     scanf("%d%d",&m,&n);
 
     S=1,T=n;
 
     for (int i=1;i<=m;i++)
     {
         int x,y,p; scanf("%d%d%d",&x,&y,&p);
 
         link(x,y,p);
     }
}
 
bool build()
{
     int tq=0,q[maxn]; 
     memset(q,0,sizeof(q));
     memset(d,-1,sizeof(d));
 
     q[++tq]=S;
     d[S]=0;
 
     for (int i=1;i<=tq;i++)
     {
         int t=q[i];
 
         for (int num=first[t];num;num=next[num])
         {
             int nt=line[num];
 
             if (d[nt]==-1 && value[num]>0)
             {
                d[nt]=d[t]+1;
                q[++tq]=nt;
 
                if (nt==T) return true;
             }
         }
     }
 
     return false;
}
 
int find(int t,int v)
{
    if (t==T || v==0) return v;
 
    int ans=0;
 
    for (int &num=work[t];num;num=next[num])
    {
        int nt=line[num],flow;
 
        if (d[nt]==d[t]+1 && (flow=find(nt,min(v,value[num]))))
        {
           value[num]-=flow;
           value[opp[num]]+=flow;
           v-=flow;
           ans+=flow;
           if (v==0) break;
        }
    }
 
    return ans;
}
 
void doit()
{
     int ans=0;
 
     while (build())
     {
           memcpy(work,first,sizeof(work));
           ans+=find(S,INF);
     }
 
     printf("%d\n",ans);
}
 
int main()
{
    init();
    doit();
 
    return 0;
}