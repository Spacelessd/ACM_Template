#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 100005
#define Dep 20
int f[N][Dep+1],M[N],n;
inline int min(int x,int y){return x<y?x:y;}
void BuildST(){
	int i,j;
	for(M[0]=-1,i=1;i<=n;++i)
		M[i]=!(i&(i-1))?M[i-1]+1:M[i-1];
	for (j=1;j<=Dep;++j)
		for (i=1;i<=n-(1<<j)+1;++i)f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
}
inline int Qmin(int x,int y){
	if (x>y){int t=x;x=y;y=t;}
	int z=M[y-x+1],Min=min(f[x][z],f[y-(1<<z)+1][z]);
	return Min;
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int m,x,y;scanf("%d",&n);
	for (int i=1;i<=n;++i)scanf("%d",&f[i][0]);
	scanf("%d",&m);
	for (int i=1;i<=m;++i)scanf("%d%d",&x,&y),printf("%d\n",Qmin(x,y));
	system("pause");for (;;);
	return 0;
}


