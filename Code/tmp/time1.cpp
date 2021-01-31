#include <time.h>
#include <stdio.h>
#include<cstdlib>
clock_t start,finish;
int a,b;
int main()
{
   start=clock();
   a=10;b=500000000;
    __asm
    (
        "mov _b,%ecx;"   //实验次数
"testBegin:;"
        "mov _a,%eax;"
        "mov _a,%ebx;"
        "cdq;"
        //"add _a,%edx;"
        "dec %ecx;"
        "jz testEnd;"
        "jmp testBegin;"
"testEnd:;"
    );
    finish=clock();
    printf("%.3lf\n",double(finish-start)/CLOCKS_PER_SEC); 
    system("pause");
    return 0;
}
