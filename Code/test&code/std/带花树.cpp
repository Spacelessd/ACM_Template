#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N=250;
int n;
int head;
int tail;
int Start;
int Finish;
int link[N];     //表示哪个点匹配了哪个点
int Father[N];   //这个就是增广路的Father……但是用起来太精髓了
int Base[N];     //该点属于哪朵花
int Q[N];
bool mark[N];
bool map[N][N];
bool InBlossom[N];
bool in_Queue[N];

void CreateGraph(){
    int x,y;
    scanf("%d",&n);
    while (scanf("%d%d",&x,&y)!=EOF)
      map[x][y]=map[y][x]=1;
}

void BlossomContract(int x,int y){
    fill(mark,mark+n+1,false);
    fill(InBlossom,InBlossom+n+1,false);
    #define pre Father[link[i]]
    int lca,i;
    for (i=x;i;i=pre) {i=Base[i]; mark[i]=true; }
    for (i=y;i;i=pre) {i=Base[i]; if (mark[i]) {lca=i; break;} }  //寻找lca之旅……一定要注意i=Base[i]
    for (i=x;Base[i]!=lca;i=pre){
        if (Base[pre]!=lca) Father[pre]=link[i]; //对于BFS树中的父边是匹配边的点，Father向后跳
        InBlossom[Base[i]]=true;
        InBlossom[Base[link[i]]]=true;
    }
    for (i=y;Base[i]!=lca;i=pre){
        if (Base[pre]!=lca) Father[pre]=link[i]; //同理
        InBlossom[Base[i]]=true;
        InBlossom[Base[link[i]]]=true;
    }
    #undef pre
    if (Base[x]!=lca) Father[x]=y;     //注意不能从lca这个奇环的关键点跳回来
    if (Base[y]!=lca) Father[y]=x;
    for (i=1;i<=n;i++)
      if (InBlossom[Base[i]]){
          Base[i]=lca;
          if (!in_Queue[i]){
              Q[++tail]=i;
              in_Queue[i]=true;     //要注意如果本来连向BFS树中父结点的边是非匹配边的点，可能是没有入队的
          }
      }
}

void Change(){
    int x,y,z;
    z=Finish;
    while (z){
        y=Father[z];
        x=link[y];
        link[y]=z;
        link[z]=y;
        z=x;
    }
}

void FindAugmentPath(){
    fill(Father,Father+n+1,0);
    fill(in_Queue,in_Queue+n+1,false);
    for (int i=1;i<=n;i++) Base[i]=i;
    head=0; tail=1;
    Q[1]=Start;
    in_Queue[Start]=1;
    while (head!=tail){
        int x=Q[++head];
        for (int y=1;y<=n;y++)
          if (map[x][y] && Base[x]!=Base[y] && link[x]!=y)   //无意义的边
            if ( Start==y || link[y] && Father[link[y]] )    //精髓地用Father表示该点是否
                BlossomContract(x,y);
            else if (!Father[y]){
                Father[y]=x;
                if (link[y]){
                    Q[++tail]=link[y];
                    in_Queue[link[y]]=true;
                }
                else{
                    Finish=y;
                    Change();
                    return;
                }
            }
    }
}

void Edmonds(){
    memset(link,0,sizeof(link));
    for (Start=1;Start<=n;Start++)
      if (link[Start]==0)
        FindAugmentPath();
}

void output(){
    fill(mark,mark+n+1,false);
    int cnt=0;
    for (int i=1;i<=n;i++)
      if (link[i]) cnt++;
    printf("%d\n",cnt);
    for (int i=1;i<=n;i++)
      if (!mark[i] && link[i]){
          mark[i]=true;
          mark[link[i]]=true;
          printf("%d %d\n",i,link[i]);
      }
}

int main(){
//  freopen("input.txt","r",stdin);
    CreateGraph();
    Edmonds();
    output();
    return 0;
}


