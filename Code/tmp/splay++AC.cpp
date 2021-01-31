#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<string>
#include<iostream>
using namespace std;
#define maxlongint 2147483647
char read_line[20];
/*$inline on*/
/*$m 1000000000*/

typedef struct{
int l,r,key,size,p,Min,sum,delta;
    } splaya;

splaya a[1000000+1];
int stack[500000+1],num[500000+1],c[500000+1];
int root,n,j,q,x,y,z,ll,s1;
int i;
  char ch;


  void out(int y,int x){
    
    if (x==0 ) return;
    out(x,a[x].l);
    //writeln(y,~ ~,x,~ ~,a[x].key,~ ~,a[x].delta,~ ~,a[x].sum);
    cout<<a[x].key<<' ';
    out(x,a[x].r);
    }


inline void update1(int x,int z) {//节点x加z
    
      a[x].sum+=a[x].size*z;
      a[x].key=a[x].key+z;
      a[x].Min=a[x].Min+z;
      a[x].delta+=z;
    }
    
inline void update(int x) {//每次旋转完更新节点的两个域
    
    a[x].size=a[a[x].l].size+a[a[x].r].size+1;
    a[x].sum=a[a[x].l].sum+a[a[x].r].sum+a[x].key;
    a[x].Min=a[x].key;
    if (a[a[x].l].Min<a[x].Min ) a[x].Min=a[a[x].l].Min;
    if (a[a[x].r].Min<a[x].Min ) a[x].Min=a[a[x].r].Min;

    }

  void build(int l,int r)//(double){/(double)一开始先用递归建立伸展树,而不是一个个插入完再splay,这样省空间又省时间,不然有可能爆栈
  {
int mid,tmp;
    
    mid=(l+r)>> 1;
    if (l<mid ) {
      build(l,mid-1);
      tmp=(l+mid-1)>> 1;
      a[mid].l=tmp;
      a[tmp].p=mid;
      }

    if (r>mid ) {
      build(mid+1,r);
      tmp=(mid+1+r)>> 1;
      a[mid].r=tmp;
      a[tmp].p=mid;
      }
    update(mid);
    }


  void down(int root,int x) {//从root开始向下推标签,直到x
  
int y;
int i;
    
    if (x==0 ) return;
    s1=0;
    y=x;
    do{
      s1++;
      stack[s1]=y;
      if (y==root ) break;
      y=a[y].p;
    }while (!(false));

    for (i=s1 ;i>= 1 ;i--)
      {
      x=stack[i];
      update1(a[x].l,a[x].delta);
      update1(a[x].r,a[x].delta);
      a[x].delta=0;
      }
    }



inline void rightrotate(int x) //右旋
{
int 	y,z;
	y=a[x].p;
	z=a[y].p;
	if (a[z].l==y ) a[z].l=x
		;else a[z].r=x;
	a[x].p=z;
	a[y].p=x;
	a[y].l=a[x].r;
	a[x].r=y;
	a[a[y].l].p=y;
	update(y);
}

inline void leftrotate(int x) //左旋
{
int 	y,z;
	y=a[x].p;
	z=a[y].p;
	if (a[z].l==y ) a[z].l=x
		;else a[z].r=x;
	a[x].p=z;
	a[y].p=x;
	a[y].r=a[x].l;
	a[x].l=y;
	a[a[y].r].p=y;
	update(y);
}

void splay(int & root,int x) {//核心操作:单旋splay

int tmp;
  
  if (x==0 ) return;
  down(root,x);
  tmp=a[root].p;
	while (a[x].p!=tmp) 
		if (a[a[x].p].l==x ) rightrotate(x)
			;else leftrotate(x);
  update(x);
  root=x;
  }


inline int fsmall(int t,int x) //找值小于x的最大节点
{
        down(root,t);
        int tmp=0;
        while (t!=0) 
        {
        down(t,t);
        if (a[t].key>=x ) t=a[t].l;
                else {
                  if ((tmp==0)|(a[tmp].key<=a[t].key) ) tmp=t;
                  t=a[t].r;
                  }
        }
        splay(root,tmp);
        return tmp;
}

