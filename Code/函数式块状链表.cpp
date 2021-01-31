#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#define N 40005
#define Lim 205
int at[N],id[N],BlockPool[N][Lim],Block1=0,n,SqrtN;
struct Block{
	int *blocks[Lim];
	void clear(){
		int *New=BlockPool[Block1++];
		memset(New,-1,sizeof(int)*SqrtN);
		for (int i=0;i<=SqrtN;++i)blocks[i]=New;
	}
	void set(Block &from,int x,int color){
		memcpy(blocks,from.blocks,sizeof(int*)*SqrtN);
		int *New=BlockPool[Block1++];
		memcpy(New,from.blocks[at[x]],sizeof(int)*SqrtN);
		New[id[x]]=color;blocks[at[x]]=New;
	}
	int operator [](int i){
		return blocks[at[i]][id[i]];
	}
};
Block block[N];
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d",&n);
	SqrtN=(int)sqrt(n)+1;
	for (int i=0;i<=n;++i)at[i]=i/SqrtN,id[i]=i%SqrtN;
	block[0].clear();
	for (int i=1;i<=n;++i)block[i].set(block[i-1],i,i);
	int m;scanf("%d",&m);
	for (int i=1;i<=n;++i)printf("%d %d\n",i,block[m][i]);
	system("pause");for (;;);
	return 0;
}


