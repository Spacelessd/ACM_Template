#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
using namespace std;
#define ll long long
#define N 1000005
int A[N],B[N],s[N],v[N],rank[N],sa[N],h[N],a[N];
char str[N]; int belong[N],n,m;
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
#define CH 29
int root,Tlen,Elen;
struct edge{
	int start,end,link;
};
struct node{
	edge *son[CH];
	int dep; ll ans;
};
node T[N*2];edge E[N*2];
char Sprint[N];
void print(int x,int top){
	bool flag=0;
	for (int i=0;i<CH;++i)
		if (T[x].son[i]!=NULL){
			int top1=top;flag=1;
			for (int j=T[x].son[i]->start;j<=T[x].son[i]->end;++j)Sprint[++top1]=a[j]+'a'-3;Sprint[++top1]=' ';
			print(T[x].son[i]->link,top1);
		}
	if (!flag){
		for (int i=1;i<=top;++i)printf("%c",Sprint[i]);printf("\n");
	}
}
int stack[N*2],stack1[N*2],top;
int Newnode(int dep){
	++Tlen;for (int i=0;i<CH;++i)T[Tlen].son[i]=NULL;
	T[Tlen].dep=dep; return Tlen;
}
void Build_SuffixTree(){
	Tlen=Elen=0;root=Newnode(0);top=1;stack[top]=root;
	for (int i=1;i<n;++i){
		while (h[i]<T[stack[top]].dep){
			if (h[i]<T[stack[top-1]].dep)--top;
			else if (h[i]>T[stack[top-1]].dep){
				int a1=Newnode(h[i]),a2=Newnode(n-sa[i]-1);
				++Elen;
					E[Elen].start=E[stack1[top]].start+h[i]-T[stack[top-1]].dep;
					T[a1].son[a[E[Elen].start]]=E+Elen;
					E[Elen].end=E[stack1[top]].end;E[Elen].link=stack[top];
				E[stack1[top]].end=E[stack1[top]].start+h[i]-T[stack[top-1]].dep-1;E[stack1[top]].link=a1;
				++Elen;
					E[Elen].start=sa[i]+h[i];T[a1].son[a[E[Elen].start]]=E+Elen;
					E[Elen].end=n-2;E[Elen].link=a2;
				stack[top]=a1;
				++top;stack[top]=a2;stack1[top]=Elen;
				goto end;
			}
			else {--top;break;}
		}
		if (h[i]==T[stack[top]].dep){
			int a1=Newnode(n-sa[i]-1);
			++Elen;
				E[Elen].start=sa[i]+h[i];T[stack[top]].son[a[E[Elen].start]]=E+Elen;
				E[Elen].end=n-2;E[Elen].link=a1;
			++top;stack[top]=a1;stack1[top]=Elen;
		}
		end:;
	}
}
ll diff[N*2];int pre[N*2],diff1;
void dfs(int x,int can){
	bool flag=0; ll tmp=0;
	for (int i=0;i<CH;++i)
		if (T[x].son[i]!=NULL){
			int c=1,next; flag=1;
			if (pre[T[x].son[i]->end]-pre[T[x].son[i]->start-1])c=0;
			if (!c&&a[T[x].son[i]->start]>=3)c=2;
			if (!can||!c)next=0;
				else if (can==1)next=c;
				else next=0;
			dfs(T[x].son[i]->link,next);
			tmp|=T[T[x].son[i]->link].ans;
		}
	if (flag)T[x].ans=tmp;
	if (x!=root&&can!=0) diff[++diff1]=T[x].ans;
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1=clock();
	memset(belong,0,sizeof(belong)); n=0;
	scanf("%d",&m);gets(str);
	for (int i=1;i<=m;++i){
		gets(str); int l=strlen(str);
		for (int j=0;j<l;++j) belong[n]=i,a[n++]=str[j]-'a'+3;
		a[n++]=1;
	}
	a[n++]=2;a[n++]=0; da(a,sa,n,128);
	//printf("time=%d\n",clock()-t1);
	/*printf("a=");for (int i=0;i<n;++i)printf("%d ",a[i]);printf("\n");
	printf("belong=");for (int i=0;i<n;++i)printf("%d ",belong[i]);printf("\n");
	printf("sa=");for (int i=0;i<n;++i)printf("%d ",sa[i]);printf("\n");
	printf("rank=");for (int i=0;i<n;++i)printf("%d ",rank[i]);printf("\n");
	printf("h=");for (int i=0;i<n;++i)printf("%d ",h[i]);printf("\n");*/
	Build_SuffixTree(); //print(root,0);
	//printf("time=%d\n",clock()-t1);
	for (int i=1;i<=Elen;++i)
		if (E[i].end==n-2)T[E[i].link].ans=!belong[n-T[E[i].link].dep-1]?0:
			(ll)1<<(belong[n-T[E[i].link].dep-1]-1);
	for (int i=1;i<=N;++i)pre[i]=a[i]<=2?pre[i-1]+1:pre[i-1];
	diff1=0; dfs(root,1);
	sort(diff+1,diff+1+diff1);
	int ans=0;
	for (int i=1;i<=diff1;++i)if (i==1||diff[i]!=diff[i-1])++ans;
	printf("%d\n",ans);
	//printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


