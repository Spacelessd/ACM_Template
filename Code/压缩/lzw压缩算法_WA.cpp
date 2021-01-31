#include <stdio.h>
#include <stdlib.h>
#include <String>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;
typedef   unsigned   char   byte;

class LzwNode{
    public:
    //   int num;//序列,规定其0-4095
       int data1;//数据1，存前面存放过的数据
       byte data2;//存放新入的数据         
    
};
class Lzw{
    public:
       int len;//字典的长度
       LzwNode lzw[4096]; //定义一个长为4096的数组，来存放数据 
       void unitLzw(){
            len=0;
            //对前256个数据进行初始化 
            for (int i=0;i<256;i++){
                lzw[i].data1=-1;//默认为0 
                lzw[i].data2=i;
                cout<<"["<<i<<"]:"<<lzw[i].data1<<" "<<(int)lzw[i].data2<<endl;
                len++;
            }
       }
       void add(int ad,byte x){
            lzw[len].data1=ad;
            lzw[len].data2=x;
			
	/*		
			cout<<"添加字典新项目："<<x;
			
			do
			{cout<<lzw[ad].data2;ad=lzw[ad].data1;}
			while (ad!=-1);
	*/		

            len++;
       }
       //判断匹配与否 
       int matchdatas(byte ss[],int sscount,int i){//传入要对比的数组及在字典中位置 
          if (i<256){
              if (((int)lzw[i].data2==(int)ss[sscount-1])&&(sscount==1)) return 1;
                            else return 0;
          }
          else{
                if (((int)lzw[i].data2==(int)ss[sscount-1])&&(sscount>=1))return matchdatas(ss,sscount-1,lzw[i].data1);
                          else return 0;
              }
       }
       int match(byte ss[],int sscount){
          for (int i=0;i<len;i++){
             if  (matchdatas(ss,sscount,i)==1){
                 return i;
             }
          }
          return -1;
          
       }
    /*   
       int pushNum(int i){
          int ii=i;
          int count=0;
          while (ii>=256){
            ii=lzw[ii].data1;
            count++;
          }
          count++;
          return count;
       }*/
       
       
       int check(int data1,byte data2){
           for (int i=0;i<len;i++){
             if ((lzw[i].data1==data1)&&((int)lzw[i].data2==(int)data2)){
               return i;
             }
           }
           return -1;
       }
       //找头的方法 
       byte gethead(int i){
          if (i<256){
          return lzw[i].data2;
          }else{
       //     printf("到:(%d)",lzw[i].data1);
            return gethead(lzw[i].data1);
          }
       }
};
class LzwCompression{

