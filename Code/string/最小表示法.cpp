#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 100005
char str[N*2];
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int T,n,i,j,k,pre;
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n);scanf("%s",str);
		memcpy(str+n,str,sizeof(char)*n);str[n+n]=0;
		for (i=0,j=1,k=0;i<n&&j<n;k=0){
			while (k<n&&str[i+k]==str[j+k])++k;
			if (k==n)break;
			if (str[i+k]<str[j+k])j+=k+1;
			else {
				pre=j;
				if (i+k<j)++j;else j=i+k+1;
				i=pre;
			}
		}
		printf("%d\n",i);
	}
	system("pause");for (;;);
	return 0;
}


