#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define maxn 1000010
#define maxm 10010
#define CH 'A'
int n,m,i,j,T,bo;
char A[maxn],B[maxm];
int P[maxm];
int f[maxm][26];
int ans;
void Preparation(){
	int i,j=0,ch;P[1]=0;
	for (i=2;i<=m;i++){
		while (j&&B[j+1]!=B[i])j=P[j];
			if (B[j+1]==B[i])j++;
		P[i]=j;
	}
	for (ch=0;ch<26;ch++) f[0][ch]=0;
	for (i=0;i<m;i++)
		for (ch=0;ch<26;ch++)
			if (B[i+1]!=ch+CH) f[i][ch]=f[P[i]][ch];
				else f[i][ch]=i+1;
	for (ch=0;ch<26;ch++)f[m][ch]=f[P[m]][ch];
}
void match(){
	int i,j=0;
	for (i=1;i<=n;i++){
		j=f[j][A[i]-CH];
		if (j==m)bo=1,ans++;//printf("%d\n",i-m+1);
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d",&T);
	for (i=1;i<=T;i++){
		bo=false;
		scanf("%s",B+1);
		m=strlen(B+1);
		Preparation();
		scanf("%s",A+1);
		n=strlen(A+1);
		//printf("CASE %d\n",i);
		ans=0;
		match();
		//if (!bo) printf("No Solution.\n");
		printf("%d\n",ans);
	}
	//system("pause");
	return 0;
}


