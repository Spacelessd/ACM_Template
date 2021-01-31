#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int NV=105;
const int LNV=11;//log2 of NV
const int NE=5015;
const int NQ=1000005;
const int intmax=0x7fffffff;
int f[2005];
int p[2005];
int n,m;
struct Edge
{
    int ne,y,v;
};
struct Edge2
{
    int x,y,v;
};
bool cmp(Edge2 a,Edge2 b)
{
    return a.v<b.v;
}
struct DisSet
{
    int fa[NV],nv;
    void init(int n)
    {
        nv=n;
        for(int i=0;i<n;i++) fa[i]=i;
    }
    int find(int x)
    {
        if (fa[x]==x) return x;
        return fa[x]=find(fa[x]);
    }
    void uni(int x,int y)
    {
        fa[find(x)]=find(y);
    }
};

struct Graph
{
    Edge e[NE];
    int ep,h[NV],nv,ne;
    void init(int n,int m=NE)
    {
        ne=m;
        nv=n;
        ep=2;
        memset(h,0,4*nv);
    }
    void add(int a,int b,int v=1)
    {
        e[ep].ne=h[a];
        e[ep].y=b;
        e[ep].v=v;
        h[a]=ep;
        ep++;
    }
///scc-tarjan
//    int ti,scc[NV],dfn[NV],sp,st[NV],low[NV],nscc;
//    bool vis[NV];
//    void tarjan_dfs(int n)
//    {
//        dfn[n]=low[n]=++ti;
//        st[sp++]=n;
//        vis[n]=1;
//        for(int i=h[n];i;i=e[i].ne)
//        {
//            if (!dfn[e[i].y])
//            {
//                tarjan_dfs(e[i].y);
//                low[n]=min(low[n],low[e[i].y]);
//            }
//            else if (vis[e[i].y]) low[n]=min(low[n],dfn[e[i].y]);
//        }
//        if (low[n]==dfn[n])
//        {
//            nscc++;
//            int v;
//            do
//            {
//                v=st[--sp];
//                vis[v]=0;
//                scc[v]=nscc;
//            }while(v!=n);
//        }
//    }
//    void tarjan()
//    {
//        ti=0;nscc=0;sp=0;
//        memset(dfn,0,sizeof(dfn));
//        memset(vis,0,sizeof(vis));
//        for(int i=0;i<nv;i++) if(!dfn[i])tarjan_dfs(i);
//    }

///scc-gabow
//    int dfn[NV],st1[NV],st2[NV],sp1,sp2,scc[NV],nscc,ti;
//    void gabow_dfs(int n)
//    {
//        dfn[n]=++ti;
//        st2[sp2++]=st1[sp1++]=n;
//        for(int i=h[n];i;i=e[i].ne)
//        {
//            if (!dfn[e[i].y]) gabow_dfs(e[i].y);
//            else if (!scc[e[i].y]) while(dfn[st2[sp2-1]]>dfn[e[i].y])sp2--;
//        }
//        if (st2[sp2-1]!=n) return;
//        sp2--;nscc++;
//        do{scc[st1[--sp1]]=nscc;} while(st1[sp1]!=n);
//    }
//    void gabow()
//    {
//        memset(dfn,0,sizeof(dfn));
//        memset(scc,0,sizeof(scc));
//        nscc=ti=sp1=sp2=0;
//        for(int i=0;i<nv;i++) if (!dfn[i]) gabow_dfs(i);
//    }

///bcc-tarjan
//    int low[NV],dfn[NV],ti;
//    int st[NE],bcc[NE];
//        //bcc is the number of bcc which egdes belong to
//        //2-vertex connected component
//    int sp,nbcc;
//    int root,croot;
//    int cut[NV];//the number of connected component after delete the node
//    int hbri[NV],brip;
//    Edge bri[NE];
//    void addbri(int a,int b,int v=1)
//    {
//        bri[brip].ne=hbri[a];
//        bri[brip].y=b;
//        bri[brip].v=v;
//        hbri[a]=brip;
//        brip++;
//    }
//    void barjan_dfs(int now,int from)
//    {
//        low[now]=dfn[now]=++ti;
//        for(int i=h[now];i;i=e[i].ne)
//        {
//            if (!dfn[e[i].y])
//            {
//                st[sp++]=i;
//                barjan_dfs(e[i].y,i);
//                if (now==root) croot++;
//                low[now]=min(low[now],low[e[i].y]);
//                if (now==root&&croot>1) cut[now]=croot-1;
//                if (now!=root&&low[e[i].y]>=dfn[now]) cut[now]++;
//                if (low[e[i].y]>=dfn[now]||now==root)
//                {
//                    nbcc++;
//                    do
//                    {
//                        bcc[st[sp-1]]=bcc[st[sp-1]^1]=nbcc;
//                        sp--;
//                    }while(st[sp]!=i);
//                }
//                if (low[e[i].y]==dfn[e[i].y])
//                {
//                    //printf("%d %d\n",now,e[i].y);
//                    addbri(now,e[i].y);
//                    //addbri(e[i].y,now);
//                }
//            }
//            else if (i!=(from^1))
//            {
//                low[now]=min(low[now],dfn[e[i].y]);
//                if (dfn[now]>dfn[e[i].y])st[sp++]=i;
//            }
//        }
//    }
//    void barjan()
//    {
//        memset(dfn,0,4*nv);
//        memset(cut,0,4*nv);
//        memset(hbri,0,4*nv);
//        ti=0;
//        brip=2;
//        nbcc=0;
//        for(int i=0;i<nv;i++)
//        {
//            if (!dfn[i])
//            {
//                croot=0;//the degree of root;
//                root=i;
//                barjan_dfs(i,-1);
//            }
//        }
//    }
//    void barjan_show()
//    {
//        for(int i=0;i<nv;i++) printf("%d ",cut[i]);puts("");
//        for(int i=0;i<nv;i++)
//        for(int j=hbri[i];j;j=bri[j].ne)
//            printf("%d %d\n",i,bri[j].y);
//        for(int i=0;i<nv;i++)
//        for(int j=h[i];j;j=e[j].ne)
//        {
//            printf("%d %d %d\n",i,e[j].y,bcc[j]);
//        }
//    }

///off-lca O(N)-O(1)
//    bool vis[NV];
//    int askh[NV],askp,lca[NQ];
//    Edge ask[NQ];
//    DisSet dset;
//    void offlca_dfs(int n)
//    {
//        vis[n]=1;
//        for(int i=h[n];i;i=e[i].ne)
//        {
//            if (!vis[e[i].y])
//            {
//                offlca_dfs(e[i].y);
//                dset.uni(e[i].y,n);
//            }
//        }
//        for(int i=askh[n];i;i=ask[i].ne)
//            if (vis[ask[i].y]) lca[ask[i].v]=dset.find(ask[i].y);
//    }
//    void offlca_addq(int a, int b,int no)
//    {
//        ask[askp].y=b;
//        ask[askp].ne=askh[a];
//        ask[askp].v=no;
//        askh[a]=askp;
//        askp++;
//    }
//    void offlca_init()
//    {
//        askp=2;
//        dset.init(nv);
//        memset(vis,0,nv);
//        memset(askh,0,4*nv);
//    }
//    void offlca(int root)
//    {
//        offlca_dfs(root);
//    }

///on-lca O(nlogn)-O(logn)
//    int d[NV],anc[NV][LNV],lnv;
//    void onlca_init(int root,int Lnv=LNV)
//    {
//        memset(anc,-1,4*LNV*nv);
//        lnv=Lnv;
//        onlca_dfs(root,-1);
//    }
//    void onlca_dfs(int now,int fa)
//    {
//        fa==-1?d[now]=0:d[now]=d[fa]+1;anc[now][0]=fa;
//        for(int j=1,i=2;i<=d[now];j++,i<<=1) anc[now][j]=anc[anc[now][j-1]][j-1];
//        for(int i=h[now];i;i=e[i].ne) onlca_dfs(e[i].y,now);
//    }
//    int onlca(int x,int y)
//    {
//        if (d[x]<d[y]) swap(x,y);
//        int dis=d[x]-d[y];
//        for(int i=0;dis;dis>>=1,i++) if (dis&1) x=anc[x][i];
//        if (x==y) return x;
//        for(int i=lnv-1;i>=0;i--)
//            if (anc[x][i]!=anc[y][i]) x=anc[x][i],y=anc[y][i];
//        return anc[x][0];
//    }
//    void onlca_show()
//    {
//        for(int i=0;i<nv;i++,puts(""))
//        for(int j=0;j<lnv;j++) printf("%d ",anc[i][j]);
//    }

///MST-kruskal
//    Edge tre[2*NV];
//    Edge2 e2[NE];
//    int trep,e2p;
//    int htre[NV];
//    DisSet dset;
//    void addtre(int a,int b,int v=1)
//    {
//        tre[trep].ne=htre[a];
//        tre[trep].y=b;
//        tre[trep].v=v;
//        htre[a]=trep;
//        trep++;
//    }
//    void kruskal_init()
//    {
//        dset.init(nv);
//        memset(htre,0,4*nv);
//        e2p=0;
//        trep=2;
//        for(int i=0;i<nv;i++)
//            for(int j=h[i];j;j=e[j].ne)
//            {
//                e2[e2p].x=i;
//                e2[e2p].y=e[j].y;
//                e2[e2p].v=e[j].v;
//                e2p++;
//            }
//    }
//    int kruskal()
//    {
//        kruskal_init();
//        int sum=0;
//        sort(e2,e2+e2p,cmp);
//        for(int i=0;i<e2p;i++)
//        {
//            int x=dset.find(e2[i].x);
//            int y=dset.find(e2[i].y);
//            if (x!=y)
//            {
//                addtre(e2[i].x,e2[i].y,e2[i].v);
//                addtre(e2[i].y,e2[i].x,e2[i].v);
//                dset.uni(x,y);
//                sum+=e2[i].v;
//            }
//        }
//        return sum;
//    }

///MST-prim
//    Edge tre[2*NV];
//    int trep;
//    int htre[NV];
//    int dis[NV];
//    priority_queue<int, vector<int>, greater<int> > q;
//    void addtre(int a,int b,int v=1)
//    {
//        tre[trep].ne=htre[a];
//        tre[trep].y=b;
//        tre[trep].v=v;
//        htre[a]=trep;
//        trep++;
//    }
//    void prim_init()
//    {
//        memset(htre,0,4*nv);
//        trep=2;
//        memset(dis,0x3f,4*nv);
//    }
//    int prim()
//    {
//        prim.init();
//        dis[0]=0;
//        for(int i=0;i<nv-1;i++)
//        {
//
//        }
//    }

///DirectedMST-chuliu
//    Edge tre[2*NV];
//    Edge2 e2[NE];
//    int trep,e2p;
//    int htre[NV];
//    int pre[NV],id[NV],vis[NV];
//    int in[NV];
//    void addtre(int a,int b,int v=1)
//    {
//        tre[trep].ne=htre[a];
//        tre[trep].y=b;
//        tre[trep].v=v;
//        htre[a]=trep;
//        trep++;
//    }
//    void chuliu_init()
//    {
//        memset(htre,0,4*nv);
//        e2p=0;
//        trep=2;
//        for(int i=0;i<nv;i++)
//            for(int j=h[i];j;j=e[j].ne)
//            {
//                e2[e2p].x=i;
//                e2[e2p].y=e[j].y;
//                e2[e2p].v=e[j].v;
//                e2p++;
//            }
//    }
//    int chuliu(int root=0)
//    {
//        chuliu_init();
//        int ans=0,n=nv;
//        while(1)
//        {
//            memset(in,0x3f,4*n);
//            for(int i=0;i<e2p;i++)
//            {
//                if (e2[i].v<in[e2[i].y]&&e2[i].x!=e2[i].y)
//                {
//                    pre[e2[i].y]=e2[i].x;
//                    in[e2[i].y]=e2[i].v;
//                }
//            }
//            for(int i=0;i<n;i++)
//            {
//               if (i==root) continue;
//               if (in[i]==0x3f3f3f3f) return -1;
//            }
//            in[root]=0;
//            int cnt=0;
//            memset(id,-1,4*nv);
//            memset(vis,-1,4*nv);
//            for(int i=0;i<n;i++)
//            {
//                ans+=in[i];
//                int v=i;
//                while(vis[v]!=i&&id[v]==-1&&v!=root)
//                {
//                    vis[v]=i;
//                    v=pre[v];
//                }
//                if (v!=root&&id[v]==-1)
//                {
//                    for(int u=pre[v];u!=v;u=pre[u]) id[u]=cnt;
//                    id[v]=cnt++;
//                }
//            }
//            if (cnt==0) break;
//            for(int i=0;i<n;i++)
//                if (id[i]==-1) id[i]=cnt++;
//            for(int i=0;i<e2p;i++)
//            {
//                int v=e2[i].y;
//                e2[i].x=id[e2[i].x];
//                e2[i].y=id[e2[i].y];
//                if (e2[i].x!=e2[i].y) e2[i].v-=in[v];
//            }
//            n=cnt;
//            root=id[root];
//        }
//        return ans;
//    }

///Shortest_path SPFA
//    int d[NV];
//    int qu[NV],p,q;
//    bool vis[NV];
//    void spfa(int src)
//    {
//        memset(d,0x3f,4*nv);
//        memset(vis,0,nv);
//        d[src]=0;
//        qu[0]=src;
//        p=0;q=1;
//        while(p<q)
//        {
//            int now=qu[p%NV];
//            vis[now]=0;
//            for(int i=h[i];i;i=e[i].ne)
//            {
//                if (d[now]+e[i].v<d[e[i].y])
//                {
//                    d[e[i].y]=d[now]+e[i].v;
//                    if (!vis[e[i].y])
//                    {
//                        vis[e[i].y]=1;
//                        qu[q%NV]=e[i].y;
//                        q++;
//                    }
//                }
//            }
//            p++;
//        }
//    }

///Shortest_path Dijkstra
//    int d[NV];
//    typedef pair<int,int> pii;
//    priority_queue< pii,vector<pii>,greater<pii> > q;
//    void dijkstra(int src)
//    {
//        memset(d,0x3f,4*nv);
//        d[src]=0;
//        while(!q.empty()) q.pop();
//        q.push(make_pair(d[src],src));
//        while(!q.empty())
//        {
//            pii u=q.top();q.pop();
//            int x=u.second;
//            if (d[x]!=u.first) continue;
//            for(int i=h[x];i;i=e[i].ne)
//            if (d[e[i].y]>d[x]+e[i].v)
//            {
//                d[e[i].y]=d[x]+e[i].v;
//                q.push(make_pair(d[e[i].y],e[i].y));
//            }
//        }
//    }

///Shortest_path Floyd
//    int d[NV][NV];
//    void floyd()
//    {
//        for(int i=0;i<nv;i++)
//        for(int j=0;j<nv;j++)
//            d[i][j]=0x3f3f3f3f;
//        for(int i=0;i<nv;i++)
//            for(int j=h[i];j;j=e[j].ne)
//                d[i][e[i].y]=e[i].v;
//        for(int i=0;i<nv;i++) d[i][i]=0;//pay attention to this!
//        for(int k=0;k<nv;k++)
//            for(int i=0;i<nv;i++)
//                for(int j=0;j<nv;j++)
//                    d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
//    }
///NetWork_Flow EK_Sap

    bool dfs(int now,int d,int t)
    {
        //printf("%d %d %d\n",now,d,t);
        if (t==m+1&&d) return 1;
        int ans=intmax;
        for(int i=h[now];i;i=e[i].ne)
        {
            if (!e[i].v)
            {
                if(!d) if (e[i].y<f[t]) continue;
                e[i].v=1;
                e[i^1].v=1;
                if (dfs(e[i].y,(e[i].y>f[t])|d,t+1))
                {
                    ans=min(ans,e[i].y);
                }
                e[i].v=0;
                e[i^1].v=0;
            }
        }

        if (ans==intmax) return 0;
        p[t]=ans;
        return 1;
    }
};
Graph g;
int main()
{
    scanf("%d%d",&n,&m);
    g.init(n,m);
    int la;
    scanf("%d",&la);
    f[0]=la;
    for(int i=1;i<=m;i++)
    {
        int a;
        scanf("%d",&a);
        g.add(la,a,0);
        g.add(a,la,0);
        la=a;
        f[i]=a;
    }
    if (g.dfs(f[0],0,1))
    {
        printf("%d",f[0]);
        for(int i=1;i<=n;i++) printf(" %d",p[i]);
        puts("");
    }
    else puts("No solution");
}


