#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define CH 2
#define half 0.5
#define base 2.0
int cnt[CH];
long double e[CH];
int main()
{
	FILE *in=fopen("1.in","r"),*out=fopen("1.out","w");
	if (in==NULL){
		printf("error:file not found!\n");
		system("pause");exit(0);
	}
	memset(cnt,0,sizeof(cnt));
	for (int i=0;i<CH;++i)cnt[i]=1;
	long double l=0,r=1;int i1=0;
	while (!feof(in)){
		unsigned char c=fgetc(in);
		if (c==255)break;c-='a';
		++i1;
		for (int i=0;i<CH;++i)e[i]=1.0*cnt[i]/(i1-1+CH);
		for (int i=1;i<CH;++i)e[i]+=e[i-1];
		double delta=r-l;
		r=l+delta*e[c];l+=delta*e[c-1];
		++cnt[c];
		printf("%.10lf %.10lf\n",(double)l,(double)r);
	}
	while (l<r){
		l*=base;r*=base;
		if (l<1.0&&r<1.0)fprintf(out,"0");
		else if (l>=1.0&&r>=1.0)fprintf(out,"1");
		else {fprintf(out,"1");break;}
		if (l>1.0)l-=1.0;
		if (r>1.0)r-=1.0;
	}
	fprintf(out,"*%d",i1);
	//printf("%.10lf %.10lf\n",(double)l,(double)r);
	system("pause");
	return 0;
}


