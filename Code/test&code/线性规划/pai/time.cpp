#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
int n,i,ans;
long double x,y,z;
int main(){
	srand(time(0));
	n=100000000;x=rand()*1.07;y=rand()*1.03;
	int t1=clock();
	for (i=1;i<=n;i++)
	{
        int t1=clock();
        z=x/y;
        ans+=clock()-t1;
    }
	printf("%d\n",clock()-t1);
	printf("%d\n",ans);
	system("pause");
	return 0;
}
