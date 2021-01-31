#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<queue>
using namespace std;
priority_queue<int> a;
struct node{int x,y;};
template<class T>
struct cmp{
	bool operator ()(T x,T y){
		return 1;
	}
};
priority_queue<node,vector<node>,cmp<node> > Q;
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	srand(time(0));
	int t1=clock();
	int n=1000000;
	for (int i=1;i<=n;++i)a.push(rand()*32768+rand());
	for (int i=1;i<=n;++i)a.pop();
	printf("%d\n",clock()-t1);
	system("pause");
	return 0;
}


