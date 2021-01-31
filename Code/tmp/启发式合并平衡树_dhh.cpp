#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define N 200005
int f[N],d[N],c[N],sum[N],n,ans=0,l=0;
int data[N+N],next[N+N],ed[N+N],son[N];
int key[N],ran[N],L[N],R[N],size[N],root[N];
void bfs(){
	int h=0,t=1; f[1]=1; d[1]=0;
	memset(c,0,sizeof(c)); c[1]=1;
	while (h<t){
		int i=f[++h];
		for (int p=son[i];p;p=next[p]){
			int j=ed[p]; if (c[j]) continue;
			d[j]=d[i]+data[p]; c[j]=c[i]+1; f[++t]=j;
		}
	}
	for (int k=n;k;--k){
		int i=f[k]; sum[i]=1;
		for (int p=son[i];p;p=next[p])
			if (c[ed[p]]>c[i]) sum[i]+=sum[ed[p]];
	}
	for (int i=1;i<=n;++i) key[i]-=d[i];
}
void updata(int x){size[x]=size[L[x]]+size[R[x]]+1;}
void zig(int x,int y){L[y]=R[x]; R[x]=y; updata(y); updata(x);}
void zag(int x,int y){R[y]=L[x]; L[x]=y; updata(y); updata(x);}
void ins(int x,int &y){
	if (!y){ran[x]=rand(); L[x]=R[x]=0; size[x]=1; y=x; return;}
	if (key[x]<key[y]){
		ins(x,L[y]); size[y]++;
		if (ran[x]<ran[y]) zig(x,y),y=x;
		}
	else{
		ins(x,R[y]); size[y]++;
		if (ran[x]<ran[y]) zag(x,y),y=x;
		}
}
void find(int x,int y){
	while (y)
		if (key[y]>x) ans+=size[R[y]]+1,y=L[y];
		else y=R[y];
}
void cal(int x,int y,int z){
	if (L[x]) cal(L[x],y,z);
	if (R[x]) cal(R[x],y,z);
	find(-key[x]-2*d[z],root[y]);
}
void merge(int x,int y){
	if (L[x]) merge(L[x],y);
	if (R[x]) merge(R[x],y);
	ins(x,root[y]);
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&key[i]);
	for (int i=1;i<n;i++){
		int x,y,z; scanf("%d%d%d",&x,&y,&z);
		ed[++l]=y; data[l]=z; next[l]=son[x]; son[x]=l;
		ed[++l]=x; data[l]=z; next[l]=son[y]; son[y]=l;
		}
	bfs();
	for (int k=n;k;k--){
		int i=f[k],w=0,q=0;
		for (int p=son[i];p;p=next[p]){
			int j=ed[p]; if (c[j]<c[i]) continue;
			if (sum[j]>w) w=sum[j],q=j;
			}
		for (int p=son[i];p;p=next[p]){
			int j=ed[p]; if (c[j]<c[i] || j==q) continue;
			cal(root[j],q,i); merge(root[j],q);
			}
		if (!q){ins(i,root[i]); continue;}
		find(-key[i]-2*d[i],root[q]); root[i]=root[q]; ins(i,root[i]);
		}
	printf("%d\n",ans);
	system("pause");
	return 0;
}


