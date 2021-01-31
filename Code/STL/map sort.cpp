#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<map>
using namespace std;
map<int,int> a;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1=clock();
	int n=1000000;
	for (int i=1;i<=n;++i)a.insert(make_pair(i,0));
	//for (map<int,int>::iterator zzy=a.begin();zzy!=a.end();++zzy)
	//	printf("%d\n",zzy->first);
	printf("%d\n",clock()-t1);
	system("pause");
	return 0;
}


