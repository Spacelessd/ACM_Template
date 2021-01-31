#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
int x;
char buf[10],out[100000000],*o=out;
inline void print(int x){
    char *b=buf;int tmp;
    while(x){tmp=x/10;*b++=x+48-tmp*10;x=tmp;} 
    while(b--!=buf)*o++=*b;
    *o++='\n';
} 
int main(){
	//srand(time(0));
	x=164476;
	double t0=(double)clock()/CLOCKS_PER_SEC;
	for (int i=1;i<=10000000;i++)print(x);
	double t1=(double)clock()/CLOCKS_PER_SEC;
	printf("%.3lf\n",t1-t0);
	system("pause");
	return 0;
}
