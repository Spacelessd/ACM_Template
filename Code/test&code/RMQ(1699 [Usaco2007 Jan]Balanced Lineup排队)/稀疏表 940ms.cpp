#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 50005
#define Dep 15
int fmin[N][Dep+1],fmax[N][Dep+1],M[N],n;
inline int max(int x,int y){int m=(x-y)>>31;return y&m|x&~m;}
inline int min(int x,int y){int m=(y-x)>>31;return y&m|x&~m;}
void BuildST(){
	int i,j;
	for(M[0]=-1,i=1;i<=n;++i)
		M[i]=!(i&(i-1))?M[i-1]+1:M[i-1];
	for (j=1;j<=Dep;++j)
		for (i=1;i<=n-(1<<j)+1;++i)fmin[i][j]=min(fmin[i][j-1],fmin[i+(1<<(j-1))][j-1]),
								   fmax[i][j]=max(fmax[i][j-1],fmax[i+(1<<(j-1))][j-1]);
}
inline int Q(int x,int y){
	if (x>y){int t=x;x=y;y=t;}
	int z=M[y-x+1],Min=min(fmin[x][z],fmin[y-(1<<z)+1][z]),Max=max(fmax[x][z],fmax[y-(1<<z)+1][z]);
	return Max-Min;
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int m,x,y;scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i)scanf("%d",&fmax[i][0]),fmin[i][0]=fmax[i][0];
	BuildST();
	for (int i=1;i<=m;++i)scanf("%d%d",&x,&y),printf("%d\n",Q(x,y));
	system("pause");for (;;);
	return 0;
}


