#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define maxn 10010
int n,m,i,j,T,bo;
char A[maxn],B[maxn];
int P[maxn];
int f[maxn][26];
void Preparation(){
	int i,j=0,ch;P[1]=0;
	for (i=2;i<=m;i++){
		while (j&&B[j+1]!=B[i])j=P[j];
		if (B[j+1]==B[i])j++;
		P[i]=j;
	}
	for (i=0;i<=m;i++)
		for (ch=0;ch<26;ch++)
			if (i==m||P[i+1]!=ch+'a') f[i][ch]=f[P[i]][ch];
				else f[i][ch]=i+1;
}
void match(){
	int i,j=0;
	for (i=1;i<=n;i++){
		j=f[j][A[i]-'a'];
		if (j==m)printf("%d\n",i-m);
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%s",B+1);
	m=strlen(B+1);
	Preparation();
	scanf("%d",&T);
	for (i=1;i<=T;i++){
		bo=false;
		scanf("%s",A+1);
		n=strlen(A+1);
		printf("CASE %d\n",i);
		match();
		if (!bo) printf("No Solution.\n");
	}
	system("pause");
	return 0;
}


