#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<ext/rope>
using namespace std;
using namespace __gnu_cxx;
#define N 3000005
char buf[N];
rope<char> S;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int Q,len=0,x;char str[105],tmp;
	scanf("%d",&Q);
	while (Q--){
		scanf("%s",str);
		if (str[0]=='M')scanf("%d",&len);
		else if (str[0]=='I'){
			scanf("%d",&x);
			for (int i=0;i<x;){
				tmp=getchar();
				if (tmp>126||tmp<32)continue;
				buf[++i]=tmp;
			}
			S.insert(len,buf+1,buf+x+1);
		}
		else if (str[0]=='D'){
			scanf("%d",&x);S.erase(len,x);
		}
		else if (str[0]=='G'){
			scanf("%d",&x);
			//for (int i=0;i<x;++i)putchar(S[len+i]);putchar('\n');
			puts(rope<char> (S.begin()+len,S.begin()+len+x).c_str());
		}
		else if (str[0]=='P')--len;
		else if (str[0]=='N')++len;
	}
	system("pause");for (;;);
	return 0;
}


