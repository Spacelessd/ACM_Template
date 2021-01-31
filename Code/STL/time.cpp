#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
using namespace std;
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n,x,y,z; srand(time(0));
	n=100000000;x=rand();y=rand();
	int t1=clock();
	for (int i=1;i<=n;++i){
		z=x/y;
	}
	printf("%d\n",clock()-t1);
	system("pause");
	return 0;
}


