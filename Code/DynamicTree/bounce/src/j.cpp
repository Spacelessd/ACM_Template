#include <stdio.h>
#define maxn 200000
typedef struct _Splay{struct _Splay *c[2],*f,*p;int s;}Splay,*PSplay;
Splay null,st[maxn];
char str[150],*p=str,out[400000],*o=out;
inline PSplay updt(PSplay x){if(x!=&null)x->s=x->c[0]->s+x->c[1]->s+1;return x;}
inline PSplay extr(PSplay x,bool c){while(x->c[c]!=&null)x=x->c[c];return x;}
inline PSplay node(PSplay x,PSplay p){x->f=x->c[0]=x->c[1]=&null;x->s=1;x->p=p;return x;}
inline PSplay rot(PSplay x){
    PSplay fx=x->f,ffx=fx->f;
    bool c=fx->c[1]==x,fc=ffx->c[1]==fx;
    if(fx!=&null){
        if((fx->c[c]=x->c[!c])!=&null)fx->c[c]->f=fx;
        if((x->f=ffx)!=&null)ffx->c[fc]=x;
        updt((fx->f=x)->c[!c]=fx);
    }return x;
}inline PSplay splay(PSplay x,PSplay p){
    if(x==&null)return x;for(;x->f!=p;rot(x))if(x->f->f!=p)rot((x->f->f->c[1]==x->f)==(x->f->c[1]==x)?x->f:x);
    return updt(x);
}
inline int getint(){
    int re=0;
    while(*p<'0'||*p>'9')p++;
    while(*p>='0'&&*p<='9')re=re*10+*p++-48;
    return re;
}inline PSplay Access(PSplay x){
    PSplay t=splay(x,&null);x->c[1]=x->c[1]->f=&null;
    while((x=splay(extr(x,0),&null))->p!=&null){
        splay(x->p,&null)->c[1]->f=&null;
        x=(x->p->c[1]=x)->f=x->p;
    }return t;
}
inline void print(int x){
    char buf[10],*b=buf;
    while(x)*b++=x%10+48,x/=10;
    while(b--!=buf)*o++=*b;
    *o++='\n';
}main(){
    int n,i=-1,x,k,t;fread(p,1,1500000,stdin);
    null.f=null.c[0]=null.c[1]=&null;
    for(n=getint();++i!=n;node(st+i,i+(k=getint())>=n?&null:st+i+k));
    for(t=getint();t--;)if(getint()==1)print(splay(Access(st+getint()),&null)->c[0]->s+1);
    else{
        splay(st+(x=getint()),&null)->c[0]->f=&null;
        st[x].c[0]=&null;
        updt(updt(st+x)->p=x+(k=getint())>=n?&null:st+x+k);
    }*--o=0;return puts(out),0;
}
