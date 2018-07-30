//----------------------------------------------------------------------------------------------------
//$Header: /home/dashley/cvsrep/e3ft_gpl01/e3ft_gpl01/dtaipubs/cron/2010/blackjack_201010/source/bjcceval/sha512.c,v 1.9 2012/03/30 00:20:15 dashley Exp $
//----------------------------------------------------------------------------------------------------
//Copyright (C) 2012, David T. Ashley.
//
//This file is part of BJCCEVAL, a program that evaluates by simulation
//the best basic strategy, card-counting, and other playing strategies
//for several variants of the game of Blackjack.
//
//BJCCEVAL is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//BJCCEVAL is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.
//(A copy of the GNU General Public License, Version 3 is provided in
//the file "COPYING" distributed with BJCCEVAL.)
//
//David T. Ashley can be contacted at DASHLEY@GMAIL.COM and/or at
//P.O. Box 918, Marshall MI 49068.
//----------------------------------------------------------------------------------------------------
#define MODULE_SHA512

#include <stdlib.h>
#include <string.h>

#include "cassert.h"
#include "charfunc.h"
#include "sha512.h"

//This is a right rotation macro for efficiency.  This
//macro rotates a 64-bit quantity x right (cyclically) by 
//n bits.  Nomenclature from FIPS 180-3.
#define SHA512_FUNC_ROTR(x, n) (((x) >> (n)) | ((x) << (64-(n))))

//This is a right shift macro for efficiency.  This
//macro shifts a 64-bit quantity x right by 
//n bits.  Nomenclature from FIPS 180-3.
#define SHA512_FUNC_SHR(x, n) ((x) >> (n))

//These functions come directly from FIPS 180-3.
#define SHA512_FUNC_CH(x, y, z)  (((x) & (y)) ^ (~(x) & (z)))
#define SHA512_FUNC_MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define SHA512_FUNC_SIGMABIG_0(x) (SHA512_FUNC_ROTR(x, 28) ^ SHA512_FUNC_ROTR(x, 34) ^ SHA512_FUNC_ROTR(x, 39))
#define SHA512_FUNC_SIGMABIG_1(x) (SHA512_FUNC_ROTR(x, 14) ^ SHA512_FUNC_ROTR(x, 18) ^ SHA512_FUNC_ROTR(x, 41))
#define SHA512_FUNC_SIGMASMALL_0(x) (SHA512_FUNC_ROTR(x,  1) ^ SHA512_FUNC_ROTR(x,  8) ^ SHA512_FUNC_SHR(x,  7))
#define SHA512_FUNC_SIGMASMALL_1(x) (SHA512_FUNC_ROTR(x, 19) ^ SHA512_FUNC_ROTR(x, 61) ^ SHA512_FUNC_SHR(x,  6))


//Constants, from FIPS 180-3.
const unsigned long long SHA512_K[80] =
{
    0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL,
    0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL,
    0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL,
    0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL,
    0xd807aa98a3030242ULL, 0x12835b0145706fbeULL,
    0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL,
    0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL,
    0x9bdc06a725c71235ULL, 0xc19bf174cf692694ULL,
    0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL,
    0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL,
    0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL,
    0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL,
    0x983e5152ee66dfabULL, 0xa831c66d2db43210ULL,
    0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL,
    0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL,
    0x06ca6351e003826fULL, 0x142929670a0e6e70ULL,
    0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL,
    0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL,
    0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL,
    0x81c2c92e47edaee6ULL, 0x92722c851482353bULL,
    0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL,
    0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL,
    0xd192e819d6ef5218ULL, 0xd69906245565a910ULL,
    0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL,
    0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL,
    0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL,
    0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL,
    0x5b9cca4f7763e373ULL, 0x682e6ff3d6b2b8a3ULL,
    0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL,
    0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
    0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL,
    0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL,
    0xca273eceea26619cULL, 0xd186b8c721c0c207ULL,
    0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL,
    0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL,
    0x113f9804bef90daeULL, 0x1b710b35131c471bULL,
    0x28db77f523047d84ULL, 0x32caab7b40c72493ULL,
    0x3c9ebe0a15c9bebcULL, 0x431d67c49c100d4cULL,
    0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL,
    0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL
};


