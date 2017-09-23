#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define maxn 10010
int n,m,i,j,T,bo;
char A[maxn],B[maxn];
int P[maxn];
int ans;
void Preparation(){
	int i,j=0;P[1]=0;
	for (i=2;i<=m;i++){
		while (j&&B[j+1]!=B[i])j=P[j];
		if (B[j+1]==B[i])j++;
		P[i]=j;
	}
}
void KMP(){
	int i,j=0;
	for (i=1;i<=n;i++){
		while (j&&B[j+1]!=A[i])j=P[j];
		if (B[j+1]==A[i])j++;
		if (j==m){
			bo=1;//printf("%d\n",i-m+1);
			ans++;
			j=P[j];
		}
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
		KMP();
		//if (!bo) printf("No Solution.\n");
		printf("%d\n",ans);
	}
	//system("pause");
	return 0;
}


