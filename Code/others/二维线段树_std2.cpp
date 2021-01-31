#include <cstdio>
#include <cstdlib>
#include <cstring>
#define maxn 1010

int a[4*maxn][4*maxn];
int ans;

void Modify_y(int rootx, int rooty, int l, int r, int y1, int y2){
	if (y1==l && y2==r){
		a[rootx][rooty]=!a[rootx][rooty];
	}
	else{
		int mid=(l+r)>>1;
		if (y2<=mid)
			Modify_y(rootx, (rooty<<1), l, mid, y1, y2);
		else if (y1>mid)
			Modify_y(rootx, (rooty<<1)+1, mid+1, r, y1, y2);
		else{
			Modify_y(rootx, (rooty<<1), l, mid, y1, mid);
			Modify_y(rootx, (rooty<<1)+1, mid+1, r, mid+1, y2);
		}
	}
}

void Modify_x(int rootx, int n, int l, int r, int x1, int x2, int y1, int y2){
	if (x1==l && x2==r){
		Modify_y(rootx, 1, 1, n, y1, y2);
	}
	else{
		int mid=(l+r)>>1;
		
		if (x2<=mid)
			Modify_x((rootx<<1), n, l, mid, x1, x2, y1, y2);
		else if (x1>mid)
			Modify_x((rootx<<1)+1, n, mid+1, r, x1, x2, y1, y2);
		else{
			Modify_x((rootx<<1), n, l, mid, x1, mid, y1, y2);
			Modify_x((rootx<<1)+1, n, mid+1, r, mid+1, x2, y1, y2);
		}
	}
}

void Query_y(int rootx, int rooty, int l, int r, int y){
	ans^=a[rootx][rooty];
	if (l<r){
		int mid=(l+r)>>1;
		if (y<=mid)
			Query_y(rootx, (rooty<<1), l, mid, y);
		else
			Query_y(rootx, (rooty<<1)+1, mid+1, r, y);
	}
}

void Query_x(int rootx, int n, int l, int r, int x, int y){
	Query_y(rootx, 1, 1, n, y);
	if (l<r){
		int mid=(l+r)>>1;
		if (x<=mid)
			Query_x((rootx<<1), n, l, mid, x, y);
		else
			Query_x((rootx<<1)+1, n, mid+1, r, x, y);
	}
}

int main(){
	int cases, n, t, x1, x2, y1, y2;
	char ch[5];
	scanf("%d", &cases);
	for (int cs=1; cs<=cases; cs++){
		if (cs!=1) printf("\n");
		scanf("%d%d", &n, &t);
		memset(a, 0, sizeof(a));
		while (t--){
			scanf("%s", ch);
			if (ch[0]=='C'){
				scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
				Modify_x(1, n, 1, n, x1, x2, y1, y2);
			}
			else{
				ans=0;
				scanf("%d%d", &x1, &y1);
				Query_x(1, n, 1, n, x1, y1);
				printf("%d\n", ans);
			}
		}
	}
	return 0;
}


