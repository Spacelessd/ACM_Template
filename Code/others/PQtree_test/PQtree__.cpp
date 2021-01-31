#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<queue>
using namespace std;
#define N 205
int n,m,k,girl[N],girl1,time1;
struct node{
	char type;int time,size;  //flag= 0:empty 1:full 2:partial
	node *p,*l,*r;
	node():p(NULL),time(0){}
	void findfather(){
		time=time1;
		if (l==NULL||r==NULL)
		node *Left=this,*Right=this;
		while (Left!=this)Left->p=p,Left=Left->r;
		while (Right!=this)Right->p=p,Right=Right->l;
	}
};
node *place[N],stack[N*2];int stack1;
void bubble(){
	static deque<node*> Q;Q.clear();
	for (int i=1;i<=girl1;++i)Q.push_back(place[girl[i]]);
	while (!Q.empty()){
		
	}
}
void reduce(){
	static deque<node*> Q;Q.clear();
	for (int i=1;i<=girl1;++i)Q.push_back(place[girl[i]]);
	while (!Q.empty()){
		
	}
}
int main()
{
	freopen("gsample.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	stack1=0;
	if (n>1){
		++stack1;stack[1].type='P';
		for (int i=1;i<=n;++i){
			place[i]=&stack[++stack1];
			place[i]->p=&stack[1];
			stack[1].son.insert(place[i]);
		}
	}
	else {
		++stack1;stack[1].type='P';
		place[1]=&stack[1];
	}
	for (int i=1;i<=m;++i){
		++time1;girl1=0;
		int x;scanf("%d",&x);
		while (x){girl[++girl1]=x;scanf("%d",&x);}
		reduce();
	}
	system("pause");for (;;);
	return 0;
}


