//¶þÎ¬Ïß¶ÎÊ÷
#include<stdio.h>
#define maxn 5048
FILE *fp,*fpo;
int s[2][maxn][2][maxn]={0};
int m,n,x1,y1,x2,y2,v;
void insert2(int s[2][maxn],int r,int t,int a,int b)
{
	int w=(a+b)>>1,p=t<<1,q=p^1;
	int aa=a>y1?a:y1,bb=b<y2?b:y2,rr=bb-aa+1;
	if(y1<=a && b<=y2) s[1][t]+=v*r;
	else
	{
		if(y1<=w) insert2(s,r,p,a,w);
		if(w<y2) insert2(s,r,q,w+1,b);
	}
	s[0][t]+=v*r*rr;
	return;
}
void insert(int t,int a,int b)
{
	int w=(a+b)>>1,p=t<<1,q=p^1;
	int aa=a>x1?a:x1,bb=b<x2?b:x2,rr=bb-aa+1;
	if(x1<=a && b<=x2) insert2(s[1][t],1,1,1,n);
	else
	{
		if(x1<=w) insert(p,a,w);
		if(w<x2) insert(q,w+1,b);
	}
	insert2(s[0][t],rr,1,1,n);
	return;
}
int ask2(int s[2][maxn],int r,int t,int a,int b)
{
	int w=(a+b)>>1,p=t<<1,q=p^1,ans=0;
	int aa=a>y1?a:y1,bb=b<y2?b:y2,rr=bb-aa+1;
	if(y1<=a && b<=y2) ans=s[0][t]*r;
	else
	{
		ans+=s[1][t]*r*rr;
		if(y1<=w) ans+=ask2(s,r,p,a,w);
		if(w<y2) ans+=ask2(s,r,q,w+1,b);
	}
	return(ans);
}
int ask(int t,int a,int b)
{
	int w=(a+b)>>1,p=t<<1,q=p^1,ans=0;
	int aa=a>x1?a:x1,bb=b<x2?b:x2,rr=bb-aa+1;
	if(x1<=a && b<=x2) ans=ask2(s[0][t],1,1,1,n);
	else
	{
		ans+=ask2(s[1][t],rr,1,1,n);
		if(x1<=w) ans+=ask(p,a,w);
		if(w<x2) ans+=ask(q,w+1,b);
	}
	return(ans);
}
int main()
{
	int k,q,ans;
	fp=fopen("rectangle.in","r");
	fpo=fopen("rectangle.out","w");
	fscanf(fp,"%d %d %d",&m,&n,&q);
	while(q-->0)
	{
		fscanf(fp,"%d %d %d %d %d",&k,&x1,&y1,&x2,&y2);
		if(k==1)
		{
			fscanf(fp,"%d",&v);
			insert(1,1,m);
		}
		else if(k==2)
		{
			ans=ask(1,1,m);
			fprintf(fpo,"%d\n",ans);
		}
	}
	fclose(fp);
	fclose(fpo);
	return 0;
}


