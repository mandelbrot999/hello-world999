//$Header: svn://localhost/dtapublic/projs/ets/trunk/src/lib_c/c_datd/bstrfunc.c 71 2016-11-05 11:07:06Z dashley $
//-------------------------------------------------------------------------------------------------
//This file is part of "David T. Ashley's Shared Source Code", a set of shared components
//integrated into many of David T. Ashley's projects.
//-------------------------------------------------------------------------------------------------
//This source code and any program in which it is compiled/used is provided under the MIT License,
//reproduced below.
//-------------------------------------------------------------------------------------------------
//Permission is hereby granted, free of charge, to any person obtaining a copy of
//this software and associated documentation files(the "Software"), to deal in the
//Software without restriction, including without limitation the rights to use,
//copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the
//Software, and to permit persons to whom the Software is furnished to do so,
//subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
//-------------------------------------------------------------------------------------------------
#define MODULE_BSTRFUNC

#include <assert.h>
#include <malloc.h>
#include <process.h>
#include <stddef.h>
#include <string.h>


#if defined(APP_TYPE_SIMPLE_DOS_CONSOLE)
   #include "ccmalloc.h"
#elif defined(APP_TYPE_IJUSCRIPTER_IJUCONSOLE)
   #include "tclalloc.h"
#else
   /* Do nothing. */
#endif

#include "bstrfunc.h"
#include "ccmalloc.h"
#include "charfunc.h"


/******************************************************************/
/***  CUSTOM ALLOCATION FUNCTIONS   *******************************/
/******************************************************************/
//We need wrappers because this software module will be used in
//more than one kind of software.  This could also be done with
//macros, but I like function wrappers better because there
//is less ambiguity and more ability to collect information if
//something goes wrong.
//
//07/24/01:  Visual inspection only.  Function deemed too 
//simple for unit testing.
void *BSTRFUNC_malloc( size_t size )
   {
   #if defined(APP_TYPE_SIMPLE_DOS_CONSOLE)
      return(CCMALLOC_malloc(size));
   #elif defined(APP_TYPE_IJUSCRIPTER_IJUCONSOLE)
      return(TclpAlloc(size));
   #else
      return(malloc(size));
   #endif 
   }


//07/24/01:  Visual inspection only.  Function deemed too 
//simple for unit testing.
void *BSTRFUNC_calloc( size_t num, size_t size )
   {
   #if defined(APP_TYPE_SIMPLE_DOS_CONSOLE)
      return(CCMALLOC_calloc(num, size));
   #elif defined(APP_TYPE_IJUSCRIPTER_IJUCONSOLE)
      return(TclpCalloc(num, size));
   #else
      return(calloc(num, size));
   #endif 
   }


//07/24/01:  Visual inspection only.  Function deemed too 
//simple for unit testing.
void *BSTRFUNC_realloc( void *memblock, size_t size )
   {
   #if defined(APP_TYPE_SIMPLE_DOS_CONSOLE)
      return(CCMALLOC_realloc(memblock, size));
   #elif defined(APP_TYPE_IJUSCRIPTER_IJUCONSOLE)
      return(TclpRealloc(memblock, size));
   #else
      return(realloc(memblock, size));
   #endif 
   }


//07/24/01:  Visual inspection only.  Function deemed too 
//simple for unit testing.
void BSTRFUNC_free( void *memblock )
   {
   #if defined(APP_TYPE_SIMPLE_DOS_CONSOLE)
      CCMALLOC_free(memblock);
   #elif defined(APP_TYPE_IJUSCRIPTER_IJUCONSOLE)
      TclpFree(memblock);
   #else
      free(memblock);
   #endif 
   }


//07/18/01:  Visual inspection and unit tests passed.
int BSTRFUNC_is_uint_wo_commas(const char *arg)
   {
   assert(arg != NULL);

   if (!*arg)
      return(0);

   if (arg[0] == '0')
      {
      if (arg[1])
         {
         return(0);
         }
      else
         {
         return(1);
         }
      }
   else
      {
      while (*arg)
         {
         if ((*arg < '0') || (*arg > '9'))
            return(0);
         arg++;
         }

      return(1);
      }
   }


