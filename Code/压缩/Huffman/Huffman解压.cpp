#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 305
typedef struct
{
	int l,r,p;
	char ch;int w;
}HuffmanTree;
typedef HuffmanTree HTree[N*2];
typedef struct
{
	char bits[N],ch;
}HuffmanCode;
typedef HuffmanCode HCode[N];
int read(HTree &T,HCode &H,int &size){
	static char s[N];
	int n=0,i,str1;
	FILE *ch=fopen("Char.txt","r"),*hc=fopen("HuffmanCode.txt","r"),
		 *wei=fopen("Weight.txt","r");
	if (ch==NULL||hc==NULL||wei==NULL){
		printf("error:can't open file!\n");
		system("pause");exit(0);
	}
	while (!feof(ch)){
		H[n].ch=fgetc(ch);++size;
		T[n].ch=H[n].ch;++n;
	}
	i=0;str1=0;
	while (!feof(hc)){
		char c=fgetc(hc);++size;
		switch(c){
			case '\n':
				++size;++i;str1=0;break;
			default:
				H[i].bits[str1++]=c;H[i].bits[str1]=0;break;
		}
	}
	for (int i=0;i<n;++i)T[i].w=0;
	i=0;str1=0;
	while (!feof(wei)){
		char c=fgetc(wei);++size;
		switch(c){
			case '\n':
				for (char *p=s;*p!=0;++p)T[i].w=T[i].w*10+*p-'0';
				++size;++i;str1=0;break;
			default:
				s[str1++]=c;s[str1]=0;
				break;
		}
	}
	fclose(ch);fclose(hc);fclose(wei);
	return n-1;
}
void CreateHuffmanTree(HTree &T,int n){
	for (int i=0;i<N*2;++i)T[i].l=T[i].r=T[i].p=0;
	for (int i=n;i<n*2-1;++i){
		int id1,min1=1<<30,id2,min2=1<<30;
		for (int j=0;j<i;++j)
			if (!T[j].p&&T[j].w<min1)id1=j,min1=T[j].w;
		for (int j=0;j<i;++j)
			if (!T[j].p&&T[j].w<min2&&j!=id1)id2=j,min2=T[j].w;
		T[id1].p=T[id2].p=i;
		T[i].l=id1;T[i].r=id2;
		T[i].w=T[id1].w+T[id2].w;
	}
}
void extract(int &size){
	char s[15];int tmp,i,j=0,str1;
	FILE *ta=fopen("Tail.txt","r"),*fiw=fopen("File0.txt","w"),
		 *co=fopen("Code.txt","rb");
	if (ta==NULL||co==NULL){
		printf("error:can't open file!\n");
		system("pause");exit(0);
	}
	fscanf(ta,"%d%s",&tmp,s);
	while (j<tmp){
		++j;char c=fgetc(co);++size;
		for (int i=7;i>=0;--i)
			fputc(((c>>i)&1)+'0',fiw);
		fputc(' ',fiw);
	}
	for (int i=0;s[i]!=0;++i)fprintf(fiw,"%c",s[i]);
	fclose(ta);fclose(fiw);fclose(co);
}
void trans(HTree &T,HCode &H,int n,int &size){
	int i=n*2-2;
	FILE *fi=fopen("File0.txt","r"),*tf=fopen("Translated File.txt","w");
	if (fi==NULL){
		printf("error:can't open file!\n");
		system("pause");exit(0);
	}
	while (!feof(fi)){
		char c=fgetc(fi);
		if (T[i].l||T[i].r){
			if (c=='0')i=T[i].l;else if (c=='1')i=T[i].r;
		}
		else {
			fputc(T[i].ch,tf);++size;
			i=n*2-2;
			if (c=='0')i=T[i].l;else if (c=='1')i=T[i].r;
		}
	}
	fclose(fi);fclose(tf);
	remove("File0.txt");
}
HTree T;HCode H;
int main()
{
	int t1=clock();
	int size1=0,size2=0;
	printf("Decoding...\n");
	int n=read(T,H,size1);
	CreateHuffmanTree(T,n);
	extract(size1);trans(T,H,n,size2);
	printf("Translated file in 'Translated File.txt'\n");
	//printf("size1=%d size2=%d\n",size1,size2);
	printf("percent=%.5lf%\n",100.0*size1/size2);
	printf("time=%d\n",clock()-t1);
	system("pause");
	return 0;
}