    public:
      void lzwCompression(){
  ifstream file1;
  ofstream file2;
  Lzw lz;
  string path1,path2;
  printf("请输入要压缩文件的位置及名称:");
  cin >> path1;
  printf("请输入压缩后文件保存的位置及名称:");
  cin >> path2;
  int fore,after;
  file1.open(path1.c_str(),ios::binary);
  file2.open(path2.c_str(),ios::binary);
//  char x;
  int times=0;
  int odd=0;//控制奇偶变量 
  byte odd0,odd1,odd2;
 // int matchint;
//  byte s[4097];
  int scount;
while (!file1.eof()){ 
  //初始化
  lz.unitLzw();
  char x;
  scount=0;
  fore=-1;
  while ((!file1.eof())&&(lz.len<=4096)){

       //要在match中记录上次的地址，放入adress中 
      file1.get(x);
      after=(int)(byte)x; 
      printf("%d ",after);
      while ((lz.check(fore,(byte)after)>=0)&&((!file1.eof()))){   
         fore=lz.check(fore,(byte)after);
          file1.get(x); 
          after=(int)(byte)x;
      };
      //当前串进LZW
      if (lz.check(fore,(byte)after)<0){
         lz.add(fore,(byte)after);
      } 
   //   printf("%d ",fore);
      //输出前缀
      if (odd==0){ 
          odd0=(byte)(fore>>4);
          odd1=((byte)(fore&0x0000000F))<<4;
      }else {
          odd1=odd1+(byte)(fore>>8);
          odd2=(byte)(fore);
          file2.put(odd0);
          file2.put(odd1);
          file2.put(odd2);  
      }
      odd=(odd+1)%2; 
      fore=after;
  }
  if (odd==0){ 
          odd0=(byte)(fore>>4);
          odd1=((byte)(fore&0x0000000F))<<4;
      }else {
          odd1=odd1+(byte)(fore>>8);
          odd2=(byte)(fore);
          file2.put(odd0);
          file2.put(odd1);
          file2.put(odd2);  
      }
      odd=(odd+1)%2; 
}
   //还有一个FORE 
   if (odd==0){ 
          odd0=(byte)(fore>>4);
          odd1=((byte)(fore&0x0000000F))<<4;
      }else {
          odd1=odd1+(byte)(fore>>8);
          odd2=(byte)(fore);
          file2.put(odd0);
          file2.put(odd1);
          file2.put(odd2);  
      }
      odd=(odd+1)%2; 
   if  (odd==1){
        file2.put(odd0);
        file2.put(odd1);
  }
  file1.close();
  file2.close();
 // cout<<endl<<"字典长度："<<lz.len<<endl;
       }
  //解压缩的方法     
   void unlzwCompression(){
  ifstream file1;
  ofstream file2;
  Lzw lz;
  string path1, path2;
  printf("请输入要解压文件的位置及名称:");
  cin >> path1;
  printf("请输入解压后文件保存的位置及名称:");
  cin >> path2;
  file1.open(path1.c_str(),ios::binary);
  file2.open(path2.c_str(),ios::binary);
  char x;
  int times=0;
  int num1,num2;
  int fore,after;//前缀，后缀 
  int odd=0;//控制奇偶变量 
  byte odd0,odd1,odd2;
  int matchint;
  byte s[4097];
  int scount;
  int ii;
while (!file1.eof()){ 
  //初始化
  lz.unitLzw();
  fore=-1;
 if (odd==1){
       num1=num2;
  }else{
  file1.get(x);
  odd0=(byte)x;
  file1.get(x);
  odd1=(byte)x;
  file1.get(x);
  odd2=(byte)x;
  num1=(((int)odd0)<<4)+(((int)odd1)>>4);
  num2=(((int)(odd1&0x0F))<<8)+((int)odd2);
  }
  odd=(odd+1)%2;
  scount=0;
  matchint=-1;
  while ((!file1.eof())&&(lz.len<=4096)){
       
       //要在match中记录上次的地址，放入adress中 
           
   /*   while ((lz.match(s,scount)>=0)&&((!file1.eof()))){   
         matchint=lz.match(s,scount); 
         file1.get(x);
         s[scount++]=(byte)x;    
      };*/ 
      //若前值在不在字典中，则 
      if (num1>=lz.len){
         after=lz.gethead(fore);
         lz.add(fore,lz.gethead(fore));
         fore=num1;
      }else{
          after=num1;
          if (lz.check(fore,lz.gethead(after))<0)//当前串不在字典中
            lz.add(fore,lz.gethead(after)); 
          fore=after;
      }
     
      
       //输入第几个位置，取得对应的字典数据
          ii=fore;
          scount=0;
          printf("进");
           printf("到了：‘%d’",ii);
          while (ii>=256)
          {
            s[scount++]=lz.lzw[ii].data2;
            ii=lz.lzw[ii].data1;
            printf("到了：‘%d’",ii);
          }
           printf("出");
          s[scount++]=lz.lzw[ii].data2;  
      //输出 
      for (int i=scount-1;i>=0;i--){
         file2.put(s[i]);
         printf("%d ",(int)s[i]);
      }
      if (odd==1){
       num1=num2;
      }else{
         file1.get(x);
         odd0=(byte)x;
         file1.get(x);
         odd1=(byte)x;
         file1.get(x);
         odd2=(byte)x;
         num1=(((int)odd0)<<4)+(((int)odd1)>>4);
         num2=(((int)(odd1&0x0F))<<8)+((int)odd2);
      }
      odd=(odd+1)%2;
      //s进LZW
   /*   if (lz.match(s,scount)<0){
         lz.add(matchint,s[scount-1]);
      } //s进lzw's if ;*/
      //清空S  
  }
}
   
  file1.close();
  file2.close();
}
  //定义一个显示界面的方法 
void showUI(){
       int choice;
       printf("\n\n\n\n");
       printf(" \n\n\n \t\t\t    *******LZW压缩软件********\n\n\n");
       printf("             1.压缩文件\n\n");
       printf("             2.解压缩文件\n\n");
       printf("             0.退出软件\n\n");
       printf("              请选择(0-2):");
       scanf("%d",&choice);
       //判断输入是否合法 
       if(choice<1&&choice>2)
       choice=0;
	switch(choice)
       {
          case    1:    lzwCompression();break;
	      case    2:    unlzwCompression();break;
          case    0:    exit(0);
       }//end switch
}          

};

int main()
{
  LzwCompression lzwC;
  lzwC.showUI();
//  system("pause");
}


