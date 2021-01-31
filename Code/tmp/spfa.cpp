#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
const int maxn=20010;
const int maxm=500010;
#define oo 50000000
int d[maxn],q[maxn],inq[maxn],son[maxn];
int n,S;

int spfa(int s)
{
     int h=0,t=1,i,j,p;
     memset(d,6,sizeof(int)*(n+5));
     memset(inq,0,sizeof(int)*(n+5));
     d[S]=0;q[1]=S;inq[S]=1;
     while (h!=t){
           h=h<n?h+1:1;i=q[h];inq[i]=0;
           for (p=son[i];p!=-1;p=next[p]){
               j=link[p];
               if (d[i]+cost[p]<d[j]&&cap[p]){
                   d[j]=d[i]+cost[p];pre[j]=p;
                   if (!inq[j])t=t<n?t+1:1,q[t]=j,inq[j]=1;
                   }
               }
           }
     return d[T]>oo?0:1;
}
int main(){
	
}
