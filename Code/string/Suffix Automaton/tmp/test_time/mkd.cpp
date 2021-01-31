#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main()
{
	int n,m,x,y,z;
	freopen("1.in","w",stdout);
	srand(time(0));
	n=2;m=250000;
	for (int i=1;i<=n;++i){
		int m1=rand()%m+1;
		for (int i=1;i<=m1;++i)//printf("%c",'a'+rand()%26);
		printf("%c",'a'+rand()<10000?'b':rand()<10000?'c':'a');
		printf("\n");
	}
	//system("pause");
	return 0;
}


