#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main()
{
	int n,m,x,y,z;
	freopen("1.in","w",stdout);
	srand(time(0));
	n=100000;
	printf("%d\n",n);
	for (int i=1;i<=n;++i)
		printf("%d %d\n",rand()*rand()%n,rand()*rand()%n);
	//system("pause");
	return 0;
}














