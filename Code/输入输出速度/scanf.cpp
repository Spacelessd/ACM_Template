#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	freopen("1.in","r",stdin);
	freopen("scanf.out","w",stdout);
	int t1=clock();
	int n,x;scanf("%d",&n);
	for (int i=1;i<=n;++i)scanf("%d",&x);
	printf("time=%d\n",clock()-t1);
	//system("pause");
	return 0;
}


