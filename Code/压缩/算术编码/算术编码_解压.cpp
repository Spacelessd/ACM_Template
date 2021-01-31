#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 10000005
#define CH 2
#define half 0.5
#define base 2.0
char s[N];
int cnt[CH];
long double e[CH];
int main()
{
	FILE *in=fopen("1.out","r"),*out=fopen("2.in","w");
	if (in==NULL){
		printf("error:file not found!\n");
		system("pause");exit(0);
	}
	memset(cnt,0,sizeof(cnt));
	for (int i=0;i<CH;++i)cnt[i]=1;
	int len;
	long double ans=0,now=1;
	while (!feof(in)){
		unsigned char c=fgetc(in);
		printf("%d\n",c);
		if (c=='*'){fscanf(in,"%d",&len);break;}
		if (c!='0'&&c!='1')continue;
		now/=base;
		if (c=='1')ans+=now;
	}
	printf("%.10lf\n",(double)ans);
	double l=0,r=1;
	for (int i1=0;i1<len;++i1){
		for (int i=0;i<CH;++i)e[i]=1.0*cnt[i]/(i1+CH);
		for (int i=1;i<CH;++i)e[i]+=e[i-1];
		double delta=r-l;unsigned char c;
		for (c=0;c<CH;++c)if ((c==0||l+e[c-1]*delta<=ans)&&ans<=l+e[c]*delta)break;
		printf("%c",c+'a');
		fprintf(out,"%c",c+'a');
		r=l+delta*e[c];l+=delta*e[c-1];
		++cnt[c];
	}
	printf("%.10lf %.10lf\n",l,r);
	system("pause");
	return 0;
}


