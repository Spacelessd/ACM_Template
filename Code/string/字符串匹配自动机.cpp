#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
#define M 10005
#define StartCH 'A'
#define CH 26
int n,m,bo;
char A[N],B[M];
int P[M],f[M][CH];
void Preparation(){
	int i,j=0,ch;P[1]=0;
	for (i=2;i<=m;++i){
		while (j&&B[j+1]!=B[i])j=P[j];
		if (B[j+1]==B[i])++j;
		P[i]=j;
	}
	for (ch=0;ch<CH;++ch)f[0][ch]=0;
	for (i=0;i<m;++i)
		for (ch=0;ch<CH;++ch)
			if (B[i+1]!=ch+StartCH)f[i][ch]=f[P[i]][ch];
				else f[i][ch]=i+1;
	for (ch=0;ch<CH;++ch)f[m][ch]=f[P[m]][ch];
}
void match(){
	int i,j=0;
	for (i=1;i<=n;++i){
		j=f[j][A[i]-StartCH];
		if (j==m)bo=1,printf("%d\n",i-m+1);
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%s",B+1); m=strlen(B+1);
	Preparation();
	int T; scanf("%d",&T);
	for (int i=1;i<=T;++i){
		bo=false;
		scanf("%s",A+1);
		n=strlen(A+1);
		printf("CASE %d\n",i);
		match();
		if (!bo)printf("No Solution.\n");
	}
	system("pause");for (;;);
	return 0;
}


