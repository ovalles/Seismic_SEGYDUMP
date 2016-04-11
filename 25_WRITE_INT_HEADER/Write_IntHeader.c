// Modify 4-byte Integer Trace Headers values from SEGY-File
// By AJ Ovalles, 2016
// Made in Venezuela

#include <stdio.h>
#include "endian.h"


// Syntax: >> WriteIntHeader filename maxTraceNumber 3600+byteToOverride FirstValue ValueIncrement conter


char *filename = NULL; //SEGY-File to be edited
int strtrc = 1;  // First Trace in file
char *str_maxtrc = NULL;  // Max number of traces in SEGY-file
//Header to override _must be int 2bytes_ 3632 for fold value replacement
char *str_inic_byte_pos;
char *str_firstTrcNum = NULL;  // Header value at first trace
char *str_ValueIncrement = NULL;  // Header value Increment
char *str_conter = NULL;  // Header value Increment
//int inic_byte_pos =3604; // Header to override _must be int 4bytes_
FILE *fp;
int conter;

int main(int argc,char* argv[]) {
  
  if (argv[1] == NULL){
    printf("Syntax: >> WriteIntHeader filename maxTraceNumber 3600+byteToOverride FirstValue ValueIncrement CounterToRepeat(Optional)\n");
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

  str_firstTrcNum = argv[4];
  int firstTrcNum = atoi(str_firstTrcNum);
  printf("Value at firs trace %d\n", firstTrcNum );

  str_ValueIncrement = argv[5];
  int ValueIncrement = atoi(str_ValueIncrement);
  printf("Increment %d\n", ValueIncrement );

  
  if (argv[6] == NULL){
    conter = maxtrc;
  }
  else{
  str_conter = argv[6];
  conter = atoi(str_conter);
  printf("Counter to repeat %d\n", conter );
  }

  short nm;
  fp = fopen(filename,"r+b");  // r for read, b for binary
  fseek( fp, 3220, SEEK_SET );
  fread(&nm,sizeof(nm),1,fp); // read 2 bytes to our buffer
  nm = be16toh(nm); // Ajusta el endiann del file al del host
  int byteOffset = inic_byte_pos - 3222 ;

 
  int trc = strtrc-1;
  int byte_seq_line;
  int seq_line;
  int seq_counter = 0;
  while (trc < maxtrc){ //iterar hasta el maximo numero de traces

    fseek( fp, byteOffset, SEEK_CUR );
    //seq_line = trc + firstTrcNum;  //Crea un secuencial
    seq_line = firstTrcNum + ValueIncrement * seq_counter;
    seq_line = htobe32(seq_line); // Ajusta el endiann del file al del host
    fwrite(&seq_line,sizeof(seq_line),1,fp); // read 4 bytes to our buffer
      
  

    //printf("Edited trace: %d\n" , trc + 1);
    trc++;
    seq_counter++;

    if(seq_counter == conter ){
      seq_counter = 0;
    }

    byteOffset = nm * 4 + 240 - 4;
  }
  
  fclose(fp); 
  }
  return 0;
}
