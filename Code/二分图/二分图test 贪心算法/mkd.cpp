#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int n1,n2,m,x,y;
int main()
{
	freopen("1.in","w",stdout);
	srand(time(0));
	n1=50000;n2=40000;m=150000;
	//n1=5000;n2=4000;m=15000;
	//n1=900;n2=800;m=15000;
	//n1=90;n2=80;m=150;
	//n1=3;n2=2;m=5;
	printf("%d %d %d\n",n1,n2,m);
	for (int i=1;i<=m;++i){
		x=rand()%n1+1;y=rand()%n2+1;
		printf("%d %d\n",x,y);
	}
	//system("pause");
	return 0;
}


