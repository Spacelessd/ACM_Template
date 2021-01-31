#include<map>
#include<set>
#include<cmath>
#include<queue>
#include<stack>
#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
const double pi = acos(-1.0);
using namespace std;
#define LL(x) (x << 1)
#define RR(x) (x << 1 | 1)
const int maxn = 100008;
int  a[maxn], b[maxn], c[maxn], n, p[maxn], ans[maxn / 2];
int  sum[maxn << 2];
bool cmp(const int &i, const int &j){
      return a[i] < a[j] || a[i] == a[j] && i < j;
}
struct node{
      int a, b, id, k;
      bool operator < (const node & B)const{
           return a < B.a;
      }
}q[maxn / 2];

void build(int id, int l, int r){
      sum[id] = 0;
      if(l == r) return ;
      int mid = (l + r) >> 1;
      build(LL(id), l, mid);
      build(RR(id), mid + 1, r);
}
void update(int id, int l, int r, int pos, int add){
      if(l == r){
            sum[id] += add; return;
      }
      int mid = (l + r) >> 1;
      if(pos <= mid) update(LL(id), l, mid, pos, add);
      else update(RR(id), mid + 1, r, pos, add);
      sum[id] = sum[LL(id)] + sum[RR(id)];
}
int query(int id, int l, int r, int ul, int ur){
      if(ul <= l && ur >= r){
           return sum[id];
      }
      int mid = (l + r) >> 1;
      int ret = 0;
      if(ur <= mid) ret += query(LL(id), l, mid, ul, ur);
      else if(ul > mid) ret += query(RR(id), mid + 1, r, ul, ur);
      else {
            ret += query(LL(id), l, mid, ul, ur);
            ret += query(RR(id), mid + 1, r, ul, ur);
      }
      return ret;
}
int find(int s){
      int l = 1, r = n, ans = -1;
      while(l <= r){
            int mid = (l + r) >> 1;
            if(query(1, 1, n, 1, mid) >= s){
                  ans = mid;
                  r = mid - 1;
            }else l = mid + 1;
      }
      return p[ans];
}
int main(){
       freopen("1.in","r",stdin);
	   freopen("2.out","w",stdout);
       int  m;
       while(scanf("%d%d",&n,&m)!=EOF){
             build(1, 1, n);
             for(int i = 1; i <= n; i++) scanf("%d", a + i);
             for(int i = 1; i <= n; i++) b[i] = i;
             sort(b + 1, b + n + 1, cmp);
             for(int i = 1; i <= n; i++) c[b[i]] = i, p[i] = a[b[i]];
             for(int i = 1; i <= m; i++){
                  scanf("%d%d%d",&q[i].a,&q[i].b,&q[i].k);
                  q[i].id = i;
                  if(q[i].a > q[i].b) swap(q[i].a, q[i].b);
             }
             sort(q + 1, q + m + 1);
             int low = 1, high = 0;
             for(int i = 1; i <= m; i++){
                  int st = q[i].a, ed = q[i].b;
                  while(high < ed){
                        high++;
                        update(1, 1, n, c[high], 1);
                  }
                  while(low < st){
                        update(1, 1, n, c[low], -1);
                        low++;
                  }
                  ans[q[i].id] = find(q[i].k);
             }
             for(int i = 1; i <= m; i++){
                   printf("%d\n", ans[i]);
             }
       }
}


