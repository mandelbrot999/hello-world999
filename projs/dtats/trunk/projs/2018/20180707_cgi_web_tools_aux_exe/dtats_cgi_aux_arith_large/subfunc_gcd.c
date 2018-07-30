//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools_aux_exe/dtats_cgi_aux_arith_large/subfunc_gcd.c 207 2018-07-15 21:50:56Z dashley $
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
//This module is the GCD subfunction of a general-purpose CGI-BIN program to support
//number theory demonstration applications.
//
//INPUT PARAMETERS
//----------------
//The subfunction accepts two parameters, the integers whose GCD is to be
//calculated.  There is substantial tolerance for invalid characters.
//Naturally, the integers should be positive.
//
//OUTPUT RESULTS
//--------------
//The notation below gives the outputs of the program.  In some cases, [i] notation
//is used to indicate line numbers.
//
//[01] An overall success or failure code for the operation.  Valid responses
//     are:
//        S      :  Success.
//        EP1A   :  The first integer could not be parsed, which means it is ill-formatted.
//        EP1B   :  The first integer was zero or negative.
//        EP2A   :  The second integer could not be parsed, which means it is ill-formatted.
//        EP2B   :  The second integer was zero or negative.
//        EQ     :  Other or unspecified error.
//
//[02] The fully normalized first integer entered.  This means it has been
//     stripped of all weird characters, etc.  This can be used by the
//     PHP script to repopulate the form boxes.
//[03] The fully normalized second integer entered.
//
//In the event that the status code indicates error, no further lines
//will be written.
//
//[04] The round number of the application of Euclid's algorithm, starting
//     at "1".
//[05] "a".
//[06] "b".
//[07] a div b.
//[08] a mod b.
//[09] ... repeating sequence, starting back at [4] and repeating until a
//     zero remainder.
//[..] The GCD of the two integers.  This will be positive and
//     contain no commas or extraneous characters.
//[..] "S", indicating success.
//
//Note that as per the definition above, any valid non-error output from
//this program will contain a number of lines which is a multiple of 5.
//
//The return value (exit code) from this subfunction is always 0.
//

#define MODULE_SUBFUNC_GCD

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <gmp.h>

#include "auxfuncs.h"
#include "subfunc_gcd.h"

int SUBFUNC_GCD_main(int argc, char *argv[])
   {
   //Normalized first and second parameters (the integers).
   char *arg1;
   char *arg2;

   //GMP types to maintain the algorithm.
   int round;
   mpz_t alg_a, alg_b, alg_adivb, alg_amodb;

   //There must be an acceptable number of command-line arguments.
   if (argc != 4)
      {
      printf("EQ\n0\n0\n");
      return(0);
      }

   //Copy the command-line arguments to a safe place where we can manipulate them.
   //Leave 2 characters of space in case we assign a "0".
   arg1 = (char *)malloc((AUXFUNCS_size_t_max(1, strlen(argv[2])) + 1) * sizeof(char));
   arg2 = (char *)malloc((AUXFUNCS_size_t_max(1, strlen(argv[3])) + 1) * sizeof(char));
   if ((arg1 == NULL) || (arg2 == NULL))
      {
      printf("EQ\n%s\n%s\n", argv[2], argv[3]);
      exit(0);
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

   //If either argument exceeds 1000 digits, abort.
   if ((strlen(arg1)>1000) || (strlen(arg2) > 1000))
      {
      printf("EQ\n0\n0\n");
      return(0);
      }

   //If either argument is zero, abort.
   if (!strcmp(arg1, "0"))
      {
      printf("EP1B\n0\n0\n");
      return(0);
      }
   if (!strcmp(arg2, "0"))
      {
      printf("EP2B\n0\n0\n");
      return(0);
      }

   //Initialize all of the GMP variables.
   mpz_init(alg_a);
   mpz_init(alg_b);
   mpz_init(alg_adivb);
   mpz_init(alg_amodb);

   //Assign a and b to initial values.
   mpz_set_str(alg_a, arg1, 10);
   mpz_set_str(alg_b, arg2, 10);

   //We assume at this point that we will be successful.  Output
   //the header stuff.
   printf("S\n");
   mpz_out_str(stdout, 10, alg_a);
   printf("\n");
   mpz_out_str(stdout, 10, alg_b);
   printf("\n");

   //We require as an initial condition that a >= b.  Make
   //that happen.
   if (mpz_cmp(alg_a, alg_b) < 0)
      {
      mpz_swap(alg_a, alg_b);
      }

   //To make the algorithm cleaner, we preload for the first
   //assignment.
   mpz_set(alg_amodb, alg_b);
   mpz_set(alg_b,     alg_a);

   //Now begin the algorithm proper.
   round = 0;
   do
      {
      //We are at next round.
      round++;

      //Values for this round inherited from the last one.
      mpz_set(alg_a, alg_b);
      mpz_set(alg_b, alg_amodb);

      //Calculate the quotient and remainder.
      mpz_fdiv_qr(alg_adivb, alg_amodb, alg_a, alg_b);

      //Output all the data from the round.
      printf("%d\n", round);
      mpz_out_str(stdout, 10, alg_a);
      printf("\n");
      mpz_out_str(stdout, 10, alg_b);
      printf("\n");
      mpz_out_str(stdout, 10, alg_adivb);
      printf("\n");
      mpz_out_str(stdout, 10, alg_amodb);
      printf("\n");
      }
   while((round < 2000) && (mpz_sgn(alg_amodb) > 0));

   //The GCD canonically will be the last non-zero remainder.
   mpz_out_str(stdout, 10, alg_b);
   printf("\n");

   //Finally, we output the trailing "S".
   printf("S\n");

   return(0);
   }

//********************************************************************************
// End of SUBFUNC_GCD.C.
//********************************************************************************
