#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
typedef double real;
const int maxn=1010;
const real oo=1e20;
const real eps=1e-10;
real A[maxn][maxn];
real b[maxn],c[maxn],x[maxn],origC[maxn];
int N[maxn],B[maxn];
int n,m; double v;
void read()
{
     int i,j;
     scanf("%d%d",&n,&m);
     for (i=1;i<=n;++i)scanf("%lf",&c[i]);
     for (i=1;i<=m;++i)
     {
         for (j=1;j<=n;++j)scanf("%lf",&A[n+i][j]);
         scanf("%lf",&b[n+i]);
     }
}
void pivot(int l,int e)
{
     int i,j,tmpn,tmpb;
     b[e]=b[l]/A[l][e];
     A[e][l]=1/A[l][e];
     for (i=1;i<=N[0];++i)
         if (N[i]!=e) {
                      A[e][N[i]]=A[l][N[i]]/A[l][e];
                      c[N[i]]-=A[e][N[i]]*c[e];
                      }
             else tmpn=i;
     for (i=1;i<=B[0];++i)
     if (B[i]!=l)
         {
         b[B[i]]-=A[B[i]][e]*b[e];
         A[B[i]][l]=-A[B[i]][e]*A[e][l];
         for (j=1;j<=N[0];++j) if (N[j]!=e)
             A[B[i]][N[j]]-=A[B[i]][e]*A[e][N[j]];
         }
         else tmpb=i;
     v+=b[e]*c[e];
     c[l]=-A[e][l]*c[e];
     N[tmpn]=l;B[tmpb]=e;
}
int opt() //false stands for unbounded
{
    int i,e,l,tl,ie,te;
    real delta,tmp,maxUp;
    while (1){
        maxUp=-1;
        for (ie=1;ie<=N[0];ie++)
        if (c[N[ie]]>eps){
            te=N[ie];delta=oo;tl=maxn;
            for (i=1;i<=B[0];++i)
                if (A[B[i]][te]>eps)
                {
                    tmp=b[B[i]]/A[B[i]][te];
                    if (tmp<delta || tmp==delta && B[i]<tl)
                    {
                        delta=tmp;tl=B[i];
                        if (delta*c[te]<maxUp)break;
                    }
                }
            if (tl==maxn) return 0;
            if (delta*c[te]>maxUp)
            {
                maxUp=delta*c[te];
                l=tl;e=te;
            }
        }
        if (maxUp<-0.99)return 1;
        pivot(l,e);
        }
}
void delete0()
{
     int p,i;
     for (p=1;p<=B[0];p++) if (B[p]==0)break;
     if (p<=B[0])pivot(0,N[1]);
     for (p=1;p<=N[0];p++) if (N[p]==0)break;
     for (i=p;i<N[0];++i) N[i]=N[i+1];
     N[0]--;
}
int initialize()
{
     int i,j,l;
     N[0]=B[0]=0;
     for (i=1;i<=n;++i)N[++N[0]]=i;
     for (i=1;i<=m;++i)B[++B[0]]=n+i;
     v=0; l=B[1];
     for (i=2;i<=B[0];++i)
       if (b[B[i]]<b[l])l=B[i];
     if (B[l]>=0)return 1;
     memcpy(origC,c,sizeof(real)*(n+m+1));
     N[++N[0]]=0;
     for (i=1;i<=B[0];++i)A[B[i]][0]=-1;
     memset(c,0,sizeof(real)*(n+m+1));
     c[0]=-1;
     pivot(l,0);
     opt();
     if (v<-eps)return 0;
     delete0();
     memcpy(c,origC,sizeof(real)*(n+m+1));
     for (i=1;i<=B[0];++i)
     {
         v+=c[B[i]]*b[B[i]];
         for (j=1;j<=N[0];++j) c[N[j]]-=A[B[i]][N[j]]*c[B[i]];
     }	
     return 1;
}
void simplex()
{
     int i;
     read();
     if (!initialize()){
        printf("Infeasible\n");
        return;
		}
     if (!opt()){
		printf("Unbounded\n");
		return;
		}
     printf("Max value is %f\n",v);
     memset(x,0,sizeof(real)*(n+m+1));
     for(i=1;i<=B[0];++i)x[B[i]]=b[B[i]];
     //for(i=1;i<=n;++i)printf("x%d = %f\n",i,x[i]);
}
int main()
{
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    int t1=clock();
    simplex();
    printf("%d\n",clock()-t1);
    //system("pause");
    //for(;;);
}


