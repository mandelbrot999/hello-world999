//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools_aux_exe/dtats_cgi_aux_arith_large/sieve_eratosthenes.h 207 2018-07-15 21:50:56Z dashley $
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
#ifndef SIEVE_ERATOSTHENES_H_INCLUDED
   #define SIEVE_ERATOSTHENES_H_INCLUDED

   #ifdef MODULE_SIEVE_ERATOSTHENES
      #define DECMOD_SIEVE_ERATOSTHENES
   #else
      #define DECMOD_SIEVE_ERATOSTHENES extern
   #endif

   //Declare the factors which must be checked before using the table.
   #define  SIEVE_ERATOSTHENES_N_SIEVE_FACTORS                 (5)
   DECMOD_SIEVE_ERATOSTHENES
      const unsigned SIEVE_ERATOSTHENES_sieve_factors[SIEVE_ERATOSTHENES_N_SIEVE_FACTORS];

   //Declare the sieve table itself.
   #define  SIEVE_ERATOSTHENES_N_SIEVE                       (480)
   DECMOD_SIEVE_ERATOSTHENES
      const unsigned SIEVE_ERATOSTHENES_sieve[SIEVE_ERATOSTHENES_N_SIEVE];

   //Declare the first starting prime number to use in the trial divisions, and
   //after that is exhausted the index of the first table entry to use to advance
   //the trial divisor.
   #define  SIEVE_ERATOSTHENES_FIRST_TRIAL_DIVISOR            (13)
   #define  SIEVE_ERATOSTHENES_FIRST_SIEVE_INDEX               (1)

#endif /* SIEVE_ERATOSTHENES_H_INCLUDED */

//********************************************************************************
// End of SIEVE_ERATOSTHENES.H.
//********************************************************************************
