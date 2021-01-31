#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define J (")
int T;long long x,y;char ch;
int main()
{
	freopen("1.in","r",stdin);
	freopen("3.out","w",stdout);
	scanf("%d",&T);
	while (T--){
		scanf("%I64d %c%I64d",&x,&ch,&y);
		if (ch=='+')printf("%I64d\n",x+y);
		if (ch=='-'){
			if (x<y)puts("error");
			else printf("%I64d\n",x-y);
		}
		if (ch=='*')printf("%I64d\n",x*y);
		if (ch=='/')printf("%I64d\n",x/y);
		if (ch=='%')printf("%I64d\n",x%y);
		if (ch=='<')printf("%d\n",(int)(x<y));
	}
	//system("pause");for (;;);
	return 0;
}


