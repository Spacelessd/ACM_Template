#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 500005
int rad[N],n,n1,len,ans;
char str[N],str1[N];
void Manacher(int *rad,char *str,int n){
	int mx=0,id;
	for (int i=1;i<n;++i){
		if (mx>i)rad[i]=rad[2*id-i]<mx-i?rad[2*id-i]:mx-i;
			else rad[i]=1;
		for(;str[i+rad[i]]==str[i-rad[i]];++rad[i]);
		if(rad[i]+i>mx)mx=rad[i]+i,id=i;
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	while (scanf("%s",str1)!=EOF){
		n1=strlen(str1);n=2*n1+2;
		str[0]='$';
		for (int i=0;i<=n1;++i){
			str[i*2+1]='#';str[i*2+2]=str1[i];
		}
		Manacher(rad,str,n);
		ans=1;
		for (int i=0;i<n;++i)if (rad[i]>ans)ans=rad[i];
		//for (i=0;i<n;++i)printf("%c %d\n",str[i],rad[i]);
		printf("%d\n",ans-1);
	}
	system("pause");for (;;);
	return 0;
}


