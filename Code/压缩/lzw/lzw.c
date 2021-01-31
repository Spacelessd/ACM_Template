#include <stdio.h>
#include <stdlib.h>
//------------------------------------------------------------------------------

#include "lzw.h"
#include "hash.h"
#include "fileio.h"
#include "encode.h"
#include "decode.h"

//------------------------------------------------------------------------------
HANDLE h_file_sour;  
HANDLE h_file_dest;
HANDLE h_file;
/*CHAR*  file_name_in = "input.gif";
CHAR*  file_name_out= "encode.e";
CHAR*  file_name    = "decode.gif";*/

CHAR*  file_name_in = "input.txt";
CHAR*  file_name_out= "encode.txt";
CHAR*  file_name    = "decode.txt";
//------------------------------------------------------------------------------
int main(int argc, char *argv[]) 
{
    h_file_sour = file_handle(file_name_in);
    h_file_dest = file_handle(file_name_out);
    h_file     = file_handle(file_name);
    
    //encode first ,then decode
    printf("compress(0) or decompress(1)?:\n");
    char c;scanf("%c",&c);
	if (c=='0')encode(h_file_sour, h_file_dest);  
    if (c=='1')decode(h_file_dest,h_file); 
    
    CloseHandle(h_file_sour); 
    CloseHandle(h_file_dest);  
    CloseHandle(h_file);
    system("pause");
    return 0;      
}


