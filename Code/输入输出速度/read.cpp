#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
inline void read(int &x){
	char ch;int bo=0;x=0;
	for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
	for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
	if (bo)x=-x;
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("read.out","w",stdout);
	int t1=clock();
	int n,x;read(n);
	for (int i=1;i<=n;++i)read(x);
	printf("time=%d\n",clock()-t1);
	//system("pause");
	return 0;
}


