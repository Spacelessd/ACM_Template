#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<fcntl.h>
#include<io.h>
using namespace std;
#define BUFSIZE 1000000
char buf[BUFSIZE],*pt=buf+BUFSIZE,*pend=buf+BUFSIZE;
#define read() \
	do{ \
		if (pt >= pend) \
		{ \
			pt = buf; \
			fread(buf, 1, BUFSIZE, stdin); \
		} \
	} while(0)

#define scan(t) \
{ \
	t = 0; \
	read(); \
	bool nega = false; \
	while (!(((*pt) >= '0' && (*pt) <= '9') || (*pt == '-'))) {pt ++; read();} \
	if ((*pt) == '-') {nega = true, pt ++; read();} \
	while (((*pt) >= '0' && (*pt) <= '9')) {t = t * 10 + (*(pt ++)) - '0'; read();}\
	if (nega) t = -t; \
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("fread.out","w",stdout);
	_setmode(fileno(stdin),_O_BINARY);
	int t1=clock();
	int n,x;scan(n);
	for (int i=1;i<=n;++i)scan(x);
	printf("time=%d\n",clock()-t1);
	//system("pause");
	return 0;
}


