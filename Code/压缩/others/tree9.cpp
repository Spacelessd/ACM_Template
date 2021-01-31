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
int main()
{
	freopen("tree9+-.out","r",stdin);
	freopen("test1.out","w",stdout);
	char ch;
	while (scanf("%c",&ch)!=EOF)s[++s1]=ch;
	int start=1;
	while (start<=s1){
		string str="";
		for (int i=1;i<=2;++i)str=str+s[start++];
		++S[str];
	}
	printf("%d\n",S.size());
	while (!S.empty()){
		cout<<S.begin()->first<<" ";
		printf("%d\n",S.begin()->second);
		S.erase(S.begin());
	}
	//system("pause");for (;;);
	return 0;
}


