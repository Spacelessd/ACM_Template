#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main()
{
	int n,m,x,y,z;
	freopen("1.in","w",stdout);
	srand(time(0));
	n=30;m=10000;
	printf("%d %d\n",n,m);
	for (int i=1;i<=n;++i)printf("%d ",rand()%10);printf("\n");
	for (int i=1;i<=m;++i){
		int x=rand()%n+1,y=rand()%n+1;
		if (x>y){int tmp=x;x=y;y=tmp;}
		int k=rand()%(y-x+1)+1;
		printf("%d %d %d\n",x,y,k);
	}
	
	//system("pause");
	return 0;
}


