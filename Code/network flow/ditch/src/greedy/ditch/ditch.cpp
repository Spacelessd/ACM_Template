/*
ID:hqztrue1
LANG:C++
TASK:ditch
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
const int maxn=20010;
const int maxm=1000010;
int n,m,i,x,y,z,sums,sumt,S,T;
int main()
{
    freopen("ditch.in","r",stdin);
    freopen("ditch.out","w",stdout);
    scanf("%d%d",&m,&n);S=1;T=n;
    for (i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        if (x==y)continue;
        if (x==S)sums+=z;
        if (y==T)sumt+=z;
    }
    printf("%d\n",sums<sumt?sums:sumt);
    //system("pause");
    //for(;;);
    return 0;
}










