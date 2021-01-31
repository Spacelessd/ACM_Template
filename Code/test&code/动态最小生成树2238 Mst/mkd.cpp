#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
inline int Rand(){return (rand()<<15)+rand();}
int main()
{
	int n,m,x,y,z,q;
	freopen("1.in","w",stdout);
	srand(time(0));
	n=50000;m=100000;q=100000;
	//n=2;m=4;q=3;
	printf("%d %d\n",n,m);
	for (int i=1;i<=m;++i){
		x=Rand()%n+1;y=Rand()%n+1;
		if (x>y){int tmp=x;x=y;y=tmp;}
		printf("%d %d %d\n",x,y,Rand()%50000);
	}
	printf("%d\n",q);
	for (int i=1;i<=q;++i)printf("%d\n",Rand()%m+1);
	//system("pause");
	return 0;
}


