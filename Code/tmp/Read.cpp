#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
inline void read(int &x){
	char ch;int bo=0;x=0;
	for (ch=getchar();!(ch>='0' && ch<='9');ch=getchar())if (ch=='-')bo=1;
	for (;ch>='0' && ch<='9';x=x*10+ch-'0',ch=getchar());
	if (bo)x=-x;
}

char str[1500000],*p=str;
inline int Read(){
	int re=0;
	while(*p<'0'||*p>'9')p++;
	while(*p>='0'&&*p<='9')re=re*10+*p++-48;
	return re;
}
char buf[10],out[400000],*o=out;
inline void print(int x){
	char *b=buf;if (!x)*b++='0';
	while(x){*b++=x%10+48;x/=10;}
	while(b--!=buf)*o++=*b;
	*o++='\n';
}


#define BUFSIZE 1000000
char buf[BUFSIZE], *pt = buf + BUFSIZE, *pend = buf + BUFSIZE;
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

int main(){
	fread(p,1,1500000,stdin);
	system("pause");
	return 0;
}


