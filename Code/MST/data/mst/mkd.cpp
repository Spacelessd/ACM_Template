#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
inline int Rand(){return rand()*rand();}
int main()
{
	int n,m,x,y,z;
	freopen("mst.in","w",stdout);
	srand(time(0));
	scanf("%d%d",&n,&m);
	printf("%d %d\n",n,m);
	for (int i=2;i<=n;++i){
		int x=rand()*rand()%(i-1)+1;
		printf("%d %d %d\n",x,i,Rand());
	}
	m-=n-1;
	for (int i=1;i<=m;++i){
		x=rand()%n+1;y=rand()%n+1;
		printf("%d %d %d\n",x,y,Rand());
	}
	//system("pause");
	return 0;
}


