#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 100005
char A[N],B[N];
int extend[N],T[N],n,m;
int max(int a,int b){return a>b?a:b;}
void Exkmp(){
	int i,j,k,len,l;
	memset(T,0,sizeof(int)*(n+5));
	memset(extend,0,sizeof(int)*(m+5));
	T[1]=T[2]=0;
	while (T[2]+2<=n&&A[T[2]+1]==A[T[2]+2])++T[2];
	for (i=3,k=2;i<=n;++i){
		len=k+T[k]-1;l=T[i-k+1];
		if (i+l<len+1)T[i]=l;
		else{
			j=max(0,len-i+1);
			while (i+j<=n&&A[1+j]==A[i+j])++j;
			T[i]=j;k=i;
		}
	}
	while (1+extend[1]<=n&&1+extend[1]<=m&&A[1+extend[1]]==B[1+extend[1]])++extend[1];
	for (i=2,k=1;i<=m;++i){
		len=k+extend[k]-1;l=T[i-k+1];
		if (i+l<len+1)extend[i]=l;
		else{
			j=max(0,len-i+1);
			while (i+j<=m&&1+j<=n&&A[1+j]==B[i+j])++j;
			extend[i]=j;k=i;
		}
	}
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	gets(A+1);n=strlen(A+1);
	gets(B+1);m=strlen(B+1);
	Exkmp();
	for (int i=1;i<=m;++i)printf("%d %d\n",i,extend[i]);
	system("pause");for (;;);
	return 0;
}


