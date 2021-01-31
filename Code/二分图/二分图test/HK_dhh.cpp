#include<cstdio>
#include<cstring>
#define N 50005
int n,m,k,x,y,l,f[N*10];
int dx[N],dy[N],px[N],py[N];
int son[N],next[N*3],ed[N*3];
bool build()
{
	int h=0,t=0,flag=0; memset(dx,0,sizeof(dx)); memset(dy,0,sizeof(dy));
	for (int i=1;i<=n;i++) if (!px[i]) f[++t]=i;
	while (h<t){
		int i=f[++h];
		for (int p=son[i];p;p=next[p]){
			int j=ed[p]; if (dy[j]) continue; dy[j]=dx[i]+1;
			if (!py[j]) flag=1; else dx[f[++t]=py[j]]=dy[j]+1;
			}
		}
	return flag;
}
bool find(int i)
{
	for (int p=son[i];p;p=next[p]){
		int j=ed[p]; if (dy[j]!=dx[i]+1 || !dy[j]) continue;
		dy[j]=0; if (!py[j] || find(py[j])) {py[j]=i,px[i]=j; return 1;}
		}
	return 0;
}
int Hopcroft_Karp()
{
	int ans=0;
	while (build())
		for (int i=1;i<=n;i++) if (!px[i]) ans+=find(i);
	return ans;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for (int i=0;i<k;i++) scanf("%d%d",&x,&y),ed[++l]=y,next[l]=son[x],son[x]=l;
	printf("%d\n",Hopcroft_Karp());
	system("pause");for (;;);
	return 0;
}


