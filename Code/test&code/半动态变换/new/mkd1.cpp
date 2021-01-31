#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int n,m,i,j,x,y,z;
int main()
{
	freopen("1.in","w",stdout);
	srand(time(0));
	n=1000000;m=100000;
	for (int i=1;i<=n;++i)
		printf("I %d\n",rand());
	for (int i=1;i<=m;++i){
		int x=rand(),y=rand();
		if (x>y){int tmp=x,x=y,y=tmp;}
		printf("Q %d %d\n",x,y);
	}
	//system("pause");
	return 0;
}