//07/28/01:  Visual inspection only.
int BSTRFUNC_is_sint_wo_commas(const char *arg)
   {
   //This function will use its unsigned counterpart.
   //
   //Eyeball the input parameter.
   assert(arg != NULL);

   if (!*arg)  //Empty string ain't an integer.
      return(0);

   if (*arg == '-')
      {
      if (arg[1] == '0')
         return(0);
      else
        return(BSTRFUNC_is_uint_wo_commas(arg+1));
      }
   else
      {
      return(BSTRFUNC_is_uint_wo_commas(arg));
      }
   }


//07/18/01:  Visual inspection and unit tests passed.
int BSTRFUNC_is_uint_w_commas(const char *arg)
   {
   int state;

   //Input pointer cannot be NULL.
   assert(arg != NULL);

   //Can't be empty string.
   if (!*arg)
      return(0);

   //If the first digit is 0, that must be the only digit.
   if (arg[0] == '0')
      {
      if (arg[1])
         {
         return(0);
         }
      else
         {
         return(1);
         }
      }

   //The remainder of this function is an efficient state
   //machine recognizer.  The state machine involved is
   //pretty simple and was drawn and discarded on a sheet
   //of paper.  It doesn't need to be filed because it is
   //so basic.
   if ((*arg < '0') || (*arg > '9'))
      return(0);

   state = 0;
   arg++;

   while(1)
      {
      switch (state)
         {
         case 0 : if (!*arg)
                     {
                     return(1);
                     }
                  else if (*arg == ',')
                     {
                     state = 3;
                     }
                  else if ((*arg >= '0') && (*arg <= '9'))
                     {
                     state = 1;
                     }
                  else
                     {
                     return(0);
                     }
                  break;
         case 1 : if (!*arg)
                     {
                     return(1);
                     }
                  else if (*arg == ',')
                     {
                     state = 3;
                     }
                  else if ((*arg >= '0') && (*arg <= '9'))
                     {
                     state = 2;
                     }
                  else
                     {
                     return(0);
                     }
                  break;
         case 2 : if (!*arg)
                     {
                     return(1);
                     }
                  else if (*arg == ',')
                     {
                     state = 3;
                     }
                  else if ((*arg >= '0') && (*arg <= '9'))
                     {
                     return(0);
                     }
                  else
                     {
                     return(0);
                     }
                  break;
         case 3 : if (!*arg)
                     {
                     return(0);
                     }
                  else if (*arg == ',')
                     {
                     return(0);
                     }
                  else if ((*arg >= '0') && (*arg <= '9'))
                     {
                     state = 4;
                     }
                  else
                     {
                     return(0);
                     }
                  break;
         case 4 : if (!*arg)
                     {
                     return(0);
                     }
                  else if (*arg == ',')
                     {
                     return(0);
                     }
                  else if ((*arg >= '0') && (*arg <= '9'))
                     {
                     state = 5;
                     }
                  else
                     {
                     return(0);
                     }
                  break;
         case 5 : if (!*arg)
                     {
                     return(0);
                     }
                  else if (*arg == ',')
                     {
                     return(0);
                     }
                  else if ((*arg >= '0') && (*arg <= '9'))
                     {
                     state = 6;
                     }
                  else
                     {
                     return(0);
                     }
                  break;
         case 6 : if (!*arg)
                     {
                     return(1);
                     }
                  else if (*arg == ',')
                     {
                     state = 3;
                     }
                  else if ((*arg >= '0') && (*arg <= '9'))
                     {
                     return(0);
                     }
                  else
                     {
                     return(0);
                     }
                  break;
         default:
                  abort();
                  break;
         }

      arg++;
      }
     
   //We should never get here.
   }


//07/28/01:  Visual inspection only.
int BSTRFUNC_is_sint_w_commas(const char *arg)
   {
   //This function will use its unsigned counterpart.
   //
   //Eyeball the input parameter.
   assert(arg != NULL);

   if (!*arg)  //Empty string ain't an integer.
      return(0);

   if (*arg == '-')
      {
      if (arg[1] == '0')
         return(0);
      else
        return(BSTRFUNC_is_uint_w_commas(arg+1));
      }
   else
      {
      return(BSTRFUNC_is_uint_w_commas(arg));
      }
   }


