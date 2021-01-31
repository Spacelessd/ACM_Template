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
	freopen("cin.out","w",stdout);
	int t1=clock();
	int n,x;cin>>n;
	for (int i=1;i<=n;++i)cin>>x;
	printf("time=%d\n",clock()-t1);
	//system("pause");
	return 0;
}


