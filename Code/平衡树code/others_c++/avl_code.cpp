#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct AvlNode;
typedef AvlNode *Position;
typedef AvlNode *AvlTree;
#define ElementType int

int Max(int,int);
int Height(Position T);
AvlTree MakeEmpty(AvlTree T);
Position Find(ElementType x,AvlTree T);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
AvlTree Insert(ElementType x,AvlTree T);
AvlTree Delete(ElementType x,AvlTree T);
AvlTree LLRotate(Position k2);
AvlTree RRRotate(Position k2);
AvlTree LRRotate(Position k2);
AvlTree RLRotate(Position k2);
void PrintTree(AvlTree T,int depth);
void PrintName(AvlTree T,int depth);
char Welcome(void);

struct AvlNode
{
	ElementType data;
	AvlTree left;
	AvlTree right;
	int height;
};

int main(void)
{
	char a;
	int value;
	AvlTree T = NULL;
	while(1)
	{
		switch(a = Welcome())
		{
			fflush(stdin);
		case '1':
			printf("请输入要添加的值：");
			scanf("%d",&value);
			fflush(stdin);
			T = Insert(value,T);
			break;
		case '2':
			printf("请输入要删除的值：");
			scanf("%d",&value);
			fflush(stdin);
			T = Delete(value,T);
			break;
		case '3':
			PrintTree(T,0);
			fflush(stdin);
			getch();
			break;
		case '4':
			MakeEmpty(T);
			system("pause");
			return 0;
		default:
			printf("输入错误！\n");
		}
	}

	return 0;
}

int Max(int a,int b)
{
	return ((a>b)?a:b);
}
int Height(Position T)
{
	if(T == NULL)
		return -1;
	else
		return T->height;
}
AvlTree MakeEmpty(AvlTree T)
{
	if(T != NULL)
	{
		MakeEmpty(T->left);
		MakeEmpty(T->right);
		free(T);
	}
	return NULL;
}

Position Find(ElementType x,AvlTree T)
{
	if(T == NULL)
		return NULL;
	else if(x < T->data)
		return Find(x,T->left);
	else if(x > T->data)
		return Find(x,T->right);
	else
		return T;
}

Position FindMin(AvlTree T)
{
	if(T == NULL)
		return NULL;
	while(T->left != NULL)
		T = T->left;
	return T;
}

Position FindMax(AvlTree T)
{
	if(T == NULL)
		return NULL;
	else if(T->right == NULL)
		return T;
	else
		return FindMax(T->right);
}

AvlTree Insert(ElementType x,AvlTree T)
{
	if(T == NULL)
	{
		T = (AvlTree)malloc(sizeof(struct AvlNode));
		T->data = x;
		T->height = 0;
		T->left = T->right  = NULL;
	}
	else if(x < T->data)//如果当前节点的值大于要插入的值，则进入其左子树。
	{
		T->left = Insert(x,T->left);
		if(Height(T->left) - Height(T->right) == 2)//插入完成后，验证树是否平衡。如果不平衡
		{								//看是LL还是LR型，因为已经进入左子树，所以只有这两种可能。
			if(x < T->left->data)		//下面的同理。
			{
				T = LLRotate(T);
			}
			else
			{
				T = LRRotate(T);
			}
		}
	}
	else if(x > T->data)//如果当前节点的值小于要插入的值，则进入其右子树。
	{
		T->right = Insert(x,T->right);
		if(Height(T->right) - Height(T->left) == 2)
		{
			if(x > T->right->data)
			{
				T = RRRotate(T);
			}
			else
			{
				T = RLRotate(T);
			}
		}
	}
//这个语句的主要作用是在插入完之后，改变各节点的高度。假如没有插入，则这个语句不会造成任何值得改变。
	T->height = Max(Height(T->left),Height(T->right)) + 1;//因为是递归。。从内到外。。多思考。。
	return T;
}

AvlTree Delete(ElementType x,AvlTree T)//这个删除例程是本人自己所写。差点没抓狂。囧Orz..
{
	Position tmp;
	if(T == NULL)
	{
		printf("Can't found!\n");
		return NULL;
	}
	else if(x < T->data)
	{
		T->left = Delete(x,T->left);//如果删除的是左子树的节点，假如产生不平衡，肯定是由于其右子树
		if(Height(T->right) - Height(T->left) == 2)
		{//这步是判断是RR还是RL型。下面的同理。。
			if( Height(T->right->right) >= Height(T->right->left) )
				T = RRRotate(T);
			else
				T = RLRotate(T);
		}
	}
	else if(x > T->data)
	{
		T->right = Delete(x,T->right);
		if(Height(T->left) - Height(T->right) == 2)
		{
			if( Height(T->left->left) >= Height(T->left->right) )
				T = LLRotate(T);
			else
				T = LRRotate(T);
		}
	}
	else
	{
		if(T->left && T->right) //对有两个孩子的节点删除操作。假如被删节点有两个孩子节点，就与其右子树的最小值的节点
		{						//进行替换，然后删除其右子树的最小值的节点。(因其最小，所以最多有一个右孩子。操作就方便。
			tmp = FindMin(T->left);
			T->data = tmp->data;
			Delete(tmp->data,T->left);
		}
		else//对有一个或0个孩子的节点的删除操作。
		{
			tmp = T;
			if(T->left == NULL)
				T = T->right;
			else if(T->right == NULL)
				T = T->left;
			free(tmp);
		}
	}//这个if是为了避免删除节点之后对NULL指针赋值。
	if(T != NULL)
		T->height = Max(Height(T->left),Height(T->right)) +1;//调整各节点的高度。
	return T;
}

AvlTree LLRotate(Position k2)//对LL型 直接在不平衡节点处进行左旋转。
{
	Position k1;
	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = Max(Height(k2->left),Height(k2->right))+1;
	k1->height = Max(Height(k1->left),Height(k1->right))+1;
	return k1;
}

AvlTree RRRotate(Position k1)//对RR型 直接在不平衡节点处进行右旋转。
{
	Position k2;
	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k2->height = Max(Height(k2->left),Height(k2->right))+1;
	k1->height = Max(Height(k1->left),Height(k1->right))+1;

	return k2;
}

AvlTree LRRotate(Position k3)//对于LR型
{
	k3->left = RRRotate(k3->left);//第一步，在不平衡节点k3的左儿子k1处进行右旋转。
	return LLRotate(k3);//这是第二步，在不平衡节点k3处进行左旋转，并返回新的根。
}

AvlTree RLRotate(Position k3)//对于RL型
{
	k3->right = LLRotate(k3->right);//第一步，在不平衡节点k3的右儿子k1处进行左旋转。
	return RRRotate(k3);//这是第二步，在不平衡节点k3处进行右旋转，并返回新的根。
}

void PrintTree(AvlTree T,int depth)//打印出树，为了直观，这个不是先序，也不是中序，也不是后序，囧。
{
	if(T != NULL)
	{
		PrintName(T,depth);
		PrintTree(T->right,depth+1);
		PrintTree(T->left,depth+1);
	}
}

void PrintName(AvlTree T,int depth)
{
	for(int i=0; i<depth; i++)
		printf("   ");
	printf("%d(%d)\n",T->data,T->height);
}

char Welcome(void)//测试函数
{
	char a;
	printf("1.插入节点\n");
	printf("2.删除节点\n");
	printf("3.打印树\n");
	printf("4.退出程序\n");
	a = getchar();
	return a;
}


