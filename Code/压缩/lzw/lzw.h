/* 定义了一些基本的数据结构，常量，还有变量的初始化等 */
#ifndef __LZW_H__
#define __LZW_H__
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <memory.h>
//------------------------------------------------------------------------------
#define LZW_BASE    0x102//  The code base
#define CODE_LEN       12   //  Max code length
#define TABLE_LEN      4099 // It must be prime number and bigger than 2^CODE_LEN=4096. 
       // Such as 5051 is also ok.
#define BUFFERSIZE     1024
//------------------------------------------------------------------------------
typedef struct
{
    HANDLE      h_sour;  // Source file handle.
    HANDLE      h_dest;  // Destination file handle.
    
    HANDLE      h_suffix; // Suffix table handle.
    HANDLE      h_prefix; // Prefix table handle.
    HANDLE      h_code;  // Code table handle.
    
    LPWORD      lp_prefix; // Prefix table head pointer.
    LPBYTE      lp_suffix; // Suffix table head pointer.
    LPWORD      lp_code; // Code table head pointer.

    WORD        code;
    WORD        prefix;
    BYTE        suffix;

    BYTE        cur_code_len; // Current code length.[ used in Dynamic-Code-Length mode ]

}LZW_DATA,*PLZW_DATA;


typedef struct
{
    WORD        top;
    WORD        index;

    LPBYTE      lp_buffer;
    HANDLE      h_buffer;
    
    BYTE        by_left;
    DWORD       dw_buffer;

    BOOL        end_flag;

}BUFFER_DATA,*PBUFFER_DATA;


typedef struct                  //Stack used in decode
{
WORD        index;
HANDLE      h_stack;
LPBYTE      lp_stack;

}STACK_DATA,*PSTACK_DATA;
//------------------------------------------------------------------------------
VOID stack_create( PSTACK_DATA stack )
{
stack->h_stack  = GlobalAlloc( GHND , TABLE_LEN*sizeof(BYTE) );
stack->lp_stack = GlobalLock( stack->h_stack );
stack->index = 0;
}
//------------------------------------------------------------------------------
VOID stack_destory( PSTACK_DATA stack )
{
GlobalUnlock( stack->h_stack );
    GlobalFree  ( stack->h_stack );
}
//------------------------------------------------------------------------------
VOID buffer_create( PBUFFER_DATA    buffer )
{
    buffer->h_buffer   = GlobalAlloc(  GHND,  BUFFERSIZE*sizeof(BYTE)  );
    buffer->lp_buffer  = GlobalLock( buffer->h_buffer );
    buffer->top        = 0;
    buffer->index      = 0;
    buffer->by_left    = 0;
    buffer->dw_buffer  = 0;
    buffer->end_flag   = FALSE;
}
//------------------------------------------------------------------------------
VOID buffer_destory( PBUFFER_DATA   buffer )
{
    GlobalUnlock( buffer->h_buffer );
    GlobalFree  ( buffer->h_buffer );
}
//------------------------------------------------------------------------------
VOID re_init_lzw( PLZW_DATA lzw )    //When code table reached its top it should
{                                    //be reinitialized.      
    memset( lzw->lp_code, 0xFFFF, TABLE_LEN*sizeof(WORD) );
    lzw->code          = LZW_BASE;
    lzw->cur_code_len  = 9;
}
//------------------------------------------------------------------------------
VOID lzw_create(PLZW_DATA    lzw,    HANDLE h_sour,    HANDLE h_dest)
{
WORD i;
    lzw->h_code        = GlobalAlloc( GHND, TABLE_LEN*sizeof(WORD) );
    lzw->h_prefix      = GlobalAlloc( GHND, TABLE_LEN*sizeof(WORD) );
    lzw->h_suffix      = GlobalAlloc( GHND, TABLE_LEN*sizeof(BYTE) );
    lzw->lp_code       = GlobalLock( lzw->h_code   );
    lzw->lp_prefix     = GlobalLock( lzw->h_prefix );
    lzw->lp_suffix     = GlobalLock( lzw->h_suffix );
    lzw->code          = LZW_BASE;
    lzw->cur_code_len  = 9;
    lzw->h_sour        = h_sour;
    lzw->h_dest        = h_dest;
    memset( lzw->lp_code, 0xFFFF, TABLE_LEN*sizeof(WORD) );

}
//------------------------------------------------------------------------------
VOID lzw_destory(PLZW_DATA    lzw)
{  
    GlobalUnlock( lzw->h_code   );
    GlobalUnlock( lzw->h_prefix );
    GlobalUnlock( lzw->h_suffix );

GlobalFree( lzw->h_code  );
    GlobalFree( lzw->h_prefix );
    GlobalFree( lzw->h_suffix );    
}
//------------------------------------------------------------------------------
#endif
