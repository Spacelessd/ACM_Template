#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<iterator>
#include<map>
using namespace std;
#define N 100005
struct zzy{
	int x,y;
	zzy():x(0),y(0){}
	zzy(int _x,int _y):x(_x),y(_y){}
	bool operator <(const zzy &y)const
	{
		return x<y.x;
	}
};
map<zzy,int> a;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	zzy tmp;
	a.insert(make_pair(tmp,1));
	system("pause");
	return 0;
}


