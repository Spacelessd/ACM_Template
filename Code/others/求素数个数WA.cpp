#include<iostream>
#include<math.h>
#include<windows.h>
using namespace std;
const   unsigned   default_n = 2000000000;
const   int   maxlen = 1000;

int   primes[maxlen];
int   len;
int   sum;
unsigned   int   n;
int   m = 7;
int   Q = 1;
int   phiQ = 1;
int   *v;

bool   string2int(unsigned   int   &n, char   *s);
void   init(void);
unsigned   int   phi(unsigned   int   x, int   a);

int   main()
{

	char   number_string[80];
	unsigned   int   time;

	cout << "calc   pi(n)\n";
	cout << "n(default   =   " << default_n << ")   =   ";
	cin.get(number_string, 80);
	if(!string2int(n, number_string))n = default_n;

	time = GetTickCount();
	init();
	//phi(n,len)表示0-n与prime[0--len]互质，但是有多加部分，所以要-sum;另phi不包含prime[0--len]所以要+len
	int   num = (int)phi(n, len) - sum + len - 1;
	time = GetTickCount() - time;
	GlobalFree(v);
	cout << "pi(n)=" << num << "(" << time << "ms)\n";
	cout << "press   any   key   to   continue...";
	cin.get();
	cin.get();
}

void   init(void)
{
	int   max;
	int   sqrt_max;
	bool   *mark;
	int   i, j;
	int   len2, len3;
	int   s;
	int   sqrt_n;

	sqrt_n = (int)sqrt(n);
	max = (int)pow(n, 2.0 / 3.0);
	sqrt_max = (int)sqrt(max);
	mark = (bool *)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, max);

	//i丛2开始--n^1/3，
	//mark标记0--n^2/3的素数，primes[]保存0-n^1/3的素数
	//len表示0-n^1/3的素数个数
	//筛选法
	for(i = 2, len = 0; i < sqrt_max; i++)
	{
		if(!mark[i])
		{
			j = i * i;
			primes[++len] = i;
			while(j < max)
			{
				mark[j] = true;
				j += i;
			}
		}
	}
	//i从n^1/3开始--n^1/2，
	//j从n^2/3开始，i自增，j自减
	//sum表示0--n^2/3与n^1/3--n^1/2之间素数乘积>n数的个数
	//len2表示0-n^1/2的素数个数
	for(j = max - 1, sum = 0, s = 0, len2 = len; i <= sqrt_n; i++)
	{
		if(!mark[i])
		{
			++len2;
			while((unsigned)i * j > n)
			{
				if(!mark[j--])++s;
			}
			sum += s;
		}
	}

	//i从n^1/2开始--n^2/3，
	//len3表示0-n^2/3的素数个数
	for(len3 = len2; i < max; i++)
	{
		if(!mark[i])++len3;
	}

	//sum采用组合公式
	//求len->len2与len2-len3之间素数的乘积个数
	//即n^1/3--n^1/2与n^1/2--n^2/3之间素数的乘积个数

	sum = (len2 - len) * len3 - sum;
	sum += len * (len - 1) / 2 - len2 * (len2 - 1) / 2;

	//欧拉函数
	//m=7
	//Q=2*3*5*7*11*13*17=510510
	//phiQ=1*2*4*6*10*12*16
	if(m > len)m = len;
	for(i = 1; i <= m; ++i)
	{
		Q *= primes[i];
		phiQ *= primes[i] - 1;
	}
	//v
	v = (int *)GlobalAlloc(GMEM_FIXED, Q * sizeof(int));
	for(i = 0; i < Q; ++i)v[i] = i;
	for(i = 1; i <= m; ++i)
	{
		for(j = Q - 1; j >= 0; --j)
		{
			v[j] -= v[j/primes[i]];
		}
	}

	GlobalFree(mark);
}

bool   string2int(unsigned   int   &n, char   *s)
{
	unsigned   int   val = 0;
	for(int   i = 0; s[i]; ++i)
	{
		if(s[i] > '9' || s[i] < '0')return   false;
		val *= 10;
		val += s[i] - '0';
		if(val > default_n)return   false;
	}
	n = val;
	return   true;
}

//小于x,并且与prime[0]---prime[a]之间的素数互质的数的数目
//并且不包括prime[0]--prime[a]
//递归原理
//phi(x,a)=phi(x,a-1)-phi(x/prime[a],a-1)
//phi(x,a)表示小于x,并且与prime[0]---prime[a]之间的素数互质的数的数目
//phi(x,a-1)表示小于x,并且与prime[0]---prime[a-1]之间的素数互质的数的数目
//phi(x/prime[a],a-1)表示小于x/prime[a],并且与prime[0]---prime[a-1]之间的素数互质的数的数目
//求0--x之间与prime[0]---prime[a]之间的素数互质的数的数目
//我们可以求出0--x之间与prime[0]---prime[a-1]之间的素数互质的数的数目
//这样我们实际上多加了那些0--x之间与prime[0]---prime[a-1]之间的素数互质，但是prime[a]的倍数的数，所以需要减去他们，他们的个数就是phi(x/prime[a],a-1)
unsigned   int   phi(unsigned   int   x, int   a)
{
	if(a == m)
	{
		return   (x / Q) * phiQ + v[x%Q];
	}
	if(x < (unsigned)primes[a])
	{
		return   1;
	}
	return   phi(x, a - 1) - phi(x / primes[a], a - 1);
}


