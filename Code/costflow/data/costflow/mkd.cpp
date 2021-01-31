#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int n,m,i,x;
int main()
{
	freopen("tmp.txt","r",stdin);
	scanf("%d",&x);
	srand(x);
	fclose(stdin);
	
	freopen("tmp.txt","w",stdout);
	printf("%d\n",rand());
	fclose(stdout);
	
	freopen("costflow.in","w",stdout);
	n=((rand()<<16)+rand())%1000+2;m=((rand()<<16)+rand())%200000+2;
	printf("%d %d\n",n,m);
	for (i=1;i<=m;++i)
	{
		int x=((rand()<<16)+rand())%n+1,y=((rand()<<16)+rand())%n+1;
		printf("%d %d %d %d\n",x,y,rand()%200000,rand()%5);
	}
	//system("pause");
	//for (i=1;i<=300000000;i++);
	return 0;
}


