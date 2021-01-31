#include <cstdio>
#include <ctime>
#define NMax 10000
using namespace std;
int dist[NMax];
int heap[NMax],place[NMax],hc;
int N,ecnt=0;
int E(int x,int y){ecnt++;
	if (x==y)return 0;
	/*int r=x*13687+y*68877+x*y*3611+x*x*6541+y*y*6329;
	return (r&0x7fffffff)%100001+1;*/
	if (x>y){int t=x;x=y;y=t;}
	if (y==x+1)return 1;
	return (100000-x-x)*10000+10000-y;
}
char label[NMax];
void Swap(int a,int b){
	int t;t=heap[a];heap[a]=heap[b];heap[b]=t;
	place[heap[a]]=a;place[heap[b]]=b;
}
void goDown(int a){
	while (a+a+1<hc){
		int j=a;
		if (dist[heap[a+a+1]]<dist[heap[j]])j=a+a+1;
		if (a+a+2<hc && dist[heap[a+a+2]]<dist[heap[j]])
			j=a+a+2;
		if (a==j)break;
		Swap(a,j);
		a=j;
	}
}
int outMin(){
	int r=heap[0];
	Swap(0,hc-1);
	hc--;
	goDown(0);
	return r;
}
void goUp(int a){
	while (a && dist[heap[a]]<dist[heap[(a-1)>>1]])
		Swap(a,(a-1)>>1),a=((a-1)>>1);
}
int main()
{
	int cntdec=0;
	scanf("%d",&N);
	int t1=clock();
	dist[0]=0;
	for (int i=1;i<N;i++){
		label[i]=0;
		dist[i]=E(0,i);
		place[heap[i]=i]=i;
	}
	hc=N;
	for (int i=hc-1;i>=0;i--)goDown(i);
	while (hc){
		int x=outMin();
		label[x]=1;
		for (int i=1;i<N;i++)if (!label[i]){
			int t=dist[x]+E(x,i);
			if (t<dist[i]){
				dist[i]=t;
				goUp(place[i]);
				cntdec++;
			}
		}
	}
	int t2=clock()-t1;
	//for (int i=0;i<N;i++)printf("%d %d\n",dist[i],E(0,i));
	printf("ecnt=%d cntdec=%d\n",ecnt,cntdec);
	int t3=clock();
	int becnt=ecnt;
	for (int i=0;i<becnt;i++)E(123,456);
	int t4=clock()-t3;
	printf("time=%d-%d=%d\n",t2,t4,t2-t4);
	getchar();getchar();
	return 0;
}
