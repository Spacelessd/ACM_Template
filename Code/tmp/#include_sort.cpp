#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<set>
#include<map>
#include<string>
#include<iostream>
using namespace std;
#define N 100005
map<string,int> a;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1=clock();
	string s;
	while (cin>>s){
		a.insert(make_pair(s,0));
	}
	printf("-------------------\n\n");
	for (map<string,int>::iterator zzy=a.begin();zzy!=a.end();++zzy)
		cout<<zzy->first<<endl;
	printf("%d\n",clock()-t1);
	system("pause");
	return 0;
}


