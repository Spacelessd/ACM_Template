#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;

class dui{
      public:
             int* a;
             int len;
             dui(int x=100)
             {
                  x++;
                  a=new int[x];
                  len=0;
             }
             void up(int x)
             {
                  int i=x,j;
                  while ((i>1)&&(a[i]<a[i>>1])){
                        j=a[i];a[i]=a[i>>1];a[i>>1]=j;
                        i>>=1;
                        }
             }
             void down(int x)
             {
                  int i=x,j,k;
                  while (i<<1<=len){
                        j=i;
                        if (a[i<<1]<a[i])j=i<<1;
                        if (((i<<1)+1<=len)&&(a[j]>a[(i<<1)+1]))j=(i<<1)+1;
                        if (j==i)break;
                        k=a[i];a[i]=a[j];a[j]=k;
                        i=j;
                        }
             }
             void insert(int x)
             {
                  a[++len]=x;
                  up(len);
             }
             int min()
             {
                  return a[1];
             }
             void delmin()
             {
                  //if (len==0)return;
                  a[1]=a[len--];
                  down(1);
             }
             void empty()
             {
                 len=0;
             }
             
             int isempty()
             {
                 if (len==0)return 1;
                 else return 0;
             }
};


int tmp[10000010];
dui a(1000000);
int i;
double t0,t1;

/*void build()
{
     int i;
     for (i=nn;i;i--)a.a[i]=tmp[i];
	 for (i=nn/2;i;i--)a.down(i);
	 a.len=nn;
}*/

int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	printf("start\n");
	srand(time(0));
	const int nn=10;
	for(i=1;i<=nn;i++) tmp[i]=rand()*32768+rand();
	for(i=1;i<=nn;i++)tmp[i]=i;
	t0=(double)clock()/CLOCKS_PER_SEC;
	for(i=nn;i>=1;i--) a.insert(tmp[i]);
	t1=(double)clock()/CLOCKS_PER_SEC;
	printf("%.3lf\n",t1-t0);
	for(i=1;i<=nn;i++)
	{
                      printf("%d\n",a.min());
                      a.delmin();
    }
    t1=(double)clock()/CLOCKS_PER_SEC;
	printf("%.3lf\n",t1-t0);
	system("pause");
	return 0;
}







