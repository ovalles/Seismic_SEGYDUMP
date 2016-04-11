// Display Trace Headers values from SEGY-File
// By AJ Ovalles, 2016
// Made in Venezuela

// Syntax: >> DisplayTrcHeaders filename maxTraceNumber

#include <stdio.h>
#include "endian.h"


char *filename = NULL;
int strtrc = 1;  // First Trace in file
int inic_byte_pos =3600; // Header to extract _must be int 4bytes_
char *str_maxtrc = NULL;
FILE *fp;

int getint(int byteOffset){
    int seq;
    fseek( fp, byteOffset , SEEK_CUR );
    fread(&seq,sizeof(seq),1,fp); // read 4 bytes to our buffer
    seq = be32toh(seq); // Ajusta el endiann del file al del host
    return seq;
}

short getshort(int byteOffset){
    short seq_short;
    fseek( fp, byteOffset , SEEK_CUR );
    fread(&seq_short,sizeof(seq_short),1,fp); // read 4 bytes to our buffer
    seq_short = be16toh(seq_short); // Ajusta el endiann del file al del host
    return seq_short;
}

int main(int argc, char **argv) {

  
  if (argv[1] == NULL){
    printf("Syntax: >> DisplayTrcHeaders filename maxTraceNumber\n");
  }
  else{

  filename = argv[1];
  printf("%s\n", filename);

  str_maxtrc = argv[2];
  int maxtrc = atoi(str_maxtrc);
  printf("Numero de trazas %d\n", maxtrc);

  short nm;
  fp = fopen(filename,"rb");  // r for read, b for binary
  fseek( fp, 3220, SEEK_SET );
  fread(&nm,sizeof(nm),1,fp); // read 2 bytes to our buffer
  nm = be16toh(nm); // Ajusta el endiann del file al del host
  int byteOffset = inic_byte_pos - 3222;
  printf("Samples: %d\n", nm);
 
  int trc = strtrc-1;
  int seq_line;

  printf("seq_line, seq_file, cdp, cdp_seq, cdp_fold, offset, cdpx, cdpy, iln, xln, datumProcTime, datumProcMeter, datumFloatMeter\n");

  while (trc < maxtrc){ //iterar hasta el maximo numero de traces
 
 
    unsigned int seq_line = getint( byteOffset );
    byteOffset = 0;
    unsigned int seq_file = getint( byteOffset );
    byteOffset = 12;
    unsigned int cdp = getint( byteOffset );
    byteOffset = 0;
    unsigned int cdp_seq = getint( byteOffset );
    byteOffset = 4;
    short cdp_fold = getshort( byteOffset );
    byteOffset = 2;
    unsigned int offset = getint( byteOffset );
    byteOffset = 140;
    unsigned int cdpx = getint( byteOffset );
    byteOffset = 0;
    unsigned int cdpy = getint( byteOffset );
    byteOffset = 0;
    unsigned int iln = getint( byteOffset );
    byteOffset = 0;
    unsigned int xln = getint( byteOffset );
    byteOffset = 0;
    short datum_pt = getshort( byteOffset ); //Datum de procesamiento en tiempo
    byteOffset = 0;
    short datum_p = getshort( byteOffset );  //Datum de procesamiento en metros
    byteOffset = 20;
    short datum_f = getshort( byteOffset );  //Datum flotante en metros

    printf("%d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\n", 
	   seq_line, seq_file, cdp, cdp_seq, cdp_fold,
	   offset, cdpx, cdpy, iln, xln, datum_pt, datum_p, datum_f );
    trc++;
    byteOffset = (240-222)+ nm * 4;
  }

  fclose(fp); 
  }
  return 0;
}
