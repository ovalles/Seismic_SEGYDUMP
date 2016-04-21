#include <stdio.h>
#include "endian.h"
// by Aj Ovalles 04 2016, Explore SEG-Y File

// Syntax: >> DisplayTrcHeaders filename maxTraceNumber

//char filename[] = "PP554_t506s751.sgy"; //SEGY-File to be edited
char *filename = NULL;
char *str_strtrc = NULL;
//int strtrc = 1;  // First Trace in file
//int maxtrc = 506;  // Max number of traces in SEGY-file
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
    printf("\n\n Syntax: >> DisplayTrcHeaders filename TraceInic TraceEnd\n");
    printf("\n If you want to see the reversed list then use: \n");
    printf("\n Syntax: >> DisplayTrcHeaders filename -NumberOfTraces 0\n\n");
  }
  else{
    filename = argv[1];
    printf("%s\n", filename);
    
    str_strtrc = argv[2];
    int strtrc = atoi(str_strtrc);
    printf("First Trace number %d\n", strtrc);
    
    str_maxtrc = argv[3];
    int maxtrc = atoi(str_maxtrc);
    printf("Last trace number %d\n", maxtrc);

    short nm;
    fp = fopen(filename,"rb");  // r for read, b for binary
    fseek( fp, 3220, SEEK_SET );
    fread(&nm,sizeof(nm),1,fp); // read 2 bytes to our buffer
    nm = be16toh(nm); // Ajusta el endiann del file al del host
    fseek( fp, 3600, SEEK_SET );
    int byteOffset = 0;
    printf("Samples: %d\n", nm);

    int seq_line; 

    if (strtrc > 0){

      int trc = 1;
      while ( trc < strtrc){
        fseek( fp, (240 + nm * 4), SEEK_CUR );
        trc++;
      }
    
      printf("seq_line, seq_file, cdp, cdp_seq, cdp_fold, offset, cdpx, cdpy, iln, xln, datumProcTime, datumProcMeter, datumFloatMeter\n");

      while (trc < maxtrc + 1 ){ //iterar hasta el maximo numero de traces
 
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

        printf("%d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\n", 
   	       seq_line, seq_file, cdp, cdp_seq, cdp_fold,
	       offset, cdpx, cdpy, iln, xln, datum_pt, datum_p, datum_f, feof(fp));
        trc++;
        byteOffset = (240-222)+ nm * 4;
        fseek( fp, (240-222)+ nm * 4, SEEK_CUR );
        byteOffset = 0;
      }
    }
      // REVERSE reading of SGY file
    else{
      fseek( fp, 0, SEEK_END );
      byteOffset = -1*(240 + nm * 4);
      int trc = 1;
      /*
      while ( trc < maxtrc){
        fseek( fp, -1* (240 + nm * 4), SEEK_END )
        trc++;
      }
      */
      printf("seq_line, seq_file, cdp, cdp_seq, cdp_fold, offset, cdpx, cdpy, iln, xln, datumProcTime, datumProcMeter, datumFloatMeter\n");

      while (trc <= abs(strtrc) ){ //iterar hasta el maximo numero de traces
 
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

        printf("%d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\n", 
 	       seq_line, seq_file, cdp, cdp_seq, cdp_fold,
	       offset, cdpx, cdpy, iln, xln, datum_pt, datum_p, datum_f, feof(fp));
        trc++;
        byteOffset = -1 * ((222)+ nm * 4 + 240);
        fseek( fp,byteOffset, SEEK_CUR );
        byteOffset = 0;
      }
    }
    fclose(fp); 
  }
  return 0;
}
