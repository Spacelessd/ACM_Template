#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
using std::string;
#define re(i, n) for (int i=0; i<n; i++)
#define root 1
const int MAXN = 500001, MAXLEN = 1000001, SZ = 26, INF = ~0U >> 2;
struct node {
    int mul, ch[SZ], fail;    //Attention
} T[MAXN];
int N, Q[MAXN], res;
string s0, A;
char tmp[MAXLEN], tmp0[51];
void ins()
{
    int len = s0.length(), x = root, c;
    re(i, len) {
        c = s0[i] - 97;
        if (!T[x].ch[c]) {T[x].ch[c] = ++N; T[N].mul = 0; re(j, SZ) T[N].ch[j] = 0;}
        x = T[x].ch[c];
    }
    T[x].mul++;
}
void mkf()
{
    Q[0] = root; T[root].fail = 0;
    int i, j, x;
    for (int front=0, rear=0; front<=rear; front++) {
        i = Q[front];
        re(k, SZ) if (j = T[i].ch[k]) {
            x = T[i].fail;
            while (x && !T[x].ch[k]) x = T[x].fail;        //Attention
            if (x) T[j].fail = T[x].ch[k]; else T[j].fail = root;    //Attention
            Q[++rear] = j;
        }
    }
}
void solve()
{
    int len = A.length(), x = root, y, c; res = 0;
    re(i, len) {
        c = A[i] - 97;
        while (x && !T[x].ch[c]) x = T[x].fail;    //Attention
        if (!x) x = root; else x = T[x].ch[c];    //Attention
        y = x;
        while (y) {res += T[y].mul; T[y].mul = 0; y = T[y].fail;}      //Attention
    }
}
int main()
{
    int tests, n;
    scanf("%d", &tests);
    re(testno, tests) {
        N = 1;// T[root].mul = 0; re(i, SZ) T[root].ch[i] = 0;
        scanf("%d", &n); getchar();
        re(i, n) {
            gets(tmp0);
            s0 = tmp0;
            ins();
        }
        gets(tmp);
        A = tmp;
        mkf();
        solve();
        printf("%d\n", res);
    }
    return 0;
}