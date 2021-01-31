#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int ncnt=0,ncnt2=0;
template<class T>
struct ptr{
	T* p;
	ptr(){p=NULL;}
	ptr(T* q){p=q;p->ref++;}
	ptr(const ptr<T> &a){p=a.p;p->ref++;}
	~ptr(){
		if (p){p->ref--;
			if (!p->ref){delete p;ncnt2++;}
		}
	}
	T* operator->(){return p;}
	bool operator==(const ptr<T> &a)const{return p==a.p;}
	bool operator!=(const ptr<T> &a)const{return p!=a.p;}
	ptr<T>& operator=(const ptr<T> &a){
		if (p){p->ref--;
			if (!p->ref){delete p;ncnt2++;}
		}
		p=a.p;p->ref++;
		return (*this);
	}
};
struct node{
	int s,h;
	int d,ref;
	ptr<node> l,r;
}none;
typedef ptr<node> nodeptr;
nodeptr None(&none);
nodeptr newnode(){
	ncnt++;
	node *p=new node;
	return nodeptr(p);
}
nodeptr getnew(int c){
	nodeptr p=newnode();
	p->l=p->r=None;
	p->h=0;p->s=1;
	p->d=c;
	return p;
}
nodeptr getnew(nodeptr a,nodeptr b){
	if (a->h-b->h>1 || a->h-b->h<-1){
		puts("error come");
		putchar('0'+1/(None->l.p-None.p));
	}
	nodeptr p=newnode();
	p->l=a;p->r=b;
	p->s=a->s+b->s;
	p->h=(a->h<b->h?b->h:a->h)+1;
	return p;
}
nodeptr merge(nodeptr a,nodeptr b){
	if (a==None)return b;
	if (b==None)return a;
	if (a->h-b->h>=-1 && a->h-b->h<=1){
		return getnew(a,b);
	}else if (a->h<b->h){
		nodeptr c=b->l;
		if (c->h<=b->r->h || (a->h<c->r->h && c->l->h<c->r->h))
			return getnew(merge(a,c),b->r);
		return getnew(merge(a,c->l),getnew(c->r,b->r));
	}else{
		nodeptr c=a->r;
		if (c->h<=a->l->h || (b->h<c->l->h && c->r->h<c->l->h))
			return getnew(a->l,merge(c,b));
		return getnew(getnew(a->l,c->l),merge(c->r,b));
	}
}
nodeptr left(nodeptr p,int l){
	if (l==0 || p==None)return None;
	if (p->s==l)return p;
	if (p->l->s>=l)return left(p->l,l);
	return merge(p->l,left(p->r,l-p->l->s));
}
void dfs(node* p){
	if (p==None.p)return;
	if (p->h==0){
		printf("%c(%d)",(char)p->d,p->ref);
	}else{
		printf("[%d %d(%d)",p->h,p->s,p->ref);
		dfs(p->l.p);
		dfs(p->r.p);
		printf("]");
	}
}
nodeptr right(nodeptr p,int l){
	if (l==0 || p==None)return None;
	if (p->s==l)return p;
	if (p->r->s>=l)return right(p->r,l);
	return merge(right(p->l,l-p->r->s),p->r);
}
nodeptr substr(nodeptr p,int l,int r){
	return right(left(p,r+1),r-l+1);
}
vector<nodeptr> hist;
void readstr(vector<char> &a){
	char c;
	while (c=getchar(),c==10 || c==13 || c==' ');
	while (c!=10 && c!=13){
		a.push_back(c);
		c=getchar();
	}
}
void dfs_print(nodeptr p,int l,int r){
	if (p!=None){
		if (p->h==0)printf("%c",(char)p->d);
		else{
			int u=p->l->s;
			if (l<u)dfs_print(p->l,l,r);
			if (r>=u)dfs_print(p->r,l-u,r-u);
		}
	}
}
int main()
{
	None->l=None;
	None->r=None;
	None->h=-1;None->s=0;
	None->ref=10;
	int M;
	scanf("%d",&M);
	nodeptr r=None;
	vector<char> chs;
	readstr(chs);
	for (int i=0;i<(int)chs.size();i++){
		r=merge(r,getnew(chs[i]));
	}
	hist.push_back(r);
	char cmd[10];
	while (scanf("%s",cmd)!=EOF){
		if (cmd[0]=='I'){
			int x;
			scanf("%d",&x);
			scanf("%s",cmd);
			r=merge(merge(left(r,x),getnew(cmd[0])),right(r,r->s-x));
			hist.push_back(r);
		}else if (cmd[0]=='D'){
			int x;
			scanf("%d",&x);x--;
			r=merge(left(r,x),right(r,r->s-x-1));
			hist.push_back(r);
		}else if (cmd[0]=='P'){
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);y--;z--;
			dfs_print(hist[(int)hist.size()-1-x],y,z);
			puts("");
		}else if (cmd[0]=='C'){
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);x--;y--;z--;
			r=merge(merge(left(r,x),substr(r,y+1,z)),merge(substr(r,x,y),right(r,r->s-1-z)));
			hist.push_back(r);
		}
		if ((int)hist.size()>=M+M){
			int d=hist.size()-M;
			for (int i=0;i<M;i++)hist[i]=hist[i+d];
			hist.resize(M);
		}
	}
	fprintf(stderr,"ncnt=%d ncnt2=%d\n",ncnt,ncnt2);
	system("pause");for (;;);
	return 0;
}


