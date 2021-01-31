#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
char a[N],b[N];
int Dist(char *t,char ch){
	int len=strlen(t),i=len-1;
	if (ch==t[i])return len;
	--i;
	while (i>=0){
		if (ch==t[i])return len-1-i;
		--i;
	}
	return len;
}
int BM(char *s,char *t){
	int n=strlen(s),m=strlen(t),i=m-1,j=m-1,ans=0;
	while (i<n){
		if (s[i]==t[j])--i,--j;
		else {
			i+=Dist(t,s[i]);j=m-1;
		}
		if (j<0){
			//printf("%d %d\n",i,j);system("pause");
			++ans;j=m-1;i+=m+1;
		}
	}
	return ans;
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int T;scanf("%d",&T);gets(a);
	while (T--){
		gets(a);gets(b);
		printf("%d\n",BM(b,a));
	}
	system("pause");
	return 0;
}


