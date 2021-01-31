#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int a[10000010];
void Q(int s,int t)
{
     int m,p;
     int i=s; 
     int j=t;
     m=a[(i+j)/2];
     do{
           while (a[i]<m) i++;
           while (a[j]>m) j--;
           if (i<=j){
                    p=a[i]; a[i]=a[j]; a[j]=p;
                    i++; j--;
                    }
           }while (i<=j);
     if (i<t) Q(i,t);
     if (s<j) Q(s,j);  
}
int main()
{
    int n;
    //freopen("1.in","r",stdin);
    //freopen("1.out","w",stdout);
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&a[i]);
    //sort(a,a+n);
    Q(1,n);
    for (int i=0;i<n;i++)
      printf("%d ",a[i]);
    //system("pause");
    return 0;
}       




