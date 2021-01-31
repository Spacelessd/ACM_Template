#include<cstdio>
#include<algorithm>
#include<ctime>
using namespace std;
namespace you{
const int NMax=200000;//the maximum number of stars
void Start(int){
	//every time a round begins, this function will be invoked
}
void SetWeight(int a,int x){
	//the weight of star[a] is x
	//each weight will be set only once in each round
}
long long AddEdge(int,int){
	//an edge is added between two stars. indices are 0-based
	//you are to return the new communication cost
	return 0LL;
}
void DestroyAll(){
	//a round ends or your program produced a obviously wrong answer
	//you are to clear the memory use, and get ready for the new round
}
}
int main()
{
	FILE *fin=fopen("1.in","r"),*fout=fopen("1.out","w");
	int n;
	while (fscanf(fin,"%d",&n),n){
		you::Start(n);
		int x;
		for (int i=0;i<n;i++){
			fscanf(fin,"%d",&x);
			you::SetWeight(i,x);
		}
		long long c=0;
		int flg=1;
		for (int i=0;i<n-1;i++){
			int a,b;
			fscanf(fin,"%d%d",&a,&b);a--;b--;
			if (flg){
				//so, this is the trick
				//you can't know anything unless you get the right answer
				a=a^int(c)^int(c>>32);
				b=b^(int(c)+int(c>>32));
				if (a>=0 && a<n && b>=0 && b<n){
					c=you::AddEdge(a,b);
					fprintf(fout,"%I64d\n",c);
				}else{
					flg=0;
					you::DestroyAll();
				}
			}
			if (!flg){
				fprintf(fout,"-1\n");
			}
		}
		if (flg)you::DestroyAll();
	}
	fclose(fin);fclose(fout);
	return 0;
}


