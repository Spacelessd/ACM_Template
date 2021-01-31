#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 100005
struct arr{
	int a[4][4];
	bool operator <(arr y)const
	{
		return 1;
	}
};
//typedef int arr[4][4];
arr a[5]={
	{1,2,3,4, 6,5,4,3, 0,0,0,0, 1,1,1,1},
	{1,2,3,4, 6,5,4,3, 0,0,0,0, 7,7,7,7}
};
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	for (int k=0;k<=1;++k){
		for (int i=0;i<4;++i){
			for (int j=0;j<4;++j)
				printf("%d ",a[k].a[i][j]);
			printf("\n");
		}
		printf("\n");
	}
	system("pause");
	return 0;
}


