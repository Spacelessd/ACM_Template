#include<cstdio>
#include<iostream>
using namespace std;
int main()
{
	freopen("1.in","w",stdout);
	srand(time(0));
	int n=500000; printf("%d\n",n);
	for (int i=1;i<=n;i++){
		int z=rand()%2; char ch;
		if (z) ch='+'; else ch='?';
		int x=rand(),y=rand();
		if (x>y) {int t=x;x=y;y=t;}
		printf("%c %d %d\n",ch,x,y);
		}
	return 0;
}
