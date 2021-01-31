#include<cstdio>
#include<ctime>
#include<algorithm>
using namespace std;
const int mod=1000000007;
inline int MOD(int a,int b)  //a*b%mod
{
	int div, res;
	asm("mul %3; div %4": "=a" (div), "=&d" (res): "a" (a), "r" (b), "r" (mod));
	return res;
}
int main()
{
	printf("%d\n",MOD(10000000,10000000));
	system("pause");for(;;);
}


