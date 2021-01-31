#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int n,m,b,i,x,y;
int main()
{
	freopen("cot2.in","w",stdout);
	srand(time(0));
	b=30;n=6000;m=5000;
	printf("%d %d\n",n,m);
	for (i=1;i<=n;++i)printf("%d ",rand()%b);
	printf("\n");
	for (i=2;i<=n;++i){
        x=rand()%(i-1)+1;
        printf("%d %d\n",x,i);
        }
    for (i=1;i<=m;++i){
        x=rand()%n+1;y=rand()%n+1;
        printf("%d %d\n",x,y);
        }
	//system("pause");
	return 0;
}














