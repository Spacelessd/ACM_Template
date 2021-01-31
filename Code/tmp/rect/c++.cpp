/*
ID:hqztrue1
PROB:rect1
LANG:C++
*/
//by yali wx  非递归矩形切割，全部0MS，暴爽。
/*
USER: wang x [wx539181]
TASK: rect1
LANG: C++
 
Compiling...
Compile: OK
 
Executing...
   Test 1: TEST OK [0.000 secs, 3052 KB]
   Test 2: TEST OK [0.000 secs, 3052 KB]
   Test 3: TEST OK [0.000 secs, 3052 KB]
   Test 4: TEST OK [0.000 secs, 3052 KB]
   Test 5: TEST OK [0.000 secs, 3052 KB]
   Test 6: TEST OK [0.000 secs, 3052 KB]
   Test 7: TEST OK [0.000 secs, 3052 KB]
   Test 8: TEST OK [0.000 secs, 3052 KB]
   Test 9: TEST OK [0.000 secs, 3052 KB]
   Test 10: TEST OK [0.000 secs, 3052 KB]
   Test 11: TEST OK [0.000 secs, 3052 KB]
 
All tests OK
*/
#include<stdio.h>
#include<stdlib.h>
int ans[2550],A,B,n;
struct pp
{
       int x1,x2,y1,y2,color;
}z[1010];
int max(int x,int y)
{
if(x>y)return x;
return y;
}
int min(int x,int y)
{
    if(x>y)return y;
    return x;
}
void sou(int xx1,int yy1,int xx2,int yy2,int co,int num)
{
     int i1,j2,k,i2,j1;
     if(num==n+1)
     {
      ans[co]+=(xx1-xx2+1)*(yy2-yy1+1); /*没被遮盖住，累计结果*/
      return ;
     }
     if(xx1<z[num].x2||xx2>z[num].x1||yy1>z[num].y2||yy2<z[num].y1)
     {sou(xx1,yy1,xx2,yy2,co,num+1);return;} /*不重合*/
 
      if(xx1>z[num].x1)
      sou(xx1,yy1,z[num].x1+1,yy2,co,num+1);
      if(xx2<z[num].x2)
      sou(z[num].x2-1,yy1,xx2,yy2,co,num+1);      /*上下两长矩形*/
 
      if(yy1<z[num].y1)
      sou(min(xx1,z[num].x1),yy1,max(xx2,z[num].x2),z[num].y1-1,co,num+1);   
      if(yy2>z[num].y2)
      sou(min(xx1,z[num].x1),z[num].y2+1,max(xx2,z[num].x2),yy2,co,num+1);      /*中间（左右）两短矩形*/
}
int main()
{
    FILE *fin,*fout;
    fin=fopen("rect1.in","r");
    fout=fopen("rect1.out","w");
    int i,j,k;
    fscanf(fin,"%d%d%d",&B,&A,&n);
    for(i=1;i<=n;i++)
    {
    fscanf(fin,"%d%d%d%d%d",&z[i].y1,&z[i].x1,&z[i].y2,&z[i].x2,&z[i].color);
    z[i].x1=A-z[i].x1-1;
    z[i].x2=A-z[i].x2-1;/*转换成标准矩阵*/
    z[i].y1++;z[i].x2++;/*!将左下角（右上角）第一个有颜色的点作为端点，便于写!*/
    }
 
    for(i=1;i<=n;i++)
    sou(z[i].x1,z[i].y1,z[i].x2,z[i].y2,z[i].color,i+1);
    ans[1]=A*B;
    for(i=2;i<=2500;i++)ans[1]-=ans[i];
    for(i=1;i<=2500;i++)
    if(ans[i]>0)fprintf(fout,"%d %d\n",i,ans[i]);
    return 0;
}