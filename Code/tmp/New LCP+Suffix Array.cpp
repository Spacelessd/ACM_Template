#include<stdio.h>
#include<time.h>
#include<algorithm>
#define N 500010
#define CH 256
typedef int value;
value X[N][21],ra[CH];
int l2[N],sa[N];
char str[N];
int n,i,j;
int LCP(int x,int y){
	int pre=x;
	for (int i=l2[n];i>=0;--i)
		if (x+(1<<i)<=n&&y+(1<<i)<=n&&X[x][i]==X[y][i])
			x+=1<<i,y+=1<<i;
	return x-pre;
}
bool cmp(int x,int y){
	int len=LCP(x,y);
	return str[x+len]<str[y+len];
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
int main(){
	srand(time(0));
	for (i=0;i<CH;++i)ra[i]=(rand()<<16)+rand();
	scanf("%s",str);
	//for (int i=0;i<500000;++i)str[i]=rand()%100+10;
	n=strlen(str);
	for (l2[0]=-1,i=1;i<=n;++i)l2[i]=!(i&(i-1))?l2[i-1]+1:l2[i-1];
	for (i=0;i<n;++i)X[i][0]=ra[str[i]];
	for (j=1;j<=l2[n];++j)
		for (i=0;i<=n-(1<<j);++i)
		X[i][j]=X[i][j-1]*ra[j]^X[i+(1<<(j-1))][j-1];
	for (i=1;i<=n;++i)sa[i]=i-1;
	for (i=0;i<n;++i){
		for (j=0;j<n;++j)printf("%d ",LCP(i,j));
		printf("\n");
	}
	Q(sa,1,n);
	for (i=1;i<=n;++i)printf("%d ",sa[i]);printf("\n");
	system("pause");
}
