#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define maxn 100005
char A[maxn],B[maxn];
int extend[maxn],T[maxn];
int N,M,i;
int max(int a,int b){return a>b?a:b;}
void Exkmp(){
	int i,j,k,len,l;
	memset(T,0,sizeof(int)*(N+5));
	memset(extend,0,sizeof(int)*(M+5));
	T[1]=T[2]=0;
	while (T[2]+2<=N&&A[T[2]+1]==A[T[2]+2])T[2]++;
	for (i=3,k=2;i<=N;++i){
		len=k+T[k]-1;l=T[i-k+1];
		if (i+l<len+1)T[i]=l;
		else{
			j=max(0,len-i+1);
			while (i+j<=N&&A[1+j]==A[i+j])j++;
			T[i]=j;k=i;
		}
	}
	while (1+extend[1]<=N&&1+extend[1]<=M&&A[1+extend[1]]==B[1+extend[1]])extend[1]++;
	for (i=2,k=1;i<=M;++i){
		len=k+extend[k]-1;l=T[i-k+1];
		if (i+l<len+1)extend[i]=l;
		else{
			j=max(0,len-i+1);
			while (i+j<=M&&1+j<=N&&A[1+j]==B[i+j])j++;
			extend[i]=j;k=i;
		}
	}
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	gets(A+1);N=strlen(A+1);
	gets(B+1);M=strlen(B+1);
	Exkmp();
	for (i=1;i<=M;++i)printf("%d %d\n",i,extend[i]);
	system("pause");
	return 0;
}


