#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<map>
using namespace std;
template <class T>
struct Block{
	static const int L=2000005;
	static T Pool[L*4],*cur;
	T *NewT(int len){cur+=len;return cur-len;}
	T *son[7];
	void clear(){memset(son,0,sizeof(son));}
	Block(){clear();}
	T &operator [](int x){
		if (!son[x>>2])son[x>>2]=NewT(4);
		return son[x>>2][x&3];
	}
};
template <class T>T Block<T>::Pool[Block<T>::L*4];
template <class T>T* Block<T>::cur=Block<T>::Pool;
Block<int> a[105];
int main(){
	//T2.insert("zzy",3);
	//printf("%d\n",T2.find("zzy",2));
	//printf("%d\n",T2.find("zy",2));
	for (int i=1;i<=10;++i)a[i][0]=0;
	system("pause");
	return 0;
}


