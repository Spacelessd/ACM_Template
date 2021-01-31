#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define maxn 1010
#define maxm 7000010
#define oo (1<<30)
#define null -1
struct node{
	int cover,max;
	int son[2];
};
node T[maxm];
int n,m,c,i,j,a,b,h,x,y,ans,len;
//int A[maxn][maxn];
inline int max(int x,int y){return x>y?x:y;}
inline void update(int t){
     T[t].max=-oo;
     for (int i=0;i<2;++i)T[t].max=max(T[t].max,T[T[t].son[i]].max);
}
inline void Down(int t){
     if (T[t].cover!=null){
        for (int i=0;i<2;++i)T[T[t].son[i]].max=T[T[t].son[i]].cover=T[t].cover;
        T[t].cover=null;
        }
}
void Build(int t,int left,int right,int up,int down){
     if (left==right&&up==down){
        T[t].cover=null;T[t].max=0;//A[left][up];
        return;
        }
     int X=right-left>=down-up?1:0;
     if (X){
         int mid=(left+right)>>1;
         T[t].son[0]=++len;Build(len,left,mid,up,down);
         T[t].son[1]=++len;Build(len,mid+1,right,up,down);
         }
         else {
         int mid=(up+down)>>1;
         T[t].son[0]=++len;Build(len,left,right,up,mid);
         T[t].son[1]=++len;Build(len,left,right,mid+1,down);
         }
     T[t].cover=null;update(t);
}
int Qmax(int t,int left,int right,int up,int down,int l,int r,int u,int d){
     if (left==l&&right==r&&up==u&&down==d){
        return T[t].max;
        }
     int ans=-oo,X=right-left>=down-up?1:0;
     Down(t);
     if (X){
         int mid=(left+right)>>1;
         if (r<=mid)ans=max(ans,Qmax(T[t].son[0],left,mid,up,down,l,r,u,d));
         else if (l>mid)ans=max(ans,Qmax(T[t].son[1],mid+1,right,up,down,l,r,u,d));
         else {
              ans=max(ans,Qmax(T[t].son[0],left,mid,up,down,l,mid,u,d));
              ans=max(ans,Qmax(T[t].son[1],mid+1,right,up,down,mid+1,r,u,d));
              }
         }
         else {
         int mid=(up+down)>>1;
         if (d<=mid)ans=max(ans,Qmax(T[t].son[0],left,right,up,mid,l,r,u,d));
         else if (u>mid)ans=max(ans,Qmax(T[t].son[1],left,right,mid+1,down,l,r,u,d));
         else {
              ans=max(ans,Qmax(T[t].son[0],left,right,up,mid,l,r,u,mid));
              ans=max(ans,Qmax(T[t].son[1],left,right,mid+1,down,l,r,mid+1,d));
              }
         }
     return ans;
}

void Cover(int t,int left,int right,int up,int down,int l,int r,int u,int d,int key){
     //printf("zzy%d %d %d %d %d %d %d %d %d\n",t,left,right,up,down,l,r,u,d);
     //system("pause");
     if (left==l&&right==r&&up==u&&down==d){
        T[t].max=T[t].cover=key;return;
        }
     int X=right-left>=down-up?1:0;
     Down(t);
     if (X){
         int mid=(left+right)>>1;
         if (r<=mid)Cover(T[t].son[0],left,mid,up,down,l,r,u,d,key);
         else if (l>mid)Cover(T[t].son[1],mid+1,right,up,down,l,r,u,d,key);
         else {
              Cover(T[t].son[0],left,mid,up,down,l,mid,u,d,key);
              Cover(T[t].son[1],mid+1,right,up,down,mid+1,r,u,d,key);
              }
         }
         else {
         int mid=(up+down)>>1;
         if (d<=mid)Cover(T[t].son[0],left,right,up,mid,l,r,u,d,key);
         else if (u>mid)Cover(T[t].son[1],left,right,mid+1,down,l,r,u,d,key);
         else {
              Cover(T[t].son[0],left,right,up,mid,l,r,u,mid,key);
              Cover(T[t].son[1],left,right,mid+1,down,l,r,mid+1,d,key);
              }
         }
     update(t);
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	while (scanf("%d%d%d",&n,&m,&c)!=EOF){
	//memset(A,0,sizeof(A));
	//for (i=1;i<=n;++i)
	    //for (j=1;j<=m;++j)scanf("%d",&A[i][j]);
    len=0;n=1024;m=1024;
    Build(++len,1,m,1,n);//printf("len=%d\n",len);
    for (i=1;i<=c;++i){
        scanf("%d%d%d%d%d",&a,&b,&h,&x,&y);++x;++y;
        ans=Qmax(1,1,m,1,n,y,y+b,x,x+a);
        Cover(1,1,m,1,n,y,y+b,x,x+a,ans+h);
    }
    printf("%d\n",Qmax(1,1,m,1,n,1,m,1,n));
    }
	//system("pause");
	return 0;
}














