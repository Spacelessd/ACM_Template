#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define oo (1<<28)
#define maxn 1010
#define maxm 100010
int son[maxn],mx[maxn],my[maxn],lx[maxn],ly[maxn],opp[maxn];
int w[maxn][maxn];
int n,m,i,j,x,y,z,ans;
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
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)w[i][j]=-oo;
	for (i=1;i<=m;i++)scanf("%d%d%d",&x,&y,&z),w[x][y]=z;
	KM();
	printf("%d\n",ans);
	system("pause");
	return 0;
}














