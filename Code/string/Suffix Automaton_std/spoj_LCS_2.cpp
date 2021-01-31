#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
const int NMax=250000;
const int SMax=26;
int N,M;
char A[NMax+1],B[NMax+1];
int Lth[NMax*2],Par[NMax*2],Trans[NMax*2][SMax];
int curnode,ntop;
void build(){
	memset(Trans,0xff,N*2*sizeof(Trans[0]));
	ntop=0;
	curnode=ntop++;
	Lth[0]=0;Par[0]=-1;
	for (int i=0;i<N;i++){
		int x=A[i]-'a';
		int p=curnode;
		Lth[ntop]=i+1;
		curnode=ntop++;
		for (;p!=-1 && Trans[p][x]==-1;p=Par[p])Trans[p][x]=curnode;
		if (p==-1)Par[curnode]=0;
		else{
			int q=Trans[p][x];
			if (Lth[q]==Lth[p]+1)Par[curnode]=q;
			else{
				Lth[ntop]=Lth[p]+1;Par[ntop]=Par[q];
				memcpy(Trans[ntop],Trans[q],sizeof(Trans[ntop]));
				int r=ntop++;
				Par[q]=Par[curnode]=r;
				for (;p!=-1 && Trans[p][x]==q;p=Par[p])Trans[p][x]=r;
			}
		}
	}
}
int main()
{
	scanf("%s%s",A,B);
	N=strlen(A);M=strlen(B);
	build();
	int p=0;
	int ret=0;
	for (int i=0,l=0;i<M;i++){
		int x=B[i]-'a';
		while (Par[p]!=-1 && Trans[p][x]==-1)p=Par[p],l=Lth[p];
		if (Trans[p][x]!=-1){
			if (ret==l)ret++;
			l++;
			p=Trans[p][x];
		}else p=0,l=0;
	}
	printf("%d\n",ret);
	return 0;
}


