#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
int cnt[256],sum;
void calc(string s){
	printf("FILE ");printf(s.c_str());printf(":\n");
	freopen(s.c_str(),"r",stdin);
	//freopen("tree.out","w",stdout);
	memset(cnt,0,sizeof(cnt));sum=0;
	char ch;
	while ((ch=getchar())!=EOF){
		int c=ch;
		++cnt[c],++sum;
	}
	double ans=0;
	for (int i=0;i<256;++i)if (cnt[i]){
		ans+=-log2(1.0*cnt[i]/sum)*cnt[i];
		printf("%c %.5lf\n",i,1.0*cnt[i]/sum);
	}
	printf("%.5lfbit %.5lfB\n",ans,ans/8.0);
	fclose(stdin);
}
int main()
{
	calc("tree.out");
	calc("tree1.out");
	system("pause");for (;;);
	return 0;
}


