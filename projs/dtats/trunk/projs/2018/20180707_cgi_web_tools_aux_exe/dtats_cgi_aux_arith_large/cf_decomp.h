// $Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools_aux_exe/dtats_cgi_aux_arith_large/cf_decomp.h 207 2018-07-15 21:50:56Z dashley $
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
#ifndef CF_DECOMP_H_INCLUDED
   #define CF_DECOMP_H_INCLUDED

   #ifdef MODULE_CF_DECOMP
      #define DECMOD_CF_DECOMP
   #else
      #define DECMOD_CF_DECOMP extern
   #endif

#if 0
   //CHARACTER CLASSIFICATION FUNCTIONS.
   DECMOD_CF_DECOMP int CF_DECOMP_is_digit(char c);
   DECMOD_CF_DECOMP int CF_DECOMP_digit_to_val(char digit);
#endif

   /****************************************************************/
   /***   VERSION CONTROL REPORTING FUNCTIONS   ********************/
   /****************************************************************/
   DECMOD_CF_DECOMP const char *CF_DECOMP_cvcinfo(void);
   DECMOD_CF_DECOMP const char *CF_DECOMP_hvcinfo(void);

   /* Preprocessor string to allow the H-file version to be
   ** compiled into the C-file.
   */
   #define CF_DECOMP_H_VERSION ("$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools_aux_exe/dtats_cgi_aux_arith_large/cf_decomp.h 207 2018-07-15 21:50:56Z dashley $")

#endif /* CF_DECOMP_H_INCLUDED */

//********************************************************************************
// End of CF_DECOMP.H.
//********************************************************************************