inline int fbig(int t,int x) //找值大于x的最小节点
{
       int tmp=0;
        down(root,t);
        while (t!=0) 
        {
        down(t,t);
        if (a[t].key<=x ) t=a[t].r;
                else {
                  if ((tmp==0)|(a[tmp].key>=a[t].key) ) tmp=t;
                  t=a[t].l;
                  }
        }
        splay(root,tmp);
        return tmp;
}
/*
inline int find(int t,x) //找值为x的节点
{
        down(root,t);
        find=0;
        while (t!=0) 
        {
        down(t,t);
        if (x==a[t].key ) return(t);
            else if (x<a[t].key ) t=a[t].l;
                else t=a[t].r;
        }
        //splay(root,t);
        return(t);
}

inlinefunction getmin(int root):int; //最小节点

int 	t;
{
	t=root;
	while (a[t].l!=0) 
		t=a[t].l;
        splay(root,t);
	return(t);
}

inlinefunction getmax(int root):int; //最大节点

int 	t;
{
	t=root;
	while (a[t].r!=0) 
		t=a[t].r;
        splay(root,t);
	return(t);
}


inline int join(int x,int y){//合并 (x.key<=y.key)
  
int i;
    
    if (x==0 ) return(y);
    if (y==0 ) return(x);
    i=getmin(y);
    a[y].p=0;
    splay(y,i);
    a[y].l=x;
    a[x].p=y;
    return(y);
    }


  void Delete(int & root,inlineint x)/(double){/(double)删除
    
    splay(root,x);
    root=join(a[root].l,a[root].r);
    }
  */
  
inline bool big(int x,int y){
    
    if (a[x].key>=a[y].key ) return true;
      else return false;
    }
    
    
  void insert(int & root,int z)
  {
int x,y;
    
    y=0;
    x=root;
    while (x!=0) 
      {
      y=x;
      down(x,x);
      if (big(x,z) ) x=a[x].l;
        else x=a[x].r;
      }
    a[z].p=y;
    if (y==0 ) root=z;
      else if (big(y,z) ) a[y].l=z;
        else a[y].r=z;
    splay(root,z);
    }

/*
int findkth(int & root,inlineint k){//找第k大的节点

int 	t;

	t=root;
	while (t!=0) 
	{
		if (k==a[a[t].l].size+1 ) break;
		if (k<=a[a[t].l].size ) t=a[t].l
			;else {
				t=a[t].r;
				k=k-a[a[t].l].size-1
			;}
	;}
	splay(root,t);
	return(t);
}
  
  int select(int & root,int x){/(double)求节点序号
    
    splay(root,x);
    return(a[a[root].l].size);
    }

  int pred(int & root,int x){/(double)求节点前驱
    
    splay(root,x);
    return(getmax(a[root].l));
    }
  
  int succ(int & root,int x){/(double)求节点后继
    
    splay(root,x);
    return(getmin(a[root].r));
    }
    

  void qsort(int l,int r){
      
int i,j,x1,y1;
      
         i=l;
         j=r;
         x1=a[(l+r) / 2].key;
         do{
           while (a[i].key<x1) 
            i++;
           while (x1<a[j].key) 
            j--;
           if (!(i>j) )
             {
                num[c[i]]=j;
                num[c[j]]=i;

                y1=c[i];
                c[i]=c[j];
                c[j]=y1;

                y1=a[i].key;
                a[i].key=a[j].key;
                a[j].key=y1;
                i++;
                j=j-1;
             }
         }while (!(i>j));
         if (l<j )
           qsort(l,j);
         if (i<r )
           qsort(i,r);
      }



  */
int sigma=0;
double t1;
int maxn=500000;
int deep[600000],sumdep=0;
void calc(int x,int dep)
	{
		if (x==0) return;
		//printf("%d\n",x);
		deep[dep]+=1;
		sumdep+=dep;
		calc(a[x].l,dep+1);
		calc(a[x].r,dep+1);
	}
int main()
{
	printf("start\n");
	t1=clock();
	srand(time(0));
	for (i=1;i<=maxn;i++){
        int z=i;
        a[z].l=a[z].r=a[z].p=0;
        a[z].size=1;
        a[z].key=rand();
        insert(root,z);
        }
	printf("%.4f\n",(clock()-t1)/CLOCKS_PER_SEC);
	calc(root,1);
	for (i=1;deep[i];i++) {
        sigma+=deep[i];
        printf("%d:%d\n",i,deep[i]);
        }
	printf("ave=%.5f\n",double(sumdep)/double(maxn));
	printf("%d\n",sigma);
	system("pause");
}

