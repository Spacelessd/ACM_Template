/*Ñ¹Ëõ³ÌÐòÖ÷º¯Êý*/
#ifndef __ENCODE_H__
#define __ENCODE_H__
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//------------------------------------------------------------------------------
VOID output_code( DWORD code ,PBUFFER_DATA out, PLZW_DATA lzw)
{
    out->dw_buffer |= code << ( 32 - out->by_left - lzw->cur_code_len );
    out->by_left += lzw->cur_code_len;

    while( out->by_left >= 8 )
    {
        if( out->index == BUFFERSIZE )
        {
            empty_buffer( lzw,out);
        }

        out->lp_buffer[ out->index++ ] = (BYTE)( out->dw_buffer >> 24 );
        out->dw_buffer <<= 8;
        out->by_left -= 8;
    }
}
//------------------------------------------------------------------------------
VOID do_encode( PBUFFER_DATA in, PBUFFER_DATA out, PLZW_DATA lzw)
{
    WORD prefix;
    while( in->index != in->top )
    {
        if( !in_table(lzw) )
        {
                // current code not in code table
                // then add it to table and output prefix


                insert_table(lzw);
                prefix = lzw->suffix;
                output_code( lzw->prefix ,out ,lzw );
                lzw->code++;

                if( lzw->code == (WORD)1<< lzw->cur_code_len )
                {
                    // code reached current code top(1<<cur_code_len)
                    // then current code length add one
     lzw->cur_code_len++;
     if( lzw->cur_code_len == CODE_LEN + 1 )
     {
      re_init_lzw( lzw );
     }

                }
        }
        else
        {
                // current code already in code table 
                // then output nothing
                prefix = get_code(lzw);

        }
        lzw->prefix = prefix;
        lzw->suffix = in->lp_buffer[ in->index++ ];
    }
}

//------------------------------------------------------------------------------
VOID encode(HANDLE h_sour,HANDLE h_dest)
{
    LZW_DATA        lzw;
    BUFFER_DATA     in ;
    BUFFER_DATA     out;
    
    BOOL first_run = TRUE;

    lzw_create( &lzw ,h_sour,h_dest );
    buffer_create( &in );
    buffer_create( &out );


    while( load_buffer( h_sour, &in ) )
    {
        if( first_run )
        {// File length should be considered  but here we simply 
         // believe file length bigger than 2 bytes.
                lzw.prefix = in.lp_buffer[ in.index++ ];
                lzw.suffix = in.lp_buffer[ in.index++ ];
                first_run = FALSE;
        }
        do_encode(&in , &out, &lzw);
    }
    
output_code(lzw.prefix, &out , &lzw);
output_code(lzw.suffix, &out , &lzw);
out.end_flag = TRUE;
    empty_buffer( &lzw,&out);

    lzw_destory( &lzw );
    buffer_destory( &in );
    buffer_destory( &out );
}

//------------------------------------------------------------------------------
#endif
