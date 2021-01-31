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
CHAR*  file_name_in = "1.txt";
CHAR*  file_name_out= "2.txt";
CHAR*  file_name    = "30.txt";


//------------------------------------------------------------------------------
int main(int argc, char *argv[]) 
{
    h_file_sour = file_handle(file_name_in);
    h_file_dest = file_handle(file_name_out);
    h_file      = file_handle(file_name);


    encode(h_file_sour, h_file_dest);
    decode(h_file_dest,h_file);


    CloseHandle(h_file_sour); 
    CloseHandle(h_file_dest);  
    CloseHandle(h_file);
    printf("end.\n");
  return 0;      
}


