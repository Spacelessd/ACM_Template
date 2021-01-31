#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 5005
#define M 3005
#define oo (1<<30)
#define rep(i,l,r) for (int i=l;i<=r;++i)
int a[N][M],next[M],n,m;
inline void pivot(int l,int e){
	a[l][e]=-1;int t=M-1;
	rep(i,0,m) if (a[l][i])next[t]=i,t=i; next[t]=-1;
	rep(i,0,n) if (i!=l&&(t=a[i][e])){
		a[i][e]=0;
		for (int j=next[M-1];j!=-1;j=next[j])a[i][j]+=a[l][j]*t;
	}
}
int solve(){
	for (;;){
		int min=oo,l=0,e=0;
		rep(i,1,m) if (a[0][i]>0){e=i;break;}
		if (!e)return a[0][0];
		rep(i,1,n) if (a[i][e]<0&&a[i][0]<min)min=a[i][0],l=i;
		pivot(l,e);
	}
}
int main()
{
	freopen("ditch.in","r",stdin);
	freopen("ditch.out","w",stdout);
	int n,m,x,y,z;scanf("%d%d",&m,&n);
	rep(i,1,m){
		scanf("%d%d%d",&x,&y,&z);
		a[x-1][i]=1,a[y-1][i]=-1;
		a[n*2-4+i][i]=-1,a[n*2-4+i][0]=z;
	}
	rep(i,1,n-2) rep(j,1,m) a[i+n-2][j]=-a[i][j];
	::n=n*2-4+m;::m=m;printf("%d\n",solve());
	//system("pause");
	return 0;
}


