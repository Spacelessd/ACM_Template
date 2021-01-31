#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#define N 10000005
template<class T>
struct Vector{
	typedef T* it;
	it Mem,End,MemEnd;
	void Grow(){
		int s=MemEnd-Mem;it NewMem=new T[s*2];
		memcpy(NewMem,Mem,sizeof(T)*s);delete[] Mem;
		Mem=NewMem;End=Mem+s;MemEnd=Mem+s*2;
	}
	void Shrink(){
		int s=MemEnd-Mem,l=End-Mem;it NewMem=new T[s>>1];
		memcpy(NewMem,Mem,sizeof(T)*(s>>1));delete[] Mem;
		Mem=NewMem;End=Mem+l;MemEnd=Mem+(s>>1);
	}
	Vector(){Mem=new T[1];End=Mem;MemEnd=Mem+1;}
	void push_back(const T &x){
		if (End==MemEnd)Grow();*(End++)=x;
	}
	void pop_back(){
		--End;if (End-Mem<(MemEnd-Mem)>>2)Shrink();
	}
	it begin(){return Mem;}
	it end(){return End;}
	int size(){return End-Mem;}
	int capacity(){return MemEnd-Mem;}
	T& operator [](int id){return Mem[id];}
};
Vector<int> V;
vector<int> v;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n=10,t1;
	/*for (int i=1;i<=50;++i){
		V.push_back(1);
		printf("+%d %d\n",i,V.capacity());
	}
	for (int i=1;i<=50;++i){
		V.pop_back();
		printf("-%d %d\n",i,V.capacity());
	}*/
	t1=clock();
	for (int i=1;i<=N;++i)v.push_back(i);
	//for (int i=1;i<=n;++i)printf("%d\n",v[i-1]);
	printf("time=%d\n",clock()-t1);
	t1=clock();
	for (int i=1;i<=N;++i)V.push_back(i);
	//for (int i=1;i<=n;++i)printf("%d\n",V[i-1]);
	printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


