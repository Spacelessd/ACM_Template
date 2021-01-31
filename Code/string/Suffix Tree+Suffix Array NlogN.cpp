#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<string>
#include<vector>
#include<iostream>
using namespace std;
#define N 100015
int A[N],B[N],s[N],v[N],rank[N],sa[N],h[N],a[N];
char str[N];
int n;long long K;
inline int min(int x,int y){return x<y?x:y;}
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
#define Dep 20
int f[N][Dep+1],M[N];
void BuildST(){
	int i,j;
	for (i=1;i<=n;++i)f[i][0]=h[i];
	for(M[0]=-1,i=1;i<=n;++i)
		M[i]=!(i&(i-1))?M[i-1]+1:M[i-1];
	for (j=1;j<=Dep;++j)
		for (i=1;i<=n-(1<<j)+1;++i)f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
}
inline int Qmin(int x,int y){
	if (x==y)return n-sa[x];
	if (x>y){int t=x;x=y;y=t;}++x;
	int z=M[y-x+1],Min=min(f[x][z],f[y-(1<<z)+1][z]);
	return Min;
}
inline int lcp(int x,int y){
	return Qmin(rank[x],rank[y]);
}
#define root 1
int len;
struct edge{
	int start,end,link;
};
struct node{
	vector<edge> son;
	long long size,num;
	int dep;
};
node T[N*2];
void maketree(int pre,int l,int r){
	if (l==r){T[pre].size=1;return;}
	int L=l;while (L<=r&&n-sa[L]<=T[pre].dep)++L;
	while (L<=r){
		int ll=L,rr=r,mid;
		while (ll<rr){
			mid=(ll+rr+1)>>1;
			if (Qmin(L,mid)>T[pre].dep)ll=mid;
				else rr=mid-1;
		}
		int dep=Qmin(L,ll),x=++len;
		edge Tedge; T[x].dep=dep;
		Tedge.start=sa[L]-1+T[pre].dep+1;Tedge.end=sa[L]-1+dep;Tedge.link=x;
		T[pre].son.push_back(Tedge);
		maketree(x,L,ll);L=ll+1;
	}
}
inline int getlen(edge &x){
	if (x.end==n-1)return x.end-x.start;
	else return x.end-x.start+1;
}
void build(int x){
	for (vector<edge>::iterator i=T[x].son.begin();i!=T[x].son.end();++i){
		build(i->link);
		T[x].size+=T[i->link].size;
		T[x].num+=T[i->link].num+T[i->link].size*getlen(*i);
	}
}
char S[N];
int S1=-1;
void dfs(int x,long long k){
	for (vector<edge>::iterator i=T[x].son.begin();i!=T[x].son.end();++i){
		long long Eans=T[i->link].size*getlen(*i);
		if (T[i->link].num+Eans<k)k-=T[i->link].num+Eans;
		else {
			if (k<=Eans){
				int place=k/T[i->link].size;
				if (k%T[i->link].size)++place;
				for (int j=i->start;j<=i->start+place-1;++j)S[++S1]=a[j];
				puts(S);return;
			}
			else {
				k-=Eans;
				for (int j=i->start;j<=i->end;++j)S[++S1]=a[j];
				dfs(i->link,k);
			}
			return;
		}
	}
}
void print(int x,string s){
	//if (T[x].flag){
		cout<<s<<endl;
		printf("%d %d %d %d\n",x,T[x].size,T[x].num);
	//}
	for (vector<edge>::iterator i=T[x].son.begin();i!=T[x].son.end();++i){
		string tmp="";
		for (int j=i->start;j<=i->end;++j)tmp+=(char)a[j];
		print(i->link,s+tmp);
	}
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1=clock();
	gets(str);scanf("%I64d",&K);
	n=strlen(str);str[n]='$';str[++n]=0;
	for (int i=0;i<=n;++i)a[i]=str[i];
	da(a,sa,n+1,128);BuildST();
	len=1;T[root].dep=0;
	maketree(root,1,n);
	build(root);
	dfs(root,K);
	//printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


