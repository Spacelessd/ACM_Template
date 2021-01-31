#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
struct node{
	int s,h;
	int d;
	node *l,*r;
}none,*None=&none;
int ncnt=0;
node * newnode(){
	ncnt++;
	return new node;
}
node * getnew(int c){
	node *p=newnode();
	p->l=p->r=None;
	p->h=0;p->s=1;
	p->d=c;
	return p;
}
node * getnew(node *a,node *b){
	if (a->h-b->h>1 || a->h-b->h<-1){
		puts("error come");
		putchar('0'+1/(None->l-None));
	}
	node *p=newnode();
	p->l=a;p->r=b;
	p->s=a->s+b->s;
	p->h=(a->h<b->h?b->h:a->h)+1;
	return p;
}
node * merge(node *a,node *b){
	if (a==None)return b;
	if (b==None)return a;
	if (a->h-b->h>=-1 && a->h-b->h<=1){
		return getnew(a,b);
	}else if (a->h<b->h){
		node *c=b->l;
		if (c->h<=b->r->h || (a->h<c->r->h && c->l->h<c->r->h))
			return getnew(merge(a,c),b->r);
		return getnew(merge(a,c->l),getnew(c->r,b->r));
	}else{
		node *c=a->r;
		if (c->h<=a->l->h || (b->h<c->l->h && c->r->h<c->l->h))
			return getnew(a->l,merge(c,b));
		return getnew(getnew(a->l,c->l),merge(c->r,b));
	}
}
node * left(node *p,int l){
	if (l==0 || p==None)return None;
	if (p->s==l)return p;
	if (p->l->s>=l)return left(p->l,l);
	return merge(p->l,left(p->r,l-p->l->s));
}
void dfs(node *p){
	if (p==None)return;
	if (p->h==0){
		printf("%c",(char)p->d);
	}else{
		//printf("[%d %d ",p->h,p->s);
		dfs(p->l);
		dfs(p->r);
		//printf("]");
	}
}
node * right(node *p,int l){
	if (l==0 || p==None)return None;
	if (p->s==l)return p;
	if (p->r->s>=l)return right(p->r,l);
	return merge(right(p->l,l-p->r->s),p->r);
}
node * substr(node *p,int l,int r){
	return right(left(p,r+1),r-l+1);
}
vector<node*> hist;
void readstr(vector<char> &a){
	char c;
	while (c=getchar(),c==10 || c==13 || c==' ');
	while (c!=10 && c!=13){
		a.push_back(c);
		c=getchar();
	}
}
void dfs_print(node *p,int l,int r){
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
	None->l=None->r=None;None->h=-1;None->s=0;
	int M;
	scanf("%d",&M);
	node *r=None;
	vector<char> chs;
	readstr(chs);
	for (int i=0;i<(int)chs.size();i++)
		r=merge(r,getnew(chs[i]));
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
		//dfs(r);puts("");
	}
	system("pause");for (;;);
	return 0;
}


