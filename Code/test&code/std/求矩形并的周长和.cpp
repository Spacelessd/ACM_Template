#include <cstdio>  
#include <algorithm>  
using namespace std;  
const int MAXN=5000+10,MAXR=20000+5;  
struct line  
{  
	int p1,p2,q;  
	bool f;  
	void set(int a,int b,int c,bool d)  
	{  
		p1=a; p2=b; q=c; f=d;  
	}  
} linex[MAXN<<1],liney[MAXN<<1];  
   
struct node  
{  
	int s,e,cover,m;  
}d[MAXR*4];  
   
void build(int n,int ss,int ee)  
{  
	d[n].s=ss;  
	d[n].e=ee;  
	d[n].cover=d[n].m=0;  
	if (ss+1<ee)  
	{  
		int mid=(ss+ee)>>1;  
		build((n<<1)+1,ss,mid);  
		build((n<<1)+2,mid,ee);  
	}  
}  
inline void refreshm(int n)  
{  
	if(d[n].cover>0) d[n].m=d[n].e-d[n].s;  
	else if (d[n].s+1<d[n].e) d[n].m=d[(n<<1)+1].m+d[(n<<1)+2].m;  
	else d[n].m=0;  
}  
void insert(int n,int ss,int ee,int f)  
{  
	if ( ss<=d[n].s && d[n].e<=ee )  
	{  
		d[n].cover+=f;  
		refreshm(n);  
	}  
	else 
	{  
		int mid=(d[n].s+d[n].e)>>1;  
		if (ss<mid) insert((n<<1)+1,ss,ee,f);  
		if (ee>mid) insert((n<<1)+2,ss,ee,f);  
		refreshm(n);  
	}  
}  
bool cmp(line a,line b)  
{  
	if(a.q == b.q)  return a.f > b.f;  
	return a.q < b.q;  
}  
int calc(line * l,int n)  
{  
	sort(l,l+n,cmp);  
	build(0,0,20000);  
	int old=0,cnt=0;  
	for(int i=0;i<n;i++)  
	{  
		if(l[i].f) insert(0,l[i].p1,l[i].p2,1);  
		else insert(0,l[i].p1,l[i].p2,-1);  
		cnt+=abs(old-d[0].m);  
		old=d[0].m;  
	}  
	return cnt;  
}  

int main()  
{  
	int n;  
	scanf("%d",&n);  
	int x1,y1,x2,y2;  
	for(int i=0;i<n;i++)  
	{  
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);  
		x1+=10000;x2+=10000;y1+=10000;y2+=10000;  
		linex[i*2].set(x1,x2,y1,true);  
		linex[i*2+1].set(x1,x2,y2,false);  
		liney[i*2].set(y1,y2,x1,true);  
		liney[i*2+1].set(y1,y2,x2,false);  
	}  
	printf("%d\n",calc(linex,(n<<1))+calc(liney,(n<<1)));  
	return 0;  
} 


