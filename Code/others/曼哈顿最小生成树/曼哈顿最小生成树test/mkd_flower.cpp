#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int Rand(){return (rand()<<15)+rand();}
int main()
{
	int n,m,c,x,y,z;
	freopen("1.in","w",stdout);
	srand(time(0));
	n=100000;c=100;m=100000;
	printf("%d %d %d\n",n,c,m);
	for (int i=1;i<=n;++i)printf("%d ",rand()%c+1);printf("\n");
	for (int i=1;i<=m;++i){
		x=Rand()%n+1;y=Rand()%n+1;
		if (x>y){int tmp=x;x=y;y=tmp;}
		printf("%d %d\n",x,y);
	}
	//system("pause");
	return 0;
}


