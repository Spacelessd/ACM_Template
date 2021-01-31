#ifndef LINK

#define LINK

#include<cstdio>

class edgenode
{
	public:
		int to,w;
		edgenode *next;
		edgenode(int t=0,int w1=0):to(t),w(w1),next(NULL){};
		edgenode(const edgenode &s):to(s.to),w(s.w),next(NULL){};
		operator int ()
		{
			return w;
		}
		~edgenode(){if(next!=NULL)delete next;}
};

class edge
{
	private:
		edgenode *head,*current;
	public:
		edge():head(NULL),current(NULL){}
		void seekend(void){if(head==NULL)return;current=head;while(current->next!=NULL)current=current->next;}
		void repos(void){current=head;}
		void insert(int to,int w)
		{
			if(head==NULL)
			{
				head=new edgenode(to,w);
				current=head;
			}
			else
			{
				current->next=new edgenode(to,w);
				current=current->next;
			}
		}
		bool operator ++ (int){if(current==NULL)return false;current=current->next;return true;}
		edgenode * operator -> () {return current;}
		bool isrear(void){return current==NULL?true:false;}
		~edge(){delete head;delete current;}
};

#endif
