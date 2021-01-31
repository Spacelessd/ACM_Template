#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 30000010
int check[N],p[N],p1;
int n;
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%d",&n);
	int t1=clock();
	memset(check,0,sizeof(check));p1=0;
	for (int i=2;i<=n;++i){
		if (!check[i])p[++p1]=check[i]=i;
		for (int j=1;j<=p1&&i*p[j]<=n&&check[i]>=p[j];++j)
			check[i*p[j]]=p[j];
	}
	//for (int i=1;i<=p1;++i)printf("%d\n",p[i]);
	printf("%d\n",p1);
	printf("time=%d\n",clock()-t1);
	system("pause");
	return 0;
}






