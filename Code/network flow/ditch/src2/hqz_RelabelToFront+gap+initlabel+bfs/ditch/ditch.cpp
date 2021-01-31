/*
ID:hqztrue1
LANG:C++
TASK:ditch
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define oo (1<<30)
const int maxn=20010;
const int maxm=1000010;
int h[maxn],sumh[maxn*2],e[maxn],son[maxn],cur[maxn],a[maxn],prea[maxn],nexta[maxn];
int link[maxm],next[maxm],cap[maxm],opp[maxm];
int q[maxn];
int n,m,ll,S,T,l,r,s;
inline int min(int a,int b) {return a<b?a:b;}
void addedge(int x,int y,int z)
{
    link[++ll]=y;next[ll]=son[x];son[x]=ll;cap[ll]=z;opp[ll]=ll+1;
    link[++ll]=x;next[ll]=son[y];son[y]=ll;cap[ll]=0;opp[ll]=ll-1;
}

void build()
{
    int x,y,i;l=1,r=1;
    memset(h,7,sizeof(int)*(n+5));
    q[1]=T;h[T]=0;
    while (l<=r){
          x=q[l++];
          for (i=son[x];i!=-1;i=next[i]){
                y=link[i];
                if (cap[opp[i]]&&h[x]+1<h[y]){
                    h[y]=h[x]+1;q[++r]=y;
                    }
                }
          }
    h[S]=n;
    memset(sumh,0,sizeof(int)*(n+5));
    for (i=1;i<=n;i++)if (h[i]<n*2)sumh[h[i]]++;
}
void push(int x,int y){
    int tmp=min(e[x],cap[y]),ed=link[y];
    cap[y]-=tmp;cap[opp[y]]+=tmp;
    e[x]-=tmp;e[ed]+=tmp;
}
void preflow(){
    memset(h,7,sizeof(int)*(n+5));
    build();
    e[S]=oo;for (int i=son[S];i!=-1;i=next[i])push(S,i);e[S]-=oo;
}

void relabel(int x){
    int i,minh=oo,pl;
    for (i=son[x];i!=-1;i=next[i])
        if (cap[i]&&h[link[i]]<minh)minh=h[link[i]],pl=i;
    cur[x]=pl;
    sumh[h[x]]--;
    if (!sumh[h[x]]&&h[x]<=n-1){
        for (i=1;i<=n;i++)
            if (i!=S&&h[i]>h[x]&&h[i]<n+1){
                sumh[h[i]]--;
                h[i]=n+1;
                }
        h[x]=n+1;return;
        }
    h[x]=minh+1;
    sumh[h[x]]++;
}

void discharge(int x){
    while (e[x]){
    for (int p=cur[x];p!=-1;p=next[p])
        if (cap[p]&&h[x]==h[link[p]]+1){
            push(x,p);
            if (!e[x])break;
            }
    if (e[x])relabel(x);
    }
}
void init()
{
    int i,x,y,z;
    scanf("%d%d",&m,&n);
    memset(son,-1,sizeof(int)*(n+5));
    memset(e,0,sizeof(int)*(n+5));
    S=1;T=n;ll=0;h[S]=n;
    for (i=1;i<=m;i++)scanf("%d%d%d",&x,&y,&z),addedge(x,y,z);
    memcpy(cur,son,sizeof(int)*(n+5));
}
void relabel_to_front()
{
    int i,oldh,now,head,a1=0; a[0]=-1;
    for (i=r;i;i--)
      if ((q[i]!=S)&&(q[i]!=T))a[++a1]=q[i];
    memset(prea,-1,sizeof(int)*(n+5));
    memset(nexta,-1,sizeof(int)*(n+5));
    for (i=1;i<a1;i++)nexta[a[i]]=a[i+1];
    for (i=a1;i>1;i--)prea[a[i]]=a[i-1];
    now=head=a[1];
    while (now!=-1){
        if (h[now]>=n){
            prea[nexta[now]]=prea[now];
            nexta[prea[now]]=nexta[now];
            now=nexta[now];
            continue;
            }
        s++;if (s==1000000){
            s-=1000000;
            build();
            a1=0;a[0]=-1;
            for (i=r;i;i--)
                if ((q[i]!=S)&&(q[i]!=T))a[++a1]=q[i];
            memset(prea,-1,sizeof(int)*(n+5));
            memset(nexta,-1,sizeof(int)*(n+5));
            for (i=1;i<a1;i++)nexta[a[i]]=a[i+1];
            for (i=a1;i>1;i--)prea[a[i]]=a[i-1];
            now=head=a[1];
            }
        oldh=h[now];
        discharge(now);
        if (h[now]>oldh&&now!=head){
            prea[nexta[now]]=prea[now];
            nexta[prea[now]]=nexta[now];
            prea[head]=now;
            nexta[now]=head;
            head=now;
            }
        now=nexta[now];
        }
}
int main()
{
	freopen("ditch.in","r",stdin);
	freopen("ditch.out","w",stdout);
	init();
	preflow();
	relabel_to_front();
	printf("%d\n",e[T]);
	//system("pause");
    //for(;;);
	return 0;
}















