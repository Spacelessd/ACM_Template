#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<set>
#include<map>
using namespace std;
multiset<int> a;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	/*a.clear();
	a.insert(3);a.insert(3);a.erase(3);
	for (multiset<int>::iterator zzy=a.begin();zzy!=a.end();++zzy)
		printf("%d\n",*zzy);
	*/
	a.clear();
	int t1=clock();
	int n=1000000;
	for (int i=1;i<=n;++i)a.insert(i);
	//for (multiset<int>::iterator zzy=a.begin();zzy!=a.end();++zzy)
	//	printf("%d\n",*zzy);
	printf("%d\n",clock()-t1);
	system("pause");
	return 0;
}


