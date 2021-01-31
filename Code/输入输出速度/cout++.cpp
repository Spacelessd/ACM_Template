#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
int n=10000000;
int main()
{
	freopen("1.in","w",stdout);
	srand(time(0));
	int t1=clock();
	std::ios::sync_with_stdio(false);
	cout<<n<<endl;
	for (int i=1;i<=n;++i)cout<<rand()*rand()<<" ";
	cout<<flush;
	fclose(stdout);
	freopen("cout++.out","w",stdout);
	cout<<"time="<<clock()-t1<<endl;
	fclose(stdout);
	//system("pause");
	return 0;
}


