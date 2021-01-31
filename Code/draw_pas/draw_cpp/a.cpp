#include "graphics.h"
int main() 
{ int gdrive=DETECT,gmode;/*定义两个参数:图形驱动和图形模式*/
  initgraph(&gdrive,&gmode,"");/*初始化图形模式,第三个参数填的是路径*/
  registerbgidriver(EGAVGA_driver);/*这个是用来注册图形模式来建立独立图形运行程序*/
  bar(x1,y1,x2,y2);/*画矩形*/
  circle(x1,y1,r);/*画圆*/
  getch();
  closegraph();/*关闭图形模式*/
}
