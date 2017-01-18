/* Check CRC for JRCARTS ROM */

#include <stdio.h>
#include <stdlib.h>
#include "crc16.h"

int main()
{
    FILE *f;
    unsigned int i;
    unsigned int sz = 512;
    unsigned short crc = 0;
    unsigned char *bytes = (unsigned char*)malloc(512);

    CalculateTable_CRC16();

       f = fopen("jrcarts.bin","rb");
       if(f==NULL)
       {
          printf("\nCan't open file 1!\n\n");
          return -1;
       }
       fread(bytes,1,sz,f);
       fclose(f);

    crc = Compute_CRC16(bytes,sz);
    printf("Calculated CRC is 0x%4.4X\n",crc);

    if(crc!=0)
    {
       printf("CRC is not zero - trick it!\n");
       for(i=0xFFFF;i!=0;i--)
       {
         bytes[6] = (i>>8)&255;
         bytes[7] =  i&255;
         crc = Compute_CRC16(bytes,sz);
         printf("[0x%4.4X] Calculated CRC is 0x%4.4X\n",i,crc);
         if(crc==0) break;
       }
    }

    free(bytes);
    return 0;
}
