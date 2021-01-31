#include<stdio.h> 
#define RT return 
#define N 100005
#define null 2147483647 
inline int max(int x,int y){return x>y?x:y;}
inline void read(int &x){ 
    char ch; int bo=0; x=0;
    for (ch=getchar();!(ch>='0' && ch<='9');ch=getchar())if (ch=='-')bo=1; 
    for (;ch>='0' && ch<='9';x=x*10+ch-'0',ch=getchar()); 
    if (bo)x=-x; 
} 
  
int u[N],w[N],st[N],len[N],top[N],c[N],d[N],f[N],fa[N],heavy[N],f1[N];
int data[N*2],next[N*2],e[N*2],son[N],X[N],Y[N],n;
bool b[N]; 

struct node{ 
    int m,cover,add; 
};
class tree{ 
      public: 
      node *a; 
      int *e; 
      tree(){}
      void make(int len=10) 
      { 
            a=new node[(len+1)*4]; 
            e=new int[len+2];
      } 
      void build(int t,int l,int r) 
      { 
            a[t].cover=null; 
            if (l==r) {a[t].m=e[l];RT;} 
            int mid=(l+r)>>1; 
            build(t*2,l,mid); 
            build(t*2+1,mid+1,r); 
            a[t].m=max(a[t*2].m,a[t*2+1].m); 
      } 
      void down(int t) 
      {  
            if (a[t].cover<null){  
               a[t*2+1].cover=a[t*2+1].m=a[t*2].cover=a[t*2].m=a[t].cover; 
               a[t*2].add=a[t*2+1].add=0; 
               a[t].cover=null;  
               } 
            if (a[t].add){ 
               a[t*2].m+=a[t].add; a[t*2+1].m+=a[t].add; 
               if (a[t*2].cover<null) a[t*2].cover+=a[t].add; 
                  else a[t*2].add+=a[t].add; 
               if (a[t*2+1].cover<null) a[t*2+1].cover+=a[t].add; 
                  else a[t*2+1].add+=a[t].add; 
               a[t].add=0; 
               } 
      }  
        
      void change(int t,int l,int r,int y,int v)  
      {  
            if (l==r) {a[t].m=v; RT;} 
            int mid=(l+r)>>1; down(t); 
            if (y<=mid) change(t*2,l,mid,y,v); 
            else change(t*2+1,mid+1,r,y,v); 
            a[t].m=max(a[t*2].m,a[t*2+1].m); 
      } 
        
      void cover(int t,int l,int r,int ll,int rr,int v)  
      {  
            if (l==ll && r==rr){ 
               a[t].m=a[t].cover=v; a[t].add=0; RT; 
               } 
            int mid=(l+r)>>1; down(t);  
            if (rr<=mid) cover(t*2,l,mid,ll,rr,v);  
               else if (ll>mid) cover(t*2+1,mid+1,r,ll,rr,v); 
                    else cover(t*2,l,mid,ll,mid,v),cover(t*2+1,mid+1,r,mid+1,rr,v);  
            a[t].m=max(a[t*2].m,a[t*2+1].m); 
      }  
        
      void add(int t,int l,int r,int ll,int rr,int v)  
      {  
            if (l==ll && r==rr){  
               if (a[t].cover<null) a[t].cover+=v;  
               else a[t].add+=v; 
               a[t].m+=v; RT; 
               }  
            int mid=(l+r)>>1; down(t);  
            if (rr<=mid) add(t*2,l,mid,ll,rr,v);  
            else if (ll>mid) add(t*2+1,mid+1,r,ll,rr,v);  
              else add(t*2,l,mid,ll,mid,v),add(t*2+1,mid+1,r,mid+1,rr,v); 
            a[t].m=max(a[t*2].m,a[t*2+1].m);  
      }  
        
      int query(int t,int l,int r,int ll,int rr)  
      {  
            if (l==ll && r==rr) RT a[t].m;  
            int mid=(l+r)>>1; down(t);  
            if (rr<=mid) RT query(t*2,l,mid,ll,rr);  
            if (ll>mid) RT query(t*2+1,mid+1,r,ll,rr);
            RT max(query(t*2,l,mid,ll,mid),query(t*2+1,mid+1,r,mid+1,rr));  
      }
      
}; 
tree a[N]; 
  
