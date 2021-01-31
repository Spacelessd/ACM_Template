// Arithmetic_Coding.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream >
using  namespace  std; 

#define     M  100
#define     N  4
#define     DELTA (0.000000000001)

#define		NUM 2
#define		ZERO 0.000001

//函数interger和decimal作用是将十进制转化为二进制
void integer(int n)
{
	if(n>0)
	{
		integer(n/NUM);
		//cout<<n%NUM;
		printf("%d",n%NUM);
	}
}

void decimal(double m)
{
	if(m>ZERO)
	{
		m=m*NUM;
		printf("%d",(long)m);
		decimal(m-(long)m);
	}
}

class CAC
{
    int m_iCount,m_iLength, m_iL;//信源数量，输入信号长度
    char m_cSymbol[N];
    long double m_fProb[N];
    char m_cCode[M];
    long double m_fHigh,m_fLow;//编码时计算概率的上下限中间变量

public:
    CAC();//创建结构体
    void encode();
    void decode();
    ~CAC(){}//析出结构体
};

CAC::CAC()
{
    m_fHigh = 0;
    m_fLow = 0;
    
	//设定四个信源符号a,b,c,d
    m_iCount = 4;
    m_cSymbol[0] = 'a';
    m_cSymbol[1] = 'b';
    m_cSymbol[2] = 'c';
    m_cSymbol[3] = 'd';
   
	//设定信源符号概率
    m_fProb[0] = 0.1;
    m_fProb[1] = 0.2;
    m_fProb[2] = 0.4;
    m_fProb[3] = 0.3;
    
	//设定输入的码元为acbdbcab,共8个字符，在此对其进行编码译码
    m_iLength = 8;
    m_cCode[0] = 'a';
    m_cCode[1] = 'c';
    m_cCode[2] = 'b';
    m_cCode[3] = 'd';
    m_cCode[4] = 'b';
    m_cCode[5] = 'c';
    m_cCode[6] = 'a';
    m_cCode[7] = 'b';
}

void CAC::encode()
{
    int  i,j=0;
    long double p = 1.0, d;

    cout << "begin to encode..." <<endl;

    //找到第一个码元是哪个字符
    for(i = 0; i < m_iCount; i++)
    {
        if(m_cCode[0] == m_cSymbol[i])
            break;
    }

    //找到第一个字符的概率区间下限
    while(j < i)
    {
        m_fLow += m_fProb[j++];
    }

    d = m_fProb[j];//概率区间长度赋值给d

    m_fHigh = m_fLow + d;//设定第一个字符概率区间上限
    
    //算术码具体算法如下：
    for(i = 1; i < m_iLength; i++)
    {
        for(j = 0; j < m_iCount; j++)
        {
            if(m_cCode[i] == m_cSymbol[j])
            {
                if(j == 0)//若信号为规定码元的第一个，相应的概率上下限及概率区间如下
                {
                    m_fHigh = m_fLow + m_fProb[j]*d;
                    d *= m_fProb[j];
                }
                else //若信号不是规定码元的第一个，其相应的概率上下限算法如下
                {
                    double  chance_l=0.0;
                    for(int k = 0; k <= j-1; k++)
                        chance_l += m_fProb[k];
                    m_fLow = m_fLow + d*chance_l;
                    m_fHigh = m_fLow + d*(chance_l + m_fProb[j]);
                    d *= m_fProb[j];
                }
            }
            else
                continue;
        }
    }
    
#if 1
	//计算所出现信号的概率值，并输出
    for (i = 0; i < m_iLength; i++)
    {
        for(j = 0; j < m_iCount; j++)
        {
            if (m_cCode[i] == m_cSymbol[j])
            {
                p *= m_fProb[j];
            }
        }
    }
#endif
   
	//将十进制小数转化为二进制小数输出,即所得编码
	long n;
	n=(long)m_fLow;
	integer(n);
	decimal(m_fLow-n);
	cout<<"\n";

    //输出信号概率所处概率区间下限值
    cout<<"Arithmetic coding: "<<m_fLow<<endl;
	cout<<"\n";

}

//取上面所得概率下限值作解码

void CAC::decode()
{
    int i;
    long double dd, dc;

    cout << "begin to decode..." <<endl;

    dd = m_fLow;

    while(1)
    {
        long double xlow = 0;

        if (dd < DELTA)
            break;

		//找到概率值所在相应码元的概率区间
        dc = 0;
        for (i = 0; i < N; i++)
        {
            dc += m_fProb[i];
            if (dd < dc)
                break;
            xlow += m_fProb[i];
        }
		//依次寻找下一个字符所在概率区间
        cout << m_cSymbol[i];
        dd -= xlow;
        dd /= m_fProb[i];
    }
}

int  main()
{  
    CAC  a;
    a.encode();
    a.decode();

    return  0;
}