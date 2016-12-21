#include <stdio.h>
#include "des.c"

/*
Output should be:
c95744256a5ed31d
0123456789abcde7
85e813540f0ab405
0123456789abcdef
c95744256a5ed31d
7f1d0a77826b8aff
*/

void printtext(unsigned char hash[])
{
   int i;
   for (i=0; i < 8; i++)
      printf("%02x ",hash[i]);
   printf("\n");
}

int main()
{
   uchar text1[8]={0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xE7},
         text2[8]={0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF},
         key1[8]={0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF},
         key2[8]={0x13,0x34,0x57,0x79,0x9B,0xBC,0xDF,0xF1},
         three_key1[24]={0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,
                         0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,
                         0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF},
         three_key2[24]={0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,
                         0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10,
                         0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF},
         out[8],schedule[16][6],three_schedule[3][16][6];
   uint state[2];

   key_schedule(key1,schedule,ENCRYPT);
   des_crypt(text1,out,schedule);
   printtext(out);

   key_schedule(key1,schedule,DECRYPT);
   des_crypt(out,text1,schedule);
   printtext(text1);

   key_schedule(key2,schedule,ENCRYPT);
   des_crypt(text2,out,schedule);
   printtext(out);

   key_schedule(key2,schedule,DECRYPT);
   des_crypt(out,text2,schedule);
   printtext(text2);

   three_des_key_schedule(three_key1,three_schedule,ENCRYPT);
   three_des_crypt(text1,out,three_schedule);
   printtext(out);

   three_des_key_schedule(three_key2,three_schedule,ENCRYPT);
   three_des_crypt(text1,out,three_schedule);
   printtext(out);

   getchar();
   return 0;
}
