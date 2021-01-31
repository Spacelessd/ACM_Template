#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 20005
#define M 50005
#define ll long long
#define dep_max 18
#define inf (1<<30)
int x[M],y[M],z[M],zz[M],num[M],d[M],ord[M],opt[M],f[N],n,m,q;
ll base_ans;
struct recover{
	int a[M*5],b[M*5],cnt;
	int find(int x){
		if (f[x]==x)return x;
		int fa=x;while (f[fa]!=fa)fa=f[fa];
		while (f[x]!=fa){
			a[++cnt]=x;b[cnt]=f[x];
			f[x]=fa;x=b[cnt];
		}
		return fa;
	}
	bool merge(int x,int y){
		x=find(x);y=find(y);
		if (x==y)return 0;
		a[++cnt]=x;b[cnt]=f[x];f[x]=y;
		return 1;
	}
	void action(int top=0){
		for (;cnt!=top;--cnt)f[a[cnt]]=b[cnt];
	}
}e_tmp[dep_max];
void Q(int s,int t){
	int p,i=s,j=t,m=z[ord[(i+j)>>1]];
	do {
		while (z[ord[i]]<m) ++i;
		while (z[ord[j]]>m) --j;
		if (i<=j){
			p=ord[i]; ord[i]=ord[j]; ord[j]=p;
			++i; --j;
		}
	}while (i<=j);
	if (i<t) Q(i,t);
	if (s<j) Q(s,j);
}
void work(int dep,int l,int r){
	recover &e=e_tmp[dep];e.cnt=0;
	if (l==r){
		z[num[l]]=zz[num[l]]=d[l];Q(1,m);
		ll ans=base_ans;
		for (int i=1;i<=m;++i)
			if (e.merge(x[ord[i]],y[ord[i]]))ans+=z[ord[i]];
		printf("%I64d\n",ans);e.action();return;
	}
	int m_rem=m,opt1=0;ll base_rem=base_ans;
	// Start Contraction
	for (int i=l;i<=r;++i)z[num[i]]=-inf;
	Q(1,m);
	for (int i=1;i<=m;++i)
		if (e.merge(x[ord[i]],y[ord[i]])&&z[ord[i]]!=-inf)opt[++opt1]=ord[i];
	e.action();
	for (int i=1;i<=opt1;++i)
		base_ans+=z[opt[i]],e.merge(x[opt[i]],y[opt[i]]);
	int cnt_rem=e.cnt;
	// Start Reduction
	for (int i=l;i<=r;++i)z[num[i]]=inf;
	Q(1,m);opt1=0;
	for (int i=1;i<=m;++i)
		if (!e.merge(x[ord[i]],y[ord[i]]))
			if (z[ord[i]]!=inf)opt[++opt1]=i; else break;
	for (int i=opt1;i;--i){int tmp=ord[opt[i]];ord[opt[i]]=ord[m];ord[m--]=tmp;}
	e.action(cnt_rem);
	for (int i=l;i<=r;++i)z[num[i]]=zz[num[i]];
	for (int i=1;i<=m;++i)e.find(x[ord[i]]),e.find(y[ord[i]]);
	int mid=(l+r)>>1;
	work(dep+1,l,mid);work(dep+1,mid+1,r);
	e.action();m=m_rem;base_ans=base_rem;
}
int main()
{
	int t1=clock();
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d%d%d",&n,&m,&q);
	for (int i=1;i<=n;++i)f[i]=i;
	for (int i=1;i<=m;++i)
		scanf("%d%d%d",&x[i],&y[i],&zz[i]),ord[i]=i,z[i]=zz[i];
	for (int i=1;i<=q;++i)scanf("%d%d",&num[i],&d[i]);
	if (q)work(0,1,q);
	//printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