//Initializes an SHA-512 state structure in preparation for adding data.
//
void SHA512_Sha512StateStructOpen(struct SHA512_Sha512StateStruct *arg)
{
    memset(arg, 0, sizeof(struct SHA512_Sha512StateStruct));
    //Set everything to zero--processed bitcount set to zero.

    //This assignment comes directly from FIPS 180-3.
    arg->H0 = 0x6a09e667f3bcc908ULL;
    arg->H1 = 0xbb67ae8584caa73bULL;
    arg->H2 = 0x3c6ef372fe94f82bULL;
    arg->H3 = 0xa54ff53a5f1d36f1ULL;
    arg->H4 = 0x510e527fade682d1ULL;
    arg->H5 = 0x9b05688c2b3e6c1fULL;
    arg->H6 = 0x1f83d9abfb41bd6bULL;
    arg->H7 = 0x5be0cd19137e2179ULL;
}



//Copies the byte buffer to the word buffer within the state block.
//This is done in a way which hides big-endian/little-endian concerns.
//
static void SHA512_CopyBytesToWords(struct SHA512_Sha512StateStruct *arg)
{
    unsigned int i;

#ifdef P_CASSERT
    CASSERT_Assert(arg != NULL, __FILE__, __LINE__);
#endif

    //Copy the buffer contents into the words.  We need to be careful
    //to do this correctly, because of big-endian/little-endian concerns.
    //From FIPS 180-3 (alluded to, not really stated), the message is
    //loaded in from M[0] down to M[15].  Additionally, per the other
    //conventions in the document, the first byte is uppermost in each
    //word.
    for (i=0; i<16; i++)
    {

#ifdef P_CASSERT
        CASSERT_Assert((i * 8 + 7) < 128, __FILE__, __LINE__);
#endif

        arg->M[i] = (((unsigned long long)(arg->buf[i*8+0])) << 56)
                    +
                    (((unsigned long long)(arg->buf[i*8+1])) << 48)
                    +
                    (((unsigned long long)(arg->buf[i*8+2])) << 40)
                    +
                    (((unsigned long long)(arg->buf[i*8+3])) << 32)
                    +
                    (((unsigned long long)(arg->buf[i*8+4])) << 24)
                    +
                    (((unsigned long long)(arg->buf[i*8+5])) << 16)
                    +
                    (((unsigned long long)(arg->buf[i*8+6])) <<  8)
                    +
                    (((unsigned long long)(arg->buf[i*8+7])));
    }
}


//Copies the buffer of words into a string buffer of string length 128, and also places
//the zero terminator, which means that the string supplied by the caller must be of size
//129 or larger.
//
static void SHA512_CopyWordsToStringBuffer(struct SHA512_Sha512ResultStruct *arg)
{
    unsigned int i, j;
    unsigned char *puc;
    unsigned long long woi;

#ifdef P_CASSERT
    CASSERT_Assert(arg != NULL, __FILE__, __LINE__);
#endif

    //Copy the buffer contents into the words.  We need to be careful
    //to do this correctly, because of big-endian/little-endian concerns.
    //From FIPS 180-3 (alluded to, not really stated), the message is
    //loaded in from M[0] down to M[15].  Additionally, per the other
    //conventions in the document, the first byte is uppermost in each
    //word.
    for (i=0; i<8; i++)
    {
        woi = arg->sha512_words[i];

        //Form a pointer to the buffer location of interest.  We work
        //backwards.
        puc = (unsigned char *)(arg->sha512_chars) + (i * 16) + 15;

        //Fill in the buffer.
        for (j=0; j<16; j++)
        {
            *puc = (unsigned char)CHARFUNC_nibble_to_lc_hex_digit((int)(woi & 0xF));
            woi >>= 4;
            puc--;
        }
    }

    //Place the zero string terminator.
    arg->sha512_chars[128] = 0;
}



