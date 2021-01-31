#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int n,m,x,y,z,T,size;
void put(){
	int s=rand()%size+1,x;bool zero=1;
	//s=size/2+1;
	if (rand()%10<5)printf("-");
	for (int i=1;i<s;++i)x=rand()%10,printf("%d",x),zero&=(x==0);
	if (!zero)printf("%d",rand()%10);
	else printf("%d",rand()%9+1);
}
const char opt[]={'+','-','*','/','%','<'};
int main()
{
	freopen("1.in","w",stdout);
	srand(time(0));
	//T=100000;size=9;
	//T=10000;size=5;
	T=1000;size=3;
	printf("%d\n",T);
	while (T--){
		put();
		printf(" %c ",opt[rand()%sizeof(opt)]);
		put();
		printf("\n");
	}
	//system("pause");
	return 0;
}