void bfs(int s) 
{ 
    int h=0,t=1,i; 
    f[1]=s;c[s]=1; 
    while (h<t){ 
        i=f[++h]; 
        for (int p=son[i];p;p=next[p]){ 
            int j=e[p]; if (c[j]) continue; 
            c[j]=c[i]+1; d[j]=data[p]; f[++t]=j; fa[j]=i; 
            }
        }
    for (int k=n;k;k--){ 
        int i=f[k],M=0,q=0;f1[i]=1;
        for (int p=son[i];p;p=next[p]){ 
            int j=e[p]; 
            if (j!=fa[i]){
                          if (f1[j]+1>f[i]){
                                            f[i]=f1[j]+1;
                                            q=j;
                                            }
                          }
            } 
        heavy[i]=q; 
        } 
} 
  
inline int Lca(int x,int y)  
{  
    while (u[x]!=u[y])  
        if (c[top[x]]>c[top[y]])  
            if (x==top[x]) x=fa[x];  
            else x=top[x];  
        else
            if (y==top[y]) y=fa[y];  
            else y=top[y];  
    if (c[x]<c[y]) RT x; RT y;  
} 
  
inline void Change(int x,int y,int v)  
{  
    if (c[x]<c[y]) {int tmp=x;x=y;y=tmp;}  
    if (x==top[x]) d[x]=v; else a[u[x]].change(1,1,len[u[x]],w[x],v);  
}  
  
inline void Cover(int x,int y,int v)  
{  
    while (u[x]!=u[y]){  
        if (x==top[x]) d[x]=v,x=fa[x];  
        else a[u[x]].cover(1,1,len[u[x]],1,w[x],v),x=top[x]; 
        }  
    if (x!=y) a[u[x]].cover(1,1,len[u[x]],w[y]+1,w[x],v);  
}  
inline void Add(int x,int y,int v)  
{  
    while (u[x]!=u[y]){  
        if (x==top[x]) d[x]+=v,x=fa[x];  
        else a[u[x]].add(1,1,len[u[x]],1,w[x],v),x=top[x];  
        }  
    if (x!=y) a[u[x]].add(1,1,len[u[x]],w[y]+1,w[x],v);  
}  
inline int Max(int x,int y)  
{  
    int ans=0;  
    while (u[x]!=u[y]){  
        if (x==top[x]) ans=max(d[x],ans),x=fa[x];  
        else ans=max(ans,a[u[x]].query(1,1,len[u[x]],1,w[x])),x=top[x];  
        }  
    if (x!=y) ans=max(ans,a[u[x]].query(1,1,len[u[x]],w[y]+1,w[x]));  
    RT ans;  
}

int main() 
{ 
    //freopen("1.in","r",stdin); 
    //freopen("1.out","w",stdout); 
    read(n); int x,y,z,l=0,now=0; 
    for (int i=1;i<n;i++){ 
        read(x),read(y),read(z); X[i]=x,Y[i]=y; 
        e[++l]=y; data[l]=z; next[l]=son[x]; son[x]=l; 
        e[++l]=x; data[l]=z; next[l]=son[y]; son[y]=l; 
        }
    int tmp=n>>1; 
    if (tmp<1)tmp=1; 
    bfs(tmp); 
    for (int i1=1;i1<=n;i1++){
    int i=f[i1];
    if (!b[i]){
        len[++now]=-1; 
        for (int j=i;j;j=heavy[j])
            u[j]=now,w[j]=++len[now],top[j]=i,b[j]=1; 
        if (len[now]) { 
                      a[now].make(len[now]);
                      int tot=-1;
                      for (int j=i;j;j=heavy[j])++tot,a[now].e[tot]=d[j];  
                      a[now].build(1,1,len[now]); 
                      } 
        } 
    } 
      
    for(;;){ 
        char ch=getchar();ch=getchar(); int x,y,v; 
        if (ch=='t') { 
                     //for(;;); 
                     RT 0; 
                     } 
        read(x); read(y); if (ch=='o' || ch=='d') read(v); 
        if (ch=='h') Change(X[x],Y[x],y); 
        int z=Lca(x,y); 
        if (ch=='o') Cover(x,z,v),Cover(y,z,v); 
        if (ch=='d') Add(x,z,v),Add(y,z,v); 
        if (ch=='a') printf("%d\n",max(Max(x,z),Max(y,z))); 
        } 
    RT 0; 
} 

