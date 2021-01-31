#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int x,y;
int exgcd(int a,int b){
	if (!b){x=1;y=0;return a;}
	int t,tmp=exgcd(b,a%b);
	t=x;x=y;y=t-(a/b)*y;
	return tmp;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	printf("%d\n",exgcd(n,m));
	printf("%d %d\n",x,y);
	system("pause");for (;;);
	return 0;
}


