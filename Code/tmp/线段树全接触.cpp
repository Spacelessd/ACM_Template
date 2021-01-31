
struct node{ 
    int m,cover,add; 
};
class tree{ 
      public: 
      node *a; 
      int M;
      tree(){}
      void make(int len=10) 
      { 
            for (M=1;M-2<len;M<<=1);
            a=new node[(M+1)*2]; 
      } 
      void build()
      {
           for (int i=M;i;i--)a[i].m=max(a[i*2].m,a[i*2+1].m);
      }
      
      
}; 
tree a[N]; 
