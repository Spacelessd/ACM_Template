#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 100005
#define CH 27
#define SPECIALCHAR ('z'+1)
#define ERROR -1
#define TYPE1 1
#define TYPE2 2
#define LEAF 1
#define NOTLEAF 2
struct node{
	int start,end,flag,length;
	node *next[CH],*link,*father;
};
void print(node *x){
	if (x==NULL)return;
	printf("%d %d %d %d\n",x->start,x->end,x->length,x->flag);
	for (int i=0;i<CH;++i)print(x->next[i]);
}
char str[N],buf[N];
node head;
node *P,*G,*U,*V;
int W[2],len,len2;
inline char get(char ch){return ch-'a';}
void Createnode(node *&x){
	x=(node*)malloc(sizeof(node));
	x->start=x->end=x->length=ERROR;
	for (int i=0;i<CH;++i)x->next[i]=NULL;
	x->link=x->father=NULL;
	x->flag=LEAF;
}
void Init(node &h,char s[]){
	h.start=h.end=ERROR;
	for (int i=0;i<CH;++i)h.next[i]=NULL;
	h.link=&h;h.father=NULL;
	h.flag=LEAF;h.length=0;
	
	len=strlen(s);
	s[len]=SPECIALCHAR;
	s[++len]=0;
}
int FindV(char s[]){
	int old=0;node *t=U->next[get(s[W[0]])];
	while (W[1]>t->end-t->start+1+old){
		old+=t->end-t->start+1;
		t=t->next[get(s[W[0]+old])];
	}
	if (W[1]==t->end-t->start+1+old){
		V=t;P->link=V;
		return TYPE1;
	}else {
		node *newt; Createnode(newt);
		newt->start=t->start;newt->end=t->start+W[1]-old-1;
		newt->father=t->father;
		newt->length=newt->father->length+newt->end-newt->start+1;
		t->father->next[get(s[t->start])]=newt;
		t->start=newt->end+1;t->father=newt;
		newt->next[get(s[t->start])]=t;
		V=newt;P->link=V;
		return TYPE2;
	}
}
int Insert(node *x,int start,char s[]){
	int posbegin,posend,i;
	char ch=get(s[start]);
	if (x->next[ch]==NULL){
		Createnode(x->next[ch]);
		x->next[ch]->start=start;
		x->next[ch]->end=len-1;
		x->next[ch]->father=x;
		x->next[ch]->length=x->length+len-start;
		x->flag=NOTLEAF;P=x;
		return TYPE1;
	}else {
		posbegin=x->next[ch]->start;
		posend=x->next[ch]->end;
		for (i=posbegin;i<=posend;++i){
			if (s[i]!=s[start+i-posbegin])break;
		}
		if (i==posend+1){
			return Insert(x->next[ch],start+i-posbegin,s);
		}else {
			node *t; Createnode(t);
			t->start=posbegin;t->end=i-1;t->flag=NOTLEAF;
			x->next[ch]->start=i;
			t->next[get(s[i])]=x->next[ch];
			t->next[get(s[i])]->father=t;
			x->next[ch]=t;
			t->father=x;
			t->length=x->length+t->end-t->start+1;
			Insert(t,start+i-posbegin,s);
			G=x;P=t;
			return TYPE2;
		}
	}
}
int Select(int start,char s[],int type){
	int result,result1,result2;
	if (type==TYPE1){
		U=P->link;
		result=Insert(U,start+U->length,s);
	}else {
		U=G->link;
		if (G->link==G){
			W[0]=P->start+1;
			W[1]=P->end-P->start;
		}else {
			W[0]=P->start;
			W[1]=P->end-P->start+1;
		}
		if (W[1]==0){
			V=G;P->link=V;
			result=Insert(V,start,s);
		}else {
			result1=FindV(s);
			result2=Insert(V,start+V->length,s);
			if (result1==TYPE2){
				G=P->father;
				result=result1;
			}else result=result2;
		}
	}
	return result;
}
void Buildnode(node &h,char s[]){
	int type=TYPE1;
	node *&x=h.next[get(s[0])];
	Createnode(x);
	x->start=0;x->end=len-1;
	x->father=&h;
	x->length=h.length+x->end-x->start+1;
	h.flag=NOTLEAF;P=&h;
	for (int i=1;i<len;++i)type=Select(i,s,type);
}
int FindString(int start,char s[]){
	int result,tmp=0;
	node *x=P->next[get(s[start])];
	result=P->length;
	if (x==NULL){
		P=P->link;return result;
	}
	for (int i=start;i<len2;++i){
		if (x->start+i-start-tmp>x->end){
			tmp=i-start;P=x;
			x=x->next[get(s[start+tmp])];
			if(x==NULL)break;
		}
		if(s[i]!=str[x->start+i-start-tmp])break;
		++result;
	}
    P=P->link;
    return result;
}
int Search(node &h,char s[]){
	int result=0,tmp;
	len2=strlen(s);
	P=&head;
	for (int i=0;i<len2;++i){
		tmp=FindString(i+P->length,s);
		if (result<tmp)result=tmp;
		if (result>=len2-i)break;
	}
	return result;
}
int main(){
	freopen("1.in","r",stdin);
	int result;
	scanf("%s",str);
	Init(head,str);
	Buildnode(head,str);
	scanf("%s",buf);
	result=Search(head,buf);
	printf("%d\n",result);
	system("pause");for (;;);
}





