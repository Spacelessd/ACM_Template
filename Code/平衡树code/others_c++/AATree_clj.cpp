#include<cstdio>
using namespace std;
const int inf=~0U>>1;
class AA_Tree
{
		struct node
		{
				int key,size,level;bool e;
				node*c[2];
				node(int _key,int _size,node*_c):key(_key),size(_size),level(1),e(true)
					{c[0]=c[1]=_c;}
				void rz(){size=c[0]->size+c[1]->size+e;}
		}*root,*null;
		void rot(node*&t,bool d)
		{
				node*p=t->c[d];
				t->c[d]=p->c[!d];
				p->c[!d]=t;
				t->rz();p->rz();
				t=p;
		}
		void skew(node*&t)
		{
				if(t->c[0]->level==t->level)
						rot(t,0);
		}
		void split(node*&t)
		{
				if(t->c[1]->c[1]->level==t->level)
						rot(t,1);
				t->level++;
		}
		void insert(node*&t,int x)
		{
				if(t==null){t=new node(x,1,null);return;}
				if(t->key==x){t->size+=1-t->e;t->e=true;return;}
				bool d=x>t->key;
				insert(t->c[d],x);
				skew(t);split(t);t->rz();
		}
		void Delete(node*&t,int x)
		{
				if(t==null){return;}
				if(t->key==x){t->size-=t->e;t->e=false;return;}
				bool d=x>t->key;
				Delete(t->c[d],x);
				t->rz();
		}
		int select(node*t,int k)
		{
				int r=t->c[0]->size;
				if(k==r&&t->e) return t->key;
				if(k<r) return select(t->c[0],k);
				return select(t->c[1],k-r-t->e);
		}
		int rank(node*t,int x)
		{
				if(t==null)return 0;
				int r=t->c[0]->size;
				if(x==t->key) return r;
				if(x<t->key) return rank(t->c[0],x);
				return r+t->e+rank(t->c[1],x);
		}
		public:
		AA_Tree()
		{
				null=new node(0,0,0);null->level=0;
				root=null;
		}
		void ins(int x){insert(root,x);}
		void del(int x){Delete(root,x);}
		int sel(int k){if(k>=root->size) return inf; return select(root,k);}
		int ran(int x){return rank(root,x);}
}T;
int main()
{
		//freopen("in","r",stdin);
		//freopen("out","w",stdout);
		int n;scanf("%d",&n);char t;int x,tmp;
		while(n--)
		{
				scanf("%c %d\n",&t,&x);
				switch(t)
				{
						case 'I':T.ins(x);break;
						case 'D':T.del(x);break;
						case 'K':tmp=T.sel(x-1);if(tmp==inf) printf("invalid\n");
										 else printf("%d\n",tmp);break;
						case 'C':printf("%d\n",T.ran(x));break;
				}
		}
}


