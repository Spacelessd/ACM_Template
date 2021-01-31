#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 100025
int A[N],B[N],s[N],v[N],rank[N],sa[N],h[N],a[N],belong[N];
bool c[15];
char str[N];
int n,m,t;
bool cmp(int *r,int a,int b,int l){return r[a]==r[b]&&r[a+l]==r[b+l];}
void da(int *a,int *sa,int n,int m){
	int i,j,p,k=0,*x=A,*y=B,*t;
	for (i=0;i<m;++i) s[i]=0;
	for (i=0;i<n;++i) ++s[x[i]=a[i]];
	for (i=1;i<m;++i) s[i]+=s[i-1];
	for (i=n-1;i>=0;--i) sa[--s[x[i]]]=i;
	for (j=1,p=1;p<n;j*=2,m=p){
		for (p=0,i=n-j;i<n;++i) y[p++]=i;
		for (i=0;i<n;++i) if (sa[i]>=j) y[p++]=sa[i]-j;
		for (i=0;i<n;++i) v[i]=x[y[i]];
		for (i=0;i<m;++i) s[i]=0;
		for (i=0;i<n;++i) ++s[v[i]];
		for (i=1;i<m;++i) s[i]+=s[i-1];
		for (i=n-1;i>=0;--i) sa[--s[v[i]]]=y[i];
		for (t=x,x=y,y=t,i=1,p=1,x[sa[0]]=0;i<n;++i)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
	for (i=0;i<n;++i) rank[sa[i]]=i;
	for (i=0;i<n-1;h[rank[i++]]=k)
		for (k?k--:0,j=sa[rank[i]-1];a[i+k]==a[j+k];++k);
}
bool check(int mid){
	memset(c,0,sizeof(c));
	for (int i=0;i<=n;++i){
		if (h[i]<mid || i==n){
			int j; for (j=1;j<=m && c[j];++j);
			if (j>m) return 1;
			memset(c,0,sizeof(c)); c[belong[sa[i]]]=1;
		}
		else c[belong[sa[i]]]=1;
	}
	return 0;
}
int main(){
	int T; scanf("%d",&T);
	while (T--){
		memset(belong,0,sizeof(belong));
		scanf("%d",&m);gets(str); n=0;
		for (int i=1;i<=m;++i){
			gets(str); int l=strlen(str);
			for (int j=0;j<l;++j) belong[n]=i,a[n++]=str[j];
			belong[n]=0; a[n++]=i;
		}
		a[n-1]=0; da(a,sa,n,128);
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


