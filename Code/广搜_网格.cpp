#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<iostream>
using namespace std;
#define ll long long
#define N 60
const int M=N*N;
const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};
int n,m;ll ans;
char ch,c[N][N];
ll d[N][N][N][N],a[21][21][N][N];
int xL[N*N],yL[N*N],sL,xG[N*N],yG[N*N],sG,xZ[N*N],yZ[N*N],sZ;
ll gcd(ll a,ll b){
	if (!b) return a;
	return gcd(b,a%b);
}
int qx[M],qy[M];
ll D[N][N];
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
int inq[N][N];
void Q(int s,int t){
	int i=s,j=t;
	ll p,m=D[qx[(i+j)>>1]][qy[(i+j)>>1]];
	do {
	while (D[qx[i]][qy[i]]<m) ++i;
	while (D[qx[j]][qy[j]]>m) --j;
	if (i<=j){
		p=qx[i]; qx[i]=qx[j]; qx[j]=p;
		p=qy[i]; qy[i]=qy[j]; qy[j]=p;
		++i; --j;
	}
	}while (i<=j);
	if (i<t) Q(i,t);
	if (s<j) Q(s,j);
}
void spfa(int x,int y){
	int h=0,t=0,i,j;
	for (i=1;i<=n;++i)
		for (j=1;j<=m;++j)
		if (c[i][j]!='#'){
			D[i][j]=d[xG[x]][yG[x]][i][j]+d[xZ[y]][yZ[y]][i][j];inq[i][j]=1;
			t=t<M?t+1:1;qx[t]=i;qy[t]=j;
		}
	Q(1,t);
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
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int T;scanf("%d",&T);
	while (T--){
		ans=0;sL=sG=sZ=0;
		scanf("%d%d",&n,&m);
		for (int i=0;i<=n+1;++i)
			for (int j=0;j<=m+1;++j)c[i][j]='#';
		for (int i=1;i<=n;++i){
			scanf("%s",c[i]+1);c[i][m+1]='#';c[i][m+2]=0;
		}
		for (int i=1;i<=n;++i)
			for (int j=1;j<=m;++j)
			if (c[i][j]!='#')bfs(i,j);
		for (int i=1;i<=n;++i)
			for (int j=1;j<=m;++j){
				if (c[i][j]=='L'){++sL;xL[sL]=i;yL[sL]=j;}
				if (c[i][j]=='G'){++sG;xG[sG]=i;yG[sG]=j;}
				if (c[i][j]=='Z'){++sZ;xZ[sZ]=i;yZ[sZ]=j;}
			}
		for (int i1=1;i1<=sG;++i1)
			for (int j1=1;j1<=sZ;++j1)spfa(i1,j1);
		for (int i1=1;i1<=sG;++i1)
			for (int j1=1;j1<=sZ;++j1)
				for (int i=1;i<=n;++i)
					for (int j=1;j<=m;++j)
						if (c[i][j]=='L')ans+=a[i1][j1][i][j];
		ll div=sL*sG*sZ;
		if (ans>1000000000000LL||ans==0||div==0){
			printf("0/0\n");continue;
		}
		ll mod=gcd(ans,div);
		cout<<ans/mod<<"/"<<div/mod<<endl;
	}
	system("pause");for (;;);
	return 0;
}


