#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 50005
#define M 180005
int fmax[N],fmin[N],a[N],Qmax[N],Qmin[N],ans[M];
struct Edge{
	int link[M],next[M],son[M],id[M],l;
	void addedge(int x,int y,int z){
		link[++l]=y;id[l]=z;next[l]=son[x];son[x]=l;
	}
}e;
int findmax(int x){
	if (fmax[x]==x)return x;
	else return fmax[x]=findmax(fmax[x]);
}
int findmin(int x){
	if (fmin[x]==x)return x;
	else return fmin[x]=findmin(fmin[x]);
}
char str[3000005],*p=str;
inline void read(int &x){
	int bo=0;x=0;
	while(*p<'0'||*p>'9')if (*p++=='-')bo=1;
	while(*p>='0'&&*p<='9')x=x*10+*p++-'0';
	if (bo)x=-x;
}
char buf[15],out[3000005],*o=out;
inline void print(int x){
	char *b=buf;if (!x)*b++='0';//if (x<0)x=-x,*b++='-';
	while(x){*b++=x%10+48;x/=10;}
	while(b--!=buf)*o++=*b;
	*o++='\n';
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	int t1=clock();
	fread(p,1,3000000,stdin);
	int n,q,X,Y,tmax=0,tmin=0;read(n);read(q);
	for (int i=1;i<=n;++i)read(a[i]);
	for (int i=1;i<=q;++i)read(X),read(Y),e.addedge(Y,X,i);
	for (int i=1;i<=n;++i)fmax[i]=fmin[i]=i;
	for (int i=1;i<=n;++i){
		int x=a[i];
		for (;tmax&&x>=a[Qmax[tmax]];--tmax)fmax[Qmax[tmax]]=i;
		for (;tmin&&x<=a[Qmin[tmin]];--tmin)fmin[Qmin[tmin]]=i;
		Qmax[++tmax]=Qmin[++tmin]=i;
		for (int p=e.son[i];p;p=e.next[p]){
			X=a[findmax(e.link[p])];Y=a[findmin(e.link[p])];
			ans[e.id[p]]=X-Y;
		}
	}
	for (int i=1;i<=q;++i)print(ans[i]);
	if (o>out)*--o=0;puts(out);
	printf("time=%d\n",clock()-t1);
	//system("pause");for (;;);
	return 0;
}


