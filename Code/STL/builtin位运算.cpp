#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 10000000
typedef long long ll;
inline int count_bits(int x){
	x=(x&0x55555555)+((x&0xaaaaaaaa)>>1);
	x=(x&0x33333333)+((x&0xcccccccc)>>2);
	x=(x&0x0f0f0f0f)+((x&0xf0f0f0f0)>>4);
	x=(x&0x00ff00ff)+((x&0xff00ff00)>>8);
	x=(x&0x0000ffff)+((x&0xffff0000)>>16);
	return x;
}
inline int count_bits(ll x){
	x=(x&0x5555555555555555LL)+((x&0xaaaaaaaaaaaaaaaaLL)>>1);
	x=(x&0x3333333333333333LL)+((x&0xccccccccccccccccLL)>>2);
	x=(x&0x0f0f0f0f0f0f0f0fLL)+((x&0xf0f0f0f0f0f0f0f0LL)>>4);
	x=(x&0x00ff00ff00ff00ffLL)+((x&0xff00ff00ff00ff00LL)>>8);
	x=(x&0x0000ffff0000ffffLL)+((x&0xffff0000ffff0000LL)>>16);
	x=(x&0x00000000ffffffffLL)+((x&0xffffffff00000000LL)>>32);
	return x;
}
int reverse_bits(int x){
	x=((x>>1)&0x55555555)|((x<<1)&0xaaaaaaaa);
	x=((x>>2)&0x33333333)|((x<<2)&0xcccccccc);
	x=((x>>4)&0x0f0f0f0f)|((x<<4)&0xf0f0f0f0);
	x=((x>>8)&0x00ff00ff)|((x<<8)&0xff00ff00);
	x=((x>>16)&0x0000ffff)|((x<<16)&0xffff0000);
	return x;
}
ll reverse_bits(ll x){
	x=((x>>1)&0x5555555555555555LL)|((x<<1)&0xaaaaaaaaaaaaaaaaLL);
	x=((x>>2)&0x3333333333333333LL)|((x<<2)&0xccccccccccccccccLL);
	x=((x>>4)&0x0f0f0f0f0f0f0f0fLL)|((x<<4)&0xf0f0f0f0f0f0f0f0LL);
	x=((x>>8)&0x00ff00ff00ff00ffLL)|((x<<8)&0xff00ff00ff00ff00LL);
	x=((x>>16)&0x0000ffff0000ffffLL)|((x<<16)&0xffff0000ffff0000LL);
	x=((x>>32)&0x00000000ffffffffLL)|((x<<32)&0xffffffff00000000LL);
	return x;
}
unsigned popcount(unsigned x){
	x=(x&0x55555555)+((x>>1)&0x55555555);
	x=(x&0x33333333)+((x>>2)&0x33333333);
	x=(x&0x0F0F0F0F)+((x>>4)&0x0F0F0F0F);
	x=(x&0x00FF00FF)+((x>>8)&0x00FF00FF);
	x=(x&0x0000FFFF)+((x>>16)&0x0000FFFF);
	return x;
}
void test(unsigned (*p)(unsigned)){
	int t1=clock();
	for (int i=0;i<N;++i)(*p)(645675474);
	printf("time=%d\n",clock()-t1);
}
void test1(int (*p)(int)){
	int t1=clock();
	for (int i=0;i<N;++i)(*p)(645675474);
	printf("time=%d\n",clock()-t1);
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	printf("%d\n",__builtin_clz(1));  //最左边0的个数 
	printf("%d\n",__builtin_ctz(1<<1));  //最右边0的个数 
	printf("%d\n",__builtin_popcount(77));  //1的个数 
	printf("%d\n",popcount(77));  //1的个数 
	//test1(__builtin_clz);
	//test1(__builtin_ctz);
	//test1(__builtin_popcount);
	test(popcount);
	system("pause");for (;;);
	return 0;
}


