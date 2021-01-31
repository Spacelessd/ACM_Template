#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main()
{
	int n,m,x,y,z,P;
	freopen("1.in","w",stdout);
	srand(time(0));
	n=50000;m=180000;P=1000000;
	printf("%d %d\n",n,m);
	for (int i=1;i<=n;++i)printf("%d ",rand()*rand()%P);printf("\n");
	for (int i=1;i<=m;++i){
		int x=rand()%n+1,y=rand()%n+1;
		if (x>y){int tmp=x;x=y;y=tmp;}
		printf("%d %d\n",x,y);
	}
	//system("pause");
	return 0;
}


