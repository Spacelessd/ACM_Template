/*定义了一些文件操作*/
#ifndef __FILEIO_H__
#define __FILEIO_H__
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
//------------------------------------------------------------------------------
HANDLE  file_handle(CHAR* file_name)
{
    HANDLE h_file;
    h_file = CreateFile(file_name,
                       GENERIC_READ|GENERIC_WRITE,
                       FILE_SHARE_READ|FILE_SHARE_WRITE,
                       NULL,
                       OPEN_ALWAYS,
                       0,
                       NULL
                       );
    return h_file;
}
//------------------------------------------------------------------------------
WORD load_buffer(HANDLE h_sour, PBUFFER_DATA buffer)  // Load file to buffer
{
    DWORD ret;
    ReadFile(h_sour,buffer->lp_buffer,BUFFERSIZE,&ret,NULL);
    buffer->index = 0;
    buffer->top = (WORD)ret;
    return (WORD)ret;
}
//------------------------------------------------------------------------------
WORD empty_buffer( PLZW_DATA lzw, PBUFFER_DATA buffer)// Output buffer to file
{
   
    DWORD ret;
    if(buffer->end_flag) // The flag mark the end of decode
{
  if( buffer->by_left )
  {
   buffer->lp_buffer[ buffer->index++ ] = (BYTE)( buffer->dw_buffer >> 32-buffer->by_left )<<(8-buffer->by_left);
  }
}
WriteFile(lzw->h_dest, buffer->lp_buffer,buffer->index,&ret,NULL);
    buffer->index = 0;
    buffer->top = ret;
    return (WORD)ret;
}
//------------------------------------------------------------------------------
#endif
