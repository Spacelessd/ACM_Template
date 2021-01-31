#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 100015
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
int a[N*3],sa[N*3],rank[N],h[N],wa[N],wb[N],wv[N],ws[N];
char str[N]; int belong[N],c[15],n,m;
int c0(int *r,int a,int b){return r[a]==r[b]&&r[a+1]==r[b+1]&&r[a+2]==r[b+2];}
int c12(int k,int *r,int a,int b){
	if(k==2) return r[a]<r[b]||r[a]==r[b]&&c12(1,r,a+1,b+1);
		else return r[a]<r[b]||r[a]==r[b]&&wv[a+1]<wv[b+1];
}
void sort(int *r,int *a,int *b,int n,int m)
{
	for(int i=0;i<n;++i) wv[i]=r[a[i]];
	for(int i=0;i<m;++i) ws[i]=0;
	for(int i=0;i<n;++i) ++ws[wv[i]];
	for(int i=1;i<m;++i) ws[i]+=ws[i-1];
	for(int i=n-1;i>=0;--i) b[--ws[wv[i]]]=a[i];
}
void dc3(int *r,int *sa,int n,int m)
{
	int i,j,*rn=r+n,*san=sa+n,ta=0,tb=(n+1)/3,tbc=0,p;
	r[n]=r[n+1]=0;
	for(i=0;i<n;++i) if(i%3)wa[tbc++]=i;
	sort(r+2,wa,wb,tbc,m);
	sort(r+1,wb,wa,tbc,m);
	sort(r,wa,wb,tbc,m);
	for(p=1,rn[F(wb[0])]=0,i=1;i<tbc;++i)
		rn[F(wb[i])]=c0(r,wb[i-1],wb[i])?p-1:p++;
	if(p<tbc) dc3(rn,san,tbc,p);
		else for(i=0;i<tbc;++i) san[rn[i]]=i;
	for(i=0;i<tbc;++i) if(san[i]<tb) wb[ta++]=san[i]*3;
	if(n%3==1) wb[ta++]=n-1;
	sort(r,wb,wa,ta,m);
	for(i=0;i<tbc;++i) wv[wb[i]=G(san[i])]=i;
	for(i=0,j=0,p=0;i<ta && j<tbc;++p)
		sa[p]=c12(wb[j]%3,r,wa[i],wb[j])?wa[i++]:wb[j++];
	for(;i<ta;++p) sa[p]=wa[i++];
	for(;j<tbc;++p) sa[p]=wb[j++];
}
void calheight(int *r,int *sa,int n)
{
	int j,k=0;
	for(int i=1;i<n;++i) rank[sa[i]]=i;
	for(int i=0;i<n-1;h[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];++k);
}
bool check(int mid){
	int sum=0,*x,pre=0;
	for (int i=0;i<n;++i){
		if (h[i]<mid){
			for (int j=pre;j<i;++j)c[belong[sa[j]]]=0;
			if (sum==m) return 1;sum=0;pre=i;
		}
		x=c+belong[sa[i]];
		if (!*x)*x=1,++sum;
	}
	for (int j=pre;j<n;++j)c[belong[sa[j]]]=0;
	if (sum==m) return 1;
	return 0;
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int T; scanf("%d",&T);
	while (T--){
		memset(belong,0,sizeof(belong));
		scanf("%d",&m);gets(str); n=0;
		for (int i=1;i<=m;++i){
			gets(str); int l=strlen(str);
			for (int j=0;j<l;++j) belong[n]=i,a[n++]=str[j];
			belong[n]=0; a[n++]=i;
		}
		a[n-1]=0; dc3(a,sa,n,128); calheight(a,sa,n);
		/*printf("a=");for (int i=0;i<n;++i)printf("%d ",a[i]);printf("\n");
		printf("belong=");for (int i=0;i<n;++i)printf("%d ",belong[i]);printf("\n");
		printf("sa=");for (int i=0;i<n;++i)printf("%d ",sa[i]);printf("\n");
		printf("rank=");for (int i=0;i<n;++i)printf("%d ",rank[i]);printf("\n");
		printf("h=");for (int i=0;i<n;++i)printf("%d ",h[i]);printf("\n");*/
		int l=0,r=10000,mid;
		while (l<r){
			mid=(l+r+1)>>1;
			if (check(mid))l=mid; else r=mid-1;
		}
		printf("%d\n",l);
	}
	system("pause");
	return 0;
}


