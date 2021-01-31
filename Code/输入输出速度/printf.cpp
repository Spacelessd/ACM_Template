#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
int n=10000000;
int main()
{
	freopen("1.in","w",stdout);
	srand(time(0));
	int t1=clock();
	printf("%d\n",n);
	for (int i=1;i<=n;++i)printf("%d ",rand()*rand());
	fclose(stdout);
	freopen("printf.out","w",stdout);
	printf("time=%d\n",clock()-t1);
	fclose(stdout);
	//system("pause");
	return 0;
}


