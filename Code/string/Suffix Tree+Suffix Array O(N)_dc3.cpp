#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
using namespace std;
#define ll long long
#define N 1000005
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
	a[n++]=2;a[n++]=0; dc3(a,sa,n,128);calheight(a,sa,n);
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


