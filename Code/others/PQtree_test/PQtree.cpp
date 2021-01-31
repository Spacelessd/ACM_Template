#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<vector>
#include<queue>
using namespace std;
#define N 205
int n,m,k,girl[N],girl1,time1;
struct node{
	char type,p_type;int time,full_size,partial_size,son_size,tmp_size,flag;  //flag= 0:empty 1:full 2:partial
	node *p,*link[2],*leftson,*rightson,*partial_son[2];
	vector<node*> son;
	void clear(){p=NULL;link[0]=link[1]=NULL;full_size=0;partial_size=0;son.clear();}
	node(){time=0;clear();}
	node *&l_r(node *x){if (link[0]==x)return link[1];else return link[0];}
	node *&find_link(node *x){return link[0]==x?link[0]:link[1];}
	bool findfather(){
		if (p==NULL||p_type=='P')return 1;
		if (link[0]==NULL||link[1]==NULL)return 1;
		node *ll=link[0],*ll_pre=this,*rr=link[1],*rr_pre=this,*tmp;int sum=0;
		while (sum<=girl1&&ll->l_r(ll_pre)!=NULL&&ll->time!=time1&&rr->l_r(rr_pre)!=NULL&&rr->time!=time1){
			tmp=ll_pre;ll_pre=ll;ll=ll->l_r(tmp);
			tmp=rr_pre;rr_pre=rr;rr=rr->l_r(tmp);
			++sum;
		}
		if (sum>girl1)return 0;
		if (ll->l_r(ll_pre)==NULL||ll->time==time1)p=ll->p;
		else p=rr->p;
		ll_pre=ll->l_r(ll_pre);
		while (ll!=this){
			ll->p=p;
			tmp=ll_pre;ll_pre=ll;ll=ll->l_r(tmp);
		}
		rr_pre=rr->l_r(rr_pre);
		while (rr!=this){
			rr->p=p;
			tmp=rr_pre;rr_pre=rr;rr=rr->l_r(tmp);
		}
		return 1;
	}
	void getflag(){
		if (full_size==son_size)flag=1;
		else flag=2;
	}
	bool valid(){
		if (x->type=='P')return 1;
		if (son.size()!=full_size)return 0;
		if (!full_size){
		}
		else {
		if (partial_size>=1&&(partial_son[0]->leftson->time!=time1||partial_son[0]->leftson->flag!=1)
			&&(partial_son[0]->rightson->time!=time1||partial_son[0]->rightson->flag!=1))return 0;
		}
		return 1;
	}
	node *full_son_l(){return *son.begin();}
	node *full_son_r(){return *(--son.end());}
	void insert_self(int rev){
		leftson->find_link(NULL)=link[rev];link[rev]->find_link(this)=leftson;
		rightson->find_link(NULL)=link[rev^1];link[rev^1]->find_link(this)=rightson;
	}
};
typedef vector<node*>::iterator vit;
#define rep(i,son) for (vit i=son.begin();i!=son.end();++i)
node *place[N],pool[N*2],*pertinent_root;
vector<node*> stack;
inline node *newnode(){
	if (stack.empty())printf("error:out of memory!\n");
	node *x=stack.back();stack.pop_back();
	return x;
}
inline void delnode(node *x){stack.push_back(x);}
deque<node*> Q;
bool bubble(){
	static deque<node*> Q;Q.clear();
	for (int i=1;i<=girl1;++i){
		Q.push_back(place[girl[i]]);
		place[girl[i]]->time=time1;
		place[girl[i]]->clear();
	}
	while (!Q.empty()){
		node *x=*Q.begin();Q.pop_front();
		if (!x->findfather())return 0;
		if (x->p!=NULL){
			if (x->p->time!=time1){
				x->p->time=time1;x->p->tmp_size=1;
				x->p->clear();
				Q.push_back(x->p);
			}
			else x->p->tmp_size+=1;
		}
	}
	Q.clear();::Q.clear();
	for (int i=1;i<=girl1;++i){
		Q.push_back(place[girl[i]]);
		::Q.push_back(place[girl[i]]);
		place[girl[i]]->full_size=1;
		place[girl[i]]->getflag();
	}
	while (Q.size()>1){
		node *x=*Q.begin();Q.pop_front();
		if (x->p!=NULL){
			x->p->tmp_size-=1;
			if (x->flag==1){
				x->p->full_size+=1;
				if (x->p->type=='P'){
					x->p->son.push_back(x);
				}
				else {
					if (x->p->son.size()==0)x->p->son.push_back(x);
				}
			}
			if (x->flag==2){
				x->p->partial_son[x->p->partial_size]=x;
				x->p->partial_size+=1;
			}
			if (x->p->tmp_size==0){
				if (x->p->type=='Q'&&x->p->son.size()){
					node *full_son=*(x->p->son.begin()),*pre=full_son->link[1],*y=full_son->l_r(pre),*tmp;
					while (y!=NULL&&y->time==time1&&y->flag==1){
						tmp=pre;pre=full_son;full_son=full_son->l_r(tmp);y=full_son->l_r(pre);
					}
					pre=full_son->l_r(pre);y=full_son->l_r(pre);
					while (y!=NULL&&y->time==time1&&y->flag==1){
						x->p->son.push_back(full_son);
						tmp=pre;pre=full_son;full_son=full_son->l_r(tmp);y=full_son->l_r(pre);
					}
				}
				x->p->getflag();if (!x->p->valid())return 0;
				Q.push_back(x->p);::Q.push_back(x->p);
			}
		}
	}
	pertinent_root=*Q.begin();
	return 1;
}
bool reduce(){
	Q.clear();
	for (int i=1;i<=girl1;++i)Q.push_back(place[girl[i]]);
	while (!Q.empty()){
		node *x=*Q.begin();Q.pop_front();
		if (!x->valid())return 0;
		if (x->type=='P'){
			if (x->son_size==1){  //leaf
				continue;
			}
			if (x->full_size==x->son_size){  //P1
				continue;
			}
			if (x==pertinent_root&&x->partial_size==0){  //P2
				/*if (x->full_son_l!=x->full_son_r){
					node *fa=newnode();fa->p=x;fa->son_size=x->full_size;
					fa->leftson=x->full_son_l;
					fa->rightson=x->full_son_r;
					fa->l=x->full_son_l->l;
					fa->r=x->full_son_r->r;
					if (fa->l==NULL)x->leftson=fa;
					if (fa->r==NULL)x->rightson=fa;
					if (x->full_son_l->l!=NULL)x->full_son_l->l->r=fa;
					if (x->full_son_r->r!=NULL)x->full_son_r->r->l=fa;
					x->full_son_l->p=fa;
					x->full_son_r->p=fa;
					x->full_son_l->l=NULL;
					x->full_son_r->r=NULL;
					x->son_size-=x->full_size-1;
					fa->full_son_l=fa->leftson;
					fa->full_son_r=fa->rightson;
				}*/
				continue;
			}
			if (x!=pertinent_root&&x->partial_size==0){  //P3
				
				continue;
			}
			if (x==partinent_root&&x->partial_size==1){  //P4
				node *pre=NULL,*tmp;
				while (x->leftson->flag==1){
					tmp=pre;pre=x->leftson;x->leftson=x->leftson->l_r(tmp);
				}
				pre=NULL;
				while (x->rightson->flag==1){
					tmp=pre;pre=x->rightson;x->rightson=x->rightson->l_r(tmp);
				}
				node *y=newnode();
				y->leftson=x->full_son_l();x->full_son_l()->p=y;
				y->rightson=x->full_son_r();x->full_son_r()->p=y;
				rep(i,x->son()){
					if (x->link[0]!=NULL)x->
				}
				rep(i,x->son()){
					vit j=i;
					if (i==x->son->begin()){
						--j;(*i)->link[0]=*j;
					}
					else (*i)->link[0]=NULL;
					j=i;++j;
					if (j!=x->son.end())(*i)->link[1]=*j;
					else (*i)->link[1]=NULL;
				}
				
				continue;
			}
			if (x!=partinent_root&&x->partial_size==1){  //P5
				
				continue;
			}
			if (x==partinent_root&&x->partial_size==2){  //P6
				node *pson0=x->partial_son[0],*pson1=x->partial_son[1];
				node *y=newnode();
				if (x->full_size==0){
					y->son_size=pson0->son_size+pson1->son_size;
					if (pson[0]->link[0]==pson1)
					if (pson0->link[1]==pson1&&pson1->link[0]==pson0){
						y->leftson=pson0->leftson;pson0->leftson->p=y;
						y->rightson=pson1->rightson;pson1->rightson->p=y;
						pson0->rightson->find_link(NULL)=
					}
					else 
				}
				else {
					y->son_size=pson0->son_size+pson1->son_size+x->son.size();
					if (pson0->link[1]->flag==1){
						
					}
					else
				}
				y->p=x;x->rightson->l_r(NULL)=y;x->rightson=y;
				delnode(pson0);delnode(pson1);
				continue;
			}
		}
		else if (x->type=='Q'){
			if (x->full_size==x->son_size){  //Q1
				continue;
			}
			if (x->partial_size==1){  //Q2
				/*x->son_size+=x->partial_son[0]->son_size;
				if (x->full_son_l->l!=NULL&&x->full_son_l->flag==2){
					node *tmp=x->full_son_l;
					if (tmp->rightson!=tmp->full_son_r||!tmp->full_ok())goto error;
					
					delnode(tmp);
					continue;
				}
				goto error;*/
			}
			if (x->partial_size==2){  //Q3
				node *pson0=x->partial_son[0],*pson1=x->partial_son[1];
				x->son_size+=pson0->son_size;
				x->son_size+=pson1->son_size;
				if (x->full_size==0){
					bool bool0=pson0->link[1]==pson1,bool1=pson1->link[0]==pson0;
					if (bool0)pson0->insert_self(0);
					else pson0->insert_self(1);
					if (bool1)pson1->insert_self(0);
					else pson1->insert_self(1);
				}
				else {
					bool bool0=(pson0->link[1]!=NULL&&pson0->link[1]->flag==1),
						 bool1=(pson0->link[0]!=NULL&&pson0->link[0]->flag==1);
					if (bool0)pson0->insert_self(0);
					else pson0->insert_self(1);
					if (bool1)pson1->insert_self(0);
					else pson1->insert_self(1);
				}
				delnode(pson0);delnode(pson1);
				continue;
			}
		}
		return 0;
	}
	return 1;
}
int main()
{
	freopen("gsample.in","r",stdin);
	//freopen("1.out","w",stdout);
	stack.clear();for (int i=0;i<N*2;++i)stack.push_back(pool+i);
	scanf("%d%d%d",&n,&m,&k);
	if (n>1){
		node *root=newnode();root->type='P';
		for (int i=1;i<=n;++i){
			place[i]=newnode();
			place[i]->p=root;
		}
	}
	else {
		node *root=newnode();root->type='P';
		place[1]=root;
	}
	for (int i=1;i<=m;++i){
		++time1;girl1=0;
		int x;scanf("%d",&x);
		while (x){girl[++girl1]=x;scanf("%d",&x);}
		if (!bubble())printf("error\n");
		if (!reduce())printf("error\n");
	}
	system("pause");for (;;);
	return 0;
}


