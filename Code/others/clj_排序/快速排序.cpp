#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#define rep(i,n) for(int i=0;i<n;i++)
const int inf = ~0U >> 1, maxn = 10000010;
using namespace std;
int A[maxn];
void Sort(int l, int r)
{
	if(r - l < 2)return;
	int h = l, x = A[l+rand()%(r-l+1)];
	for(int i = l; i <= r; i++)if(A[i] < x)
		{
			int t = A[i];
			A[i] = A[h];
			A[h] = t;
			h++;
		}
	Sort(l, h - 1);
	Sort(h + 1, r);
}
int main()
{
	int n;
	//cin >> n;
	//rep(i, n)scanf("%d", A + i);
	srand(time(0));int t1=clock();
	n=10000000;
	rep(i,n)A[i]=(rand()<<16)+rand();
	//sort(0, n - 1);
	sort(A,A+n);
	printf("%d\n",clock()-t1);
	system("pause");
	return 0;
}


