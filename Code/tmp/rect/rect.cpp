/*
ID:hqztrue1
PROB:rect1
LANG:C++
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 10010
#define Mc 2500
struct node{
	int x1,y1,x2,y2;
	int color;
};
node C[N],Now;
int A,B,n,tot;
int color[Mc+10];
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void Add(int x1,int y1,int x2,int y2,int c){
	++tot;C[tot].x1=x1;C[tot].y1=y1;C[tot].x2=x2;C[tot].y2=y2;C[tot].color=c;
}
bool Cross(int x1,int x2,int x3,int x4){
	if (x1>x4||x3>x2)return 0;
		else return 1;
}
void Cut(int x1,int y1,int x2,int y2,int c,int D){
	int k1,k2;
	if (D==1){
		k1=max(x1,Now.x1);k2=min(x2,Now.x2);
		if (x1<k1)Add(x1,y1,k1-1,y2,c);
		if (k2<x2)Add(k2+1,y1,x2,y2,c);
		Cut(k1,y1,k2,y2,c,2);
		
	}else if (D==2){
		k1=max(y1,Now.y1);k2=min(y2,Now.y2);
		if (y1<k1)Add(x1,y1,x2,k1-1,c);
		if (k2<y2)Add(x1,k2+1,x2,y2,c);
	}
}
int main(){
	freopen("rect1.in","r",stdin);
	freopen("rect1.out","w",stdout);
	int x1,y1,x2,y2,c,i,j;
	scanf("%d%d%d",&A,&B,&n);
	tot=0;Add(0,0,A-1,B-1,1);
	for (i=1;i<=n;++i){
		scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&c);
		Now.x1=x1;Now.y1=y1;Now.x2=x2-1;Now.y2=y2-1;Now.color=c;
		for (j=1;j<=tot;++j){
			if (Cross(C[j].x1,C[j].x2,Now.x1,Now.x2)&&
				Cross(C[j].y1,C[j].y2,Now.y1,Now.y2)){
					Cut(C[j].x1,C[j].y1,C[j].x2,C[j].y2,C[j].color,1);
					C[j--]=C[tot--];
				}
		}
		C[++tot]=Now;
	}
	for (i=1;i<=tot;++i)
		color[C[i].color]+=(C[i].x2-C[i].x1+1)*(C[i].y2-C[i].y1+1);
	for (i=1;i<=Mc;++i)
		if (color[i])printf("%d %d\n",i,color[i]);
	//printf("%d\n",tot);
	//system("pause");
}



