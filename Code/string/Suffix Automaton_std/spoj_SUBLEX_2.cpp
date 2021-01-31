#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
const int NMax=90000;
const int SMax=26;
int N;
char A[NMax+1];
int Par[NMax*2],Lth[NMax*2],Trans[NMax*2][SMax+1];
unsigned int Ways[NMax*2];
char Transchar[NMax*2];
int ntop,curnode;
void build(){
	ntop=0;
	memset(Trans,0xff,N*2*sizeof(Trans[0]));
	Par[ntop]=-1;Lth[ntop]=0;
	curnode=ntop++;
	for (int i=0;i<N;i++){
		int x=A[i]-'a';
		int p=curnode;
		Par[ntop]=-1;Lth[ntop]=i+1;
		curnode=ntop++;
		for (;p!=-1 && Trans[p][x]==-1;p=Par[p])Trans[p][x]=curnode;
		if (p==-1)Par[curnode]=0;
		else{
			int q=Trans[p][x];
			if (Lth[q]==Lth[p]+1)Par[curnode]=q;
			else{
				Par[ntop]=Par[q];Lth[ntop]=Lth[p]+1;
				memcpy(Trans[ntop],Trans[q],sizeof(Trans[ntop]));
				int r=ntop++;
				Par[curnode]=Par[q]=r;
				for (;p!=-1 && Trans[p][x]==q;p=Par[p])Trans[p][x]=r;
			}
		}
	}
}
int Q[NMax*2];
int cnt[NMax+1];
void calc(){
	for (int i=0;i<=N;i++)cnt[i]=0;
	for (int i=0;i<ntop;i++)cnt[Lth[i]]++;
	for (int i=1;i<=N;i++)cnt[i]+=cnt[i-1];
	for (int i=0;i<ntop;i++)Q[--cnt[Lth[i]]]=i;
	for (int i=ntop-1;i>=0;i--){
		int p=Q[i];
		Ways[p]=1;
		int k=0;
		for (int j=0;j<SMax;j++)
			if (Trans[p][j]!=-1){
				Ways[p]+=Ways[Trans[p][j]];
				Trans[p][k++]=Trans[p][j];
				Transchar[Trans[p][j]]='a'+j;
			}
		Trans[p][k]=-1;
	}
}
int main()
{
	scanf("%s",A);
	N=strlen(A);
	build();
	calc();
	int TT;
	scanf("%d",&TT);
	static char buf[NMax+1];
	while (TT--){
		unsigned int x;
		scanf("%u",&x);
		if (x>=Ways[0]){
			puts("WRONG");
			continue;
		}
		char *pt=buf;
		for (int p=0;x;){
			x--;
			for (int i=0;Trans[p][i]!=-1;i++){
				int q=Trans[p][i];
				if (Ways[q]<=x)x-=Ways[q];
				else{
					p=q;
					*(pt++)=Transchar[q];
					break;
				}
			}
		}
		pt[0]=0;
		puts(buf);
	}
	return 0;
}


