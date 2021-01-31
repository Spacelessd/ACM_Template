#include<cstdio>
const int oo=1000000007;
int i,T,N,Num1,Num2,t;
long long A,B,C,Ans;
int f[200005],g1[200005],g2[200005];
inline void swap1(int i,int j)
{
	int t;
	t=g1[i];
	g1[i]=g1[j];
	g1[j]=t;
}
inline void swap2(int i,int j)
{
	int t;
	t=g2[i];
	g2[i]=g2[j];
	g2[j]=t;
}
inline void Up1(int i)
{
	for(;i>1&&g1[i]>g1[i/2];)
	{
		swap1(i,i/2);
		i/=2;
	}
}
inline void Up2(int i)
{
	for(;i>1&&g2[i]<g2[i/2];)
	{
		swap2(i,i/2);
		i/=2;
	}
}
inline void Down1(int i)
{
	int j;
	for(;2*i<=Num1;)
	{
		j=i;
		if(g1[2*i]>g1[j])
			j=2*i;
		if(2*i+1<=Num1&&g1[2*i+1]>g1[j])
			j=2*i+1;
		if(i==j)
			return;
		swap1(i,j);
		i=j;
	}
}
inline void Down2(int i)
{
	int j;
	for(;2*i<=Num2;)
	{
		j=i;
		if(g2[2*i]<g2[j])
			j=2*i;
		if(2*i+1<=Num2&&g2[2*i+1]<g2[j])
			j=2*i+1;
		if(i==j)
			return;
		swap2(i,j);
		i=j;
	}
}

class RBtree{
public:
#define black 0
#define red 1
struct node{
	int l,r,key,size,color,p;
	};
	node a[200010];
	int len,root;
	void clear()
	{
		len=0;root=0;
		a[0].l=a[0].r=a[0].p=a[0].key=a[0].size=0;
		a[0].color=black;
	}
	RBtree(){clear();}
	
	int newnode(int key)
	{
		int x=++len;
		a[x].l=a[x].r=a[x].p=0;
		a[x].size=1;a[x].color=red;
		a[x].key=key;
		return x;
	}
	
	void update(int x)
	{
		 a[x].size=a[a[x].l].size+a[a[x].r].size+1;
	}
	
	inline void zig(int x)
	{
		int y=a[x].p,z=a[y].p;
	   	if (a[z].l==y) a[z].l=x;else a[z].r=x;
		a[x].p=z;a[y].p=x;
		a[y].l=a[x].r;a[x].r=y;
		a[a[y].l].p=y;
		update(y);update(x);
	}

	inline void zag(int x)
	{
		int y=a[x].p,z=a[y].p;
		if (a[z].l==y) a[z].l=x;else a[z].r=x;
		a[x].p=z;a[y].p=x;
		a[y].r=a[x].l;a[x].l=y;
		a[a[y].r].p=y;
		update(y);update(x);
	}
	
	void insert(int &root,int key)
	{
	   int x=root,y=0,fa=a[root].p,z=newnode(key);
	   while (x){
			 ++a[y=x].size;
			 if (key<a[x].key)x=a[x].l;
			   else x=a[x].r;
			 }
	   a[z].p=y;
	   if (key<a[y].key)a[y].l=z;
		 else a[y].r=z;
	   x=z;
	   while (1){
		   y=a[x].p;
		   if (y==fa){root=x;a[x].color=black;return;}
		   if (a[y].color==black)return;
		   z=a[y].p;
		   if ((x==a[y].r)&&(y==a[z].l)){zag(x);zig(x);a[y].color=black;}
			 else if ((x==a[y].l)&&(y==a[z].r)){zig(x);zag(x);a[y].color=black;}
			   else if ((x==a[y].l)&&(y==a[z].l)){zig(y);a[x].color=black;x=y;}
				 else if ((x==a[y].r)&&(y==a[z].r)){zag(y);a[x].color=black;x=y;}
		   }
	}
	
	int find(int x,int key)
	{
		if (x==0)return 0;
		if (key==a[x].key)return x;
		if (key<a[x].key)return find(a[x].l,key);
		else return find(a[x].r,key);
	}
	int findkth(int &root,int k)  //找第k大的节点
	{
		int x=root;
		while (k){
			  if (k==a[a[x].l].size+1) break;
			  if (k<=a[a[x].l].size) x=a[x].l;
				 else {k-=a[a[x].l].size+1;x=a[x].r;}			
		}
		return x;
	}
	int fmin(int x){while (a[x].l)x=a[x].l;return x;}
	int fmax(int x){while (a[x].r)x=a[x].r;return x;}
};
RBtree a;
int main()
{
	double P=95;
	scanf("%d",&T);
	for (int I=1;I<=T;++I)
	if (I<=int(T*P/100+0.5))
	{
		scanf("%lld%lld%lld%d",&A,&B,&C,&N);
		f[1]=1;
		Num1=1,Num2=0;
		g1[1]=1;
		for(i=2;i<=N;++i)
		{
			f[i]=(A*g1[1]+B*i+C)%oo;
			if(i&1)
			{
				g1[++Num1]=f[i];
				Up1(Num1);
			}
			else
			{
				g2[++Num2]=f[i];
				Up2(Num2);
			}
			for(;g1[1]>g2[1];)
			{
				t=g1[1];
				g1[1]=g2[1];
				g2[1]=t;
				Down1(1);
				Down2(1);
			}
		}
		Ans=0;
		for(i=1;i<=N;++i)
			Ans+=f[i];
		printf("%lld\n",Ans);
	}
	
	
	
	
	
	
	
	else {
		long long n,A,b,c,m,i,tmp,key,ans=1;
	a.clear();
	scanf("%lld%lld%lld%lld",&A,&b,&c,&n);
	a.insert(a.root,1);
	for (i=2;i<=n;++i){
		if ((i-1)&1)tmp=((i-1)>>1)+1;else tmp=(i-1)>>1;
		m=a.a[a.findkth(a.root,tmp)].key;
		key=(A*m+b*i+c)%1000000007;
		a.insert(a.root,(int)key);
		//printf("%d %d %d\n",i,m,A*m+b*i+c);
		ans+=key;
		//print(a.root);
		}
	printf("%lld\n",ans);
		}
	//	for (;;);
	return 0;
}

