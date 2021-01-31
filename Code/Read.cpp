#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define BUF_SIZE 100000
char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
inline void scan(){
	if (p1>=pend){
		p1=buf; fread(buf,1,BUF_SIZE,stdin);
	}
}
inline void read(int &x){
	bool sign=0; x=0; scan();
	while(*p1<'0'||*p1>'9'){if (*p1++=='-')sign=1;scan();}
	while(*p1>='0'&&*p1<='9')x=x*10+*p1++-'0',scan();
	if (sign)x=-x;
}
inline void read(double &x){
	int sign=0; x=0; scan();
	while (*p1<'0'||*p1>'9'){if (*p1++=='-')sign=1;scan();}
	while(*p1>='0'&&*p1<='9')x=x*10+*p1++-'0',scan();
	if (*p1=='.'){
		++p1;double tmp=1;
		while(*p1>='0'&&*p1<='9')tmp/=10.0,x+=tmp*(*p1++-'0'),scan();
	}
	if (sign)x=-x;
}
inline void read(char *s){
	scan();
	while(*p1<'A'||*p1>'z'){++p1;scan();}
	while(*p1!=' '&&*p1<='\t'&&*p1!='\n'){s[len++]=*p1++;scan();}
	s[len]=0;
}



inline void read(int &x){
	char ch;int bo=0;x=0;
	for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
	for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
	if (bo)x=-x;
}
inline void read(double &x){
	char ch;int bo=0;x=0;
	for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
	for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
	if (ch=='.'){
		double tmp=1;
		for (ch=getchar();ch>='0' && ch<='9';tmp/=10.0,x+=tmp*(ch-'0'),ch=getchar());
	}
	if (bo)x=-x;
}

char str[3000005],*p=str;
inline int Read(){
	int bo=0,x=0;
	while(*p<'0'||*p>'9')if (*p++=='-')bo=1;
	while(*p>='0'&&*p<='9')x=x*10+*p++-'0';
	return bo?-x:x;
}
inline void read(int &x){
	int bo=0;x=0;
	while(*p<'0'||*p>'9')if (*p++=='-')bo=1;
	while(*p>='0'&&*p<='9')x=x*10+*p++-'0';
	if (bo)x=-x;
}
inline void read(double &x){
	int bo=0;x=0;
	while (*p<'0'||*p>'9')if (*p++=='-')bo=1;
	while(*p>='0'&&*p<='9')x=x*10+*p++-'0';
	if (*p=='.'){
		p++;double tmp=1;
		while(*p>='0'&&*p<='9')tmp/=10.0,x+=tmp*(*p++-'0');
	}
	if (bo)x=-x;
}
inline void read(char *s){
	int len=0;
	while(*p<'A'||*p>'z')p++;
	while(*p>='A'&&*p<='z')s[len++]=*p++;
	s[len]=0;
}
fread(str,1,3000000,stdin);



char buf[10],out[3000005],*o=out;
inline void print(int x){
	char *b=buf;if (!x)*b++='0';if (x<0)*b++='-',x=-x;
	while(x){*b++=x%10+48;x/=10;}
	while(b--!=buf)*o++=*b;
	*o++='\n';
}
inline void put(char *s){
	while (*s)*o++=*s++; *o++='\n';
}
if (o!=out)*--o=0;puts(out);



inline void read(char *s){
	int len=0; scan();
	while(*p1<'A'||*p1>'z'){++p1;scan();}
	while(*p1>='A'&&*p1<='z'){s[len++]=*p1++;scan();}
	s[len]=0;
}

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



const int BUFFER_LEN = 1024 * 1024;
static char buffer[BUFFER_LEN];
char *ptr = buffer, *buf_end = ptr + 1;
#define PTR_NEXT() \
{ \
	ptr ++; \
	if (ptr == buf_end) \
	{ \
		ptr = buffer; \
		buf_end = buffer + fread(buffer, 1, BUFFER_LEN, fin); \
	} \
}
#define READ_INT(_x_) \
{ \
	while ((*ptr < '0' || *ptr > '9') && *ptr != '-') \
	PTR_NEXT(); \
	bool _nega_ = false; \
	if (*ptr == '-') \
	{ \
		_nega_ = true; \
		PTR_NEXT(); \
	} \
	int register _n_ = 0; \
	while (*ptr >= '0' && *ptr <= '9') \
	{ \
		_n_ = _n_ * 10 + *ptr - '0'; \
		PTR_NEXT(); \
	} \
	if (_nega_) \
	_n_ = - _n_; \
	(_x_) = (_n_); \
}

int main(){
	fread(p,1,3000000,stdin);
	
	system("pause");for (;;);
	return 0;
}


