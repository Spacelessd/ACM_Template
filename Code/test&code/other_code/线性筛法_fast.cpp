#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 30000005
int check[N],p[N],p1;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int n;scanf("%d",&n);
	int t1=clock();
	p1=0;//memset(check,0,sizeof(check));
	for (int i=2;i<=n;++i){
		if (!check[i])p[++p1]=check[i]=i;
		for (int j=1;j<=p1&&i*p[j]<=n;++j){
			check[i*p[j]]=p[j];
			if (check[i]==p[j])break;
		}
	}
	//for (int i=1;i<=p1;++i)printf("%d\n",p[i]);
	printf("%d\n",p1);
	printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


