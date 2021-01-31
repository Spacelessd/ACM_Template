#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
template<class T>
struct Gethash{
	size_t operator ()(const T &x)const{return x;}
};
template<> size_t Gethash<char*>::operator ()( char *&const str)const{
	/*const size_t seed=131;size_t hash=0;
	while (*str)hash=hash*seed+*str++;
	return hash;*/
}
Gethash<char*> C;
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	
	system("pause");for (;;);
	return 0;
}


