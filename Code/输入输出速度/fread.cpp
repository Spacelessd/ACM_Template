#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
char str[100000005],*p=str;
inline void read(int &x){
	int bo=0;x=0;
	while(*p<'0'||*p>'9')if (*p++=='-')bo=1;
	while(*p>='0'&&*p<='9')x=x*10+*p++-'0';
	if (bo)x=-x;
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("fread.out","w",stdout);
	int t1=clock();
	fread(str,1,100000000,stdin);
	int n,x;read(n);
	for (int i=1;i<=n;++i)read(x);
	printf("time=%d\n",clock()-t1);
	//system("pause");
	return 0;
}


