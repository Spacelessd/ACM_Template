#include<iostream>
#include <map>
using namespace std;
struct myComp
{
	int a, b, c;
	myComp():a(0), b(0), c(0){};
	myComp(int aa, int bb, int cc):a(aa), b(bb), c(cc){}
	bool operator< (const myComp &lb) const
	{
		if (a != lb.a) return a<lb.a;
		if (b != lb.b) return b<lb.b;
		if (c != lb.c) return c<lb.c;  
		return false;
	};
};
int main()
{
	map<myComp, char> imap;
	imap[myComp(4,5,0)] = 'q';
	imap[myComp(2,8,9)] = 'o';
	imap[myComp(3,9,1)] = 'u';
	imap[myComp(3,10,1)] = '9';
	imap[myComp(3,9,0)] = '0';
	imap[myComp(3,9,1)] = 'm';
	imap[myComp(11,11,11)] = 'g';
	map<myComp, char>::iterator iter = imap.begin();
	for (; iter != imap.end(); ++iter)
	{
		char temp[16] = {0};
		cout<<(iter->first).a<<" "<<(iter->first).b<<" "<<(iter->first).c<<" "<<iter->second<<endl;
	}
	system("pause");
	return 0;
}