//07/18/01:  Visual verification only due to simplicity.
void BSTRFUNC_str_reverse(char *s)
   {
   int l, begin, end;
   char temp;

   assert(s != NULL);

   l = strlen(s);

   begin = 0;
   end = l-1;

   while ((end-begin) >=1)
      {
      temp = s[begin];
      s[begin] = s[end];
      s[end] = temp;
      begin++;
      end--;
      }
   }


void BSTRFUNC_parse_gen_sci_not_num(const char *s,
                                    int *failure,
                                    char *mant_sign,
                                    size_t *mant_bdp,
                                    size_t *mant_bdp_len,
                                    size_t *mant_adp,
                                    size_t *mant_adp_len,
                                    char *exp_sign,
                                    size_t *exp,
                                    size_t *exp_len)
   {
   //For the parameters that can be NULL, these are the
   //local copies we keep.  We will assign these back to
   //the caller's area when appropriate before we leave.
   char i_mant_sign, i_exp_sign;
   size_t i_mant_bdp, i_mant_bdp_len, i_mant_adp, i_mant_adp_len,
          i_exp, i_exp_len;
   size_t i;
   int state;
   const char *arg;

   //Check out the parameters that can't be NULL.
   assert(s != NULL);
   assert(failure != NULL);

   //Initialize all variables to defaults.
   *failure           =  0 ;
   i_mant_sign        = 'N';
   i_exp_sign         = 'N';
   i_mant_bdp         =  0 ;
   i_mant_bdp_len     =  0 ;
   i_mant_adp         =  0 ;
   i_mant_adp_len     =  0 ;
   i_exp              =  0 ;
   i_exp_len          =  0 ;
   i                  =  0 ;
   state              =  0 ;

   //Process the string.  This is a big 10-state state
   //machine.  Because of the complexity, I've included
   //some state definitions as well in the comments.
   arg = s;

   while(1)
      {
      switch (state)
         {
         //Initial state from which we start processing.
         case 0 : if (!*arg)
                     {
                     //The string is empty.  This is not OK.
                     //Error out.
                     *failure = 1;
                     goto term_seq;
                     }
                  else if (*arg == '-')
                     {
                     //Leading - on the number.  Fine.
                     i_mant_sign = '-';
                     state = 1;
                     }
                  else if (*arg == '+')
                     {
                     //Leading + on the number.  Fine.
                     i_mant_sign = '+';
                     state = 2;
                     }
                  else if (*arg == '.')
                     {
                     //Leading . on the number.  Fine.
                     state = 5;
                     }
                  else if (*arg == '0')
                     {
                     i_mant_bdp = arg - s;
                     state = 4;
                     }
                  else if ((*arg >= '1') && (*arg <= '9'))
                     {
                     i_mant_bdp = arg - s;
                     state = 3;
                     }
                  else
                     {
                     //Unidentifiable crap.  This is not OK.
                     //Error out.
                     *failure = 1;
                     goto term_seq;
                     }
                  break;
         //The leading character of the string was '-'.  We
         //are processing a negative number.
         case 1 : if (!*arg)
                     {
                     //The string is empty.  This is not OK because
                     //it means the string was "-".
                     //Error out.
                     *failure = 1;
                     goto term_seq;
                     }
                  else if (*arg == '.')
                     {
                     //We have a - followed by a decimal point.
                     //This is impolite form, but will accept
                     //it as a number.
                     state = 5;
                     }
                  else if (*arg == '0')
                     {
                     //We have a '-' followed by a '0'.
                     //Seems reasonable.
                     i_mant_bdp = arg - s;
                     state = 4;
                     }
                  else if ((*arg >= '1') && (*arg <= '9'))
                     {
                     //We have a '-' followed by a non-zero
                     //digit.  Seems reasonable.
                     i_mant_bdp = arg - s;
                     state = 3;
                     }
                  else
                     {
                     //Unidentifiable crap.  This is not OK.
                     //Error out.
                     *failure = 1;
                     goto term_seq;
                     }
                  break;
         //The leading character of the string was '+'.  We
         //are processing an explicitly declared positive number.
         case 2 : if (!*arg)
                     {
                     //The string is empty.  This is not OK because
                     //it means the string was "+".
                     //Error out.
                     *failure = 1;
                     goto term_seq;
                     }
                  else if (*arg == '.')
                     {
                     //We have a + followed by a decimal point.
                     //This is impolite form, but will accept
                     //it as a number.
                     state = 5;
                     }
                  else if (*arg == '0')
                     {
                     //We have a '-' followed by a '0'.
                     //Seems reasonable.
                     i_mant_bdp = arg - s;
                     state = 4;
                     }
                  else if ((*arg >= '1') && (*arg <= '9'))
                     {
                     //We have a '+' followed by a non-zero
                     //digit.  Seems reasonable.
                     i_mant_bdp = arg - s;
                     state = 3;
                     }
                  else
                     {
                     //Unidentifiable crap.  This is not OK.
                     //Error out.
                     *failure = 1;
                     goto term_seq;
                     }
                  break;
         //We've encountered a non-zero digit either first as part
         //of the string or later after + or -.  We are processing
         //a mantissa that does not begin with "0".
         case 3 : if (!*arg)
                     {
                     //We've reached the end of the string.  This is 
                     //fine because we have a simple integer of the
                     //form NNNN, +NNNN, or -NNNN.  No problem with that.
                     i_mant_bdp_len = (arg - s) - i_mant_bdp;
                     *failure = 0;
                     goto term_seq;
                     }
                  else if (*arg == '.')
                     {
                     //Number followed by decimal point.  This
                     //means the mantissa is terminating.  No issue.
                     i_mant_bdp_len = (arg - s) - i_mant_bdp;
                     state = 5;
                     }
                  else if ((*arg >= '0') && (*arg <= '9'))
                     {
                     //Yet more digits.  Seems reasonable.
                     //The assignment isn't necessary, but it
                     //is aesthetic.
                     state = 3;
                     }
                  else if ((*arg == 'e') || (*arg == 'E'))
                     {
                     //Beginning of an exponent.  This again
                     //means the mantissa is terminating.  No issue.
                     i_mant_bdp_len = (arg - s) - i_mant_bdp;
                     state = 6;
                     }
                  else
                     {
                     //Unidentifiable crap.  This is not OK.
                     //Error out.
                     *failure = 1;
                     goto term_seq;
                     }
                  break;
         //We're processing a mantissa that begins with zero.  There
         //is only one zero allowed before the decimal point.
         case 4 : if (!*arg)
                     {
                     //We've reached the end of the string.  This is 
                     //fine because it means we have zero.  I'm going
                     //to be unusually permissive and allow -0 and +0,
                     //which isn't traditional.
                     i_mant_bdp_len = (arg - s) - i_mant_bdp;
                     *failure = 0;
                     goto term_seq;
                     }
                  else if (*arg == '.')
                     {
                     //Zero followed by decimal point.  This
                     //means the mantissa is terminating.  No issue.
                     i_mant_bdp_len = (arg - s) - i_mant_bdp;
                     state = 5;
                     }
                  else if ((*arg == 'e') || (*arg == 'E'))
                     {
                     //Beginning of an exponent.  This again
                     //means the mantissa is terminating.  No issue.
                     i_mant_bdp_len = (arg - s) - i_mant_bdp;
                     state = 6;
                     }
                  else
                     {
                     //Unidentifiable crap.  This is not OK.
                     //Error out.
                     *failure = 1;
                     goto term_seq;
                     }
                  break;
                  //A decimal point has been found in the string.
                  //This marks the end of the mantissa, for sure.
         case 5 : if (!*arg)
                     {
                     //We've reached the end of the string.  There are
                     //two possibilities here.  Either there have been no
                     //digits before the decimal points, which is a no-no,
                     //or there have been digits, which is fine.
                     if (i_mant_bdp_len)
                        {
                        *failure = 0;
                        goto term_seq;
                        }
                     else
                        {
                        *failure = 1;
                        goto term_seq;
                        }
                     }
                  else if ((*arg >= '0') && (*arg <= '9'))
                     {
                     //Digits after the decimal point.  Need to
                     //begin the portion after the decimal point.
                     i_mant_adp = arg - s;
                     state = 10;
                     }
                  else if ((*arg == 'e') || (*arg == 'E'))
                     {
                     //Beginning of an exponent.  This means
                     //that have no digits after the decimal point. 
                     //This is OK.
                     state = 6;
                     }
                  else
                     {
                     //Unidentifiable crap.  This is not OK.
                     //Error out.
                     *failure = 1;
                     goto term_seq;
                     }
                  break;
                 //The exponent has begin.
         case 6: if (!*arg)
                     {
                     //The string is empty.  This is not OK
                     //because it would mean an E with nothing
                     //following it.  This is a no-no.
                     //Error out.
                     *failure = 1;
                     goto term_seq;
                     }
                  else if (*arg == '-')
                     {
                     //Leading - on the exponent.  Fine.
                     i_exp_sign = '-';
                     state = 8;
                     }
                  else if (*arg == '+')
                     {
                     //Leading + on the exponent.  Fine.
                     i_exp_sign = '+';
                     state = 7;
                     }
                  else if ((*arg >= '0') && (*arg <= '9'))
                     {
                     //Beginning the digits of the exponent.  Fine.
                     i_exp = arg - s;
                     state = 9;
                     }
                  else
                     {
                     //Unidentifiable crap.  This is not OK.
                     //Error out.
                     *failure = 1;
                     goto term_seq;
                     }
                  break;

                  //Had a + sign before the exponent.  Now expecting digits.
         case  7: if (!*arg)
                     {
                     //The string is empty.  This is not OK
                     //because it would mean an E+ with nothing
                     //following it.  This is a no-no.
                     //Error out.
                     *failure = 1;
                     goto term_seq;
                     }
                  else if ((*arg >= '0') && (*arg <= '9'))
                     {
                     //Beginning the digits of the exponent.  Fine.
                     i_exp = arg - s;
                     state = 9;
                     }
                  else
                     {
                     //Unidentifiable crap.  This is not OK.
                     //Error out.
                     *failure = 1;
                     goto term_seq;
                     }
                  break;
                  //Had a - sign before the exponent.  Now expecting digits.
         case  8: if (!*arg)
                     {
                     //The string is empty.  This is not OK
                     //because it would mean an E- with nothing
                     //following it.  This is a no-no.
                     //Error out.
                     *failure = 1;
                     goto term_seq;
                     }
                  else if ((*arg >= '0') && (*arg <= '9'))
                     {
                     //Beginning the digits of the exponent.  Fine.
                     i_exp = arg - s;
                     state = 9;
                     }
                  else
                     {
                     //Unidentifiable crap.  This is not OK.
                     //Error out.
                     *failure = 1;
                     goto term_seq;
                     }
                  break;
                  //Had one digit of exponent.  Am processing remaining ones.
         case 9 : if (!*arg)
                     {
                     //We've reached the end of the string.  This is 
                     //fine because we have an exponent of the
                     //form NNNN, +NNNN, or -NNNN.  No problem with that.
                     i_exp_len = (arg - s) - i_exp;
                     *failure = 0;
                     goto term_seq;
                     }
                  else if ((*arg >= '0') && (*arg <= '9'))
                     {
                     //Yet more digits.  Seems reasonable.
                     //The assignment isn't necessary, but it
                     //is aesthetic.
                     state = 9;
                     }
                  else
                     {
                     //Unidentifiable crap.  This is not OK.
                     //Error out.
                     *failure = 1;
                     goto term_seq;
                     }
                  break;
                  //Processing digits after decimal point.  This state is out
                  //of sequence because added it after on diagram.
         case 10: if (!*arg)
                     {
                     //We've reached the end of the string.  This is 
                     //fine.
                     i_mant_adp_len = (arg - s) - i_mant_adp;
                     *failure = 0;
                     goto term_seq;
                     }
                  else if ((*arg >= '0') && (*arg <= '9'))
                     {
                     //Yet more digits.  Seems reasonable.
                     //The assignment isn't necessary, but it
                     //is aesthetic.
                     state = 10;
                     }
                  else if ((*arg == 'e') || (*arg == 'E'))
                     {
                     //Beginning of an exponent.  This terminates
                     //the digits after the decimal point.
                     i_mant_adp_len = (arg - s) - i_mant_adp;
                     state = 6;
                     }
                  else
                     {
                     //Unidentifiable crap.  This is not OK.
                     //Error out.
                     *failure = 1;
                     goto term_seq;
                     }
                  break;
         default:
                  abort();
                  break;
         }

      arg++;
      }


   //This is the setup for returning to the caller.  We can
   //only fill in those data pointer for the caller that are
   //not NULL.
   term_seq:
   if (mant_sign)
      *mant_sign = i_mant_sign;
   if (mant_bdp)
      *mant_bdp = i_mant_bdp;
   if (mant_bdp_len)
      *mant_bdp_len = i_mant_bdp_len;
   if (mant_adp)
      *mant_adp = i_mant_adp;
   if (mant_adp_len)
      *mant_adp_len = i_mant_adp_len;
   if (exp_sign)
      *exp_sign = i_exp_sign;
   if (exp)
      *exp = i_exp;
   if (exp_len)
      *exp_len = i_exp_len;
   }


