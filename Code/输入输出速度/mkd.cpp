#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main()
{
	int n=10000000;
	freopen("1.in","w",stdout);
	srand(time(0));
	printf("%d\n",n);
	for (int i=1;i<=n;++i)printf("%d ",rand()*rand());
	//system("pause");
	return 0;
}


