#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define maxn 100010
#define CH 256
char str[maxn];
int wx[maxn],wy[maxn],nrank[maxn];
int SA[maxn],rank[maxn],height[maxn];
int bar[CH];
int query[maxn][25];
int i,len;
int min(int x,int y){return x<y?x:y;}
void get_query(int *a,int len){
	int i,j;
	for (i=0;i<len;i++)query[i][0]=a[i];
	for (j=1;1<<j<=len;j++)
		for (i=0;i+(1<<j)<=len;j++)
			query[i][j]=min(query[i][j-1],query[i+(1<<(j-1))][j-1]);
}
void lcp(int x,int y){
	
}
void get_SA(char *s,int *SA){
	int len=strlen(s)-1,m=CH,p,k;
	memset(bar,0,sizeof(int)*(m+5));
	for (i=0;i<len;i++)bar[rank[i]=s[i]]++;
	for (i=0;i<m-1;i++)bar[i+1]+=bar[i];
	for (i=len-1;i;--i)SA[--bar[rank[i]]]=i;
	for (p=1,k=1;p<len;k*=2,m=p)
	{
		
	}
}
void get_height(char *s,int *SA,int *height){
	
}
int main(){
	gets(str+1);
	len=strlen(str+1);
	str[len+1]='$';str[len+2]='\0';
	get_SA(str,SA);
	for (i=1;i<=len;i++)printf("%d %d\n",i,SA[i]);
	system("pause");
	get_height(str,SA,height);
	get_query(height,len);
	system("pause");
}









