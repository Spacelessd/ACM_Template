#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
#include<list>
#include<functional>

using namespace std;
int main()
{
	int i;
	char *text = new char[100];
	text = "substring searching algorithm search";
	char *patt = new char[10];
	patt = "search";
	size_t temp[256];
	size_t *shift = temp;
	size_t patt_size = strlen(patt);
	cout << "size : " << patt_size << endl;
	for(size_t i = 0; i < 256; i++)
		*(shift + i) = patt_size + 1; //所有值赋于7，对这题而言
	for(i = 0; i < patt_size; i++)
		*(shift + (unsigned char)(*(patt + i) ) ) = patt_size - i;
	//移动3步-->shift['r']=6-3=3;移动三步
	//shift['s']=6步,shitf['e']=5以此类推
	size_t text_size = strlen(text);
	size_t limit = text_size - i + 1;
	for(i = 0; i < limit; i += shift[text[i+patt_size] ] )
		if(text[i] == *patt)
		{
			/*	^13--这个r是位，从0开始算
				substring searching algorithm
				search
				searching-->这个s为第10位，从0开始算
				如果第一个字节匹配，那么继续匹配剩下的
				*/
			char *match_text = text + i + 1;
			size_t	 match_size = 1;
			do
			{
				if(match_size == patt_size)
					cout << "the no is " << i << endl;
			}
			while( (*match_text++) == patt[match_size++] );
		}
	cout << endl;
	system("pause");for (;;);
	return 0;
}


