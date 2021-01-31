#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define oo (1<<28)
#define maxn 3005
int mx[maxn],my[maxn],lx[maxn],ly[maxn],opp[maxn];
int w[maxn][maxn];
int n,i,j,x,y,z,ans;
inline int min(int x,int y){return x<y?x:y;}
bool Extend_path(int u){
	int v;mx[u]=1;
	for (v=1;v<=n;++v)
		if (!my[v]&&lx[u]+ly[v]==w[u][v]){
			my[v]=1;
			if (!opp[v]||Extend_path(opp[v])){
				opp[v]=u;return 1;
			}
		}
	return 0;
}
void Modify(){
	int i,j,delta=oo;
	for (i=1;i<=n;i++)if (mx[i]) 
		for (j=1;j<=n;j++)if (!my[j])delta=min(delta,lx[i]+ly[j]-w[i][j]);
	for (i=1;i<=n;i++)if (mx[i])lx[i]-=delta;
	for (i=1;i<=n;i++)if (my[i])ly[i]+=delta;
}
void KM(){
	int i,j;
	memset(opp,0,sizeof(int)*(n+5));
	for (i=1;i<=n;i++){
		lx[i]=-oo;
		for (j=1;j<=n;j++)lx[i]=lx[i]>w[i][j]?lx[i]:w[i][j];
	}
	memset(ly,0,sizeof(int)*(n+5));
	for (i=1;i<=n;i++)
		while (1){
			memset(mx,0,sizeof(int)*(n+5));
			memset(my,0,sizeof(int)*(n+5));
			if (Extend_path(i))break;
			Modify();
		}
	ans=0;
	for (i=1;i<=n;i++)ans+=lx[i];
	for (i=1;i<=n;i++)ans+=ly[i];
}
int main()
{
	
	int n1,n2,m;system("pause");
	freopen("1.in","r",stdin);
	//freopen("5.out","w",stdout);
	scanf("%d%d%d",&n1,&n2,&m);
	if (n1>n)n=n1;
	if (n2>n)n=n2;
	printf("%d\n",n);
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)w[i][j]=0;
	for (i=1;i<=m;i++)scanf("%d%d",&x,&y),w[x][y]=1;
	KM();
	printf("%d\n",ans);
	system("pause");
	return 0;
}




