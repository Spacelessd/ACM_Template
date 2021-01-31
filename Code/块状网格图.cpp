#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#define N 505
#define SqrtN 30
struct Block{
	int x1,y1,x2,y2,sum;
	int xsum[SqrtN],ysum[SqrtN];
};
int n,Lim;
int a[N][N];char str[N];
Block *link[N][N],Pool[N*3];int p1;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
void Build(){
	p1=0;Block *x;
	for (int i=1;i<=n;i+=Lim)
		for (int j=1;j<=n;j+=Lim){
			x=Pool+(p1++);x->x1=i;x->y1=j;x->sum=0;
			x->x2=i+Lim-1>n?n:i+Lim-1;x->y2=j+Lim-1>n?n:j+Lim-1;
			link[i][j]=x;
			for (int i=0;i<=x->x2-x->x1;++i)x->xsum[i]=0;
			for (int i=0;i<=x->y2-x->y1;++i)x->ysum[i]=0;
			for (int i1=x->x1;i1<=x->x2;++i1)
				for (int j1=x->y1;j1<=x->y2;++j1)
					x->sum+=a[i1][j1],x->xsum[i1-x->x1]+=a[i1][j1],x->ysum[j1-x->y1]+=a[i1][j1];
		}
}
void Changex(int xx,char str[]){
	int i,delta;
	for (i=1;i<=n;i+=Lim)if (i<=xx&&i+Lim>xx)break;
	for (int j=1;j<=n;j+=Lim){
		Block *x=link[i][j];
		for (int i1=x->y1;i1<=x->y2;++i1)
			delta=str[i1]-a[xx][i1],x->xsum[xx-x->x1]+=delta,x->ysum[i1-x->y1]+=delta,x->sum+=delta;
	}
}
void Changey(int yy,char str[]){
	int j,delta;
	for (j=1;j<=n;j+=Lim)if (j<=yy&&j+Lim>yy)break;
	for (int i=1;i<=n;i+=Lim){
		Block *x=link[i][j];
		for (int i1=x->x1;i1<=x->x2;++i1)
			delta=str[i1]-a[i1][yy],x->xsum[i1-x->x1]+=delta,x->ysum[yy-x->y1]+=delta,x->sum+=delta;
	}
}
int Query(int xx1,int yy1,int xx2,int yy2){
	int tmp=0;
	for (int i=1;i<=n;i+=Lim)
		for (int j=1;j<=n;j+=Lim){
			int x1=link[i][j]->x1,y1=link[i][j]->y1,
				x2=link[i][j]->x2,y2=link[i][j]->y2;
			if (max(x1,xx1)>min(x2,xx2)||max(y1,yy1)>min(y2,yy2))continue;
			if (x1>=xx1&&y1>=yy1&&x2<=xx2&&y2<=yy2)tmp+=link[i][j]->sum;
			else if (x1>=xx1&&x2<=xx2)
				for (int i1=max(y1,yy1)-y1;i1<=min(y2,yy2)-y1;++i1)
					tmp+=link[i][j]->ysum[i1];
			else if (y1>=yy1&&y2<=yy2)
				for (int i1=max(x1,xx1)-x1;i1<=min(x2,xx2)-x1;++i1)
					tmp+=link[i][j]->xsum[i1];
			else
				for (int i=max(x1,xx1);i<=min(x1,xx2);++i)
					for (int j=max(y1,yy1);j<=min(y1,yy2);++j)
						tmp+=a[i][j];
		}
	return tmp;
}
void print(){
	printf("start\n");
	for (int i=1;i<=n;++i){
		for (int j=1;j<=n;++j)
			printf("%d ",a[i][j]);
		printf("\n");
	}
	printf("end\n");
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int T,q,x,y,x1,y1,x2,y2;scanf("%d",&T);
	while (T--){
		scanf("%d%d",&n,&q);Lim=(int)sqrt(n)+1;
		for (int i=1;i<=n;++i){
			scanf("%s",str);
			for (int j=0;j<n;++j)str[j]=str[j]-'A'+1;
			for (int j=1;j<=n;++j)a[i][j]=str[j-1];
		}
		Build();int ch;
		while (q--){
			scanf("%d",&ch);
			if (ch==0){
				scanf("%d%d%s",&x,&y,str);
				for (int i=0;i<n;++i)str[i]=str[i]-'A'+1;
				if (x==0)Changex(y+1,str-1);
					else Changey(y+1,str-1);
			}
			else {
				scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
				printf("%d\n",Query(x1+1,y1+1,x2+1,y2+1));
			}
		}
	}
	system("pause");for (;;);
	return 0;
}


