#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
int n,m,bo;
char A[N],B[N];
int P[N];
void Preparation(){
	int i,j=0;P[1]=0;
	for (i=2;i<=m;++i){
		while (j&&B[j+1]!=B[i])j=P[j];
		if (B[j+1]==B[i])++j;
		P[i]=j;
	}
}
void KMP(){
	int i,j=0;
	for (i=1;i<=n;++i){
		while (j&&B[j+1]!=A[i])j=P[j];
		if (B[j+1]==A[i])++j;
		if (j==m){
			bo=1;printf("%d\n",i-m+1);
			j=P[j];
		}
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%s",B+1);
	m=strlen(B+1);
	Preparation();
	int T;scanf("%d",&T);
	for (int i1=1;i1<=T;++i1){
		bo=false;
		scanf("%s",A+1);
		n=strlen(A+1);
		printf("CASE %d\n",i1);
		KMP();
		if (!bo)printf("No Solution.\n");
	}
	system("pause");for (;;);
	return 0;
}


