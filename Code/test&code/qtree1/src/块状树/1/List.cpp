#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
using namespace std;
struct List{
      struct node{
             int key;
             node *next;
             };
      node *start,*tmp;
      void clear(){start=NULL;}
      List(){clear();}
      bool empty(){return start?1:0;}
      void push_back(int key){
           tmp=new node;tmp->key=key;
           tmp->next=start;
           start=tmp;
      }
      node* begin(){return start;}
      node* end(){return NULL;}
      struct iterator{
             node *key;
             void operator =(node *x){key=x;}
             void operator ++(){key=key->next;}
             //void operator ++(iterator x){x->key=x->key->next;}
             int operator *(){return key->key;}
             bool operator !=(node *x){return key==x;}
      };
};
List a;
List::iterator b;
int main()
{
    a.push_back(3);
    a.push_back(1);
    b=a.begin();
    ++b;
    printf("%d\n",*b);
    system("pause");
}
