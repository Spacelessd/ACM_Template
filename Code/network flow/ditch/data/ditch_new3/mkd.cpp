#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <math.h>
using namespace std;
inline int min(int x,int y){return x<y?x:y;}
void makedata(int num,int N,int edge){
	char infile[20],outfile[20];
	sprintf(infile,"ditch%d.in",num);
	sprintf(outfile,"ditch%d.out",num);
	freopen(infile,"w",stdout);
	printf("%d %d\n",edge,N);
	for (int i=1;i<=edge;i++){
      int x=((rand()<<16)+rand())%N+1,y=((rand()<<16)+rand())%N+1,z=rand();
	  printf("%d %d %d\n",x,y,z);
      }
	fclose(stdout);
}
void solvedata(int num){
	char infile[20],outfile[20],cmd[100];
	sprintf(infile,"ditch%d.in",num);
	sprintf(outfile,"ditch%d.out",num);
	sprintf(cmd,"rename %s ditch.in",infile);
	system(cmd);
	system("ditch");
	sprintf(cmd,"rename ditch.in %s",infile);
	system(cmd);
	sprintf(cmd,"rename ditch.out %s",outfile);
	system(cmd);
}
int n;
int main(){
    srand(time(0));
	for(int i=0;i<10;++i){
        n=(i+1)*2000;
		makedata(i,n,min(n*((int)log2(n)+rand()%20+3),400000-rand()));
		solvedata(i);
	}
}
