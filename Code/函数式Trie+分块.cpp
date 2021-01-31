#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#define N 12005
#define Sqrt 155
#define W 30
#define ll long long
inline int min(int x,int y){return x<y?x:y;}
inline int max(int x,int y){return x>y?x:y;}
struct node{
	node *son[2];
	int last;
}a[N*(W+2)],*root[N],*null;int top=0;
int c[N],block[Sqrt][N];
inline node *Newnode(int time){
	++top;a[top].son[0]=a[top].son[1]=null;a[top].last=time;
	return a+top;
}
node *insert(node *x,int key,int time){
	node *y=Newnode(time),*root=y;int id;
	for (int i=W;i>=0;--i){
		id=(key>>i)&1;
		y->son[id^1]=x->son[id^1];
		y->son[id]=Newnode(time);
		y=a+top;x=x->son[id];
	}
	return root;
}
int ask(int l,int r,int key,int best){
	node *x=root[r];int ans=0,id;
	for (int i=W;i>=0;--i){
		id=(key>>i)&1^1;
		if (x->son[id]->last>=l)ans|=1<<i;else {id^=1;if (ans+(1<<i)<=best)return 0;}
		x=x->son[id];
	}
	return ans;
}
void print(node *x,int dep,int ans){
	if (x==null)return;
	if (dep==-1){printf("print %d\n",ans);return;}
	print(x->son[0],dep-1,ans);print(x->son[1],dep-1,ans+(1<<dep));
}
inline void read(int &x){
	char ch;int bo=0;x=0;
	for (ch=getchar();!(ch>='0' && ch<='9');ch=getchar())if (ch=='-')bo=1;
	for (;ch>='0' && ch<='9';x=x*10+ch-'0',ch=getchar());
	if (bo)x=-x;
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	null=new node;null->son[0]=null->son[1]=null;null->last=-1;
	int n,m,x,y,Lim,Len,ans=0;scanf("%d%d",&n,&m);Len=int(1.0*n/sqrt(m)+1);Lim=n/Len;
	for (int i=1;i<=n;++i)read(c[i]),c[i]^=c[i-1];
	root[0]=insert(null,0,0);for (int i=1;i<=n;++i)root[i]=insert(root[i-1],c[i],i);
	for (int i=0;i<=Lim;++i)
		for (int j=i*Len+1;j<=n;++j)
			block[i][j]=max(block[i][j-1],ask(i*Len,j-1,c[j],block[i][j-1]));
	while (m--){
		read(x);read(y);x=((ll)x+ans)%n+1;y=((ll)y+ans)%n+1;
		if (x>y){int tmp=x;x=y;y=tmp;}--x;
		int start=x/Len+(x%Len!=0);
		ans=start*Len<=y?block[start][y]:0;
		for (int i=x,end=min(start*Len-1,y);i<=end;++i)ans=max(ans,ask(x,y,c[i],ans));
		printf("%d\n",ans);
	}
	system("pause");for (;;);
	return 0;
}


