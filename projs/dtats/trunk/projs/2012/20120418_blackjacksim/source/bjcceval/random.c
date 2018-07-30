//----------------------------------------------------------------------------------------------------
//$Header: /home/dashley/cvsrep/e3ft_gpl01/e3ft_gpl01/dtaipubs/cron/2010/blackjack_201010/source/bjcceval/random.c,v 1.7 2012/04/15 12:57:08 dashley Exp $
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
#define MODULE_RANDOM

#include "mt19937.h"
#include "random.h"

//Returns a single random bit as FALSE or TRUE.
//
//Unit-tested 20120411.  Unit-testing involved stepping
//through the function and observing behavior.
//
unsigned RANDOM_Bit(void)
{
   static unsigned nbitsavail = 0;
   static unsigned bit_buffer;
   unsigned rv;

   if (! nbitsavail)
   {
      bit_buffer = RANDOM_Uint32();
      nbitsavail = 32;
   }

   if (bit_buffer & 0x01)
   {
      rv = 1;
   }
   else
   {
      rv = 0;
   }

   bit_buffer >>= 1;
   nbitsavail--;

   return(rv);
}


//Returns a random unsigned integer.  Because the MT19937
//test vectors passed when the MT19937 code was added,
//this was not carefully unit-tested.
//
//However, a basic unit test involving 256 bins for modulo
//result and 256 bins for partition was performed.  The results
//seemed reasonable.
//
//Unit tested 20120411.
//
unsigned RANDOM_Uint32(void)
{
   unsigned rv;

   rv = MT19937_genrand_int32();

   return(rv);
}


//Returns a randomly-distributed value between min and max inclusive.
//
//20120411:  Unit-tested.  Attempted full statement coverage.
//
unsigned RANDOM_UintBounded32(unsigned min, unsigned max)
{
   unsigned diff; 
      //Difference between max and min values.
   unsigned span;
      //Number of different values that could be returned that would satisfy the
      //criteria of being between min and max, inclusive.
   unsigned max_random_allowed;
      //Max random value that would be of use to us.
   unsigned random_val;
      //The random value obtained.
   unsigned rv;
      //The value returned to the caller.

   //Swap min and max if they are reversed.
   if (min > max)
   {
      unsigned temp;

      temp = min;
      min  = max;
      max  = temp;
   }

   //Calculate parameters that parameterize the generation.
   diff = max  - min;
   span = diff + 1;            //Possible rollover to 0, but this case excluded below.
   
   if (diff == 0)
   {
      rv = min;                //We can choose only one value.  Choose it.
   }
   else if (diff == 0xFFFFFFFF)
   {
      rv = RANDOM_Uint32();    //The input parameters are 0 and 0xFFFFFFFF.  We can't
                               //safely calculate with this max range, so return without
                               //further calculation.
   }
   else
   {
      //At this point we can possibly "fold" or "equivalence class" 
      //any random integer we obtain to meet the interval.
      //
      //Figure out how big of a random unsigned integer would be useful to us.
      //
      //The correct expression for the maximum random integer that is useful to us is
      //
      //   0x100000000 - (0x100000000 mod span) - 1.
      //
      //This isn't easy to calculate with 32-bit arithmetic.
      //
      //   0xFFFFFFFF - (0x100000000 mod span)
      //
      //Note that 
      //
      //   (0x100000000 mod span) = ((0xFFFFFFFF mod span) + 1) mod span
      //
      //So the overall expression is:
      //
      //   0xFFFFFFFF - (((0xFFFFFFFF mod span) + 1) mod span)
      //
      max_random_allowed = 0xFFFFFFFF - (((0xFFFFFFFF % span) + 1) % span);

      do
      {
         random_val = RANDOM_Uint32();
      } while (random_val > max_random_allowed);

      rv = (random_val % span) + min;
   }
   
   return(rv);
}


//Returns a uniformly distributed signed integer.
//
//20120414:  Unit tested to be sure it attains test cases commented out below.
//
int RANDOM_Int32(void)
{
   unsigned ov;
   int      rv;

   //Because the distribution of an unsigned is uniform (no previous
   //value gives information about the next value) it should be
   //acceptable just to let an unsigned int be remapped as an int.
   ov = RANDOM_Uint32();
   rv = ov - 0x80000000;

   //Debugging trap to be sure values map correctly from unsigned to signed.
   //
   //if (     (ov == 0x00000000) || (ov == 0x00000001) || (ov == 0x7FFFFFFF) || (ov == 0x80000000) 
   //      || (ov == 0x80000001) || (ov == 0xFFFFFFFE) || (ov == 0xFFFFFFFF))
   //      {
   //      static unsigned count=0;
   //
   //      count++;
   //
   //      printf("----------\n");
   //      printf("Result #%u\n", count);
   //      printf("ov: %u rv: %d\n", ov, rv);
   //      printf("ov: %08X rv: %08X\n", ov, rv);
   //      }

   return(rv);
}


//Returns a random signed integer in the interval [min, max].
//
//20120415:  Several intervals checked.  Function seems OK, including intervals
//at negative and positive limits.
//
int RANDOM_IntBounded32(int min, int max)
{
   long long bigmin, bigmax, bigdiff;
   long long int ri;

   if (min > max)
   {
      int temp;

      temp = min;
      min  = max;
      max  = temp;
   }

   bigmin = min;
   bigmax = max;
   bigdiff = bigmax - bigmin;

   ri = RANDOM_UintBounded32(0, (unsigned)bigdiff);

   ri += bigmin;

   return((int)ri);
}


//Returns version control information for the .C file.
//
const char *RANDOM_Vcinfo_C(void)
{
    return("$Revision: 1.7 $");
}


//Returns version control for the .H file.
//
const char *RANDOM_Vcinfo_H(void)
{
    return(RANDOM_VCINFO_H);
}



#if defined(P_TEST) || defined(P_TEST_RANDOM)

int RANDOM_Test(void)
{
    return(1);
}

#endif

//----------------------------------------------------------------------------------------------------
//$Log: random.c,v $
//Revision 1.7  2012/04/15 12:57:08  dashley
//Unit testing performed.
//
//Revision 1.6  2012/04/12 01:51:57  dashley
//Edits.
//
//Revision 1.5  2012/04/11 03:31:51  dashley
//Edits.
//
//Revision 1.4  2012/03/30 00:20:14  dashley
//Edits.
//
//Revision 1.3  2012/03/29 23:44:01  dashley
//Edits.
//
//Revision 1.2  2012/03/15 23:38:08  dashley
//License text enhanced.
//
//Revision 1.1  2012/03/11 21:01:46  dashley
//Initial checkin.
//----------------------------------------------------------------------------------------------------
//End of $RCSfile: random.c,v $
//----------------------------------------------------------------------------------------------------
