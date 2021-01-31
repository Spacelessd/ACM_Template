#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 100005
void dfs(int dep){
	if (dep%10000==0)printf("%d\n",dep);
	if (dep>=2000000)return;
	dfs(dep+1);
}
template<class T>
void Calldfs(T *p,int a)
{
	#define stack_size 10000005
	static int Stack[stack_size],bak;
	__asm__ __volatile__
	(
		"mov %%esp,%0\n"
		"mov %1,%%esp\n"
		:"=g"(bak)
		:"g"(Stack+stack_size-1)
		:
	);
	(*p)(a);
	__asm__ __volatile__
	(
		"mov %0,%%esp\n"
		:
		:"g"(bak)
		:
	);
	#undef stack_size
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	Calldfs(dfs,1);
	//dfs(1);
	system("pause");for (;;);
	return 0;
}