//Do the SHA-512 rounds as specified by FIPS 180-3.
//
static void SHA512_DoSha512Rounds(struct SHA512_Sha512StateStruct *arg)
{
    int i;
    //Iteration variable.
    unsigned long long T1, T2;
    //Temporary variables.  Nomenclature is from FIPS 180-3.
    unsigned long long M[16];
    //Buffer of message block to avoid repeated dereferences.
    unsigned long long H[8];
    //Buffer of hash state to avoid repeated dereferences.
    unsigned long long W[80];
    //Working variable.  Nomenclature directly from FIPS 180-3.
    unsigned long long a, b, c, d, e, f, g, h;
    //Nomenclature above directly from FIPS 180-3.

#ifdef P_CASSERT
    CASSERT_Assert(arg != NULL, __FILE__, __LINE__);
#endif

    //Copy bytes into words.
    SHA512_CopyBytesToWords(arg);

    //Copy out the message buffer for speed.  This should avoid repeated
    //dereferences.
    M[ 0] = arg->M[ 0];
    M[ 1] = arg->M[ 1];
    M[ 2] = arg->M[ 2];
    M[ 3] = arg->M[ 3];
    M[ 4] = arg->M[ 4];
    M[ 5] = arg->M[ 5];
    M[ 6] = arg->M[ 6];
    M[ 7] = arg->M[ 7];
    M[ 8] = arg->M[ 8];
    M[ 9] = arg->M[ 9];
    M[10] = arg->M[10];
    M[11] = arg->M[11];
    M[12] = arg->M[12];
    M[13] = arg->M[13];
    M[14] = arg->M[14];
    M[15] = arg->M[15];

    //Copy out the hash state for speed.  This should avoid repeated dereferences.
    H[0]  = arg->H0;
    H[1]  = arg->H1;
    H[2]  = arg->H2;
    H[3]  = arg->H3;
    H[4]  = arg->H4;
    H[5]  = arg->H5;
    H[6]  = arg->H6;
    H[7]  = arg->H7;

    //Prepare the message schedule.  The nomenclature comes directly from FIPS 180-3.
    W[ 0] = M[ 0];
    W[ 1] = M[ 1];
    W[ 2] = M[ 2];
    W[ 3] = M[ 3];
    W[ 4] = M[ 4];
    W[ 5] = M[ 5];
    W[ 6] = M[ 6];
    W[ 7] = M[ 7];
    W[ 8] = M[ 8];
    W[ 9] = M[ 9];
    W[10] = M[10];
    W[11] = M[11];
    W[12] = M[12];
    W[13] = M[13];
    W[14] = M[14];
    W[15] = M[15];

    for (i=16; i<80; i++)
    {
        W[i] =    SHA512_FUNC_SIGMASMALL_1(W[i-2])
                  +  W[i-7]
                  +  SHA512_FUNC_SIGMASMALL_0(W[i-15])
                  +  W[i-16];
    }

    //Initialize the 8 working variables as specified in FIPS 180-3.
    a = H[0];
    b = H[1];
    c = H[2];
    d = H[3];
    e = H[4];
    f = H[5];
    g = H[6];
    h = H[7];

    //Perform the rounds as specified in FIPS 180-3.  Nomenclature below comes from 
    //FIPS 180-3.
    for (i=0; i<80; i++)
    {
        T1 =    h 
                + SHA512_FUNC_SIGMABIG_1(e) 
                + SHA512_FUNC_CH(e, f, g)
                + SHA512_K[i]
                + W[i];
        //
        T2 =    SHA512_FUNC_SIGMABIG_0(a)
                + SHA512_FUNC_MAJ(a, b, c);
        //
        h = g;
        //
        g = f;
        //
        f = e;
        //
        e = d + T1;
        //
        d = c;
        //
        c = b;
        //
        b = a;
        //
        a = T1 + T2;
    }

    //Compute the next hash value.  The nomenclature comes from FIPS 180-3.
    H[0] = a + H[0];
    H[1] = b + H[1];
    H[2] = c + H[2];
    H[3] = d + H[3];
    H[4] = e + H[4];
    H[5] = f + H[5];
    H[6] = g + H[6];
    H[7] = h + H[7];

    //Place the local variables back in the structure.  This the only state that
    //gets preserved between the operation of doing the rounds.
    arg->H0 = H[0];
    arg->H1 = H[1];
    arg->H2 = H[2];
    arg->H3 = H[3];
    arg->H4 = H[4];
    arg->H5 = H[5];
    arg->H6 = H[6];
    arg->H7 = H[7];
}


//Adds a block of data to the SHA-512 structure.  Zero length is allowed.
//
void SHA512_Sha512StateStructAddData(struct    SHA512_Sha512StateStruct *arg,
                                     void      *pointer_in,
                                     unsigned  len)
{
    unsigned int   low_32;
    unsigned int   byte_offset;
    unsigned char *data;

#ifdef P_CASSERT
    CASSERT_Assert((len == 0) || (arg != NULL), __FILE__, __LINE__);
    CASSERT_Assert(pointer_in != NULL, __FILE__, __LINE__);
#endif

    data = (unsigned char *)pointer_in;
    //It is easier to do it this way, rather than cast all the time.

    low_32 = (unsigned int)arg->bit_count;
    //Copy off the least significant bits.  Easier to do once.  We only
    //need the 32 least significant because the block size is 0 modulo 1024.

    byte_offset = low_32 >> 3;
    //This gives our byte offset, up to 500+Mb or so.

    while (len--)
    {
        //We process rounds AFTER a byte is added to the buffer.  So
        //it is always safe to add a byte first.
        arg->buf[byte_offset & 0x7F] = *data;

        //Nothing to do unless this was the final byte of the buffer.
        if ((byte_offset & 0x7F) == 127)
        {
            SHA512_DoSha512Rounds(arg);
        }

        //Increment.
        data++;
        byte_offset++;
        arg->bit_count += 8;
    }
}


