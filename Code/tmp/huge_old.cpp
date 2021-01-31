#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxn 510
#define maxm 70
struct huge{
      int tmp[maxn];
      int *a,wei;
      huge()
      {
               a=new int[maxn];wei=10;
               memset(a,0,sizeof(int[maxn]));
      }
      huge(int len)
      {
               len+=10;wei=10;
               a=new int[len];
               memset(a,0,sizeof(a));
      }
      huge operator +(huge& b)
      {
            int len=a[0]>b.a[0]?a[0]:b.a[0],i;
            memset(tmp,0,sizeof(int)*(len+5));
            for (i=1;i<=len;i++){
                if (i>a[0])a[i]=0;
                if (i>b.a[0])b.a[i]=0;
                tmp[i]=tmp[i]+a[i]+b.a[i];
                if (tmp[i]>=wei){
                   tmp[i]-=wei;tmp[i+1]++;
                   }
                }
            if (tmp[i+1])tmp[0]=len+1;
               else tmp[0]=len;
            huge T(len);memcpy(T.a,tmp,sizeof(int)*(len+5));
            return T;
      }
      huge operator *(huge& b)
      {
            int len=a[0]+b.a[0],i,j;
            memset(tmp,0,sizeof(int)*(len+5));
            for (i=1;i<=a[0];i++)
                for (j=1;j<=b.a[0];j++){
                tmp[i]=tmp[i]+a[i]*b.a[i];
                if (tmp[i]>=wei){
                   tmp[i+1]+=tmp[i]/wei;tmp[i]%=wei;
                   }
                }
            len=a[0]+b.a[0]+1;
            while (len>1&&tmp[len]==0)--len;
            huge T(len);memcpy(T.a,tmp,sizeof(int)*(len+5));
            return T;
      }
      huge operator *(int b)
      {
            int len=a[0],i;
            memset(tmp,0,sizeof(int)*(len+5));
            for (i=1;i<=len;i++){
                tmp[i]+=a[i]*b;
                if (tmp[i]>=wei){
                   tmp[i+1]+=tmp[i]/wei;tmp[i]%=wei;
                   }
                }
            if (tmp[i+1])tmp[0]=len+1;
               else tmp[0]=len;
            huge T(len);memcpy(T.a,tmp,sizeof(int)*(len+5));
            return T;
      }
      
      void operator =(int b){
           a[0]=0;
           while (b)a[++a[0]]=b%10,b/=10;
           if (!a[0])a[0]++,a[1]=0;
           //printf("%d\n",a[0]);
           }
      void print()
      {
           for (int i=a[0];i;i--)printf("%d",a[i]);
           printf("\n");
      }
};
long double ans,ans1;
long double c[maxm][maxm];
long double exp[maxm];
int n,m,i,j;
int main()
{
    for (i=0;i<maxm;i++)c[i][0]=1;//printf("zzy");
    for (i=1;i<maxm;i++)
        for (j=1;j<maxm;j++){
            c[i][j]=c[i-1][j]+c[i-1][j-1];
            //printf("%d %d %.5lf*\n",i,j,c[i][j]);
            }
    exp[0]=1;
    for (i=1;i<maxm;i++)exp[i]=exp[i-1]*2;
    while (scanf("%d%d",&n,&m)!=EOF){
          if (m>n){
                   printf("100.00000\n");
                   continue;
                   }
          ans=0;
          for (i=0;i<=m-1;i++)ans=ans+c[n][i]*exp[n-i];
          //printf("%.5lf\n",ans);
          ans1=0;
          for (i=0;i<=m;i++)ans1=ans1+c[n][i]*exp[n-i];
          //printf("%.5lf\n",ans1);
          printf("%.5lf\n",double(100.0*ans/ans1));
          }
    //system("pause");
}






