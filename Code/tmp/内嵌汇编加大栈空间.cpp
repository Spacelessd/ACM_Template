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
#define stack_size 10000005
int Stack[stack_size],bak;
void Calldfs(void (*p)(int),int a)
{
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


