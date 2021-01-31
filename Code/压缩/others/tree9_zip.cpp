#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<string>
#include<map>
using namespace std;
#define N 10000005
map<string,int> S;
char s[N];int s1=0;
int rank[256];
int main()
{
	freopen("tree9+-.out","r",stdin);
	freopen("test1.out","w",stdout);
	for (int i=0;i<=9;++i)rank['0'+i]=i;
	rank['+']=10;rank['-']=11;
	char ch;
	while (scanf("%c",&ch)!=EOF)s[++s1]=ch;
	int start=1;
	while (start<=s1){
		int x=0;
		for (int i=1;i<=1;++i)x=x*12+s[start++];
		printf("%c",x);
	}
	//system("pause");for (;;);
	return 0;
}


