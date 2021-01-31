#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;

const int maxn=1024;
int G[maxn][maxn];
void makedata(int num,int N,int edge){
	memset(G,0,sizeof(G));
	for(int i=0;i<edge;++i)
		G[rand()%N+1][rand()%N+1]+=rand();
	int m=0;
	for(int i=1;i<=N;++i)
		for(int j=i+1;j<=N;++j){
			G[i][j]-=G[j][i];
			if(G[i][j])
				++m;
		}
	char infile[20],outfile[20];
	sprintf(infile,"ditch%d.in",num);
	sprintf(outfile,"ditch%d.out",num);
	freopen(infile,"w",stdout);
	printf("%d %d\n",m,N);
	for(int i=1;i<=N;++i){
		G[1][i]=abs(G[1][i]);
		G[i][N]=abs(G[i][N]);
	}
	for(int i=1;i<=N;++i){
		for(int j=i+1;j<=N;++j){
			if(G[i][j]>0)
				printf("%d %d %d\n",i,j,G[i][j]);
			else if(G[i][j]<0)
				printf("%d %d %d\n",j,i,-G[i][j]);
		}
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
int main(){
    srand(time(0));
	for(int i=0;i<10;++i){
		makedata(i,(i+1)*100,(i+1)*100*(rand()%20+10));
		solvedata(i);
	}
}
