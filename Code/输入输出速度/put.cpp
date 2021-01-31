#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
int n=10000000;
char buf[10],out[100000005],*o=out;
inline void print(int x){
	char *b=buf;if (!x)*b++='0';if (x<0)*b++='-',x=-x;
	while(x){*b++=x%10+48;x/=10;}
	while(b--!=buf)*o++=*b;
	*o++=' ';
}
inline void put(char *s){
	while (*s)*o++=*s++; *o++='\n';
}
int main()
{
	freopen("1.in","w",stdout);
	srand(time(0));
	int t1=clock();
	printf("%d\n",n);
	for (int i=1;i<=n;++i)print(rand()*rand());
	if (o!=out)*--o=0;puts(out);
	fclose(stdout);
	freopen("put.out","w",stdout);
	printf("time=%d\n",clock()-t1);
	fclose(stdout);
	//system("pause");
	return 0;
}


