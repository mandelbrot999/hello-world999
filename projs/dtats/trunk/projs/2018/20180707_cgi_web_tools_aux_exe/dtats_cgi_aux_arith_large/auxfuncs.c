//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools_aux_exe/dtats_cgi_aux_arith_large/auxfuncs.c 207 2018-07-15 21:50:56Z dashley $
//********************************************************************************
//Copyright (c) 2003, 2018 David T. Ashley.
//********************************************************************************
//This file is part of "arith_large_cgi", a program that is designed to be
//invoked by a PHP script as part of serving a web page that performs
//calculations involving large integers.  (A secondary compiled program is
//used because a compiled program can perform certain  calculation-intensive
//tasks far more efficiently than a PHP script.)  This program is provided by
//David T. Ashley (dashley@gmail.com) under the MIT License (reproduced
//immediately below).
//********************************************************************************
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
//********************************************************************************
//
#define MODULE_AUXFUNCS

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "auxfuncs.h"


/******************************************************************/
/***  CHARACTER CLASSIFICATION FUNCTIONS   ************************/
/******************************************************************/
int AUXFUNCS_is_digit(char c)
   {
   if ((c >= '0') && (c <= '9'))
      return(1);
   else
      return(0);
   }

int AUXFUNCS_digit_to_val(char digit)
{
  switch (digit)
    {
    case '0':  return(0);
      break;
    case '1':  return(1);
      break;
    case '2':  return(2);
      break;
    case '3':  return(3);
      break;
    case '4':  return(4);
      break;
    case '5':  return(5);
      break;
    case '6':  return(6);
      break;
    case '7':  return(7);
      break;
    case '8':  return(8);
      break;
    case '9':  return(9);
      break;
    default:   return(-1);
      break;
    }
}

/******************************************************************/
/***  INTEGER SIZE_T FUNCTIONS             ************************/
/******************************************************************/
size_t AUXFUNCS_size_t_min(size_t a, size_t b)
   {
   if (a < b)
      return(a);
   else
      return(b);
   }

size_t AUXFUNCS_size_t_max(size_t a, size_t b)
   {
   if (a > b)
      return(a);
   else
      return(b);
   }


/******************************************************************/
/***  CONTRACTING STRING FUNCTIONS  *******************************/
/******************************************************************/
void AUXFUNCS_remove_non_digits(char *s)
   {
   char *src;
   char *dst;

   src = s;
   dst = s;

   while(*src)
      {
      if (AUXFUNCS_is_digit(*src))
         {
    *dst = *src;
    dst++;
    }
      src++;
      }

   *dst = 0;
   }

void AUXFUNCS_remove_leading_zeros(char *s)
   {
   char *src;
   char *dst;

   src = s;
   dst = s;

   while((*src) && (*src == '0'))
      {
      src++;
      }

   while(*src)
      {
      *dst = *src;
      src++;
      dst++;
      }

   *dst = 0;
   }


/******************************************************************/
/***  VERSION CONTROL IDENTITY FUNCTIONS   ************************/
/******************************************************************/
const char *AUXFUNCS_cvcinfo(void)
   {
   return("$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools_aux_exe/dtats_cgi_aux_arith_large/auxfuncs.c 207 2018-07-15 21:50:56Z dashley $");
   }

const char *AUXFUNCS_hvcinfo(void)
   {
   return(AUXFUNCS_H_VERSION);
   }

//********************************************************************************
// End of AUXFUNCS.C.
//********************************************************************************
