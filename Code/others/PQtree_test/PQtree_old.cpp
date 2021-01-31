#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<queue>
#include<set>
using namespace std;
#define N 205
struct node{
	char type;int time,size;  //flag= 0:empty 1:full 2:partial
	node *p;
	set<node*> son,son_full,son_partial;
	node():p(NULL),time(0){}
};
typedef set<node*>::iterator sit;
int n,m,k,girl[N],girl1,time1;
node *place[N];
node stack[N*2];int stack1;
void bubble(){
	static deque<node*> Q;Q.clear();
	for (int i=1;i<=girl1;++i)Q.push_back(place[girl[i]]);
	while (!Q.empty()){
		node *x=Q.front();Q.pop_front();
		
	}
}
void reduce(){
	static deque<node*> Q;Q.clear();
	for (int i=1;i<=girl1;++i)Q.push_back(place[girl[i]]);
	while (!Q.empty()){
		node *x=Q.front();Q.pop_front();
		x->size=0;
		if (x->time!=time1){x->son_full.clear();x->son_partial.clear();x->time=time1;}
		int cnt_full=x->son_full.size(),cnt_partial=x->son_partial.size(),cnt_empty=x->son.size()-cnt_full-cnt_partial;
		for (sit i=x->son_full.begin();i!=x->son_full.end();++i)x->size+=(*i)->size;
		for (sit i=x->son_partial.begin();i!=x->son_partial.end();++i)x->size+=(*i)->size;
		if (x->type=='P'){
			if (x->son.size()==1){  //leaf
				x->size=1;
				if (x->p!=NULL){
					if (x->p->time!=time1){
						x->p->time=time1;
						x->p->son_full.clear();x->p->son_partial.clear();
					}
					x->p->son_full.insert(x);
				}
				if (x->size==girl1)break;
				else continue;
			}
			if (cnt_full==x->son.size()){  //P1
				if (x->p!=NULL){
					if (x->p->time!=time1){
						x->p->time=time1;
						x->p->son_full.clear();x->p->son_partial.clear();
					}
					x->p->son_full.insert(x);
				}
				if (x->size==girl1)break;
				else continue;
			}
			if (x->size==girl1&&cnt_full&&cnt_empty&&!cnt_partial){  //P2
				if (cnt_full>1){
					node *tmp=&stack[++stack1];
					tmp->type='P';tmp->p=x;x->son.insert(tmp);
					for (sit i=x->son_full.begin();i!=x->son_full.end();++i)
						x->son.erase(*i),tmp->son.insert(*i),(*i)->p=tmp;
				}
				if (x->size==girl1)break;
				else continue;
			}
			if (x->size!=girl1&&cnt_full&&cnt_empty&&!cnt_partial){  //P3
				node *now=x;
				if (cnt_empty>1){
					node *tmp=&stack[++stack1];
					tmp->type='Q';tmp->p=x->p;x->p.son.erase(x);x->p.son.insert(tmp);
					x->type='P';x->p=tmp;tmp->son.insert(x);
					now=tmp;
				}
				if (cnt_full>1){
					node *tmp=&stack[++stack1];
					tmp->type='P';tmp->p=now;now->son.insert(tmp);
					for (sit i=x->son_full.begin();i!=x->son_full.end();++i)
						x->son.erase(*i),tmp->son.insert(*i),(*i)->p=tmp;
				}
				x=now;
				if (x->size==girl1)break;
				else continue;
			}
			if (x->size==girl1&&cnt_partial==1){  //P4
			
				if (x->size==girl1)break;
				else continue;
			}
			if (){  //P5
				if (x->size==girl1)break;
				else continue;
			}
			if (){  //P6
				if (x->size==girl1)break;
				else continue;
			}
		}
		else {
			if (cnt_full==x->son.size()){  //Q1
				x->time=time1;
				continue;
			}
			if (cnt_partial==1){
			}
			if (cnt_partial==2){
			}
		}
		printf("WA\n");
	}
}
void print(const node &x){
	
}
int main()
{
	freopen("1.in","r",stdin);
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
	}else {
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


