#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#define Maxlevel 3
int n;
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//scanf("%d",&n);
	n=200000;
	int Exp=(int)(32768/pow(2,1.0/Maxlevel*log2(n)));
	printf("exp=%d\n",Exp);
	printf("%.10lf\n",pow(2,1.0/Maxlevel*log2(n)));
	//printf("%.10lf\n",pow(2,2*log2(3.3)));
	system("pause");
	return 0;
}




