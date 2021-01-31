#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<iostream>
using namespace std;
#define ll long long
#define maxn 60
const int M=maxn*maxn;
const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};
int n,m;
ll ans;
char ch,c[maxn][maxn];
ll d[maxn][maxn][maxn][maxn],a[21][21][maxn][maxn];
int xL[maxn*maxn],yL[maxn*maxn],sL,xG[maxn*maxn],yG[maxn*maxn],sG,xZ[maxn*maxn],yZ[maxn*maxn],sZ;
ll gcd(ll a,ll b){
	if (!b) return a;
	return gcd(b,a%b);
	}
int qx[M],qy[M];
ll D[maxn][maxn];
void bfs(int xx,int yy){
	int h=1,t=1;
	memset(D,10,sizeof(D));
	qx[h]=xx;qy[h]=yy;D[xx][yy]=0;
	while (h<=t){
		int x=qx[h],y=qy[h];
		ll dist=D[x][y]+1;
		for (int i=0;i<4;++i){
			int X=x+dx[i],Y=y+dy[i];
			if (c[X][Y]!='#'&&dist<D[X][Y]){
				D[X][Y]=dist;
				++t;qx[t]=X;qy[t]=Y;
			}
		}
		++h;
	}
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)d[xx][yy][i][j]=D[i][j];
}
int inq[maxn][maxn];
void spfa(int x,int y){
	int h=0,t=0,i,j;
	for (i=1;i<=n;++i)
		for (j=1;j<=m;++j){
			D[i][j]=d[xG[x]][yG[x]][i][j]+d[xZ[y]][yZ[y]][i][j];inq[i][j]=1;
			t=t<M?t+1:1;qx[t]=i;qy[t]=j;
		}
	while (h!=t){
		h=h<M?h+1:1;
		int x=qx[h],y=qy[h];
		ll dist=D[x][y]+1;
		inq[x][y]=0;
		for (int i=0;i<4;++i){
			int X=x+dx[i],Y=y+dy[i];
			if (c[X][Y]!='#'&&dist<D[X][Y]){
				D[X][Y]=dist;
				if (!inq[X][Y]){
					inq[X][Y]=1;
					t=t<M?t+1:1;qx[t]=X;qy[t]=Y;
				}
			}
		}
	}
	for (i=1;i<=n;++i)
		for (j=1;j<=m;++j)a[x][y][i][j]=D[i][j];
}
int main()
{
	int T,i,j;
	//int t1=clock();
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	scanf("%d",&T);
	while (T--){
		ans=0;sL=sG=sZ=0;
		scanf("%d%d",&n,&m);
		for (i=0;i<=n+1;++i)
			for (j=0;j<=m+1;++j)c[i][j]='#';
		for (i=1;i<=n;++i){
			scanf("%s",c[i]+1);c[i][m+1]='#';c[i][m+2]=0;
		}
		//memset(d,10,sizeof(d));
		//memset(a,10,sizeof(a));
		//printf("%d\n",clock()-t1);
		for (i=1;i<=n;++i)
			for (j=1;j<=m;++j)
			if (c[i][j]!='#'){
				bfs(i,j);
			}
		//printf("%d\n",clock()-t1);
		for (i=1;i<=n;++i)
			for (j=1;j<=m;++j){
			if (c[i][j]=='L'){++sL;xL[sL]=i;yL[sL]=j;}
			if (c[i][j]=='G'){++sG;xG[sG]=i;yG[sG]=j;}
			if (c[i][j]=='Z'){++sZ;xZ[sZ]=i;yZ[sZ]=j;}
			}
		for (int i1=1;i1<=sG;++i1)
			for (int j1=1;j1<=sZ;++j1){
				spfa(i1,j1);
			}
		//printf("%d\n",clock()-t1);
		for (int i1=1;i1<=sG;++i1)
			for (int j1=1;j1<=sZ;++j1)
				for (i=1;i<=n;++i)
					for (j=1;j<=m;++j)
					if (c[i][j]=='L'){
						ans+=a[i1][j1][i][j];
						//printf("%d %d %d %d %d %d  ans=%d\n",i,j,xG[i1],yG[i1],xZ[j1],yZ[j1],a[i1][j1][i][j]);
					}
		//printf("%d\n",ans);
		ll div=sL*sG*sZ;
		if (ans>1000000000000LL||ans==0||div==0){
			printf("0/0\n");continue;
		}
		ll mod=gcd(ans,div);
		//printf("%d/%d\n",ans/mod,div/mod);
		cout<<ans/mod<<"/"<<div/mod<<endl;
		//printf("%d\n",clock()-t1);
	}
	//system("pause");for (;;);
	return 0;
}














