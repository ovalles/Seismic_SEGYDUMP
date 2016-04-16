// Display a integer 2bytes Trace Header values from SEGY-File
// By AJ Ovalles, 2016
// Made in Venezuela

#include <stdio.h>
#include "endian.h"

char *filename = NULL;
int strtrc = 1;  // First Trace in file
char *str_inic_byte_pos;
char *str_maxtrc = NULL;
FILE *fp;


int main(int argc,char* argv[]) {

  if (argv[1] == NULL){
    printf("Syntax: >> Extract_ShortHeader filename maxTraceNumber 3600+ByteToExtract\n");
  }
  else{

  filename = argv[1];
  printf("%s\n", filename);

  str_maxtrc = argv[2];
  int maxtrc = atoi(str_maxtrc);
  printf("Numero de trazas %d\n", maxtrc);

  str_inic_byte_pos= argv[3];
  int inic_byte_pos = atoi(str_inic_byte_pos);
  printf("Byte to Override %d\n", inic_byte_pos );
 
  short nm;
  fp = fopen(filename,"rb");  // r for read, b for binary
  fseek( fp, 3220, SEEK_SET );
  fread(&nm,sizeof(nm),1,fp); // read 2 bytes to our buffer
  nm = be16toh(nm); // Ajusta el endiann del file al del host
  int byteOffset = inic_byte_pos - 3222;

 
  int trc = strtrc-1;
  int byte_seq_line;
  short seq_line;

  while (trc < maxtrc){ //iterar hasta el maximo numero de traces

    //printf("byte %d\n" ,byteOffset );
    fseek( fp, byteOffset, SEEK_CUR );
    fread(&seq_line,sizeof(seq_line),1,fp); // read 4 bytes to our buffer
    seq_line = be16toh(seq_line); // Ajusta el endiann del file al del host  
  

    printf("%d\n" , seq_line);
    trc++;
    byteOffset = nm * 4 + 240 - 2;
  }

  fclose(fp); 
  }
  return 0;
}
