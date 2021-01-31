#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define N 100005
int Pool[N*15*7],*cur=Pool;
inline int *Newint(int len){cur+=len;return cur-len;}
struct Hash{
	int *son[7];
	int &operator [](int x){
		if (!son[x>>2])son[x>>2]=Newint(4);
		return son[x>>2][x&3];
	}
	bool find(int x){return son[x&3];}
};
Hash c[N*15];
int main(){
	system("pause");
	return 0;
}


