#include<stdio.h>
#include<string.h>
//#include<iostream>
//using namespace std;
class huge{
      public:
      int *a;
      huge *tmp;
      huge(int len=10)
      {
               len++;
               a=new int[len];
               memset(a,0,sizeof(a));
      }
      
      huge& operator +(huge& b)
      {
      
      }
      void print()
      {
           
      }
};
huge a;
int main()
{
    a=32;
    a.print();
    for(;;);
}
