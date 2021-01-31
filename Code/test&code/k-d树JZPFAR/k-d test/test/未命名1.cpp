#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<queue>

#define maxn 100010
int n,i;
std::priority_queue<int> a;
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//scanf("%d",&n);
	n=1000000;
	for (i=1;i<=n;++i)a.push(rand());
	for (i=1;i<=n;++i)printf("%d\n",a.top()),a.pop();
	system("pause");
	return 0;
}






