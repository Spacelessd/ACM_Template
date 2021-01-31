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
	int l,r,p,w;
}HuffmanTree;
typedef HuffmanTree HTree[N*2];
typedef struct
{
	char bits[N],ch;
	int start;
}HuffmanCode;
typedef HuffmanCode HCode[N];
int read(int count[],char s[],char file_name[]){
	static int tmp[N];
	FILE *f=fopen(file_name,"r");
	if (f==NULL){
		printf("error:Can't open file!\n");system("pause");exit(0);
	}
	int n=0;
	for (int i=0;i<N;++i)tmp[i]=0,count[i]=0;
	while (!feof(f))
		++tmp[fgetc(f)];
	for (int i=0;i<N;++i)if (tmp[i]){
		s[n]=i;count[n]=tmp[i];++n;
	}
	return n;
}
void CreateHuffmanTree(HTree &T,int n,int count[],char s[]){
	for (int i=0;i<n*2+1;++i){
		T[i].l=T[i].r=T[i].p=0;
	}
	for (int i=0;i<n;++i)T[i].w=count[i];
	for (int i=n;i<n*2-1;++i){
		int id1,min1=1<<30,id2,min2=1<<30;
		for (int j=0;j<i;++j)
			if (!T[j].p&&T[j].w<min1)min1=T[j].w,id1=j;
		for (int j=0;j<i;++j)
			if (!T[j].p&&j!=id1&&T[j].w<min2)min2=T[j].w,id2=j;
		T[id1].p=T[id2].p=i;
		T[i].l=id1;T[i].r=id2;
		T[i].w=T[id1].w+T[id2].w;
	}
}
void HuffmanCoding(HTree &T,HCode &H,int n,char s[]){
	char code[N];code[n]=0;
	for (int i=0;i<n;++i)code[i]='W';
	for (int i=0;i<n;++i){
		int now=i,start=n;H[i].ch=s[i];
		for (int p=T[now].p;p;now=p,p=T[p].p){
			if (T[p].l==now)code[--start]='0';
			else code[--start]='1';
		}
		H[i].start=start;
		strcpy(H[i].bits,code);
	}
}
void print(HTree &T,HCode &H,int n){
	FILE *hc=fopen("HuffmanCode.txt","w"),
		 *ch=fopen("Char.txt","w"),*wei=fopen("Weight.txt","w");
	for (int j=0;j<n;++j){
		for (int i=H[j].start;i<n;++i)fprintf(hc,"%c",H[j].bits[i]);
		fprintf(hc,"\n");
	}
	for (int i=0;i<n;++i)fputc(H[i].ch,ch);
	for (int i=0;i<n;++i)fprintf(wei,"%d\n",T[i].w);
	fclose(hc);fclose(ch);fclose(wei);
}
HuffmanCode *Link_[N*2],**Link=Link_+N;
void write(HCode &H,int n,char file_name[]){
	int p=0;
	FILE *f=fopen(file_name,"r"),*fi=fopen("File.txt","w");
	if (fi==NULL){
		printf("error:Can't open file!\n");system("pause");exit(0);
	}
	for (int i=0;i<n;++i)Link[H[i].ch]=H+i;
	while (!feof(f)){
		char c=fgetc(f);
		HuffmanCode *i=Link[c];
		if (i==NULL)continue;
		for (int j=i->start;j<n;++j){
			fputc(i->bits[j],fi);
			if (++p==8)fputc(' ',fi),p=0;
		}
	}
	fclose(f);fclose(fi);
	
}
void FileConvert(){
	char str[15];int x=0,str1=0,sum=0;
	FILE *fi=fopen("File.txt","r"),*co=fopen("Code.txt","wb"),
		 *ta=fopen("Tail.txt","w");
	if (fi==NULL){
		printf("error:Can't open file!\n");system("pause");exit(0);
	}
	while (!feof(fi)){
		str[str1]=fgetc(fi);
		switch(str[str1]){
			case '0':x=x*2+0;++str1;break;
			case '1':x=x*2+1;++str1;break;
			case ' ':
				fwrite(&x,1,1,co);++sum;x=0;str1=0;break;
			default:
				fprintf(ta,"%d ",sum);
				for (int j=0;j<str1;++j)fprintf(ta,"%c",str[j]);
			break;
		}
	}
	fclose(fi);fclose(co);fclose(ta);
	remove("File.txt");
}
HTree T; HCode H;
int cnt[N],n;
char s[N],file_name[105];
int main()
{
	printf("Input Filename:\n");
	scanf("%s",file_name);
	printf("\n");
	int t1=clock();
	printf("Encoding...\n");
	n=read(cnt,s,file_name);
	printf("Character in 'Char.txt'\n");
	printf("Character weight in 'Weight.txt'\n");
	CreateHuffmanTree(T,n,cnt,s);
    HuffmanCoding(T,H,n,s);
    print(T,H,n);
    printf("Huffman Code In 'HuffmanCode.txt'\n");
    write(H,n,file_name);
    FileConvert();
    printf("Code file in 'Code.txt'\n");
    printf("Tail file in 'Tail.txt'\n");
    printf("time=%d\n",clock()-t1);
	system("pause");
	return 0;
}


