#include <cstdio>
#include <algorithm>
using namespace std;
struct md5er{
	int A,B,C,D;
	long long leng;
	md5er(){
		A=0x67452301;
		B=0xefcdab89;
		C=0x98badcfe;
		D=0x10325476;
		leng=0;
	}
	void update(int *dat){
		//puts("update");
		//for (int i=0;i<16;i++)printf("%08x",dat[i]);
		//puts("");
		unsigned int tt;
#define F(x,y,z) ((x&y)|((~x)&z))
#define G(x,y,z) ((x&z)|(y&(~z)))
#define H(x,y,z) (x^y^z)
#define I(x,y,z) (y^(x|(~z)))
#define FF(a,b,c,d,m,s,t)\
	tt=(a+(F(b,c,d)+m+t));\
	a=b+((tt<<s)|(tt>>(32-s)));
#define GG(a,b,c,d,m,s,t)\
	tt=(a+(G(b,c,d)+m+t));\
	a=b+((tt<<s)|(tt>>(32-s)));
#define HH(a,b,c,d,m,s,t)\
	tt=(a+(H(b,c,d)+m+t));\
	a=b+((tt<<s)|(tt>>(32-s)));
#define II(a,b,c,d,m,s,t)\
	tt=(a+(I(b,c,d)+m+t));\
	a=b+((tt<<s)|(tt>>(32-s)));
		int a=A,b=B,c=C,d=D;
		FF(a,b,c,d,dat[0] , 7,0xd76aa478);
		FF(d,a,b,c,dat[1] ,12,0xe8c7b756);
		FF(c,d,a,b,dat[2] ,17,0x242070db);
		FF(b,c,d,a,dat[3] ,22,0xc1bdceee);
		FF(a,b,c,d,dat[4] , 7,0xf57c0faf);
		FF(d,a,b,c,dat[5] ,12,0x4787c62a);
		FF(c,d,a,b,dat[6] ,17,0xa8304613);
		FF(b,c,d,a,dat[7] ,22,0xfd469501);
		FF(a,b,c,d,dat[8] , 7,0x698098d8);
		FF(d,a,b,c,dat[9] ,12,0x8b44f7af);
		FF(c,d,a,b,dat[10],17,0xffff5bb1);
		FF(b,c,d,a,dat[11],22,0x895cd7be);
		FF(a,b,c,d,dat[12], 7,0x6b901122);
		FF(d,a,b,c,dat[13],12,0xfd987193);
		FF(c,d,a,b,dat[14],17,0xa679438e);
		FF(b,c,d,a,dat[15],22,0x49b40821);
		GG(a,b,c,d,dat[1] , 5,0xf61e2562);
		GG(d,a,b,c,dat[6] , 9,0xc040b340);
		GG(c,d,a,b,dat[11],14,0x265e5a51);
		GG(b,c,d,a,dat[0] ,20,0xe9b6c7aa);
		GG(a,b,c,d,dat[5] , 5,0xd62f105d);
		GG(d,a,b,c,dat[10], 9,0x02441453);
		GG(c,d,a,b,dat[15],14,0xd8a1e681);
		GG(b,c,d,a,dat[4] ,20,0xe7d3fbc8);
		GG(a,b,c,d,dat[9] , 5,0x21e1cde6);
		GG(d,a,b,c,dat[14], 9,0xc33707d6);
		GG(c,d,a,b,dat[3] ,14,0xf4d50d87);
		GG(b,c,d,a,dat[8] ,20,0x455a14ed);
		GG(a,b,c,d,dat[13], 5,0xa9e3e905);
		GG(d,a,b,c,dat[2] , 9,0xfcefa3f8);
		GG(c,d,a,b,dat[7] ,14,0x676f02d9);
		GG(b,c,d,a,dat[12],20,0x8d2a4c8a);
		HH(a,b,c,d,dat[5] , 4,0xfffa3942);
		HH(d,a,b,c,dat[8] ,11,0x8771f681);
		HH(c,d,a,b,dat[11],16,0x6d9d6122);
		HH(b,c,d,a,dat[14],23,0xfde5380c);
		HH(a,b,c,d,dat[1] , 4,0xa4beea44);
		HH(d,a,b,c,dat[4] ,11,0x4bdecfa9);
		HH(c,d,a,b,dat[7] ,16,0xf6bb4b60);
		HH(b,c,d,a,dat[10],23,0xbebfbc70);
		HH(a,b,c,d,dat[13], 4,0x289b7ec6);
		HH(d,a,b,c,dat[0] ,11,0xeaa127fa);
		HH(c,d,a,b,dat[3] ,16,0xd4ef3085);
		HH(b,c,d,a,dat[6] ,23,0x04881d05);
		HH(a,b,c,d,dat[9] , 4,0xd9d4d039);
		HH(d,a,b,c,dat[12],11,0xe6db99e5);
		HH(c,d,a,b,dat[15],16,0x1fa27cf8);
		HH(b,c,d,a,dat[2] ,23,0xc4ac5665);
		II(a,b,c,d,dat[0] , 6,0xf4292244);
		II(d,a,b,c,dat[7] ,10,0x432aff97);
		II(c,d,a,b,dat[14],15,0xab9423a7);
		II(b,c,d,a,dat[5] ,21,0xfc93a039);
		II(a,b,c,d,dat[12], 6,0x655b59c3);
		II(d,a,b,c,dat[3] ,10,0x8f0ccc92);
		II(c,d,a,b,dat[10],15,0xffeff47d);
		II(b,c,d,a,dat[1] ,21,0x85845dd1);
		II(a,b,c,d,dat[8] , 6,0x6fa87e4f);
		II(d,a,b,c,dat[15],10,0xfe2ce6e0);
		II(c,d,a,b,dat[6] ,15,0xa3014314);
		II(b,c,d,a,dat[13],21,0x4e0811a1);
		II(a,b,c,d,dat[4] , 6,0xf7537e82);
		II(d,a,b,c,dat[11],10,0xbd3af235);
		II(c,d,a,b,dat[2] ,15,0x2ad7d2bb);
		II(b,c,d,a,dat[9] ,21,0xeb86d391);
		A+=a;
		B+=b;
		C+=c;
		D+=d;
#undef F
#undef G
#undef H
#undef I
#undef FF
#undef GG
#undef HH
#undef II
	}
	char buf[64];
	void refresh(){
		//puts("refresh");
		//for (int i=0;i<64;i++)printf("%02x",(unsigned int)(unsigned char)buf[i]);
		//puts("");
		int bufx[16];
		for (int i=0;i<16;i++)bufx[i]=0;
		for (int i=0;i<64;i++)
			bufx[i>>2]|=((int)(unsigned char)(buf[i])<<((i&3)<<3));
		update(bufx);
	}
	void add(char *dat,int l){
		if (!l)return;
		int o=(leng>>3)&63;
		leng+=(l<<3);
		for (int i=0;i<l;i++){
			buf[o++]=dat[i];
			if (o==64){
				refresh();
				o=0;
			}
		}
	}
	void result(char *r){
		int o=(leng>>3)&63;
		int a=A,b=B,c=C,d=D;
		if (o<=56){
			buf[o]=128;
			for (int i=o+1;i<56;i++)buf[i]=0;
			for (int i=0;i<8;i++)
				buf[56+i]=leng>>(i<<3);
			refresh();
		}else{
			buf[o]=128;
			for (int i=o+1;i<64;i++)buf[i]=0;
			refresh();
			int bufx[16];
			for (int i=0;i<14;i++)bufx[i]=0;
			bufx[14]=leng;
			bufx[15]=leng>>32;
			update(bufx);
		}
		int t[4];
		t[0]=A;t[1]=B;t[2]=C;t[3]=D;
		for (int i=0;i<16;i++)
			r[i]=t[i>>2]>>((i&3)<<3);
		A=a;B=b;C=c;D=d;
	}
	void goback(int a){
		leng-=(a<<3);
	}
};
int main()
{
	md5er md5;
	char b[16];
	md5.add("1",1);
	md5.goback(3);
	md5.result(b);
	for (int i=0;i<16;i++)
		printf("%02x",(int)(unsigned char)b[i]);
	puts("");
	system("pause");
	return 0;
}


