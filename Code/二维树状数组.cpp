#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#include<map>
using namespace std;
typedef long long ll;
struct BIT_2D{
	int W;map<pair<int,int>,int> A;
	void init(int _W=0){W=_W;A.clear();}
	BIT_2D(int _W=0):W(_W){}
	void insert(int x,int y,int c){
		for (int i=x;i<=W;i+=i&-i)
			for (int j=y;j<=W;j+=j&-j)A[make_pair(i,j)]+=c;
	}
	ll query(int x,int y){
		ll res=0;
		for (int i=x;i>0;i-=i&-i)
			for (int j=y;j>0;j-=j&-j)res+=A[make_pair(i,j)];
		return res;
	}
};
BIT_2D A;
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int ch,W,x,y,z,x1,y1,x2,y2;scanf("%d%d",&ch,&W);A.init(W);
	for (scanf("%d",&ch);ch!=3;scanf("%d",&ch))
		if (ch==1)scanf("%d%d%d",&x,&y,&z),A.insert(x,y,z);
		else scanf("%d%d%d%d",&x1,&y1,&x2,&y2),printf("%I64d\n",A.query(x2,y2)-A.query(x1-1,y2)-A.query(x2,y1-1)+A.query(x1-1,y1-1));
	system("pause");for (;;);
	return 0;
}


