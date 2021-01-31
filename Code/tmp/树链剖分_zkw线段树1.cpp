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
    
int u[N],w[N],st[N],len[N],top[N],c[N],d[N],f[N],fa[N],sum[N],heavy[N]; 
int data[N*2],next[N*2],e[N*2],son[N],X[N],Y[N],n; 
bool b[N];  
  
struct node{  
    int m,cover,add;  
}; 
struct tree{ 
    #define oo (1<<30) 
    node *a; int M,top; 
    static int stack[25]; 
    void down(int t){   
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
    void make(int len=10){ 
        for (M=1;M-2<len;M<<=1); 
        a=new node[M*2];//memset(a,0,sizeof(node)*M*2); 
    } 
    void build(){ 
        for (int i=M-1;i;--i)a[i].cover=null,a[i].add=0, 
            a[i].m=max(a[i*2].m,a[i*2+1].m); 
    } 
    void change(int x,int key){ 
        x+=M;int tmp; 
        for (top=0,tmp=x>>1;tmp;stack[++top]=tmp,tmp>>=1); 
        while (top--)down(stack[top]); 
        a[x].m=key; 
        for (x>>=1;x;x>>=1)a[x].m=max(a[x*2].m,a[x*2+1].m); 
    } 
    void cover(int l,int r,int key){ 
        l=l+M-1;r=r+M+1;int L,R,x; 
        for (top=0,L=l>>1;L;stack[++top]=L,L>>=1); 
        while (top--)down(stack[top]); 
        for (top=0,R=r>>1;R;stack[++top]=R,R>>=1); 
        while (top--)down(stack[top]); 
        for (L=l,R=r;L^R^1;L>>=1,R>>=1){ 
            if (~L&1){ 
                x=L^1;a[x].m=a[x].cover=key,a[x].add=0; 
            } 
            if (R&1){ 
                x=R^1;a[x].m=a[x].cover=key,a[x].add=0; 
            } 
        } 
        for (l>>=1;l;l>>=1)a[l].m=max(a[l*2].m,a[l*2+1].m); 
        for (r>>=1;r;r>>=1)a[r].m=max(a[r*2].m,a[r*2+1].m); 
    } 
    void add(int l,int r,int key){ 
        l=l+M-1;r=r+M+1;int L,R,x; 
        for (top=0,L=l>>1;L;stack[++top]=L,L>>=1); 
        while (top--)down(stack[top]); 
        for (top=0,R=r>>1;R;stack[++top]=R,R>>=1); 
        while (top--)down(stack[top]); 
        for (L=l,R=r;L^R^1;L>>=1,R>>=1){ 
            if (~L&1){ 
                x=L^1; 
                if (a[x].cover<null) a[x].cover+=key;   
                    else a[x].add+=key;  
                a[x].m+=key;  
            } 
            if (R&1){ 
                x=R^1; 
                if (a[x].cover<null) a[x].cover+=key;   
                    else a[x].add+=key;  
                a[x].m+=key;  
            } 
        } 
        for (l>>=1;l;l>>=1)a[l].m=max(a[l*2].m,a[l*2+1].m); 
        for (r>>=1;r;r>>=1)a[r].m=max(a[r*2].m,a[r*2+1].m); 
    } 
    int query(int l,int r){ 
        l=l+M-1;r=r+M+1;int ans=-oo,tmp; 
        for (top=0,tmp=l>>1;tmp;stack[++top]=tmp,tmp>>=1); 
        while (top--)down(stack[top]); 
        for (top=0,tmp=r>>1;tmp;stack[++top]=tmp,tmp>>=1); 
        while (top--)down(stack[top]); 
        for (;l^r^1;l>>=1,r>>=1){ 
            if (~l&1)ans=max(ans,a[l^1].m); 
            if (r&1)ans=max(ans,a[r^1].m); 
        } 
        return ans; 
    } 
};int tree::stack[25]; 
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
        int i=f[k],M=0,q=0; sum[i]=1;  
        for (int p=son[i];p;p=next[p]){  
            int j=e[p];  
            if (j!=fa[i]) sum[i]+=sum[j];  
            if (sum[j]>M) M=sum[j],q=j;  
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
    if (x==top[x]) d[x]=v; else a[u[x]].change(w[x],v);   
}   
    
inline void Cover(int x,int y,int v)   
{   
    while (u[x]!=u[y]){   
        if (x==top[x]) d[x]=v,x=fa[x];   
        else a[u[x]].cover(1,w[x],v),x=top[x];  
        }   
    if (x!=y) a[u[x]].cover(w[y]+1,w[x],v);   
}   
inline void Add(int x,int y,int v)   
{   
    while (u[x]!=u[y]){   
        if (x==top[x]) d[x]+=v,x=fa[x];   
        else a[u[x]].add(1,w[x],v),x=top[x];   
        }   
    if (x!=y) a[u[x]].add(w[y]+1,w[x],v);   
}   
inline int Max(int x,int y)   
{   
    int ans=0;   
    while (u[x]!=u[y]){   
        if (x==top[x]) ans=max(d[x],ans),x=fa[x];   
        else ans=max(ans,a[u[x]].query(1,w[x])),x=top[x];   
        }   
    if (x!=y) ans=max(ans,a[u[x]].query(w[y]+1,w[x]));   
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
                      for (int j=i;j;j=heavy[j])++tot,a[now].a[tot+a[now].M].m=d[j]; 
                      a[now].build(); 
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


