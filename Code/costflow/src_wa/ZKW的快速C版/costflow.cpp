#include <cstdio>
#include <cstring>
using namespace std;
const int maxint=~0U>>1;

int n,m,pi[550]={0},cost=0,c[550][550],u[550][550];
bool v[550]={0};

int aug(int no,int m)
{
        if(no==n)return cost+=pi[1]*m,m;
        v[no]=true;
        for(int i=1;i<=n;++i)if(!v[i] && u[no][i] && pi[i]+c[no][i]==pi[no])
                if(int d=aug(i,m<u[no][i]?m:u[no][i]))return u[no][i]-=d,u[i][no]+=d,d;
        return 0;
}

bool modlabel()
{
        int d=maxint,cc;
        for(int i=1;i<=n;++i)if(v[i])
                for(int j=1;j<=n;++j)if(!v[j] && u[i][j] && (cc=c[i][j]-pi[i]+pi[j])<d)d=cc;
        if(d==maxint)return false;
        for(int i=1;i<=n;++i)if(v[i])pi[i]+=d;
        return true;
}

int main()
{
        freopen("costflow.in","r",stdin);
        freopen("costflow.out","w",stdout);
        scanf("%d%d",&n,&m);
        memset(u,0,sizeof(u));
        while(m--)
        {
                int s,t,c0,u0;
                scanf("%d%d%d%d",&s,&t,&u0,&c0);
                c[s][t]=c0,c[t][s]=-c0,u[s][t]=u0,u[t][s]=0;
        }
        do do memset(v,0,sizeof(v));while(aug(1,maxint));while(modlabel());
        printf("%d\n",cost);
        return 0;
}
