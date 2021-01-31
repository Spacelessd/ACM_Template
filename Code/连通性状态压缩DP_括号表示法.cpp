#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define ll long long
#define N 15
#define maxn 1594323
struct node{
	int state;
	ll sum;
}Q_pool[2][maxn],*Q,*Q1;
int pos[maxn],power[N+1],n,m,tail,tail1,last,place;
char map[N][N];
inline int get(int x,int index){
	return x/power[index]%3;
}
inline int set(int x,int index,int value){
	return x+=(-x/power[index]%3+value)*power[index];
}
inline int RtoL(int state,int i){
	int stack=0;
	for (;i<=m;++i){
		int bit=get(state,i);
		if (bit==1)++stack;
		else if (bit==2)--stack;
		if (!stack)return set(state,i,1);
	}
}
inline int LtoR(int state,int i){
	int stack=0;
	for (;i;--i){
		int bit=get(state,i);
		if (bit==2)++stack;
		else if (bit==1)--stack;
		if (!stack)return set(state,i,2);
	}
}
void insert(int state,ll sum){
	if (place==m&&get(state,m+1))return;
	if (pos[state])Q[pos[state]].sum+=sum;
	else {
		pos[state]=++tail;
		Q[tail].state=state;
		Q[tail].sum=sum;
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	power[1]=1;
	for (int i=2;i<=N;++i)power[i]=power[i-1]*3;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j){
			while (scanf("%c",&map[i][j]),(map[i][j]!='*'&&map[i][j]!='.'));
			if (map[i][j]=='.')last=i*m+j;
		}
	for (int i=0;i<maxn;++i)pos[i]=0;
	Q=Q_pool[0];Q1=Q_pool[1];
	tail=0;insert(0,1);
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j){
			place=j;
			for (int head=1;head<=tail;++head)
				pos[Q[head].state]=0;
			node *tmp=Q;Q=Q1,Q1=tmp;
			tail1=tail;tail=0;
			for (int head=1;head<=tail1;++head){
				int state=Q1[head].state;
				ll sum=Q1[head].sum;
				int up=get(state,j),left=get(state,m+1);
				bool crash=(map[i][j]=='*');
				if (up==0&&left==0){  //Case 1
					if (!crash)state=set(set(state,j,1),m+1,2);
					insert(state,sum);
				}
				else if (up==2&&left==1){  //Case 2.3
					if (i*m+j==last)insert(set(set(state,j,0),m+1,0),sum);
				}
				else if (crash)continue;
				else if (up==0||left==0){  //Case 3
					insert(set(set(state,j,up+left),m+1,0),sum);
					insert(set(set(state,m+1,up+left),j,0),sum);
				}
				else if (up==1&&left==1){  //Case 2.1
					state=RtoL(state,j);
					insert(set(set(state,j,0),m+1,0),sum);
				}
				else if (up==2&&left==2){  //Case 2.2
					state=LtoR(state,j);
					insert(set(set(state,j,0),m+1,0),sum);
				}
				else if (up==1&&left==2){  //Case 2.4
					insert(set(set(state,j,0),m+1,0),sum);
				}
			}
		}
	printf("%I64d\n",Q[pos[0]].sum);
	system("pause");for (;;);
	return 0;
}