//07/18/01:  Has passed visual verification plus unit tests.
void BSTRFUNC_commanate(char *s)
   {
   int l;
   int ncommas;
   char *putpt, *getpt;
   int ndigits;

   //Adds commas to a numeric string.  The space
   //must exist in the area passed.
   assert(s);

   //If the leading character on the string is a 
   //'-', bump the pointer.  Then everything
   //else applies as for an unsigned.
   if (*s == '-')
     s++;

   //Be sure the string currently meets the syntax for
   //a signed integer.  If not, don't even touch it.
   if (!BSTRFUNC_is_uint_wo_commas(s))
      return;

   //Get the length of the current string.
   l = strlen(s);

   //Let's agree, just in case something slipped through
   //the cracks, that zero length strings are not of
   //interest to us.
   if (l==0)
     return;

   //The number of commas to add is precisely 
   //(N-1) div 3.
   if (l==0)
      ncommas = 0;
   else
      ncommas = (l-1)/3;

   //Walk through the string, adding commas.
   getpt = s + l - 1;
   putpt = s + l + ncommas;

   *putpt = 0; //Write the zero terminator.
   putpt--;

   ndigits = 0;

   while ((putpt > s) && (getpt > s))
      {
      *putpt = *getpt;
      putpt--;
      getpt--;
      ndigits++;
      if (((ndigits % 3) == 0) && (putpt != s))
         {
         *putpt = ',';
         putpt--;
         }
      assert((putpt >= s) && (getpt>=s));
      }
   }


