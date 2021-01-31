#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<vector>
#include<iostream>
using namespace std;
#define rep(i,n) for(int i=0;i<n;++i)
const int inf=~0U>>1;
template<class T>
struct Vector
{
	typedef T* it;
	it Mem,End,MemEnd;
	void Grow()
	{
		int s=MemEnd-Mem;
		it NewMem=new T[s*2];
		memcpy(NewMem,Mem,sizeof(T)*s);
		delete[] Mem;Mem=NewMem;
		MemEnd=Mem+s*2;
		End=Mem+s;
	}
	Vector()
	{
		Mem=new T[1];
		MemEnd=Mem+1;
		End=Mem;
	}
	void Add(const T&a)
	{
		if(End==MemEnd)Grow();
		*(End++)=a;
	}
	it begin(){return Mem;}
	it end(){return End;}
};
int main(int argc,int argv[])
{
	if (argc<=1){
		system("g++ vector_clj.cpp -o vector -O2");
		system("cmd /c start vector.exe 1");
	}
	int time=clock();
	Vector<int> V;
	rep(i,100000000) V.Add(i);
	cout<<clock()-time<<endl;time=clock();
	vector<int> A;
	rep(i,100000000) A.push_back(i);
	cout<<clock()-time<<endl;time=clock();
	system("pause");
	return 0;
}


