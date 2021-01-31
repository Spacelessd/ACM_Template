#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 500005
#define CH 128
typedef int value;
value X[N][21],ra[CH];
int l2[N],sa[N];
char str[N];int n;
inline int LCP(int x,int y){
	int pre=x;
	for (int i=l2[n];i>=0;--i)
		if (x+(1<<i)<=n&&y+(1<<i)<=n&&X[x][i]==X[y][i])
			x+=1<<i,y+=1<<i;
	return x-pre;
}
inline bool cmp(int x,int y){
	int len=LCP(x,y);
	return str[x+len]<str[y+len];
}
inline bool cmp_bl(int x,int y){
	for (int i=0;i<n;++i){
		if (str[x+i]<str[y+i])return 1;
		if (str[x+i]>str[y+i])return 0;
	}
	return 0;
}
void Q(int a[],int s,int t){
	int p,i=s,j=t,m=a[(i+j)>>1];
	do {
		while (cmp(a[i],m)) ++i;
		while (cmp(m,a[j])) --j;
		if (i<=j){
			p=a[i]; a[i]=a[j]; a[j]=p;
			++i; --j;
		}
	}while (i<=j);
	if (i<t) Q(a,i,t);
	if (s<j) Q(a,s,j);
}
void Buildsa(char str[],int n){
	int i,j; srand(time(0));
	for (i=0;i<CH;++i)ra[i]=(rand()<<16)+rand();
	for (l2[0]=-1,i=1;i<=n;++i)l2[i]=!(i&(i-1))?l2[i-1]+1:l2[i-1];
	for (i=0;i<n;++i)X[i][0]=ra[str[i]];
	for (j=1;j<=l2[n];++j)
		for (i=0;i<=n-(1<<j);++i)
			X[i][j]=X[i][j-1]*ra[j]^X[i+(1<<(j-1))][j-1];
	for (i=1;i<=n;++i)sa[i]=i-1;
	Q(sa,1,n);
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1=clock();
	//scanf("%s",str);
	for (int i=0;i<200000;++i)str[i]=rand()%(CH-1)+1;
	n=strlen(str);
	Buildsa(str,n);
	//printf("sa=");for (int i=1;i<=n;++i)printf("%d ",sa[i]);printf("\n");
	printf("time=%d\n",clock()-t1);
	system("pause");
	return 0;
}


