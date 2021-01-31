#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
namespace fastIO{
	#define BUF_SIZE 100000
	//fread->read
	bool IOerror=0;
	inline char nc(){
		static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
		if (p1==pend){
			p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin);
			if (pend==p1){IOerror=1;return -1;}
			//{printf("IO error!\n");system("pause");for (;;);exit(0);}
		}
		return *p1++;
	}
	inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
	inline void read(int &x){
		bool sign=0; char ch=nc(); x=0;
		for (;blank(ch);ch=nc());
		if (IOerror)return;
		if (ch=='-')sign=1,ch=nc();
		for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
		if (sign)x=-x;
	}
	inline void read(double &x){
		bool sign=0; char ch=nc(); x=0;
		for (;blank(ch);ch=nc());
		if (IOerror)return;
		if (ch=='-')sign=1,ch=nc();
		for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
		if (ch=='.'){
			double tmp=1; ch=nc();
			for (;ch>='0'&&ch<='9';ch=nc())tmp/=10.0,x+=tmp*(ch-'0');
		}
		if (sign)x=-x;
	}
	inline void read(char *s){
		char ch=nc();
		for (;blank(ch);ch=nc());
		if (IOerror)return;
		for (;!blank(ch)&&!IOerror;ch=nc())*s++=ch;
		*s=0;
	}
	//getchar->read
	inline void read1(int &x){
		char ch;int bo=0;x=0;
		for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
		for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
		if (bo)x=-x;
	}
	inline void read1(double &x){
		char ch;int bo=0;x=0;
		for (ch=getchar();ch<'0'||ch>'9';ch=getchar())if (ch=='-')bo=1;
		for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getchar());
		if (ch=='.'){
			double tmp=1;
			for (ch=getchar();ch>='0'&&ch<='9';tmp/=10.0,x+=tmp*(ch-'0'),ch=getchar());
		}
		if (bo)x=-x;
	}
	void read1(char *s){
		char ch=getchar();
		for (;blank(ch);ch=getchar());
		for (;!blank(ch);ch=getchar())*s++=ch;
		*s=0;
	}
	//scanf->read
	void read2(int &x){scanf("%d",&x);}
	void read2(double &x){scanf("%lf",&x);}
	void read2(char *s){scanf("%s",s);}
	//fwrite->write
	struct Ostream_fwrite{
		char *buf,*p1,*pend;
		Ostream_fwrite(){buf=new char[BUF_SIZE];p1=buf;pend=buf+BUF_SIZE;}
		void out(char ch){
			if (p1==pend){
				fwrite(buf,1,BUF_SIZE,stdout);p1=buf;
			}
			*p1++=ch;
		}
		void print(int x){
			static char s[15],*s1;s1=s;
			if (!x)*s1++='0';if (x<0)*s1++='-',x=-x;
			while(x)*s1++=x%10+'0',x/=10;
			while(s1--!=s)out(*s1); out('\n');
		}
		void print(char *s){
			while (*s)out(*s++);out('\n');
		}
		void flush(){
			if (p1!=buf){fwrite(buf,1,p1-buf,stdout);p1=buf;}
		}
		~Ostream_fwrite(){flush();}
	}Ostream;
	inline void print(int x){Ostream.print(x);}
	inline void print(char *s){Ostream.print(s);}
	inline void flush(){Ostream.flush();}
	//puts->write
	char Out[BUF_SIZE],*o=Out;
	inline void print1(int x){
		static char buf[15];
		char *p1=buf;if (!x)*p1++='0';if (x<0)*p1++='-',x=-x;
		while(x)*p1++=x%10+'0',x/=10;
		while(p1--!=buf)*o++=*p1; *o++='\n';
	}
	inline void print1(char *s){
		while (*s)*o++=*s++; *o++='\n';
	}
	inline void flush1(){if (o!=Out)*--o=0;puts(Out);}
	#undef BUF_SIZE
};
using namespace fastIO;
int main(){
	freopen("1.in","r",stdin);
	freopen("fastIO_fread.out","w",stdout);
	int t1=clock();
	int n,x;read(n);
	for (int i=1;i<=n;++i)read(x);
	printf("time=%d\n",clock()-t1);
	fclose(stdin);fclose(stdout);
	
	freopen("1.in","w",stdout);
	srand(time(0));t1=clock();
	n=10000000;printf("%d\n",n);
	for (int i=1;i<=n;++i)print(rand()*rand());
	flush();
	fclose(stdout);
	freopen("fastIO_fwrite.out","w",stdout);
	printf("time=%d\n",clock()-t1);
	fclose(stdout);
	//system("pause");for (;;);
	return 0;
}


