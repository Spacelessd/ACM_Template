#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
#define N 1005
struct node{
int key,times;
};
bool operator <(const node &x,const node &y){
	return x.key<y.key;
}
node a[N];
int s[N],f[N][N],from[N][N];
int n;
inline int min(int x,int y){return x<y?x:y;}
void print(int x,int y){
	if (x>y){printf("#");return;}
	printf("%d",a[from[x][y]].key);
	if (x==y)return;
	printf("(");
	print(x,from[x][y]-1);
	printf(",");
	print(from[x][y]+1,y);
	printf(")");
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;++i)scanf("%d%d",&a[i].key,&a[i].times);
	std::sort(a+1,a+1+n);
	s[0]=0; for (int i=1;i<=n;++i)s[i]=s[i-1]+a[i].times;
	memset(f,33,sizeof(f));
	for (int i=1;i<=n;++i)f[i][i]=a[i].times,from[i][i]=i;
	for (int i=1;i<=n+1;++i)f[i][i-1]=0;
	for (int j=1;j<n;++j)
		for (int i=1;i<=n-j;++i){
			//int begin=i,end=i+j;
			int begin=from[i][i+j-1],end=from[i+1][i+j];
			for (int k=begin;k<=end;++k){
				int tmp=a[k].times+f[i][k-1]+s[k-1]-s[i-1]+f[k+1][i+j]+s[i+j]-s[k];
				if (tmp<f[i][i+j])f[i][i+j]=tmp,from[i][i+j]=k;
			}
		}
	printf("SSL = %d\n",f[1][n]);
	print(1,n);printf("\n");
	/*for (int i=1;i<=n;++i){
		for (int j=1;j<=n;++j)printf("%d ",from[i][j]);
		printf("\n");
	}*/
	system("pause");for (;;);
	return 0;
}


