# ACM模板文件



# 如何与队友交流

## 开题

跟榜单走!相信前排大佬!

## 如何提出想到的算法

### 画草稿图

显然写在纸上的东西更加易懂

### 估算时间复杂度

最重要的东西,不要没有依据的口胡

### 给出公式/伪代码

这步需要在打完草稿和时间复杂度论证完成后做

## 如何否定队友的算法

# 起手式

## 默认代码

```cpp
#include<bits/extc++.h>
#include<bits/stdc++.h>
#define ll long long
//#define int long long
//#define int __int128
//#define int __uint128_t
#define ull unsigned long long
#define MMST(x,y) memset(x,y,sizeof(x))

using namespace std;
using namespace __gnu_pbds;

const int INF=0x3f3f3f3f;

int read(){char c;int num,f=1;while(c=(char)getchar(),!isdigit(c))if(c=='-')f=-1;num=(int)(c-'0');while(c=(char)getchar(),isdigit(c))num=num*10+(int)(c-'0');return num*f;}
void prt(int x){if(x<0){putchar('-');x=-x;}if(x>9)prt(x/10);putchar(x%10+'0');}

void work()
{
    return;
}

signed main()
{
    int T=1;//read();
	for(int Case=1;Case<=T;Case++)
    {
        //printf("Case #%d: ",Case);
        work();
    }
    return 0;
}
```
# 数据结构

## 线段树

```cpp
int n, m, mod;
int a[MAXN];

struct Segment_Tree {
	ll sum, add, mul;
	int l, r;
}s[MAXN * 4];

void update(int pos) {
	s[pos].sum = (s[pos << 1].sum + s[pos << 1 | 1].sum) % mod;
    return;
}

void pushdown(int pos) { //pushdown的维护
	s[pos << 1].sum = (s[pos << 1].sum * s[pos].mul + s[pos].add * (s[pos << 1].r - s[pos << 1].l + 1)) % mod;
	s[pos << 1 | 1].sum = (s[pos << 1 | 1].sum * s[pos].mul + s[pos].add * (s[pos << 1 | 1].r - s[pos << 1 | 1].l + 1)) % mod;
	
	s[pos << 1].mul = (s[pos << 1].mul * s[pos].mul) % mod;
	s[pos << 1 | 1].mul = (s[pos << 1 | 1].mul * s[pos].mul) % mod;
	
	s[pos << 1].add = (s[pos << 1].add * s[pos].mul + s[pos].add) % mod;
	s[pos << 1 | 1].add = (s[pos << 1 | 1].add * s[pos].mul + s[pos].add) % mod;
		
	s[pos].add = 0;
	s[pos].mul = 1;
	return; 
}

void build_tree(int pos, int l, int r) { //建树
	s[pos].l = l;
	s[pos].r = r;
	s[pos].mul = 1;
	
	if (l == r) {
		s[pos].sum = a[l] % mod;
		return;
	}
	int mid = (l + r) >> 1;
	build_tree(pos << 1, l, mid);
	build_tree(pos << 1 | 1, mid + 1, r);
	update(pos);
	return;
}

void ChangeMul(int pos, int x, int y, int k) { //区间乘法
	if (x <= s[pos].l && s[pos].r <= y) {
		s[pos].add = (s[pos].add * k) % mod;
		s[pos].mul = (s[pos].mul * k) % mod;
		s[pos].sum = (s[pos].sum * k) % mod;
		return;
	}
	pushdown(pos);
	int mid = (s[pos].l + s[pos].r) >> 1;
	if (x <= mid) ChangeMul(pos << 1, x, y, k);
	if (y > mid) ChangeMul(pos << 1 | 1, x, y, k);
	update(pos);
	return;
}

void ChangeAdd(int pos, int x, int y, int k) { //区间加法
	if (x <= s[pos].l && s[pos].r <= y) {
		s[pos].add = (s[pos].add + k) % mod;
		s[pos].sum = (s[pos].sum + k * (s[pos].r - s[pos].l + 1)) % mod;
		return;
	}
	pushdown(pos);
	int mid = (s[pos].l + s[pos].r) >> 1;
	if (x <= mid) ChangeAdd(pos << 1, x, y, k);
	if (y > mid) ChangeAdd(pos << 1 | 1, x, y, k);
	update(pos);
	return;
}

ll AskRange(int pos, int x, int y) { //区间询问
	if (x <= s[pos].l && s[pos].r <= y) {
		return s[pos].sum;
	}
	pushdown(pos);
	ll val = 0;
	int mid = (s[pos].l + s[pos].r) >> 1;
	if (x <= mid) val = (val + AskRange(pos << 1, x, y)) % mod;
	if (y > mid) val = (val + AskRange(pos << 1 | 1, x, y)) % mod;
	return val;
}

int main() {
	scanf("%d%d%d", &n, &m, &mod);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	build_tree(1, 1, n);
	for (int i = 1; i <= m; i++){
		int opt, x, y;
		scanf("%d%d%d", &opt, &x, &y);
		if (opt == 1) {
			int k;
			scanf("%d", &k);
			ChangeMul(1, x, y, k);
		}
		if (opt == 2) {
			int k;
			scanf("%d", &k);
			ChangeAdd(1, x, y, k);
		}
		if (opt == 3) {
			printf("%lld\n", AskRange(1, x, y));
		}
	}
    
	return 0;
}
```

#  图论

## 最短路

### Dijkstra

```cpp
int n,m,s;//n-点数 m边数 s起点
bool vis[200003];
struct Edge{
    int to,dis,next;
}e[200003];
int head[200003],dis[200003],cnt;
void addedge(int u,int v,int d)//from u to v dis d(w);
{
    cnt++;
    e[cnt].dis=d;
    e[cnt].to=v;
    e[cnt].next=head[u];
    head[u]=cnt;
}

struct Node
{
    int dis,pos;
    bool operator < (const Node &x)const
    {
        return x.dis<dis;
    }
};
std::priority_queue<Node> q;//区别pbds的优先队列和std的优先队列 

void dij()
{
    dis[s]=0;
    q.push((Node){0,s});
    while(!q.empty())
    {
        Node t=q.top();
        q.pop();
        int x=t.pos,d=t.dis;
        if(vis[x])continue;
        vis[x]=true;
        for(int i=head[x];i;i=e[i].next)
        {
            int y=e[i].to;
            if(dis[y]>dis[x]+e[i].dis)
            {
                dis[y]=dis[x]+e[i].dis;
                if(!vis[y]) q.push((Node){dis[y],y});
            }
        }
    }
}

void work()
{
    n=read();m=read();s=read();
    for(int i=1;i<=n;i++) dis[i]=INF;
    for(int u,v,w,i=1;i<=m;i++)
    {
        u=read();v=read();w=read();
        addedge(u,v,w);
    }
    dij();
    for(int i=1;i<=n;i++) printf("%d ",dis[i]);
    return;
}
```