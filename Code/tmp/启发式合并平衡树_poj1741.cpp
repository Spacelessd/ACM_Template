#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct node{
	int l,r,key,fix,size,num;
};
	node a[1000010];
	int len,oo;
	int n1,n2,n3;
	void treap()
	{
		srand(time(0));
		oo=100000000;
		len=0;
		a[0].l=a[0].r=a[0].key=a[0].size=a[0].num=0;
		a[0].fix=oo;
	}
	
	void renew(int x)
	{
         a[x].size=a[a[x].l].size+a[a[x].r].size+a[x].num;
    }
    
	void zig(int &x)
	{
		int y=a[x].l;
		a[x].l=a[y].r;
		a[y].r=x;
		x=y;
	}
	
    void zag(int &x)
	{
		int y=a[x].r;
		a[x].r=a[y].l;
		a[y].l=x;
		x=y;
	}
	
	
	void insert(int &x,int key)
	{
		if (x==0)
		{
			x=++len;
			a[x].l=a[x].r=0;
			a[x].num=a[x].size=1;
			a[x].key=key;
			a[x].fix=rand();
		}
		else 
		if (key<a[x].key)
		{
			insert(a[x].l,key);
			if (a[a[x].l].fix<a[x].fix)zig(x);
	        renew(a[x].r);
            renew(x);
		}
		else if (key>a[x].key)
		{
			insert(a[x].r,key);
			if (a[a[x].r].fix<a[x].fix)zag(x);
	        renew(a[x].l);
            renew(x);
		}
		else {
             a[x].num++;
             renew(x);
             }
    }
	
int p[20010],deep[20010],v[20010],next[20010],e[20010],w[20010],root[20010],size[20010];
int n,i,k,l,x,y,z,ans;
double t1;

	void print(int x)
	{
        int i;
		if (x==0) return;
		print(a[x].l);
		/*for (i=1;i<=a[x].num;i++)*/printf("%d %d\n",a[x].key,a[x].num);
		print(a[x].r);
	}
	
void dfs(int x,int dep)
{
     int i=v[x];
     p[x]=1;deep[x]=dep;
     while (i)
     {
           if (!p[e[i]])dfs(e[i],dep+w[i]);
           i=next[i];
           }
}

void merge(int &x,int &y)
{
     int i;
		if (x==0) return;
		merge(a[x].l,y);
		for (i=1;i<=a[x].num;i++) insert(y,a[x].key);
		merge(a[x].r,y);
}

void query(int x,int y)
{
	while (y)
		if (a[y].key<=x) ans+=a[a[y].l].size+a[y].num;y=a[y].r;
		else y=a[y].l;
}

void make(int x,int y,int z)
{
        int i;
		if (x==0) return;
		make(a[x].l,y,z);
		for (i=1;i<=a[x].num;i++) query(k+2*z-a[x].key,y);
		make(a[x].r,y,z);
}

void f(int x,int y)
{
    int i=v[x],max=-1,po;
     p[x]=y;size[x]=1;
     while (i)
     {
           if (!p[e[i]]){
                         f(e[i],x);
                         size[x]+=size[e[i]];
                         if (size[e[i]]>max){
                                             max=size[e[i]];po=e[i];
                                             }
                         }
           i=next[i];
     }
     if (max>=0) root[x]=root[po];
     else root[x]=0;
     if (max==-1){
                  insert(root[x],deep[x]);
                  return;
                  }
     i=v[x];
     while (i)
     {
           if ((p[e[i]]==x)&&(e[i]!=po)){
                           make(root[e[i]],root[x],deep[x]);
                           merge(root[e[i]],root[x]);
                           
                           }
           i=next[i];
     }
     query(k+deep[x],root[x]);
     insert(root[x],deep[x]);
}
int main()
{
    //freopen(".in","r",stdin);
	while (1)
	{
          scanf("%d%d",&n,&k);
          if ((n==0)&&(k==0))break;
          treap();
          memset(p,0,sizeof(p));
          memset(v,0,sizeof(v));
          memset(next,0,sizeof(next));
          l=0;
          for (i=1;i<n;i++)
          {
              scanf("%d%d%d",&x,&y,&z);
              l++;e[l]=y;w[l]=z;next[l]=v[x];v[x]=l;
              l++;e[l]=x;w[l]=z;next[l]=v[y];v[y]=l;
          }
   dfs(1,0);
   ans=0;
   memset(p,0,sizeof(p));
   f(1,10000);
   printf("%d\n",ans);
   }
   //system("pause");
   //for(;;);
}

