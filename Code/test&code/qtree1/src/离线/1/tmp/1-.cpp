#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define maxn 10010
#define oo (1<<30)
struct node{
       int min,max,sum,cover,add;
       };
struct opt{
       char ch;
       int x,y,z;
       };
struct Edge{
	int link[maxn*2],next[maxn*2],node[maxn*2],son[maxn],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y,int z){
		link[++l]=y;node[l]=z;next[l]=son[x];son[x]=l;
		}
};
Edge e,enew;
opt opt[maxn];
int n,q,root;
int a[maxn],alca[maxn],w[maxn],f[maxn],deep[maxn],p[maxn],fnew[maxn],fnode[maxn],other[maxn],is[maxn],tmpa[maxn];
node node[maxn*2];
void Bfs(int root){
     int h=1,t=1,x,i,j;a[1]=root;f[root]=0;deep[root]=0;
     while (h<=t){
           x=a[h++];
           for (i=e.son[x];i;i=e.next[i]){
               j=e.link[i];
               if (j!=f[x]){a[++t]=j;deep[j]=deep[x]+1;f[j]=x;}
           }
     }
}
void Buildlca(int now,int next){
     int i,j,h=1,t=0,Max,top=n,dep,a1,Root,sum;
     for (i=now;i<next;i++){
         if (opt[i].ch=='A')p[opt[i].x]=1;
         if (opt[i].ch=='B'){p[opt[i].x]=1;p[opt[i].y]=1;}
     }
     enew.clear();
     for (i=n;i;i--)if (p[a[i]])alca[++t]=a[i],is[a[i]]=1;
     while (h<t){
           dep=deep[alca[h]];
           for (i=h;i<=t&&deep[alca[i]]==dep;i++)alca[i]=f[alca[i]];
           a1=0;j=i;
           for (i=h;i<j;i++){
               if (!is[alca[i]]){tmpa[++a1]=alca[i];}
               is[alca[i]]++;
               }
           for (j=1;j<=a1;j++)alca[i-j]=tmpa[j];
           h=i-a1;
           }
     Root=alca[h];
     for (i=n;i;i--)if (is[a[i]]>1){
         node[a[i]].max=w[a[i]];
         if (a[i]==Root)continue;
         Max=-oo;j=f[a[i]];
         while (!(is[j]>1)){Max=max(Max,w[j]);j=f[j];}
         ++top;node[top].max=Max;
         fnew[a[i]]=j;fnode[a[i]]=top;
     }
     fnew[Root]=0;fnode[Root]=0;
     sum=0;
     for (i=1;i<=n;i++)sum+=is[i];printf("%d\n",sum);
     memset(p,0,sizeof(int)*(n+5));
     memset(is,0,sizeof(int)*(n+5));
}
void Rebuild(){
     
}
int Qlca(int x,int y){
    int tmp=x,lca;
    while (tmp){p[tmp]=1;tmp=fnew[tmp];}
    tmp=y;
    while (!p[tmp]){tmp=fnew[tmp];}
    lca=tmp;tmp=x;
    while (tmp){p[tmp]=0;tmp=fnew[tmp];}
    return lca;
}
void Change(int x,int key){
     node[x].max=key;w[x]=key;
}
int Qmax(int x,int y){
    int tmp,lca=Qlca(x,y),Max=-oo;
    tmp=x;while (tmp!=lca){
                Max=max(Max,node[tmp].max);Max=max(Max,node[fnode[tmp]].max);
                tmp=fnew[tmp];
                }
    tmp=y;while (tmp!=lca){
                Max=max(Max,node[tmp].max);Max=max(Max,node[fnode[tmp]].max);
                tmp=fnew[tmp];
                }
    //Max=max(Max,node[lca].max);
    return Max;
}
void Changef(int x,int y){
    int lca=Qlca(x,y),tmp;if (lca==x)return;
    fnew[x]=y;fnode[x]=0;
}
void bfs(int root){
     int h=1,t=1,x,i,j;a[1]=root;f[root]=0;deep[root]=0;
     while (h<=t){
           x=a[h++];
           for (i=e.son[x];i;i=e.next[i]){
               j=e.link[i];
               if (j!=f[x]){a[++t]=j;deep[j]=deep[x]+1;f[j]=x;w[j]=e.node[i];}
           }
     }
}
void init(){
     static char str[100];
     int x,y,z,i,tmp;
     static int edgex[maxn],edgey[maxn];
     root=1;e.clear();
     scanf("%d",&n);
     for (i=1;i<=n-1;i++)scanf("%d%d%d",&x,&y,&z),e.addedge(x,y,z),e.addedge(y,x,z),edgex[i]=x,edgey[i]=y;
     bfs(root);q=0;
     while (1){
           gets(str);scanf("%s",str);
           if (str[0]=='D')break;q++;
           scanf("%d%d",&x,&y);
           if (str[1]=='H'){
                         if (deep[edgex[x]]>deep[edgey[x]])tmp=edgex[x];
                         else tmp=edgey[x];
                         opt[q].ch='A';opt[q].x=tmp;opt[q].y=y;
                         }
           else if (str[1]=='U'){opt[q].ch='B';opt[q].x=x;opt[q].y=y;}
     }
}
int main()
{
    node[0].max=-oo;node[0].min=oo;
	freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int T,now,i,next,Lim;
	scanf("%d",&T);
	while (T--){
          init();
          Lim=(int)(sqrt(q))+1;
          now=1;
          while (now<=q){
                next=now+Lim;if (next>q)next=q+1;
                Bfs(root);
                Buildlca(now,next);
                for (i=now;i<next;i++){
                    if (opt[i].ch=='A')Change(opt[i].x,opt[i].y);
                    if (opt[i].ch=='B')printf("",Qmax(opt[i].x,opt[i].y));
                    }
                Rebuild();now=next;
                }
          }
	system("pause");
    for (;;);
	return 0;
}














