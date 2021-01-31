#ifndef _123DSL_
#define _123DSL_
template< class T >
class DSL
{
private:
	T Infinite;
	struct Node
	{
		T Data;
		Node *Right;
		Node *Down;
	};
	Node *Head;
	Node *Bottom;
	Node *Tail;
public:
	DSL( const T &inf )   /* 构造函数,参数用于设置无穷元的值 */
	{
		Infinite = inf;
		Head = new Node;
		Bottom = new Node;
		Tail = new Node;
		Head->Data = Tail->Data = Infinite;
		Head->Right = Tail->Right = Tail;
		Head->Down = Bottom->Down = Bottom->Right = Bottom;
	}
	~DSL()   /* 析构函数 */
	{
		while( Head != Bottom )
		{
			Node *HeadDown = Head->Down;
			while( Head != Tail )
			{
				Node *HeadRight = Head->Right;
				delete Head;
				Head = HeadRight;
			}
			Head = HeadDown;
		}
		delete Bottom;
		delete Tail;
	}
	bool Find( const T &item )   /* 查找函数 */
	{
		Node *p = Head;
		while( p != Bottom )
		{
			while( p->Data < item )
				p = p->Right;
			if( p->Data == item )
				return true;
			else p = p->Down;
		}
		return false;
	}
	void Insert( const T &item )   /* 插入函数,将item插入到最底层 */
	{
		Bottom->Data = item; /* 无防护代码,可以有效地提高效率 */
		Node *p = Head;
		while( p != Bottom )
		{
			while( p->Data < item )
				p = p->Right;
			if( p->Data > p->Down->Right->Right->Data )   /* 该语句判断是否下降一层的gap为3;或者当前是最底层且item元素没有出现过 */
			{
				Node *newNode = new Node;
				newNode->Right = p->Right;
				newNode->Down = p->Down->Right->Right;
				newNode->Data = p->Data;
				p->Right = newNode;
				p->Data = p->Down->Right->Data;
			}
			else p = p->Down;
		}
		if( Head->Right != Tail )   /* 若有必要,增加DSL的高度 */
		{
			Node *newHead = new Node;
			newHead->Data = Infinite;
			newHead->Right = Tail;
			newHead->Down = Head;
			Head = newHead;
		}
	}
	void Delete( const T &item )   /* 删除函数 */
	{
		Node *p = Head;
		Node *StackHead = Tail; /* 栈Stack用于记录之前的所有关键码等于item的节点地址 */
		while( p->Down != Bottom )
		{
			Node *father = p; /* 在p下降之前,记录上一层的节点father */
			p = p->Down; /* p下降一层 */
			Node *q = p; /* 指针q用来记录p在同一层中的前驱节点 */
			while( p->Data < item )   /* p和q的右移操作 */
			{
				q = p;
				p = p->Right;
			}
			/* 维护栈信息 */
			if( father->Data == p->Data )   /* 如果节点father的数据需要随着节点p的数据变化而一起变化,将father压入栈Stack中 */
			{
				Node *newStackHead = new Node;
				newStackHead->Right = StackHead;
				newStackHead->Down = father;
				StackHead = newStackHead;
			}
			else	/* 如果连接关系到这一层已断,将栈Stack清空 */
			{
				while( StackHead != Tail )
				{
					Node *newStackHead = StackHead->Right;
					delete StackHead;
					StackHead = newStackHead;
				}
			}
			/* 维护节点信息 */
			if( p->Down == Bottom )   /* 若是最底层,需要直接删除 */
			{
				if( q == p )   /* 删p的右节点并将其信息拷贝到p上 */
				{
					Node *pRight = p->Right;
					p->Right = pRight->Right;
					p->Data = pRight->Data;
					delete pRight;
				}
				else	/* 直接删节点p */
				{
					q->Right = p->Right;
					delete p;
					p = q; /* 重新设置指针p以适合p->Down的判断 */
				}
				while( StackHead != Tail )   /* 如果栈Stack非空,将其中所有节点重新赋值为q->Data */
				{
					Node *newStackHead = StackHead->Right;
					StackHead->Down->Data = q->Data;
					delete StackHead;
					StackHead = newStackHead;
				}
			}
			else if( p->Data != p->Down->Right->Data  )	/* 若下一层gap大于1,则什么也不做 */
			{
			}
			else if ( q == p )	/* 考虑右边相邻的gap */
			{
				if( p->Right->Data != p->Right->Down->Right->Data )   /* 若右边相邻的gap大于1,则向右边的gap借一个 */
				{
					p->Data = p->Right->Down->Data;
					p->Right->Down = p->Down->Right->Right->Right;
					while( StackHead != Tail )   /* 由于p->Data有所改变,所以将栈Stack中所有节点重新赋值 */
					{
						Node *newStackHead = StackHead->Right;
						StackHead->Down->Data = p->Data;
						delete StackHead;
						StackHead = newStackHead;
					}
				}
				else	/* 若右边相邻的gap也等于1,则删去p的右节点 */
				{
					Node *pRight = p->Right;
					p->Right = pRight->Right;
					p->Data = pRight->Data;
					delete pRight;
					while( StackHead != Tail )   /* 由于p->Data有所改变,所以将栈Stack中所有节点重新赋值 */
					{
						Node *newStackHead = StackHead->Right;
						StackHead->Down->Data = p->Data;
						delete StackHead;
						StackHead = newStackHead;
					}
				}
			}
			else	/* 考虑左边相邻的gap,左边相邻的gap以q为头指针 */
			{
				if( q->Data != q->Down->Right->Data )   /* 若左边相邻的gap大于1,则向左边借一个 */
				{
					Node *tmp = q->Down->Right;
					while( tmp->Right->Data != q->Data )
						tmp = tmp->Right;
					q->Data = tmp->Data;
					p->Down = tmp;
				}
				else	/* 若左边相邻的gap也等于1,则删去节点p */
				{
					q->Right = p->Right;
					q->Data = p->Data;
					delete p;
					p = q; /* 重新设置指针p以适合p->Down的判断 */
				}
			}
		}
		if( Head->Down->Data == Infinite )   /* 若有必要,降低DSL的高度 */
		{
			Node *newHead = Head->Down;
			delete Head;
			Head = newHead;
		}
	}
	void print(){
		Node *x=Head;
		while (x->Down!=Bottom)x=x->Down;
		while (x->Right!=Tail)printf("%d ",x->Data),x=x->Right;
		printf("\n");
	}
};
#endif


