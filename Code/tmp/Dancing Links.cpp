#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxn 20
#define maxans 100
#define N (maxn*maxn*25)
#define C (maxn*maxn)
#define ka 400000000
int xx[4][5]={{0,0,0,1,2},{0,1,1,1,2},{0,1,2,2,2},{0,1,1,1,2}};
int yy[4][5]={{0,1,2,1,1},{2,0,1,2,2},{1,1,0,1,2},{0,0,1,2,0}};
struct num{
       int x,y,z;
       };
int l[N],r[N],d[N],u[N],c[N],add[N],s[C],tmp[C];
num o[maxans],name[N],best[maxans];
int bb[maxn][maxn];
char out[maxn][maxn];
int n,m,i,j,k,i1,len=0,ans=0,ss=0;
int bo;
inline int calc(int x,int y){return (x-1)*m+y;}
void remove(int x)
{
     l[r[x]]=l[x]; r[l[x]]=r[x];
     for (int i=d[x];i!=x;i=d[i]){
         for (int j=r[i];j!=i;j=r[j]){
             u[d[j]]=u[j];
             d[u[j]]=d[j];
             s[c[j]]--;ss++;
             }
         }
}

void resume(int x)
{ 
     for (int i=u[x];i!=x;i=u[i])
         for (int j=l[i];j!=i;j=l[j]){
             u[d[j]]=j;
             d[u[j]]=j;
             s[c[j]]++;ss++;
             }
     l[r[x]]=x; r[l[x]]=x;
}

void dfs(int t)
{
     if (ss>ka)return;
     if (bo)return;
     if (!r[0]){
        if (t>=ans){
                   //ans=t;
                   memcpy(best,o,sizeof(o));
                   //printf("%d %d\n",ans,ss);
                   bo=1;
                   //for (i=1;i<=ans;i++)printf("%d %d %d\n",o[i].x,o[i].y,o[i].z);
                   }
        return;
        }
     int x=0,min=100000,num=0;
     for (int i=r[0];i;i=r[i]){
         if (s[i]<min) min=s[i],x=i;
         num++;
         }
     if (num/5+t+1<=ans)return;
     //if (min>5)printf("%d\n",min);
     remove(x);
     for (int i=d[x];i!=x;i=d[i]){
         for (int j=r[i];j!=i;j=r[j]) remove(c[j]);
         if (add[i]==1) o[t+1]=name[i];
         dfs(t+add[i]);
         for (int j=l[i];j!=i;j=l[j]) resume(c[j]);
         }
     resume(x);
}
int main()
{
        //freopen(".in","r",stdin);
        //freopen(".out","w",stdout);
        scanf("%d%d",&n,&m);
        for (i=1;i<=n;i++)
          for (j=1;j<=m;j++)
          {
          r[len]=len+1;++len;l[len]=len-1;
          c[len]=len;tmp[len]=len;
          add[len]=1;s[len]=1;
      }
    
        for (i=1;i<=n-2;i++)
          for (j=1;j<=m-2;j++)
            for (k=0;k<4;k++)
            for (i1=0;i1<5;i1++)
            {
                int x=i+xx[k][i1],y=j+yy[k][i1];
                ++len;add[len]=1;
                name[len].x=i;
                name[len].y=j;
                name[len].z=k;
                s[calc(x,y)]++;
                c[len]=calc(x,y);
                if (i1==0)l[len]=len+4;
                  else l[len]=len-1;
                if (i1==4)r[len]=len-4;
                  else r[len]=len+1;
                u[len]=tmp[calc(x,y)];
                d[tmp[calc(x,y)]]=len;
                tmp[calc(x,y)]=len;
            }
    
    for (i=1;i<=n;i++)
          for (j=1;j<=m;j++)
          {
          len++;c[len]=calc(i,j);
          r[len]=l[len]=len;
          u[len]=tmp[calc(i,j)];
          d[tmp[calc(i,j)]]=len;
          u[calc(i,j)]=len;d[len]=calc(i,j);
          s[calc(i,j)]++;
          //printf("%d\n",s[calc(i,j)]);
      }
    for (ans=0;ans<=maxans;ans++)
    {
        bo=0;
        ss=0;
        dfs(0);
        if (ss>=ka){
                          ans++;
                          printf("rp\n");
                          break;
                          }
        if (!bo)break;
    }
    ans--;
    if (ans<0)ans=0;
    printf("%d\n",ans);
    //for (i=1;i<=ans;i++)printf("%d %d %d\n",best[i].x,best[i].y,best[i].z);
    for (i=1;i<=ans;i++)
      for (j=0;j<5;j++)
      bb[best[i].x+xx[best[i].z][j]][best[i].y+yy[best[i].z][j]]=i;
    for (i=1;i<=n;i++)
          for (j=1;j<=m;j++){
          if (bb[i][j]==0)out[i][j]='.';
            else out[i][j]='A'+bb[i][j]-1;
     }
    for (i=1;i<=n;i++)
          {
                      for(j=1;j<=m;j++)printf("%c",out[i][j]);
                      printf("\n");
      }
        system("pause");
        return 0;
}
