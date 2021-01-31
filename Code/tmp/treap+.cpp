#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>

int deep[100000],sumdep=0;
class treap{
public:
struct node{
	int l,r,key,fix,size,num;
};
	node a[1000010];
	int len,root,oo;
	treap()
	{
		srand(time(0));
		oo=100000000;
		len=0;root=0;
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

	int find(int x,int key)
	{
        if (x==0)return 0;
        if (key==a[x].key)return x;
        if (key<a[x].key)return find(a[x].l,key);
        else return find(a[x].r,key);
	}

	void down(int &x)
	{
        if (!a[x].l && !a[x].r)return;
        if (a[a[x].l].fix<a[a[x].r].fix){
                                          zig(x);
                                          down(a[x].r);
                                          renew(x);
                                          }
                                          else {
                                          zag(x);
                                          down(a[x].l);
                                          renew(x);
                                          }
    }

	void del(int &x,int key)
	{
        if (x==0)return;
        if (key==a[x].key){
                           a[x].num--;
                           if (!a[x].num){
                              a[x].fix=oo;
                              down(x);
                              }
                           renew(x);
                           }
        else if (key<a[x].key)del(a[x].l,key);
        else del(a[x].r,key);
    }


	int fmin(int x)
	{
        while (a[x].l!=0)x=a[x].l;
        return x;
    }

    int fmax(int x)
	{
        while (a[x].r!=0)x=a[x].r;
        return x;
    }

	void print(int x)
	{
        int i;
		if (x==0) return;
		print(a[x].l);
		for (i=1;i<=a[x].num;i++)printf("%d\n",a[x].key);
		//for (i=1;i<=a[x].num;i++)printf("%d %d %d %d\n",a[x].key,a[x].l,a[x].r,a[x].fix);
		print(a[x].r);
	}

	void calc(int x,int dep)
	{
        int i;
		if (x==0) return;
		deep[dep]+=a[x].num;
		sumdep+=dep*a[x].num;
		calc(a[x].l,dep+1);
		calc(a[x].r,dep+1);
	}
};
int n,i,x,sigma=0;
treap a;
double t1;
int maxn=500000;
int main()
{
	printf("start\n");
	t1=clock();
	for (i=1;i<=maxn;i++)a.insert(a.root,rand()/*32768+rand()*/);
	//a.print(a.root);
	a.calc(a.root,1);
	for (i=1;deep[i];i++) {
        sigma+=deep[i];
        printf("%d:%d\n",i,deep[i]);
        }
	printf("ave=%.5f\n",double(sumdep)/double(maxn));
	printf("%d\n",sigma);
	printf("%.4f\n",(clock()-t1)/CLOCKS_PER_SEC);
	system("pause");
}


