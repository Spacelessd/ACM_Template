#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int n,m,i,j,x,y,z;
int main()
{
	freopen(".in","w",stdout);
	srand(time(0));
	n=5;m=3;
	printf("%d %d\n",n,m);
	for (i=1;i<=n;++i)printf("%d ",rand()%n+1);printf("\n");
    for (i=1;i<=m;++i){
        x=rand()%n+1;y=rand()%n+1;
        if (x>y){int tmp=x;x=y;y=tmp;}
        printf("%d %d\n",x,y);
        }
	//system("pause");
	return 0;
}














