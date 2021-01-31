#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 100005
inline int max(int x,int y){int m=(x-y)>>31;return y&m|x&~m;}
inline int min(int x,int y){int m=(y-x)>>31;return y&m|x&~m;}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	printf("%d\n",min(734,123));
	printf("%d\n",max(7,999));
	system("pause");for (;;);
	return 0;
}


