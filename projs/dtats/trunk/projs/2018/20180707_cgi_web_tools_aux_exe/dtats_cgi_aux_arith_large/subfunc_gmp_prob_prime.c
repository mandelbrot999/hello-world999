//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools_aux_exe/dtats_cgi_aux_arith_large/subfunc_gmp_prob_prime.c 207 2018-07-15 21:50:56Z dashley $
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
//This module uses the GMP libary function:
//
//   mpz_probab_prime_p()
//
//To make a probabilistic assessment of whether an integer is most likely
//prime, definitely composite, etc.  This module is just a direct interface
//to the GMP function cited above.
//
//INPUT PARAMETERS
//----------------
//The subfunction accepts two parameters, the integers whose primality is to be
//assessed, and the number of reps (passed directly to the GMP function).
//Naturally, the integers should be positive.  Invalid integers are assigned
//defaults.  It is the responsibility of the calling script to do whatever
//sanity checking is desired.
//
//OUTPUT RESULTS
//--------------
//The notation below gives the outputs of the program.  In some cases, [i] notation
//is used to indicate line numbers.
//
//[01] An overall success or failure code for the operation.  Valid responses
//     are:
//        S      :  Success (for this subfunction, the only possible outcome).
//
//[02] The fully normalized first integer entered.  This means it has been
//     stripped of all weird characters, etc., and also perhaps assigned
//     a default value if the original parameter wasn't acceptable.
//     This can be used by the PHP script to repopulate form boxes.
//[03] The fully normalized second integer entered.
//[04] The output from the GMP function.  Semantics are:
//         2  -- definitely prime.
//         1  -- probably prime.
//         0  -- definitely composite.
//[05] "S", indicating success.
//
//Note that this subfunction will always return exactly five lines,
//and the first and last line will be "S".
//
//The return value (exit code) from this subfunction is always 0.
//

#define MODULE_SUBFUNC_GMP_PROB_PRIME

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <gmp.h>

#include "auxfuncs.h"
#include "subfunc_gmp_prob_prime.h"


int SUBFUNC_GMP_PROB_PRIME_main(int argc, char *argv[])
   {
   //Normalized first and second parameters (the integers).
   char *arg1;
   char *arg2;

   //GMP types to maintain the algorithm.
   int nreps_native;
   mpz_t number_to_test, nreps_mpz;

   //Result from the GMP.
   int gmp_result;

   //There must be an acceptable number of command-line arguments.   If not,
   //abort the progam with phony data.
   if (argc != 4)
      {
      printf("S\n2\n5\n2\nS\n");
      return(0);
      }

   //Copy the command-line arguments to a safe place where we can manipulate them.
   //Leave 2 characters of space in case we assign a "0".
   arg1 = (char *)malloc((AUXFUNCS_size_t_max(1, strlen(argv[2])) + 1) * sizeof(char));
   arg2 = (char *)malloc((AUXFUNCS_size_t_max(1, strlen(argv[3])) + 1) * sizeof(char));
   if ((arg1 == NULL) || (arg2 == NULL))
      {
      printf("S\n2\n5\n2\nS\n");
      return(0);
      }
   strcpy(arg1, argv[2]);
   strcpy(arg2, argv[3]);

   //Strip all of the non-digit trash out of the arguments.
   AUXFUNCS_remove_non_digits(arg1);
   AUXFUNCS_remove_non_digits(arg2);

   //Remove all leading zeros from both arguments.
   AUXFUNCS_remove_leading_zeros(arg1);
   AUXFUNCS_remove_leading_zeros(arg2);

   //If either argument is zero length, fill it in with 0.
   if (!strlen(arg1))
      strcpy(arg1, "0");
   if (!strlen(arg2))
      strcpy(arg2, "0");

   //We are not allowed to have 0's in this function, so
   //abort on zeros.  Also, we can't have 1 for a number to check,
   //as 1 is neither prime nor composite.
   if ((!strcmp(arg1, "0")) || (!strcmp(arg2, "0")) || (!strcmp(arg1, "1")))
      {
      printf("S\n2\n5\n2\nS\n");
      return(0);
      }

   //If either argument exceeds 10000 digits, abort.
   if ((strlen(arg1)>10000) || (strlen(arg2) > 10000))
      {
      printf("S\n2\n5\n2\nS\n");
      return(0);
      }

   //Initialize all of the GMP variables.
   mpz_init(number_to_test);
   mpz_init(nreps_mpz);

   //Assign a and b to initial values.
   mpz_set_str(number_to_test, arg1, 10);
   mpz_set_str(nreps_mpz,      arg2, 10);

   //We don't want to allow any more than 5000 repetitions for that
   //parameter.  So, if it is larger than 5000, whack it down.
   if (mpz_cmp_d(nreps_mpz, (double)5000) > 0)
      mpz_set_str(nreps_mpz, "5000", 10);

   //Extract the arbitrary length value of the number of reps into
   //a normal integer.
   nreps_native = mpz_get_si(nreps_mpz);

   //Run the GMP library function to guess at primality and get the result
   //back.
   gmp_result = mpz_probab_prime_p(number_to_test, nreps_native);

   //Now, write the output block.
   printf("S\n");
   mpz_out_str(stdout, 10, number_to_test);
   printf("\n");
   mpz_out_str(stdout, 10, nreps_mpz);
   printf("\n");
   printf("%d\n", gmp_result);
   printf("S\n");

   //Always return 0.
   return(0);
   }

//********************************************************************************
// End of SUBFUNC_GMP_PROB_PRIME.C.
//********************************************************************************
