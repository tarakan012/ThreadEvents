/******************************************
** DES-Implementation
** Author: B-Con (b-con@b-con.us)
** Copyright/Restrictions: GNU GPL
** Disclaimer: This code is presented "as is" without any garuentees; said author holds
               liability for no problems rendered by the use of this code.
** Details: This code is the implementation of the AES algorithm, as specified by the
            NIST in in publication FIPS PUB 197, availible on the NIST website at
            http://csrc.nist.gov/publications/fips/fips46-3/fips46-3.pdf .
******************************************/

#ifndef DES_C
#define DES_C



#define uchar unsigned char
#define uint unsigned int
#define ENCRYPT 1
#define DECRYPT 0

// Obtain bit "b" from the left and shift it "c" places from the right
#define BITNUM(a,b,c) (((a[(b)/8] >> (7 - (b%8))) & 0x01) << (c))
#define BITNUMINTR(a,b,c) ((((a) >> (31 - (b))) & 0x00000001) << (c))
#define BITNUMINTL(a,b,c) ((((a) << (b)) & 0x80000000) >> (c))
// This macro converts a 6 bit block with the S-Box row defined as the first and last
// bits to a 6 bit block with the row defined by the first two bits.
#define SBOXBIT(a) (((a) & 0x20) | (((a) & 0x1f) >> 1) | (((a) & 0x01) << 4))

//extern uchar sbox1[64];
//uchar sbox2[64];
//uchar sbox3[64];
//uchar sbox4[64];
//uchar sbox5[64];
//uchar sbox6[64];
//uchar sbox7[64];
//uchar sbox8[64];


void key_schedule(uchar key[], uchar schedule[][6], uint mode);

// Initial (Inv)Permutation step
void IP(uint state[], uchar in[]);

void InvIP(uint state[], uchar in[]);

uint f(uint state, uchar key[]);

void des_crypt(uchar in[], uchar out[], uchar key[][6]);

/**************************************
             3DES functions
**************************************/

void three_des_key_schedule(uchar key[], uchar schedule[][16][6], uint mode);

void three_des_crypt(uchar in[], uchar out[], uchar key[][16][6]);

/************************************/

#endif // !DES_C
