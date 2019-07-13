/* Based on PCJRCART.C by Shaos (Dec 2016) */

/* Create ROM image from COM file for generic BIOS Extension ROM */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 65535

int main(int argc, char **argv)
{
    FILE *f;
    int i;
    int sum8 = 0;
    char fname[100],*po;
    unsigned long counter;
    unsigned long sz;
    unsigned char extra = 0;
    unsigned short crc = 0;
    unsigned char *bytes = (unsigned char*)malloc(MAXSIZE);
    if(bytes==NULL)
    {
       printf("\nCan't allocate memory!\n\n");
       return -1;
    }
    if(argc<2)
    {
       printf("\nFilename was not specified!\n\n");
       return -2;
    }
    memset(bytes,0,MAXSIZE);

    strcpy(fname,argv[1]);
    f = fopen(fname,"rb");
    if(f==NULL)
    {
       printf("\nCan't open file '%s'!\n\n",fname);
       free(bytes);
       return -3;
    }
    fseek(f,0,SEEK_END);
    sz = ftell(f);
    printf("%s %lu\n",fname,sz);
    if(sz>=65280L)
    {
       printf("\nFile is too large!\n\n");
       fclose(f);
       free(bytes);
       return -4;
    }

    /* Load the binary image at the 0x0003 entry point */
    fseek(f,0,SEEK_SET);
    fread(&bytes[3],1,sz,f);
    fclose(f);

    /* bytes[1:0] contain the BIOS extension magic number 0x55 0xAA */
    bytes[0] = 0x55;
    bytes[1] = 0xAA;

    sz += 258;
    if(sz&511)
    {
       sz &= 0xFE00;
       sz += 512;
    }

    /* bytes[2] contains the number of 512 byte blocks in the image */
    bytes[2] = sz>>9;
    printf("ROM size is %lu bytes (%i)\n",sz,bytes[2]);

    /* generate simple 8-bit checksum */
    sum8=0;
    for (counter=0; counter < sz ; counter++) {
       sum8 = sum8 + bytes[counter];
    }

    sum8=(((~(sum8 & 0xff)) + 1) & 0xff);
    printf("8-bit Checksum=%x\n",sum8);

    /* for this implementation the last byte in the image is used  */
    /* to store the 8-bit checksum value. some implementations may */
    /* use bytes[5] as this location, as the last two bytes in an  */
    /* may be used as majic numbers to identify image type.        */
    bytes[sz-1]=sum8;

    po = strrchr(fname,'.');
    if(po!=NULL) *po=0;
    strcat(fname,".bin");
    f = fopen(fname,"wb");
    if(f==NULL)
    {
       printf("\nCan't open file '%s'!\n\n",fname);
       free(bytes);
       return -5;
    }
    if(sz<=32768L) fwrite(bytes,1,sz,f);
    else fwrite(bytes,1,32768L,f);
    fclose(f);
    if(sz>32768L)
    {
       fname[strlen(fname)-1] = '2';
       f = fopen(fname,"wb");
       if(f==NULL)
       {
          printf("\nCan't open file '%s'!\n\n",fname);
          free(bytes);
          return -6;
       }
       if(sz==65536L)
       {
          fwrite(&bytes[32768L],4,0x1FFF,f);
          fputc(bytes[65532L],f);
          fputc(bytes[65533L],f);
          fputc(bytes[65534L],f);
          fputc(extra,f);
       }
       else fwrite(&bytes[32768L],1,sz-32768L,f);
       fclose(f);
    }
    free(bytes);
    return 0;
}
