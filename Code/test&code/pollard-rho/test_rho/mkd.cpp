#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define ll long long
#define mod 1000000000000LL
int main()
{
	freopen("1.in","w",stdout);
	srand(time(0));
	printf("1\n");
	int n=10000;
	printf("%d\n",n);
	for (int i=1;i<=n;++i)
		printf("%I64d\n",(((ll)rand()<<(ll)40)+((ll)rand()<<(ll)32)
		+((ll)rand()<<(ll)16)+(ll)rand())%mod+2);
	/*int n=10000;
	printf("%d\n",n);
	for (int i=1;i<=n;++i)
		printf("%I64d\n",((ll)rand()<<(ll)16)+(ll)rand()+1);*/
	//system("pause");
	return 0;
}














