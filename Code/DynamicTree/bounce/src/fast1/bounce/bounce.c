#include <stdio.h>
#define maxn 200010
typedef struct _Splay{struct _Splay *c[2],*f;int s;}Splay,*PSplay;
Splay null,st[maxn];
char str[1500000],*p=str,*o=str;
inline PSplay fa(PSplay x){return x->f->c[0]==x||x->f->c[1]==x?x->f:&null;}
inline PSplay updt(PSplay x){x->s=x->c[0]->s+x->c[1]->s+1;return x;}
inline PSplay node(PSplay x,PSplay f){x->f=f;x->c[0]=x->c[1]=&null;x->s=1;return x;}
inline PSplay rot(PSplay x){
    PSplay fx=fa(x),ffx=fa(fx);
    _Bool c=fx->c[1]==x,fc=ffx->c[1]==fx;
    if(fx!=&null){
        x->f=fx->f;
        if((fx->c[c]=x->c[!c])!=&null)fx->c[c]->f=fx;
        if(ffx!=&null)ffx->c[fc]=x;
        updt((fx->f=x)->c[!c]=fx);
    }return x;
}inline PSplay splay(PSplay x,PSplay p){
    PSplay fx,ffx;if(x==&null)return x;
    for(;(fx=fa(x))!=p;rot(x))if((ffx=fa(fx))!=p)rot((ffx->c[1]==fx)==(fx->c[1]==x)?fx:x);
    return updt(x);
}inline getint(){
    int re=0;
    while(*p<'0'||*p>'9')p++;
    while(*p>='0'&&*p<='9')re=re*10+*p++-48;
    return re;
}inline PSplay Access(PSplay x){
    PSplay t=&null,y=x;
    while(splay(x,&null)->c[1]=t,x->f!=&null)x=(t=updt(x))->f;
    return splay(y,&null);
}inline void print(x){
    char buf[10],*b=buf;
    while(x)*b++=x%10+48,x/=10;
    while(b--!=buf)*o++=*b;
    *o++='\n';
}main(){
	freopen("bounce.in","r",stdin);
	freopen("bounce.out","w",stdout);
    int n,i=-1,x,k,t;fread(p,1,1500000,stdin);
    null.f=null.c[0]=null.c[1]=&null;
    for(n=getint();++i!=n;node(st+i,i+(k=getint())>=n?&null:st+i+k));
    for(t=getint();t--;)if(*++p==49)p++,print(Access(st+(x=getint()))->c[0]->s+1);
    else if(*p==50){
        p++;Access(st+(x=getint()))->c[0]->f=&null;st[x].c[0]=&null;
        updt(st+x)->f=x+(k=getint())>=n?&null:st+x+k;
    }else t++;*--o=0;return puts(str),0;
}
