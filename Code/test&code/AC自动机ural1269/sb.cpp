
#include <stdio.h>

#include <string>

#include <iostream>

 

#define MAXN 100000

 

using namespace std;

 

struct Trie{

       char chr;

       bool word; //该节点的路径是否为单词

       long son;  //儿子指针

       long next;  //兄弟指针

       long suffix;  //后缀节点

       long len;  //保存该单词的长度(直接路径长度或者后缀节点的单词长度)

};

 

Trie a[MAXN];

long num=0;

 

void addword(string s,Trie *a){  //把单词加入Trie树

       long i,j,k;

       j=0;

       for (i=0;i<s.length();i++) {

              k=a[j].son;

              if (k!=0) {

                     while (a[k].chr!=s[i] && a[k].next!=0) k=a[k].next;

                     if (a[k].chr==s[i]) {

                            j=k;

                     }else{

                            num++;

                            a[num].chr=s[i];

                            a[num].word=false;

                            a[k].next=num;

                            j=num;

                     };

              }else{

                     num++;

                     a[num].chr=s[i];

                     a[num].word=false;

                     a[j].son=num;

                     j=num;

              };

       };

       a[j].len=i;

       a[j].word=true;

};

 

long getchild(long &x,char &c,Trie *a){ //获取x点(后缀等价点)的c儿子

       long i,j=x;

       while (1) {

              i=a[j].son;

              while (a[i].chr!=c && i!=0) i=a[i].next;

              if (a[i].chr==c && i!=0)

                     return i;

              else 

                     if (j!=0)

                            j=a[j].suffix;

                     else 

                            return 0;

       };

};

 

void BuildGraph(Trie *a){  //用BFS求出每个点的后缀节点

       long que[MAXN];

       long i,j,k;

       que[0]=0;

       j=1;k=0;

       i=a[0].son;

       while (i!=0) {k++;que[k]=i;i=a[i].next;};

       while (j<=k) {

              i=a[que[j]].son;

              while (i!=0) {

                     k++;

                     que[k]=i;

                     a[i].suffix=getchild(a[que[j]].suffix,a[i].chr,a);

                     if (a[a[i].suffix].len>a[i].len) {a[i].word=true; a[i].len=a[a[i].suffix].len;};

                     i=a[i].next;

              };

              j++;

       };

};

 

long n,m;

string s;

char c;

char dhh[1000010];

int main(){

       long x,y,ans=999999999;

       long i;

       //cin>>n;
scanf("%d",&n);
       a[0].word=false;

      // getline(cin,s);
gets(dhh);
       for (i=1;i<=n;i++) {

              //getline(cin,s);
gets(dhh);
s=dhh;
              addword(s,a);

       };

       BuildGraph(a);

       cin>>m;//gets(dhh);

       long j=0,k;

       x=0;y=0;

       c=getchar();

       while (x<=m) {

              y++;

              if (c==0 || c==10 || c==13) {

                     j=0;

                     if (c==10) {

                            if (ans<999999999) {cout<<x<<" "<<ans<<endl; //for (;;);
                            return 0;};

                            x++;y=0;

                     }

              }else{

                     k=getchild(j,c,a);

                     if (a[k].word==true) {

                            if (y-a[k].len+1<ans) ans=y-a[k].len+1;

                     };

              j=k;

              };

              c=getchar();

       };

       cout<<"Passed"<<endl;
//for (;;);
       return 0;

}
