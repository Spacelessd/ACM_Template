#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int n,m,i;
int main()
{
	freopen("ditch.in","w",stdout);
	srand(time(0));
	scanf("%d %d",&n,&m);
	printf("%d %d\n",m,n);
	for (i=1;i<=m;i++)
	{
		int x=((rand()<<16)+rand())%n+1,y=((rand()<<16)+rand())%n+1;
		printf("%d %d %d\n",x,y,rand());
	}
	//system("pause");
	return 0;
}


