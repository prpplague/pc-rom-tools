/* Algorithm was taken from here:
   http://www.sunshine2k.de/articles/coding/crc/understanding_crc.html#ch5
   and translated to C by Shaos
*/

#include "crc16.h"

unsigned short crctable16[256];

void CalculateTable_CRC16(void)
{
    int divident,bit,generator = 0x1021;
    unsigned short curByte;
    for(divident = 0; divident < 256; divident++) /* iterate over all possible input byte values 0 - 255 */
    {
        curByte = (unsigned short)(divident << 8); /* move divident byte into MSB of 16Bit CRC */

        for(bit = 0; bit < 8; bit++)
        {
            if(curByte & 0x8000)
            {
                curByte <<= 1;
                curByte ^= generator;
            }
            else
            {
                curByte <<= 1;
            }
        }

        crctable16[divident] = curByte;
    }
}

unsigned short Compute_CRC16(unsigned char* bytes, unsigned int nbytes)
{
    unsigned int i;
    unsigned char pos,*b;
    unsigned short crc = 0xFFFF; /* as per IBM source code of BIOS */

    for(i=0,b=bytes;i<nbytes;i++,b++)
    {
        /* XOR-in next input byte into MSB of crc, that's our new intermediate divident */
        pos = (unsigned char)( (crc >> 8) ^ *b); /* equal: ((crc ^ (b << 8)) >> 8) */
        /* Shift out the MSB used for division per lookuptable and XOR with the remainder */
        crc = (unsigned short)((crc << 8) ^ crctable16[pos]);
    }

    return crc;
}

#ifdef MAIN

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    FILE *f;
    int i;
    unsigned long sz;
    unsigned short crc = 0;
    unsigned char* bytes;

    CalculateTable_CRC16();
#if 0
    for(i=0;i<256;i++) printf("[%i]=0x%4.4X\n",i,crctable16[i]);
#endif
    if(argc>1)
    {
       f = fopen(argv[1],"rb");
       if(f==NULL)
       {
          printf("\nCan't open file '%s'!\n\n",argv[1]);
          return -1;
       }
       fseek(f,0,SEEK_END);
       sz = ftell(f);
       fseek(f,0,SEEK_SET);
       if(sz>0)
       {
          if(sz==65536L)
          {
            sz-=2;
            printf("\nAttention! CRC is calculated only for %lu bytes!\n",sz);
          }
          bytes = (unsigned char*)malloc(sz);
          if(bytes!=NULL)
          {
             fread(bytes,1,sz,f);
             crc = Compute_CRC16(&bytes[2],sz);
          }
          else
          {
             fclose(f);
             printf("\nCan't allocate %lu bytes!\n\n",sz);
             return -3;
          }
          free(bytes);
       }
       else
       {
          fclose(f);
          printf("\nFile '%s' is empty!\n\n",argv[1]);
          return -2;
       }
       fclose(f);
    }
    printf("\nCalculated CRC is 0x%4.4X\n",crc);

    return 0;
}

#endif