//Closes the SHA-512 structure and places the SHA-512 result into the result structure.
//After this operation, state is destroyed and no further data may be added.
//
void SHA512_Sha512StateStructClose(struct SHA512_Sha512StateStruct  *state,
                                   struct SHA512_Sha512ResultStruct *result)
{
    unsigned long long msglen;
    //Used to hold message length before we pad the message.
    unsigned char c80 = 0x80;
    //Used to append the "1" per FIPS 180-3.
    unsigned char c00 = 0x00;
    //Used to add 0's per FIPS 180-3.
    unsigned char  length_buf[16];
    //Buffer used to form the message length and append it to the message per FIPS 180-3.

    //Be sure the input pointers aren't obviously invalid.
#ifdef P_CASSERT
    CASSERT_Assert(state  != NULL, __FILE__, __LINE__);
    CASSERT_Assert(result != NULL, __FILE__, __LINE__);
#endif

    //Snapshot the message length.  We'll be changing it when we pad the message.
    msglen = state->bit_count;

    //Add the required "1" to the end of the message, per FIPS 180-3.  Because
    //this software module only allows the addition of bytes (not bits), adding the
    //"1" will always involve adding the byte 0x80.
    SHA512_Sha512StateStructAddData(state, &c80, 1);

    //Add enough 0's to the message so that we have exactly room for 16 bytes (128 bits)
    //of length information at the end of the message.
    while ((state->bit_count & 0x3FF) != 896)
        SHA512_Sha512StateStructAddData(state, &c00, 1);

    //Calculate the length as a series of bytes.
    length_buf[ 0] = 0;
    length_buf[ 1] = 0;
    length_buf[ 2] = 0;
    length_buf[ 3] = 0;
    length_buf[ 4] = 0;
    length_buf[ 5] = 0;
    length_buf[ 6] = 0;
    length_buf[ 7] = 0;
    length_buf[ 8] = (unsigned char)((msglen >> 56) & 0xFF);
    length_buf[ 9] = (unsigned char)((msglen >> 48) & 0xFF);
    length_buf[10] = (unsigned char)((msglen >> 40) & 0xFF);
    length_buf[11] = (unsigned char)((msglen >> 32) & 0xFF);
    length_buf[12] = (unsigned char)((msglen >> 24) & 0xFF);
    length_buf[13] = (unsigned char)((msglen >> 16) & 0xFF);
    length_buf[14] = (unsigned char)((msglen >>  8) & 0xFF);
    length_buf[15] = (unsigned char)((msglen) & 0xFF);

    //Add the length to the message.  This should work out to generate the
    //final manipulation round.
    SHA512_Sha512StateStructAddData(state, length_buf, 16);

    //Copy the words from the state vector to the result vector.
    result->sha512_words[0] = state->H0;
    result->sha512_words[1] = state->H1;
    result->sha512_words[2] = state->H2;
    result->sha512_words[3] = state->H3;
    result->sha512_words[4] = state->H4;
    result->sha512_words[5] = state->H5;
    result->sha512_words[6] = state->H6;
    result->sha512_words[7] = state->H7;

    //Form a string from the hash vector.
    SHA512_CopyWordsToStringBuffer(result);

    //Destroy the state, which may contain sensitive information.
    memset(state, 0, sizeof(struct SHA512_Sha512StateStruct));
}


const char *SHA512_Vcinfo_C(void)
{
    return("$Revision: 1.9 $");
}


const char *SHA512_Vcinfo_H(void)
{
    return(SHA512_VCINFO_H);
}


//----------------------------------------------------------------------------------------------------
//$Log: sha512.c,v $
//Revision 1.9  2012/03/30 00:20:15  dashley
//Edits.
//
//Revision 1.8  2012/03/29 23:44:01  dashley
//Edits.
//
//Revision 1.7  2012/03/26 02:17:49  dashley
//Edits.
//
//Revision 1.6  2012/03/26 02:11:07  dashley
//Edits.
//
//Revision 1.5  2012/03/15 23:38:08  dashley
//License text enhanced.
//
//Revision 1.4  2012/03/14 02:44:49  dashley
//Edits.
//
//Revision 1.3  2012/03/14 01:57:52  dashley
//Edits.
//----------------------------------------------------------------------------------------------------
// End of $RCSfile: sha512.c,v $.
//----------------------------------------------------------------------------------------------------

