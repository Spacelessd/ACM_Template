#include <direct.h>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
char str[1000005];
int allline,effectline,big,small,allchar,visiblechar;
int filenum;
string bigfile,smallfile;
void count(const string &filename)
{
	freopen(filename.data(),"r",stdin);
	filenum++;
	int line=0;
	while(gets(str))
	{
		allline++;
		line++;
		bool flag=false;
		for(int i=0; str[i]; i++)
		{
			if(!(str[i]==' ' || str[i]=='{' || str[i]=='}' || str[i]=='\t'))
			{
				flag=true;
				visiblechar++;
			}
			if(str[i]=='{' || str[i]=='}')visiblechar++;
			allchar++;
		}
		if(flag)effectline++;
	}
	if(big<line)
	{
		bigfile=filename;
		big=line;
	}
	if(small>line)
	{
		smallfile=filename;
		small=line;
	}
	fclose(stdin);
	freopen("CON","r",stdin);
}
void getFiles(const string &path)
{
	//文件句柄
	long hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string *pp=new string;
	string &p=*pp;
	if((hFile=_findfirst(p.assign(path).append("\\*").c_str(),&fileinfo))   !=   -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if((fileinfo.attrib&_A_SUBDIR))
			{
				if(strcmp(fileinfo.name,".")!=0&&strcmp(fileinfo.name,"..")!=0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name));
			}
			else
			{
				string filename=p.assign(path).append("\\").append(fileinfo.name);
				int t=filename.find(".cpp");
				if(filename.length()-t==4)
					count(filename);
				t=filename.find(".java");
				if(filename.length()-t==5)
					count(filename);
			}
		}
		while(_findnext(hFile,&fileinfo)==0);
		_findclose(hFile);
	}
}
int main()
{
	allline=effectline=big=allchar=visiblechar=filenum=0;
	small=0x7fffffff;
	printf("请输入路径\n格式：\nE:\\yy\n");
	string path;
	cin>>path;
	getFiles(path.data());
	printf("<< %s >>下共有<< %d >>个源文件\n",path.data(),filenum);
	printf("其中所有代码行数为<< %d >>行\n",allline);
	printf("有效代码行数为<< %d >>行\n",effectline);
	printf("每个文件平均行数为<< %d >>行\n",allline/filenum);
	printf("代码最长的文件是 << %s >> 共有代码<< %d >>行\n",bigfile.data(),big);
	printf("代码最短的文件是 << %s >> 共有代码<< %d >>行\n",smallfile.data(),small);
	printf("所有的字符数<< %d >>个\n",allchar);
	printf("其中可见字符数<< %d >>个\n",visiblechar);
	printf("平均每个文件可见字符数<< %d >>个\n",visiblechar/filenum);
	system("pause");
	return 0;
}


