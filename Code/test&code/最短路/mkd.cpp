#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main()
{
	int n,m,x,y,z;
	freopen("1.in","w",stdout);
	srand(time(0));
	n=1000000;m=5000000;
	n=100000;m=500000;
	//n=10;m=n;
	//n=50;m=7000;
	//n=5;m=17;
	//n=3;m=5;
	printf("%d %d\n",n,m);
	for (int i=1;i<n;++i)printf("%d %d %d\n",i,i+1,rand()%1000);
	for (int i=1;i<=m-n+1;++i){
		x=rand()%n+1;y=rand()%n+1;
		printf("%d %d %d\n",x,y,rand()%1000);
	}
	printf("%d %d\n",1,n);
	//system("pause");
	return 0;
}


