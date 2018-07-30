//----------------------------------------------------------------------------------------------------
//$Header: /home/dashley/cvsrep/e3ft_gpl01/e3ft_gpl01/dtaipubs/cron/2010/blackjack_201010/source/bjcceval/sha512.h,v 1.7 2012/03/30 00:20:15 dashley Exp $
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
#ifndef SHA512_H_INCLUDED
#define SHA512_H_INCLUDED

#ifdef MODULE_SHA512
    #define DECMOD_SHA512
#else
    #define DECMOD_SHA512 extern
#endif


//Fundamental state for forming SHA-512s.  Conceptually private to this module.
//
struct SHA512_Sha512StateStruct
{
    unsigned long long H0, H1, H2, H3, H4, H5, H6, H7;
    //Directly from FIPS 180-3.  In retrospect, this might have
    //been better implemented as an array.
    unsigned long long bit_count;
    //The count of bits processed thus far.  The algorithm here
    //works in bytes, not bits, so this is advanced by 8 on
    //each byte processed.  FIPS 180-3 calls for processing
    //messages up to length 2^128, but for obvious reasons
    //we don't do that.  2^64-1 bits is in excess of 2^61-1
    //bytes, or somewhere around 2,000 terabytes.  This
    //isn't a practical limit with current computer technology.
    unsigned long long M[16];
    //These are the words corresponding to the chars (below).  We don't
    //dare union to extract them because of big-endian/little-endian concerns.
    //The "M" nomenclature is from FIPS 180-3.  At the time the
    //SHA-512 rounds are done, the chars (below) are converted to words
    //(this field) so that the rounds can be done using the words.
    unsigned char buf[128];
    //We can't proceed to execute a round unless we have the 
    //full 1024 bits = 16 words = 128 bytes of data.  We must
    //buffer it because we can't count on being called with data
    //blocks that are a multiple of 128.  We may have data hanging
    //around between calls.  We fill up this buffer from the low
    //end, i.e. [0], then [1], then [2], etc.
};


//Result structure, used to hold result.  Caller is allowed to
//pick it apart.
//
struct SHA512_Sha512ResultStruct
{
    unsigned long long sha512_words[8];
    //Hash in binary form, as the 64-bit integers.
    char     sha512_chars[129];
    //Zero-terminated string containing character representation
    //of SHA-512 formed.
};


DECMOD_SHA512 void SHA512_Sha512StateStructOpen(struct SHA512_Sha512StateStruct *arg);
DECMOD_SHA512 void SHA512_Sha512StateStructAddData(struct    SHA512_Sha512StateStruct *arg,
                                                   void      *pointer_in,
                                                   unsigned  len);
DECMOD_SHA512 void SHA512_Sha512StateStructClose(struct SHA512_Sha512StateStruct  *state,
                                                 struct SHA512_Sha512ResultStruct *result);

DECMOD_SHA512 const char *SHA512_Vcinfo_C(void);
DECMOD_SHA512 const char *SHA512_Vcinfo_H(void);

#define SHA512_VCINFO_H  "$Revision: 1.7 $"

#if defined(P_TEST) || defined(P_TEST_SHA512)
DECMOD_SHA512 int SHA512_Test(void);
#endif

#endif

//----------------------------------------------------------------------------------------------------
//$Log: sha512.h,v $
//Revision 1.7  2012/03/30 00:20:15  dashley
//Edits.
//
//Revision 1.6  2012/03/29 23:44:01  dashley
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
//
//Revision 1.2  2012/03/12 02:54:01  dashley
//Edits.
//
//Revision 1.1  2012/03/11 21:01:46  dashley
//Initial checkin.
//----------------------------------------------------------------------------------------------------
// End of $RCSfile: sha512.h,v $.
//----------------------------------------------------------------------------------------------------
