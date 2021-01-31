#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
int a[N],b[N];
/*void *Memcpy(void *dest, const void *src, size_t count)
{
 char *tmp = (char*)dest;
 const char *s = (char*)src;
 while (count--)*tmp++ = *s++ ;
 return dest;
}*/
void  *Memcpy(void *pvTo, const void *pvFrom, size_t size) {

       //assert((pvTo != NULL) && (pvFrom != NULL));      // 使用断言

       char *pbTo = (char *) pvTo;         // 防止改变pvTo的地址

       char *pbFrom = (char *) pvFrom; // 防止改变pvFrom的地址

       while(size -- > 0 )

              *pbTo = *pbFrom ;

       return pvTo;

}

/*void * __cdecl memcpy1 (
        void * dst,
        const void * src,
        size_t count
        )
{
        void * ret = dst;

        while (count--) {
                *(unsigned long long *)dst = *(unsigned long long *)src;
                ++dst;
                ++src;
        }

        return(ret);
}*/
typedef struct BYTE_0
{
        char a ;
}
Byte_0 ;

typedef struct BYTE_1
{
        char a[10] ;
}
Byte_1 ;

typedef struct BYTE_2
{
        char a[100] ;
}
Byte_2 ;

typedef struct BYTE_3
{
        char a[1000] ;
}
Byte_3 ;

typedef struct BYTE_4
{
        char a[10000] ;
}
Byte_4 ;

typedef struct BYTE_5
{
        char a[100000] ;
}
Byte_5 ;

typedef struct BYTE_6
{
        char a[1000000] ;
}
Byte_6 ;

typedef struct BYTE_7
{
        char a[10000000] ;
}
Byte_7 ;

typedef struct BYTE_8
{
        char a[100000000] ;
}
Byte_8 ;

typedef struct BYTE_9
{
        char a[1000000000] ;
}
Byte_9 ;


void
copy_0( void **dtp, void **src )
{
        **(Byte_0 **)dtp = **(Byte_0 **)src ;
        *(Byte_0 **)dtp += 1 ;
        *(Byte_0 **)src += 1 ;
}

void
copy_1( void **dtp, void **src )
{
        **(Byte_1 **)dtp = **(Byte_1 **)src ;
        *(Byte_1 **)dtp += 1 ;
        *(Byte_1 **)src += 1 ;
}

void
copy_2( void **dtp, void **src )
{
        **(Byte_2 **)dtp = **(Byte_2 **)src ;
        *(Byte_2 **)dtp += 1 ;
        *(Byte_2 **)src += 1 ;
}

void
copy_3( void **dtp, void **src )
{
        **(Byte_3 **)dtp = **(Byte_3 **)src ;
        *(Byte_3 **)dtp += 1 ;
        *(Byte_3 **)src += 1 ;
}

void
copy_4( void **dtp, void **src )
{
        **(Byte_4 **)dtp = **(Byte_4 **)src ;
        *(Byte_4 **)dtp += 1 ;
        *(Byte_4 **)src += 1 ;
}

void
copy_5( void **dtp, void **src )
{
        **(Byte_5 **)dtp = **(Byte_5 **)src ;
        *(Byte_5 **)dtp += 1 ;
        *(Byte_5 **)src += 1 ;
}

void
copy_6( void **dtp, void **src )
{
        **(Byte_6 **)dtp = **(Byte_6 **)src ;
        *(Byte_6 **)dtp += 1 ;
        *(Byte_6 **)src += 1 ;
}

void
copy_7( void **dtp, void **src )
{
        **(Byte_7 **)dtp = **(Byte_7 **)src ;
        *(Byte_7 **)dtp += 1 ;
        *(Byte_7 **)src += 1 ;
}

void
copy_8( void **dtp, void **src )
{
        **(Byte_8 **)dtp = **(Byte_8 **)src ;
        *(Byte_8 **)dtp += 1 ;
        *(Byte_8 **)src += 1 ;
}

void
copy_9( void **dtp, void **src )
{
        **(Byte_9 **)dtp = **(Byte_9 **)src ;
        *(Byte_9 **)dtp += 1 ;
        *(Byte_9 **)src += 1 ;
}


void
depart_number( int *dtp, int size )
{
        int i ;
        
        for( i = 0 ; i < 10 ; i++ )
        {
                if( i == 9 )
                        dtp[i] = size ;
                else
                {
                        dtp[i] = size % 10 ;
                        size /= 10 ;
                } 
        }
}

void
mem_copy( void *dtp, void *src , size_t size )
{
        void *tmp_dtp = dtp ;
        void *tmp_src = src ;
        int i ;
        int j ;
        void (*copy_fun[10])( void **dtp, void **src ) = {copy_0, copy_1, copy_2, copy_3, copy_4, copy_5, copy_6, copy_7, copy_8, copy_9 } ;
        
        int size_val[10] ;
        
        depart_number( size_val, size ) ;

        for( i = 0 ; i < 10 ; i++ )
        {
                for( j = 0 ; j < size_val[i] ; j++ )
                {
                        copy_fun[i]( (void **)&tmp_dtp, (void **)&tmp_src ) ;
                }
        }
}
struct zzy{
	int a[10000];
};
void memcopy(int *a,int *b,size_t size){
	size/=4;
	zzy *A=(zzy*)a,*B=(zzy*)b;
	size/=10000;
	while (size--)*A++=*B++;
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	int t1;
	t1=clock();
	b[1]=1;
	for (int i=1;i<=5000;++i)
		memcopy(a,b,sizeof(b));
	printf("a=%d\n",a[1]);
	printf("time=%d\n",clock()-t1);
	
	t1=clock();
	for (int i=1;i<=5000;++i){
		if (i%40==0)for (int i=0;i<N;++i)a[i]=rand();
		memcpy(a,b,sizeof(b));
	}
	printf("time=%d\n",clock()-t1);
	
	t1=clock();
	b[1]=1;
	for (int i=1;i<=5000;++i)
		mem_copy(a,b,sizeof(b));
	printf("a=%d\n",a[1]);
	printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
	return 0;
}


