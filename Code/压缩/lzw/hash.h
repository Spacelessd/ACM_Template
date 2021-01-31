/*定义了压缩时所用的码表操作函数，为了快速查找使用了hash算法，还有处理hash冲突的函数*/
#ifndef __HASH_H__
#define __HASH_H__
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
//------------------------------------------------------------------------------
#define   DIV       TABLE_LEN
#define   HASHSTEP  13         // It should bigger than 0.
//------------------------------------------------------------------------------
WORD get_hash_index( PLZW_DATA lzw )
{
    DWORD tmp;
    WORD result;
    DWORD prefix;
    DWORD suffix;
    prefix = lzw->prefix;
    suffix = lzw->suffix;
    tmp = prefix<<8 | suffix;
    result = tmp % DIV;
    return result;
}
//------------------------------------------------------------------------------
WORD re_hash_index( WORD hash ) // If hash conflict occured we must recalculate
{                               // hash index .
    WORD result;
    result = hash + HASHSTEP;
    result = result % DIV;
    return result;
}
//------------------------------------------------------------------------------
BOOL in_table( PLZW_DATA lzw ) // To find whether current code is already in table.
{
    BOOL result;
    WORD hash;

    hash = get_hash_index( lzw );
    if( lzw->lp_code[ hash ] == 0xFFFF )
    {
        result = FALSE;    
    }
    else
    {
        if( lzw->lp_prefix[ hash ] == lzw->prefix &&
            lzw->lp_suffix[ hash ] == lzw->suffix )
        {
            result = TRUE;
        }
        else
        {
            result = FALSE;
            while( lzw->lp_code[ hash ] != 0xFFFF )
            {
                if( lzw->lp_prefix[ hash ] == lzw->prefix &&
                    lzw->lp_suffix[ hash ] == lzw->suffix )
                {
                        result = TRUE;
                        break;    
                }
                hash = re_hash_index( hash );
            }
        }
    }
    return result;
}
//------------------------------------------------------------------------------
WORD get_code( PLZW_DATA lzw )
{
    WORD hash;
    WORD code;
    hash = get_hash_index( lzw );
    if( lzw->lp_prefix[ hash ] == lzw->prefix &&
        lzw->lp_suffix[ hash ] == lzw->suffix )
    {
        code = lzw->lp_code[ hash ];
    }
    else
    {
        while( lzw->lp_prefix[ hash ] != lzw->prefix ||
               lzw->lp_suffix[ hash ] != lzw->suffix )
        {
                hash = re_hash_index( hash );    
        }
        code = lzw->lp_code[ hash ];
    }
    return code;
}
//------------------------------------------------------------------------------
VOID insert_table( PLZW_DATA lzw )
{

    WORD hash;
    hash = get_hash_index( lzw );
    if( lzw->lp_code[ hash ] == 0xFFFF )
    {
        lzw->lp_prefix[ hash ] = lzw->prefix;
        lzw->lp_suffix[ hash ] = lzw->suffix;
        lzw->lp_code[ hash ]   = lzw->code;
    }
    else
    {
        while( lzw->lp_code[ hash ] != 0xFFFF )
        {
                hash = re_hash_index( hash );    
        }
        lzw->lp_prefix[ hash ] = lzw->prefix;
        lzw->lp_suffix[ hash ] = lzw->suffix;
        lzw->lp_code[ hash ]   = lzw->code;
    }

}
//------------------------------------------------------------------------------


#endif
