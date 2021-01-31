#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int n,m,i,j,x,y,z;
int main()
{
	freopen("a.in","w",stdout);
	srand(time(0));
	n=500000;m=500000;
	printf("%d\n",n);
	for (i=2;i<=n;++i){
		int x=i-1-rand()%30;if (x<1)x=1;
		//int x=i/2;
		printf("%d %d\n",i,x);
	}
	printf("%d\n",m);
	for (i=1;i<=m;++i){
		x=rand()%n+1;y=rand()%n+1;
		if (x>y){int tmp=x;x=y;y=tmp;}
		printf("%d %d\n",x,y);
	}
	//system("pause");
	return 0;
}


