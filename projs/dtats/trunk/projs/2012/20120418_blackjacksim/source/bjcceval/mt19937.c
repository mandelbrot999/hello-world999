//----------------------------------------------------------------------------------------------------
//$Header: /home/dashley/cvsrep/e3ft_gpl01/e3ft_gpl01/dtaipubs/cron/2010/blackjack_201010/source/bjcceval/mt19937.c,v 1.3 2012/04/11 03:31:51 dashley Exp $
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
//Additionally, this source file (other than minor name changes and edits to customize it for the
//BJCCEVAL program) is based on the program downloaded from the website of Takuji Nishimura and 
//Makoto Matsumoto.  Their licensing conditions are reproduced verbatim below.
//----------------------------------------------------------------------------------------------------
//A C-program for MT19937, with initialization improved 2002/1/26.
//Coded by Takuji Nishimura and Makoto Matsumoto.
//
//Before using, initialize the state by using init_genrand(seed)  
//or init_by_array(init_key, key_length).
//
//Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
//All rights reserved.                          
//
//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions
//are met:
//
//  1. Redistributions of source code must retain the above copyright
//     notice, this list of conditions and the following disclaimer.
//
//  2. Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in the
//     documentation and/or other materials provided with the distribution.
//
//  3. The names of its contributors may not be used to endorse or promote 
//     products derived from this software without specific prior written 
//     permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//Any feedback is very welcome.
//http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
//email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
//----------------------------------------------------------------------------------------------------
#define MODULE_MT19937

#include <stdio.h>

#include "mt19937.h"

/* Period parameters */  
#define MT_19937_N 624
#define MT_19937_M 397
#define MT_19937_MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define MT_19937_UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define MT_19937_LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[MT_19937_N]; /* the array for the state vector  */
static int mti=MT_19937_N+1; /* mti==MT_19937_N+1 means mt[MT_19937_N] is not initialized */

/* initializes mt[MT_19937_N] with a seed */
static void MT19937_init_genrand(unsigned long s)
{
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<MT_19937_N; mti++) {
        mt[mti] = 
	    (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti); 
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
static void MT19937_init_by_array(unsigned long init_key[], int key_length)
{
    int i, j, k;
    MT19937_init_genrand(19650218UL);
    i=1; j=0;
    k = (MT_19937_N>key_length ? MT_19937_N : key_length);
    for (; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
          + init_key[j] + j; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++; j++;
        if (i>=MT_19937_N) { mt[0] = mt[MT_19937_N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=MT_19937_N-1; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
          - i; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++;
        if (i>=MT_19937_N) { mt[0] = mt[MT_19937_N-1]; i=1; }
    }

    mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */ 
}

/* generates a random number on [0,0xffffffff]-interval */
//
//DTA Note:  Because the code is commented to indicate it will provide initialization if
//the init function is not called, the init functions aren't made externally visible.
//It will perform well enough for my application with the default initialization, and in some
//ways it is advantageous to get the same stream of random numbers every time.  (And in some ways
//not advantageous.)
unsigned long MT19937_genrand_int32(void)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MT_19937_MATRIX_A};
    /* mag01[x] = x * MT_19937_MATRIX_A  for x=0,1 */

    if (mti >= MT_19937_N) { /* generate MT_19937_N words at one time */
        int kk;

        if (mti == MT_19937_N+1)   /* if MT19937_init_genrand() has not been called, */
            MT19937_init_genrand(5489UL); /* a default initial seed is used */

        for (kk=0;kk<MT_19937_N-MT_19937_M;kk++) {
            y = (mt[kk]&MT_19937_UPPER_MASK)|(mt[kk+1]&MT_19937_LOWER_MASK);
            mt[kk] = mt[kk+MT_19937_M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<MT_19937_N-1;kk++) {
            y = (mt[kk]&MT_19937_UPPER_MASK)|(mt[kk+1]&MT_19937_LOWER_MASK);
            mt[kk] = mt[kk+(MT_19937_M-MT_19937_N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[MT_19937_N-1]&MT_19937_UPPER_MASK)|(mt[0]&MT_19937_LOWER_MASK);
        mt[MT_19937_N-1] = mt[MT_19937_M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }
  
    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}


const char *MT19937_Vcinfo_C(void)
{
    return("$Revision: 1.3 $");
}


const char *MT19937_Vcinfo_H(void)
{
    return(MT19937_VCINFO_H);
}



#if defined(P_TEST) || defined(P_TEST_MT19937)

int MT19937_Test(void)
{
    return(1);
}

#endif

//----------------------------------------------------------------------------------------------------
//$Log: mt19937.c,v $
//Revision 1.3  2012/04/11 03:31:51  dashley
//Edits.
//
//Revision 1.2  2012/04/11 01:48:54  dashley
//Edits.
//
//Revision 1.1  2012/04/11 00:52:58  dashley
//Initial checkin.
//----------------------------------------------------------------------------------------------------
//End of $RCSfile: mt19937.c,v $
//----------------------------------------------------------------------------------------------------