//07/28/01:  Visual inspection only.
void BSTRFUNC_decommanate(char *s)
   {
   char *src, *dst;

   assert(s != NULL);

   src = dst = s;

   while(1)
      {
      if (!*src)
         {
         *dst = 0;
         break;
         }
      else if (*src == ',')
         {
         src++;
         }
      else
         {
         *dst = *src;
         src++;
         dst++;
         }
      }
   }


void BSTRFUNC_parse_str_to_uint32(const char *s, 
                                  unsigned int *rv, 
                                  int *error)
   {
   unsigned _int64 temp;
   int digval;

   //Eyeball the input arguments.
   assert(s != NULL);
   assert(error != NULL);

   //Start off believing there is no error.
   *error = 0;

   //The string has to parse out as an unsigned integer or an
   //unsigned integer with commas, or we won't touch it.
   if (!BSTRFUNC_is_uint_wo_commas(s) && !BSTRFUNC_is_uint_w_commas(s))
      {
      *error = 1;
      return;
      }

   //OK, we know we have an unsigned integer, either without commas,
   //or with properly placed commas.  Our only worry now is that it
   //is of a size that will fit in 32 bits.  The way we can deal with
   //this is to format it into 64 bits and watch for overflow.
   temp = 0;

   while (*s)
      {
      digval = CHARFUNC_digit_to_val(*s);
      if (digval >= 0)
         {
         temp *= 10;
         temp += digval;
         if ((temp >> 32) & 0xFFFFFFFF)
            {
            //We've had an overflow.
            *error = 1;
            return;
            }
         }
      s++;
      }

   *rv = (unsigned int)temp;
   }


const char *BSTRFUNC_cvcinfo(void)
   {
   return("$Header: svn://localhost/dtapublic/projs/ets/trunk/src/lib_c/c_datd/bstrfunc.c 71 2016-11-05 11:07:06Z dashley $");
   }


const char *BSTRFUNC_hvcinfo(void)
   {
   return(BSTRFUNC_H_VERSION);
   }

//End of bstrfunc.c.
