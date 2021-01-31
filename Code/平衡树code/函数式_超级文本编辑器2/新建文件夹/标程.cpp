#include <cstdio> 
#include <algorithm> 
#include <vector> 
using namespace std; 
struct node{ 
	int s,h; 
	int d,ref; 
	node *l,*r; 
}none,*None=&none; 
int ncnt=0; 
int ncnt2=0,ncnt3=0; 
node * npool=NULL; 
void giveback(node *p){ 
	if (p){ 
		p->ref--; 
		if (!p->ref){ 
			giveback(p->l);giveback(p->r); 
			p->r=npool;npool=p; 
			ncnt2++; 
		} 
	} 
} 
node * newnode(){ 
	if (npool==NULL){ 
		node *q=new node[10000]; 
		for (int i=0;i<10000;i++){ 
			q[i].r=npool;npool=q+i; 
		} 
		ncnt3+=10000; 
	} 
	node *p=npool;npool=npool->r; 
	ncnt++; 
	return p; 
} 
node * newref(node *p){ 
	p->ref++; 
	return p; 
} 
node * getnew(int c){ 
	node *p=newnode(); 
	p->l=newref(None); 
	p->r=newref(None); 
	p->h=0;p->s=1; 
	p->d=c; 
	p->ref=1; 
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
	p->ref=1; 
	return p; 
} 
node * merge(node *a,node *b){ 
	if (a==None)return newref(b); 
	if (b==None)return newref(a); 
	if (a->h-b->h>=-1 && a->h-b->h<=1){ 
		return getnew(newref(a),newref(b)); 
	}else if (a->h<b->h){ 
		node *c=b->l; 
		if (c->h<=b->r->h || (a->h<c->r->h && c->l->h<c->r->h)) 
			return getnew(merge(a,c),newref(b->r)); 
		return getnew(merge(a,c->l),getnew(newref(c->r),newref(b->r))); 
	}else{ 
		node *c=a->r; 
		if (c->h<=a->l->h || (b->h<c->l->h && c->r->h<c->l->h)) 
			return getnew(newref(a->l),merge(c,b)); 
		return getnew(getnew(newref(a->l),newref(c->l)),merge(c->r,b)); 
	} 
} 
node * merge2(node *p,node *q){node *r=merge(p,q);giveback(p);giveback(q);return r;} 
void dfs(node *p){ 
	if (p==None)return; 
	if (p->h==0){ 
		printf("%c",(char)p->d); 
	}else{ 
		dfs(p->l); 
		dfs(p->r); 
	} 
} 
node * left(node *p,int l){ 
	if (l==0 || p==None)return newref(None); 
	if (p->s==l)return newref(p); 
	if (p->l->s>=l)return left(p->l,l); 
	return merge2(newref(p->l),left(p->r,l-p->l->s)); 
} 
node * right(node *p,int l){ 
	if (l==0 || p==None)return newref(None); 
	if (p->s==l)return newref(p); 
	if (p->r->s>=l)return right(p->r,l); 
	return merge2(right(p->l,l-p->r->s),newref(p->r)); 
} 
node * left2(node *p,int l){node *r=left(p,l);giveback(p);return r;} 
node * right2(node *p,int l){node *r=right(p,l);giveback(p);return r;} 
node * substr(node *p,int l,int r){ 
	return right2(left(p,r+1),r-l+1); 
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
	None->ref=3; 
	int M; 
	scanf("%d",&M); 
	node *r=newref(None); 
	vector<char> chs; 
	readstr(chs); 
	for (int i=0;i<(int)chs.size();i++)r=merge2(r,getnew(chs[i])); 
	hist.push_back(r); 
	char cmd[10]; 
	while (scanf("%s",cmd)!=EOF){ 
		if (cmd[0]=='I'){ 
			int x; 
			scanf("%d",&x); 
			scanf("%s",cmd); 
			r=merge2(merge2(left(r,x),getnew(cmd[0])),right(r,r->s-x)); 
		}else if (cmd[0]=='D'){ 
			int x,y; 
			scanf("%d%d",&x,&y);x--;y--; 
			r=merge2(left(r,x),right(r,r->s-y-1)); 
		}else if (cmd[0]=='P'){ 
			int x,y,z; 
			scanf("%d%d%d",&x,&y,&z);y--;z--; 
			dfs_print(hist[(int)hist.size()-1-x],y,z); 
			puts(""); 
			continue; 
		}else if (cmd[0]=='C'){ 
			int x,y,z; 
			scanf("%d%d%d",&x,&y,&z);x--;y--; 
			r=merge2(left(r,z),merge2(substr(r,x,y),right(r,r->s-z))); 
		} 
		hist.push_back(r); 
		if ((int)hist.size()>=M+M){ 
			int d=hist.size()-M; 
			for (int i=0;i<d;i++)giveback(hist[i]); 
			for (int i=0;i<M;i++)hist[i]=hist[i+d]; 
			hist.resize(M); 
		} 
	} 
	//fprintf(stderr,"ncnt=%d ncnt2=%d ncnt3=%d\n",ncnt,ncnt2,ncnt3); 
	system("pause");
	return 0; 
} 


