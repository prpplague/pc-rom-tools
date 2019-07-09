/* Creating ROM image from JRCARTS4.IMG */

/* by Shaos (Jan 2017) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GAMES 9
#define OFFSET 256

long offsets[GAMES] = {
/* ScubaVenture */    0x01200L,
/* Mouser */          0x03600L,
/* River Raid */      0x05A00L,
/* Pitfall II */      0x0A200L,
/* Demon Attack */    0x0EA00L,
/* Microsurgeon */    0x19e00L,
/* Crossfire */       0x25200L,
/* Mine Shaft */      0x27600L,
/* PCjr colorpaint */ 0x29A00L };
long offsetsnew[GAMES];

int main()
{
 int i,j,b,b1,b2,b3;
 long l,maxzero,nonzero,nzero,current;
 FILE *f,*fo;
 f = fopen("JRCARTS4.IMG","rb");
 if(f==NULL) return -1;
 fo = fopen("JRCARTS4.BIN","wb");
 if(fo==NULL){fclose(f);return -2;}
 maxzero = nonzero = current = 0;
 for(i=0;i<8;i++)
 {
    fseek(f,offsets[i],SEEK_SET);
    b1 = fgetc(f);
    b2 = fgetc(f);
    b3 = fgetc(f);
    fputc(b1,fo);
    fputc(b2,fo);
    fputc(b3,fo);
    if(b3==0x90) b3=16; /* trick for #1 */
    printf("%i) 0x%2.2X 0x%2.2X 0x%2.2X (%lu bytes)\tcurrent=0x%5.5lX (0x%5.5lX)\n",i,b1,b2,b3,b3*512L,current,current+OFFSET);
    offsetsnew[i] = current;
    current += 3;
    nzero = 0;
    for(l=3;l<b3*512L;l++)
    {
       b = fgetc(f);
       if(b)
       {
          if(nzero){if(nzero>maxzero)maxzero=nzero;current++;fputc(0,fo);if(nzero==2){current++;fputc(0,fo);}else if(nzero>2){current+=4;fputc(0,fo);fputc(0,fo);fputc(nzero&255,fo);fputc(nzero>>8,fo);}}
          nzero = 0;
          nonzero++;
          current++;
          fputc(b,fo);
       }
       else nzero++;
    }
    if(nzero){if(nzero>maxzero)maxzero=nzero;current++;fputc(0,fo);if(nzero==2){current++;fputc(0,fo);}else if(nzero>2){current+=4;fputc(0,fo);fputc(0,fo);fputc(nzero&255,fo);fputc(nzero>>8,fo);}}
 }
 printf("maxzero=%li nonzero=%li current=%li (0x%5.5lX)\n",maxzero,nonzero,current,current+OFFSET);
 offsetsnew[i] = current;
 fclose(fo);
 fclose(f);
 return 0;
}
