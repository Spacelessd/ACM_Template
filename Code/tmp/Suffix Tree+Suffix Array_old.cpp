#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<string>
#include<vector>
#include<iostream>
using namespace std;
#define N 100015
long long A[N],B[N],s[N],v[N],rank[N],sa[N],h[N],a[N];
char str[N]="abc";
long long n;
long long K=5;
bool cmp(long long *r,long long a,long long b,long long l){return r[a]==r[b]&&r[a+l]==r[b+l];}
void da(long long *a,long long *sa,long long n,long long m){
	long long i,j,p,k=0,*x=A,*y=B,*t;
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
#define Dep 25
long long f[N][Dep+1];
void BuildST(){
	long long i,j;
	for (i=1;i<=n;++i)f[i][0]=h[i];
	for (j=1;j<=Dep;++j)
		for (i=1;i<=n-(1<<j)+1;++i)f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
}
long long Qmin(long long x,long long y){
	if (x==y)return n-sa[x];
	if (x>y){long long t=x;x=y;y=t;}++x;
	long long z=(long long)log2(y-x+1);
	long long Min=min(f[x][z],f[y-(1<<z)+1][z]);
	return Min;
}
long long lcp(long long x,long long y){
	return Qmin(rank[x],rank[y]);
}
long long len,root;
struct edge{
	long long start,end,link;
};
struct node{
	vector<edge> son;
	long long dep,flag,size,size1,num;
};
node T[N*10];
void maketree(long long pre,long long l,long long r){
	if (l==r){T[pre].flag=1;return;}
	long long L=l;while (L<=r&&n-sa[L]<=T[pre].dep)++L;
	while (L<=r){
		long long ll=L,rr=r,mid;
		while (ll<rr){
			mid=(ll+rr+1)>>1;
			if (Qmin(L,mid)>T[pre].dep)ll=mid;
				else rr=mid-1;
		}
		long long dep=Qmin(L,ll);
		long long x=++len;
		edge Tedge;
		Tedge.start=sa[L]-1+T[pre].dep+1;Tedge.end=sa[L]-1+dep;Tedge.link=x;
		T[pre].son.push_back(Tedge);
		T[x].dep=dep;
		maketree(x,L,ll);
		L=ll+1;
	}
}
long long getlen(edge x){
	if (x.end==n-1)return x.end-x.start;
	else return x.end-x.start+1;
}

void build(long long x){
	long long bo=0;
	T[x].size=T[x].flag;
	for (vector<edge>::iterator i=T[x].son.begin();i!=T[x].son.end();++i){
		build(i->link);
		if (i->start==n-1)bo=1,T[i->link].size1=0;
		T[x].size+=T[i->link].size;
		T[x].num+=T[i->link].num+T[i->link].size1*getlen(*i);
	}
	T[x].size1=T[x].size;
}
string S;
void dfs(long long x,long long k){
	for (vector<edge>::iterator i=T[x].son.begin();i!=T[x].son.end();++i){
		if (T[i->link].num+T[i->link].size1*getlen(*i)<k)k-=T[i->link].num+T[i->link].size1*getlen(*i);
		else {
			if (k<=T[i->link].size1*getlen(*i)){
				long long place=k/T[i->link].size1;
				if (k%T[i->link].size1)++place;
				for (long long j=i->start;j<=i->start+place-1;++j)S+=(char)a[j];
				cout<<S<<endl;
				return;
			}
			else {
				k-=T[i->link].size1*getlen(*i);
				for (long long j=i->start;j<=i->end;++j)S+=(char)a[j];
				dfs(i->link,k);
			}
			return;
		}
	}
}

void print(long long x,string s){
	//if (T[x].flag){
		cout<<s<<endl;
		printf("%d %d %d %d\n",x,T[x].size,T[x].size1,T[x].num);
	//}
	for (vector<edge>::iterator i=T[x].son.begin();i!=T[x].son.end();++i){
		string tmp="";
		for (long long j=i->start;j<=i->end;++j)tmp+=(char)a[j];
		print(i->link,s+tmp);
	}
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	gets(str);scanf("%I64d",&K);
	n=strlen(str);str[n]='$';str[++n]=0;
	for (long long i=0;i<=n;++i)a[i]=str[i];
	da(a,sa,n+1,128);BuildST();
	root=len=1;T[root].dep=0;
	maketree(root,1,n);
	build(root);
	S="";
	dfs(root,K);
    //system("pause");
    //for (;;);
	return 0;
}


