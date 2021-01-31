#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define AC {fprintf(res,"1\nÕýÈ·\n"); exit(0);}
#define WA {fprintf(res,"0\n´íÎó\n"); exit(0);}
#define eps 0.01
int main(int argc,char **argv){
	FILE *fin=fopen(argv[1],"r"),*fstd=fopen(argv[2],"r"),*fout=fopen(argv[3],"r"),*res=fopen(argv[4],"w");
	double std_ans,out_ans;
	static char std_ans_s[105],out_ans_s[105];
	while (fscanf(fstd,"%s",&std_ans_s)!=EOF){
		if (fscanf(fout,"%s",&out_ans_s)==EOF)WA;
		if (std_ans_s[0]=='N'){
			if (strcmp(std_ans_s,out_ans_s)!=0)WA;
		}
		else {
			sscanf(std_ans_s,"%lf",&std_ans);sscanf(out_ans_s,"%lf",&out_ans);
			if (fabs(std_ans-out_ans)>eps)WA;
		}
	}
	AC;
	return 0;
}


