#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define Size 2005
typedef long long ll;
const ll P=1000000007LL;
size_t size;
struct matrix{
	ll key[Size][Size];
	void clear(){
		//for (int i=0;i<size;++i)
		//	for (int j=0;j<size;++j)key[i][j]=0;
		memset(key,0,sizeof(key));
	}
	void print(int n){
		for (int i=0;i<size;++i)
			for (int j=0;j<size;++j)
				printf("%d%c",(int)key[i][j],j+1==size?'\n':' ');
	}
};
const matrix& operator +(const matrix &a,const matrix &b){
	static matrix T;T.clear();
	for (int i=0;i<size;++i)
		for (int j=0;j<size;++j)T.key[i][j]=(a.key[i][j]+b.key[i][j])%P;
	return T;
}
const matrix& operator *(const matrix &a,const matrix &b){
	static matrix T;T.clear();
	for (int k=0;k<size;++k)
		for (int i=0;i<size;++i)
			for (int j=0;j<size;++j)
				T.key[i][j]+=a.key[i][k]*b.key[k][j];
	for (int i=0;i<size;++i)
		for (int j=0;j<size;++j)T.key[i][j]=T.key[i][j]%P;
	return T;
}
matrix a,b,c;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d",&size);
	int t1=clock();srand(time(0));
	for (int i=0;i<size;++i)
		for (int j=0;j<size;++j)
			a.key[i][j]=rand()*rand(),
			b.key[i][j]=rand()*rand();
	c=a*b;//c.print(size);
	printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


