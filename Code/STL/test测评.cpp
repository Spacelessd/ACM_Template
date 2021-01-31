#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
using namespace std;
int main()
{
	char prob[100];
	int b,e;
	scanf("%s %d %d",prob,&b,&e);
	char buf[100];
	for (int i=b;i<=e;++i){
		sprintf(buf,"copy %s%d.in %s.in",prob,i,prob);
		system(buf);
		sprintf(buf,"%s.exe",prob);
		int t1=clock();
		system(buf);
		printf("time=%d\n",(int)clock()-t1);
		sprintf(buf,"fc %s%d.out %s.out",prob,i,prob);
		system(buf);
	}
	getchar();getchar();
	return 0;
}


