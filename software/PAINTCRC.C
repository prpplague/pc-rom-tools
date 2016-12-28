/* Check CRC in Paint ROM */

#include <stdio.h>
#include <stdlib.h>
#include "crc16.h"

int main()
{
    FILE *f;
    int i;
    unsigned int sz;
    unsigned short crc = 0;
    unsigned char *bytes = (unsigned char*)malloc(65535);

    CalculateTable_CRC16();

       f = fopen("paint0.bin","rb");
       if(f==NULL)
       {
          printf("\nCam't open file 1!\n\n");
          return -1;
       }
       fseek(f,0,SEEK_END);
       sz = ftell(f);
       fseek(f,0,SEEK_SET);
       fread(bytes,1,sz,f);
       fclose(f);

       f = fopen("paint1.bin","rb");
       if(f==NULL)
       {
          printf("\nCam't open file 2!\n\n");
          return -2;
       }
       fseek(f,0,SEEK_END);
       sz = ftell(f);
       fseek(f,0,SEEK_SET);
       fread(&bytes[32768],1,sz,f);
       fclose(f);

#if 1
    for(i=0;i<20;i++)
       printf("[%i]=0x%2.2X %c\n",i,
          bytes[i],(bytes[i]>32)?bytes[i]:' ');
#endif

    sz = 512*bytes[2];
    printf("Size is %u bytes (0x%4.4X)\n",sz,sz);

    crc = Compute_CRC16(bytes,sz);
    printf("Calculated CRC is 0x%4.4X\n",crc);

    free(bytes);
    return 0;
}
