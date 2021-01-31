//模板来源：http://www.ahalei.com/?p=1055  由hahahuo撰写//这是NOI 2011 Day1 T2 智能车比赛的SJ代码//分别从标准输出和选手输出读入一个浮点数并判断误差是否在允许范围内#include<stdio.h>#include<stdlib.h>#include<string.h>#include<time.h>#include<math.h>#include<iostream>#include<algorithm>using namespace std;FILE *fscore,*freport,*fstd,*fin,*fout;bool Judge(){	double x,y,dif;	fscanf(fstd,"%lf",&x);	fscanf(fout,"%lf",&y);	dif=(x>y)?(x-y):(y-x);	fprintf(freport,"Std:%.10lf\nYour Ans:%.10lf\nDiffer:%.10lf\n",x,y,dif);	return dif<=0.000001;}int main(int argc,char *argv[]){	fscore=fopen("score.log","w");//打开得分文件	freport=fopen("report.log","w");//打开报告文件	fstd=fopen(argv[2],"r");//打开测试点标准输出文件	int score=atoi(argv[1]);//取得测试点的分数	fin=fopen("car.in","r");//打开测试点标准输入文件	fout=fopen("car.out","r");//打开用户的数据输出文件	if (!fout)	{		fprintf(fscore,"%d",0);//返回0分		fprintf(freport,"no output");//报告Judge结果为no output	}	else if (Judge())//Judge后结果为真	{		fprintf(fscore,"%d",score);//返回满分		fprintf(freport,"right");//报告Judge结果为right	}	else	{		fprintf(fscore,"%d",0);//返回0分		fprintf(freport,"wrong");//报告Judge结果为wrong	}	fclose(fscore);//关闭得分文件	fclose(freport);//关闭报告文件	return 0;}