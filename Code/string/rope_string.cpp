#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<rope.h>
#include<string>
#include<iostream>
using namespace std;
#define N 70005
rope<char> a,b;
//string a,b;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	a="nie";b="ga";
	cout<<a+" "+b<<endl;
	a=a.substr(0,1)+"r"+a.substr(2,1);
	cout<<a<<endl;
	int t1=clock();
	for (int i=1;i<=N;++i)a=a+"w";
	for (int i=1;i<=N;++i){
		a=a.substr(0,N/2)+a.substr(N/2,N-N/2);
		if (i%1000==0)printf("%d\n",i);
	}
	//cout<<a<<endl;
	printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


