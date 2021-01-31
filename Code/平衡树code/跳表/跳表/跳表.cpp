#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<cmath>
#include<ctime>
using namespace std;
#define DefaultSize 12

//SkipNode结构  跳表的结点声明和定义,E为结点数据域类型,K为关键码的类型
template<class T>
struct SkipNode
{
	T data;						   //数据域
	SkipNode<T>** link;			   //指针域数组
	SkipNode(T x,int size=DefaultSize)//构造函数
	{
		data=x;
		link=new SkipNode<T>*[size];
		//如果内存分配失败
		if(link==NULL)
		{
			cout<<"内存分配失败!"<<endl;
			exit(1);
		};
		//把指针数组初始化为NULL
		for(int i=0;i<size;i++)
			link[i]=NULL;
	};
	~SkipNode()					  //析构函数
	{delete [] link;};
};
//SkipList类模板  跳表的类模板即通过多级链表的组织方式提高搜索的效率,0级链表的排列顺序是从左到右升序
template<class T>
class SkipList
{
private:
	int maxLevel;		//允许的跳表最高级别
	int level;		   //当前非空链的最高级别
	T TailKey;		   //最后一个结点里放的正无穷
	SkipNode<T>* head;   //附加头结点指针
	SkipNode<T>* tail;   //附加尾结点指针
	SkipNode<T>** last;  //每条链上的最后一个元素的指针
	//为从L到H之间的元素分配lev级别
	void setGrade(int* grade,int L,int H,int lev);
	//在[0,level]之间随机产生一个级别
   int randLevel();
public:
	//构造函数
	SkipList(T large,int maxLev);
	//通过描述数组来创建一个跳表
	void CreateSkipList(T* A,int n);
	//析构函数
	~SkipList();
	//显示各级链表的内容
	void Display();
	//搜索指定内容x的结点
	SkipNode<T>* Search(T x);
	//判断元素在跳表中是否存在
	bool Exist(T x);
	//把指定的元素x插入到当前的跳表中去
	bool Insert(T x);
	//删除跳表中指定值的结点
	bool Remove(T x);
};
//构造函数  构造一个空链表
template<class T>
SkipList<T>::SkipList(T large,int maxLev)
{
	maxLevel=maxLev;	 //初始化最高级别
	level=0;			 //当前初始级别为0级
	TailKey=large;	   //为结点中的最大关键码

	//创建附加头结点
	head=new SkipNode<T>(-1000,maxLevel+1);
	//创建一个附加尾结点
	tail=new SkipNode<T>(TailKey,maxLevel+1);
	//为last数组开辟内存,并进行初始化
	last=new SkipNode<T>*[maxLevel];
	for(int i=0;i<=maxLevel;i++)
		last[i]=head;
	//让head附加头结点里的指针全部指向tail,表示链表空
	for(int i=0;i<=maxLevel;i++)
		head->link[i]=tail;
};
//析构函数,释放跳表的内存空间
template<class T>
SkipList<T>::~SkipList()
{
	//游标指针
	SkipNode<T>* ptr=head;
	SkipNode<T>* pre=head;
	//依次删除每个结点
	while(pre!=NULL)
	{
		//把ptr先移到后面的链表头
		ptr=ptr->link[0];
		//释放pre结点的空间
		delete pre;
		pre=ptr;
	};
};
//Display()公有成员函数,显示各级链表的内容
template<class T>
void SkipList<T>::Display()
{
	//游标指针
	SkipNode<T>* ptr=head;
	//遍历各级链表
	for(int i=0;i<=level;i++)
	{
		cout<<i<<"级链:";
		ptr=head->link[i];
		while(ptr!=tail)
		{
			cout<<ptr->data<<" ";
			ptr=ptr->link[i];
		}
		cout<<endl;
	};
};
//CreateSkipList()公有成员函数,通过描述数组串创建跳表
template<class T>
void SkipList<T>::CreateSkipList(T* A,int n)
{
	int* grade=new int[n];   //存放级数的数组
	for(int i=0;i<n;i++)	 //把级别数组初始化为0
		grade[i]=0;
	level=int(log(n)/log(2));//根据n求最大级别

	//为每个结点分配级别，并把级别存入grade数组
	setGrade(grade,0,n-1,level);

	//先把A中的取出来建立各级链表
	for(int i=0;i<n;i++)
	{
		//新建一个结点
		SkipNode<T>* newNode=new SkipNode<T>(A[i]);
		//建立第i个结点的各级链表
		for(int j=0;j<=grade[i];j++)
		{
			//挂入第j级链中
			last[j]->link[j]=newNode;
			//第j级游标指针向后推进
			last[j]=newNode;
		};
	};
	//挂上附加尾结点
	for(int i=0;i<=level;i++)
		last[i]->link[i]=tail;

	//释放grade数组的空间
	delete [] grade;
};
//Search()公有成员函数,在跳表中搜索指定值x的元素的结点指针
template<class T>
SkipNode<T>* SkipList<T>::Search(T x)
{
	//游标指针从最高级链的第一个元素开始
	SkipNode<T>* ptr=head->link[level];
	//当前级别链表的回溯指针
	SkipNode<T>* base=head;
	int grade=level;
	//从最高级链开始依次往下搜索
	//在第grade级链中进行搜索
	while(base!=tail && grade!=-1)
	{
		//如果找到就返回当前结点指针
		if(x==ptr->data)
			return ptr;
		//如果x比当前结点大,就继续向后
		else if(x>ptr->data)
		{
			base=ptr;
			ptr=ptr->link[grade];
		}
		//如果x比当前结点小,就降级
		else if(x<ptr->data)
		{
			//从次级的base重新开始搜索
			grade--;
			ptr=base->link[grade];
		};
	};
	//如果没有找到就返回尾指针的值
	return tail;
};
//Exist()公有成员函数,判断元素x在当前跳表中是否存在
template<class T>
bool SkipList<T>::Exist(T x)
{
	//游标指针从最高级链的第一个元素开始
	SkipNode<T>* ptr=head->link[level];
	//当前级别链表的回溯指针
	SkipNode<T>* base=head;
	int grade=level;
	//从最高级链开始依次往下搜索
	//在第grade级链中进行搜索
	while(base!=tail && grade!=-1)
	{
		//如果找到就返回真
		if(x==ptr->data)
			return true;
		//如果x比当前结点大,就继续向后
		else if(x>ptr->data)
		{
			base=ptr;
			ptr=ptr->link[grade];
		}
		//如果x比当前结点小,就降级
		else if(x<ptr->data)
		{
			//从次级的base重新开始搜索
			grade--;
			ptr=base->link[grade];
		};
	};
	//如果没有找到就返回假
	return false;
};
//Insert()公有成员函数,把元素x插入到当前的跳表中去,成功就返回true
template<class T>
bool SkipList<T>::Insert(T x)
{
	//如果元素已经存在就返回false
	if(Exist(x)||x>TailKey)
		return false;
	//为新元素创建新的结点
	SkipNode<T>* newNode=new SkipNode<T>(x);
	//用于存放要插入的结点前在各级链表中的指针
	SkipNode<T>** preLoc=new SkipNode<T>*[level+1];
	//游标指针
	SkipNode<T>* ptr=head;
	//从最高级别开始向下搜索
	int grade=level;
	//寻找新结点在各级链表中插入位置
	while(grade!=-1)
	{
		//如果x小于ptr下个结点的值
		if(x<ptr->link[grade]->data)
		{
			//把当前的ptr记录到preLoc数组中
			preLoc[grade]=ptr;
			//来到下级链继续进行搜索
			grade--;
		}
		//如果x大于ptr下个结点的值
		else if(x>ptr->link[grade]->data)
			ptr=ptr->link[grade];
	};
	//为待插入的结点随机分配级别
	int g=randLevel();
	//把新结点newNode插入到各级链表中
	for(int i=g;i>=0;i--)
	{
		//把新结点挂入第i级链表中
		newNode->link[i]=preLoc[i]->link[i];
		preLoc[i]->link[i]=newNode;
	};
	return true;
};
//Remove()//公有成员函数,删除跳表中指定值的元素结点
template<class T>
bool SkipList<T>::Remove(T x)
{
	//如果指定的元素不存在
	if(!Exist(x))
		return false;
	//用于存放要删除的结点前在各级链表中的指针
	SkipNode<T>** preLoc=new SkipNode<T>*[level+1];
	//把该数组初始化为NULL
	for(int i=0;i<=level+1;i++)
		preLoc[i]=NULL;
	//游标指针
	SkipNode<T>* ptr=head;
	//从最高级别开始向下搜索
	int grade=level;
	//寻找新结点在各级链表中插入位置
	while(grade!=-1)
	{
		//如果x小于ptr下个结点的值
		if(ptr->link[grade]->data>x)
			//x在当前级的链表中不存在,
			//来到下级链继续进行搜索
			grade--;
		//如果x大于ptr下个结点的值
		else if(ptr->link[grade]->data<x)
			ptr=ptr->link[grade];
		//如果等于ptr下个结点的值
		else if(ptr->link[grade]->data==x)
		{
			//记录下当前要删除结点的前驱指针
			preLoc[grade]=ptr;
			//继续降级
			grade--;
		};
	};
	//把该元素在各级链中进行删除
	for(int i=0;preLoc[i]!=NULL;i++)
		preLoc[i]->link[i]=preLoc[i]->link[i]->link[i];

	return true;
};
//setGrade()私有成员函数,把下表从L到H的结点分配lev的级数
template<class T>
void SkipList<T>::setGrade(int* grade,int L,int H,int lev)
{
	//如果下界小于上界
	if(L<H && lev>0)
	{
		//取中间元素
		int q=int((L+H)/2);
		//设置该元素的级别
		grade[q]=lev;
		//递归设置q左右的结点
		setGrade(grade,L,q-1,lev-1);
		setGrade(grade,q+1,H,lev-1);
	};
};
//randLevel()私有成员函数，在[0,level]之间随机产生一个级别
template<class T>
int SkipList<T>::randLevel()
{
	srand(time(0));
	return rand()%(level+1);
};
int e=1000,d=4;
SkipList<int> s(e,d);
int main()
{
	int sp[12]={1,3,5,12,15,18,21,32,35,45,55,66};
	s.CreateSkipList(sp,12); //产生跳表
	s.Display();//输出原始跳表
	printf("nie\n");
	int k=1;
	while(k!=4)  //操作菜单的设计
	{
		cout<<"1.搜索元素\n";
		cout<<"2.删除元素\n";
		cout<<"3.添加元素\n";
		cout<<"4.结束操作\n";
		cin>>k;
		switch(k)
		{
		case 1:	cout<<"输入搜索的元素"<<endl;
				int a;
				cin>>a;
				if(s.Search(a)->data==1000)
				{	cout<<"该值不存在！\n"<<'\n';}
				else
				{
					cout<<"元素:"<<s.Search(a)->data<<"存在\n"<<'\n';
				}
				break;
		case 2:	cout<<"输入删除的元素"<<endl;
				int b;
				cin>>b;
				if(s.Search(b)->data==1000)
				{	cout<<"该值不存在！\n"<<'\n';}
				else
				{
				s.Remove(b);
				cout<<"删除后跳表显示："<<endl;
				s.Display();
				}
				break;
		case 3:	cout<<"输入添加的元素"<<endl;
				int c;
				cin>>c;
				if(s.Search(b)->data!=1000)
				{
					cout<<"添加的值已经存在\n";
				}
				else
				{
				s.Insert(c);
				cout<<"添加后跳表显示："<<endl;
				s.Display();
				}
				break;
		case 4:	;
		}
	}
}


