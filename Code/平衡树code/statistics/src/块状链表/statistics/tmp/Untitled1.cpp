#include<stdio.h>
struct A{
struct T{
	int *a;
	T(int len){a=new int[len];}
};
void f(){
	T *pt;
	pt=new T(10);
}
};
A a;
int main(){
	a.f();
	for (;;);
}
