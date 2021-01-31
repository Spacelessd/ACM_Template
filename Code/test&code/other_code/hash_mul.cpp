#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
template<class T>
struct Gethash{
	size_t operator ()(const T &x)const{return x;}
};
const int mask=(1<<30)-1;
template<> size_t Gethash<int>::operator ()(const int &x)const{
	return (long long)663572447*x&mask>>10;
	//return x;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	Gethash<int> h;
	for (int i=1;i<=1000;++i)printf("%d\n",h(i));
	system("pause");for (;;);
	return 0;
}



