#include<cstdio>
#include<cmath>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
using namespace std;
const char path[]="E:\\MyCode\\test\\leezy.txt";
const int inf=0x7fffffff;
const int maxn=105;
int r[maxn],p[maxn];
void init(int n)
{
    for(int i=1;i<=n;++i) r[i]=0,p[i]=i;
}
int find(int x)
{
    if(p[x]!=x) p[x]=find(p[x]);
    return p[x];
}
void lnk(int x,int y)
{
    if(r[x]<r[y]){
        p[x]=y;
    }else {
        p[y]=x;
        if(r[x]==r[y])++r[x];
    }
}
void join(int x,int y)
{
    lnk(find(x),find(y));
}

int g[maxn];
double w[maxn];
struct edge{
    int u,v;
    double w;
}e[maxn*maxn];
double boruvka(int n,int m)//顶点数,边数
{
    double ans=0,c=0;
    init(n);
    while(1){
        bool has=false;
        for(int i=1;i<=n;++i)g[i]=i,w[i]=1000000000.f;
        for(int k=0;k<m;++k){
            int u(find(e[k].u)),v(find(e[k].v));
            if(u==v)continue;
            double ww(e[k].w);
            if(w[u]>ww)w[u]=ww,g[u]=v;
            if(w[v]>ww)w[v]=ww,g[v]=u;
        }
        for(int i=1,u=-1;i<=n;++i){
            int v(find(g[u=find(i)]));
            if(u!=v){
               has=true;
               ans+=w[u];
               join(u,v);
                ++c;
            }
        }
        if(!has)break; //没有更多的边,退出
    }
    return ans;
}
double a[maxn][2];
double dis(double x1,double y1,double x2,double y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
int main()
{
    int n,m=0,t;
    while(scanf("%d",&n),n>0){
        if(m>0)putchar('\n');
        t=0;
        for(int i=0;i<n;++i)
        scanf("%lf%lf",&a[i][0],&a[i][1]);
        for(int i=0;i<n;++i)
        for(int j=0;j<i;++j){
            double d=dis(a[i][0],a[i][1],a[j][0],a[j][1]);
            e[t].u=i+1,e[t].v=j+1,e[t].w=d,++t;
        }
        printf("Case #%d:\nThe minimal distance is: %.2lf\n",++m,boruvka(n,t));

    }
    return 0;
}


