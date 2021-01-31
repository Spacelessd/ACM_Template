/*解压函数主函数*/

#ifndef __DECODE_H__
#define __DECODE_H__
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
//------------------------------------------------------------------------------
VOID out_code( WORD code ,PBUFFER_DATA buffer,PLZW_DATA lzw,PSTACK_DATA stack)
{
WORD tmp;
if( code < 0x100 )
{
  stack->lp_stack[ stack->index++ ] = code;
}
else
{
   stack->lp_stack[ stack->index++ ] = lzw->lp_suffix[ code ];
   tmp = lzw->lp_prefix[ code ];
   while( tmp > 0x100 )
   {
    stack->lp_stack[ stack->index++ ] = lzw->lp_suffix[ tmp ];
    tmp = lzw->lp_prefix[ tmp ];
   }
   stack->lp_stack[ stack->index++ ] = (BYTE)tmp;

}


while( stack->index )
{
  if( buffer->index == BUFFERSIZE )
  {
   empty_buffer(lzw,buffer);
  }
  buffer->lp_buffer[ buffer->index++ ] = stack->lp_stack[ --stack->index ] ;
}
}
//------------------------------------------------------------------------------
VOID insert_2_table(PLZW_DATA lzw )
{

lzw->lp_code[ lzw->code ]   = lzw->code;
lzw->lp_prefix[ lzw->code ] = lzw->prefix;
lzw->lp_suffix[ lzw->code ] = lzw->suffix;
lzw->code++;

if( lzw->code == ((WORD)1<<lzw->cur_code_len)-1 )
{
  lzw->cur_code_len++;
  if( lzw->cur_code_len == CODE_LEN+1 )
      lzw->cur_code_len = 9;
}
if(lzw->code >= 1<<CODE_LEN )
{
  re_init_lzw(lzw);
}

}
//------------------------------------------------------------------------------
WORD get_next_code( PBUFFER_DATA buffer , PLZW_DATA lzw )
{

BYTE next;
WORD code;
while( buffer->by_left < lzw->cur_code_len )
{
  if( buffer->index == BUFFERSIZE )
  {
   load_buffer( lzw->h_sour, buffer );
  }
  next = buffer->lp_buffer[ buffer->index++ ];
  buffer->dw_buffer |= (DWORD)next << (24-buffer->by_left);
  buffer->by_left   += 8;
}
code = buffer->dw_buffer >> ( 32 - lzw->cur_code_len );
buffer->dw_buffer <<= lzw->cur_code_len;
buffer->by_left    -= lzw->cur_code_len;

return code;
}
//------------------------------------------------------------------------------
VOID do_decode( PBUFFER_DATA in, PBUFFER_DATA out, PLZW_DATA lzw, PSTACK_DATA stack)
{
WORD code;
WORD tmp;
while( in->index != in->top  )
{
  code = get_next_code( in ,lzw );

  if( code < 0x100 )
  {
   // code already in table 
   // then simply output the code
   lzw->suffix = (BYTE)code;
  }
  else 
  {
   if( code < lzw->code  )
   {
    // code also in table 
    // then output code chain
    
    tmp = lzw->lp_prefix[ code ];
    while( tmp > 0x100 )
    {
     tmp = lzw->lp_prefix[ tmp ];
    }
    lzw->suffix = (BYTE)tmp;
   }
   else
   {
    // code == lzw->code
    // code not in table
    // add code into table
    // and out put code 
    tmp = lzw->prefix;
    while( tmp > 0x100 )
    {
     tmp = lzw->lp_prefix[ tmp ];
    }
    lzw->suffix = (BYTE)tmp;
   }
  }
  insert_2_table( lzw );
  out_code(code,out,lzw,stack);

  lzw->prefix = code;

}

}
//------------------------------------------------------------------------------
VOID decode( HANDLE h_sour, HANDLE h_dest )
{
    LZW_DATA        lzw;
    BUFFER_DATA     in ;
    BUFFER_DATA     out;
STACK_DATA      stack;
BOOL   first_run;

first_run = TRUE;


    lzw_create( &lzw ,h_sour,h_dest );
    buffer_create( &in );
    buffer_create( &out );
stack_create(&stack );

    while( load_buffer( h_sour, &in ) )
    {
  if( first_run )
  {
   lzw.prefix = get_next_code( &in, &lzw );
   lzw.suffix = lzw.prefix;
   out_code(lzw.prefix, &out, &lzw , &stack);
   first_run = FALSE;
  }
        do_decode(&in , &out, &lzw, &stack);
    }

    empty_buffer( &lzw,&out);

    lzw_destory( &lzw );
    buffer_destory( &in );
    buffer_destory( &out );
stack_destory( &stack);
}

#endif
