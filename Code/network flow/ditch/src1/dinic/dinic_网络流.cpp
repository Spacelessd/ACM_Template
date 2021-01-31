#include<iostream>
using namespace std;
const long maxn=300;
const long maxm=300000;
const long inf=0x7fffffff;
struct node
{
    long v,next;
    long val;
}s[maxm*2];
long level[maxn],p[maxn],que[maxn],out[maxn],ind;
void init()
{
    ind=0;
    memset(p,-1,sizeof(p));
}
inline void insert(long x,long y,long z)
{
    s[ind].v=y;
    s[ind].val=z;
    s[ind].next=p[x];
    p[x]=ind++;
    s[ind].v=x;
    s[ind].val=0;
    s[ind].next=p[y];
    p[y]=ind++;
}
inline void insert2(long x,long y,long z)
{
    s[ind].v=y;
    s[ind].val=z;
    s[ind].next=p[x];
    p[x]=ind++;
    s[ind].v=x;
    s[ind].val=z;
    s[ind].next=p[y];
    p[y]=ind++;
}
long max_flow(long n,long source,long sink)
{
    long ret=0;
    long h=0,r=0;
    while(1)
    {
        long i;
        for(i=0;i<n;++i)
            level[i]=0;
        h=0,r=0;
        level[source]=1;
        que[0]=source;
        while(h<=r)
        {
            long t=que[h++];
            for(i=p[t];i!=-1;i=s[i].next)
            {
                if(s[i].val&&level[s[i].v]==0)
                {
                    level[s[i].v]=level[t]+1;
                    que[++r]=s[i].v;
                }
            }
        }
        if(level[sink]==0)break;
        for(i=0;i<n;++i)out[i]=p[i];
        long q=-1;
        while(1)
        {
            if(q<0)
            {
                long cur=out[source];
                for(;cur!=-1;cur=s[cur].next)
                {
                    if(s[cur].val&&out[s[cur].v]!=-1&&level[s[cur].v]==2)
                    {
                        break;
                    }
                }
                if(cur>=0)
                {
                    que[++q]=cur;
                    out[source]=s[cur].next;
                }
                else
                {
                    break;
                }
            }
            long u=s[que[q]].v;
            if(u==sink)
            {
                long dd=inf;
                long index=-1;
                for(i=0;i<=q;i++)
                {
                    if(dd>s[que[i]].val)
                    {
                        dd=s[que[i]].val;
                        index=i;
                    }
                }
                ret+=dd;
                //cout<<ret<<endl;
                for(i=0;i<=q;i++)
                {
                    s[que[i]].val-=dd;
                    s[que[i]^1].val+=dd;    
                }
                for(i=0;i<=q;i++)
                {
                    if(s[que[i]].val==0)
                    {
                        q=index-1;
                        break;
                    }
                }
            }
            else
            {
                long cur=out[u];
                for(;cur!=-1;cur=s[cur].next)
                {
                    if(s[cur].val&&out[s[cur].v]!=-1&&level[u]+1==level[s[cur].v])
                    {
                        break;
                    }
                }
                if(cur!=-1)
                {
                    que[++q]=cur;
                    out[u]=s[cur].next;
                }
                else
                {
                    out[u]=-1;
                    q--;
                }
            }
        }
    }
    return ret;
}

long m,n;

int main()
{

    while(scanf("%ld %ld",&m,&n)!=EOF)
    {
        init();
        for(int i=0;i<n;i++)
        {
            long from,to,cost;
            scanf("%ld %ld %ld",&from,&to,&cost);
            insert(--from,--to,cost);
        }
        long Start,End;
        scanf("%ld %ld",&Start,&End);
        printf("%ld\n",max_flow(n,--Start,--End));
    }
    return 0;
}