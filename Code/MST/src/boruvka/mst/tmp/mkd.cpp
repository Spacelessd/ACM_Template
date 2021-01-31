#include <cstring>
#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;

int n,m;

int main()
{
	srand(time(0));
	freopen("road8.in","w",stdout);
	n=100000; m=4000000;
	printf("%d %d\n",n,m);
	for (int i=1; i<=n; i++) printf("%d ", rand()%10);
	printf("\n");
	for (int i=1; i<n; i++)
		printf("%d %d %d\n",rand()%i+1,i+1,rand()%1000+20);
	for (int i=n; i<=m; i++)
	{
		int x=rand()%n+1,y=rand()%n+1;
		while (y==x) y=rand()%n+1;
		printf("%d %d %d\n",x,y,rand()%1000+20);
	}
}
