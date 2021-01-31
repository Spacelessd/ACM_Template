#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main()
{
	int n,m,x,y,z;
	freopen("1.in","w",stdout);
	srand(time(0));
	//n=30000;m=100000;
	n=3;m=100;
	printf("%d %d\n",n,m);
	for (int i=1;i<=m;++i){
		x=rand()%n+1;y=rand()%n+1;
		printf("%d %d %d\n",x,y,rand());
	}
	//system("pause");
	return 0;
}


