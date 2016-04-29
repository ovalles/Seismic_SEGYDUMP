#!/bin/bash
#
## SCRIPT:  method1.sh
#
## PURPOSE: MAKING A BYTE DUMP OF A BINARY FILE IN DIFERENT FORMATS
#
#  Syntax  >>./bytedumao file.in number_of_starting_byte number_of_ending_byte
#
#  by Asdrubal Ovalles, july 2015
#
FILENAME=$1
STRT_BYTE=$2
END_BYTE=$3
#B_NUM_LIN=$(xxd -s 3200 -l2 -g2 $1 | awk '{print toupper($2)}' | awk '{print "echo \"ibase=16;"$1"\"|bc"}'|sh)
#B_NUM_REEL=$(xxd -s 3208 -l4 -g4 $1 | awk '{print toupper($2)}' | awk '{print "echo \"ibase=16;"$1"\"|bc"}'|sh)
#B_SAMP_RATE=$(xxd -s 3216 -l2 -g2 $1 | awk '{print toupper($2)}' | awk '{print "echo \"ibase=16;"$1"\"|bc"}'|sh)
#B_TRC_SAMP=$(xxd -s 3220 -l2 -g2 $1 | awk '{print toupper($2)}' | awk '{print "echo \"ibase=16;"$1"\"|bc"}'|sh)


echo "Byte   2-Byte Int	   2-Byte SigInt    4-Byte decimal      4-Byte Float"

for (( c=$STRT_BYTE; c<=$END_BYTE; c++ ))
do


#BYTE2=$(xxd -s $c  -l2 -g2 $FILENAME | awk '{print toupper($2)}' | awk '{print "echo \"ibase=16;"$1"\"|bc"}'|sh)  
#BYTE4=$(xxd -s $c  -l4 -g4 $FILENAME | awk '{print toupper($2)}' | awk '{print "echo \"ibase=16;"$1"\"|bc"}'|sh)

## Native BigEndiann
#B_UnSig_ShortInt=$(od -j $c -N 2 -tu2 $FILENAME|awk '{print $2}')
#B_Sig_ShortInt=$(od -j $c -N 2 -td2 $FILENAME|awk '{print $2}')
#B_Sig_Int=$(od -j $c -N 4 -td4 $FILENAME|awk '{print $2}')

## Non Native Endiann (for HPC little endian)

L_UnSig_ShortInt=$(od -j $c -N 2 -tx1 $FILENAME |awk '{print $3 $2}'|xxd -r -p | od -tu2|awk '{print $2}')
L_Sig_ShortInt=$(od -j $c -N 2 -tx1 $FILENAME |awk '{print $3 $2}'|xxd -r -p | od -td2|awk '{print $2}')
L_Sig_Int=$(od -j $c -N 4 -tx1 $FILENAME |awk '{print $5 $4 $3 $2}'|xxd -r -p | od -td4|awk '{print $2}')
L_Sig_Float=$(od -j $c -N 4 -tx1 $FILENAME |awk '{print $5 $4 $3 $2}'|xxd -r -p | od -tf4|awk '{print $2}')

awk 'BEGIN{printf "%-15i%-15i%-15d%-15d%-12.3e\n","'$c'","'$L_UnSig_ShortInt'","'$L_Sig_ShortInt'","'$L_Sig_Int'","'$L_Sig_Float'"}'

#echo -en "$c\t\t $L_UnSig_ShortInt\t\t $L_Sig_ShortInt\t\t $L_Sig_Int\t\t $L_Sig_Float\t\t\n"

done


#dd if=PP_PSTM_SPP.sgy ibs=1 skip=3708 count=2 seek=3600 obs=1 conv=notrunc of=PP_PSTM_SPP.sgy

