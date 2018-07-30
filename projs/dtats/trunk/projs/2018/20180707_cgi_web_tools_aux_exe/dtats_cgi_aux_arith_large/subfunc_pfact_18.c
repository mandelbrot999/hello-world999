//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools_aux_exe/dtats_cgi_aux_arith_large/subfunc_pfact_18.c 207 2018-07-15 21:50:56Z dashley $
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
//This module attempts to factor an integer of up to 18 decimal
//digits using a sieve method and subject to elapsed time constraints.
//The constraint of "up to 18 digits"
//is because that way trial divisors can stay in one unsigned
//integer, which speeds the division.  Additionally, there isn't
//much use in trying to factor larger integers on a web page.
//This subfunction is "parlor trivia" grade only.
//
//INPUT PARAMETERS
//----------------
//This subfunction accepts the following parameters, in order.
//
// (a) The number to factor.
//
// (b) The number of Miller-Rabin rounds to use when looking
//     at the probable primality of the original argument or of
//     residues.
//
// (c) The maximum time that should be allowed to elapse before the
//     program terminates (perhaps without finding factors).
//     This constraint is to protect the server capacity.  (In the long
//     term, however, the web page may need to be removed--if too many
//     people use it, it will bring any server to a crawl.)
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
//[04] The fully normalized second integer entered.
//[05] The type of factor specified on the next line.
//     Possibilities are:
//         "P"  :  The factor is definitely prime.
//         "C"  :  The factor is definitely composite.
//         "p"  :  The factor is probably prime, established by
//                 Miller-Rabin.
//
//     Note that the "C" code can only appear if the utility has to give
//     up because it runs out of allowed time.  This means that the input
//     number has not been fully factored or perhaps not factored at all.
//     The "C" code can only appear for the last factor or the only factor.
//
//     The "p" code can also only appear for the last factor.  This occurs when
//     either the original input argument is prime as established by
//     Miller-Rabin or else a division leaves a result that is similarly
//     established by Miller-Rabin.
//[06] The factor itself.
//[07] Its multiplicity.
//[..] Lines 5-7 are repeated for as many factors as are located.
//[..] The second-to-last line will contain "X".
//[..] The last line will contain an "S".
//
//Note the following:
//   (a) Any valid output will contain at least 9 lines.
//   (b) Any valid output will have a number of lines divisible by 3.
//   (c) The number of factors found is (nlines - 6)/3 or alternately
//       nlines/3 - 2.
//   (d) What happened can be determined using the number of lines plus
//       the code of the last factor.
//
//The return value (exit code) from this subfunction is always 0.
//

#define MODULE_SUBFUNC_PFACT_18

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <gmp.h>

#include "auxfuncs.h"
#include "subfunc_pfact_18.h"
#include "sieve_eratosthenes.h"


int SUBFUNC_PFACT_18_main(int argc, char *argv[])
   {
   //The time snapshot against which we compare to see if we're over
   //time budget.
   time_t time_snapshot;

   //Normalized first and second parameters (the integers).
   char *arg1;
   char *arg2;
   char *arg3;

   //Number of Miller-Rabin iterations to establish probable primality.
   int miller_rabin_iterations;

   //Maximum elapsed time allowed.
   int max_time;

   //Temporary iteration integers.
   int i;

   //Mask counter.  Only check for timeout periodically, as calling the OS to get time
   //is presumed expensive.
   int mask_counter;

   //The current trial divisor.
   unsigned long trial_divisor, new_trial_divisor;

   //The current sieve table index.
   int sieve_table_index;

   //An exit flag kept to remember if we should bail the loop.
   int exit_flag;

   //The number to factor.
   mpz_t number_to_factor;

   //The square root limit.  We only need to go that far.
   mpz_t square_root_limit;

   //The multiplicity of any factors we find.
   int multiplicity;

   //Initialize all of the GMP variables.
   mpz_init(number_to_factor);
   mpz_init(square_root_limit);

   //Grab a time snapshot.
   time_snapshot = time(NULL);

   //There must be an acceptable number of command-line arguments.   If not,
   //abort the progam with phony data.
   if (argc != 5)
      {
      printf("S\n2\n25\n2\nC\n2\n2\nX\nS\n");
      return(0);
      }

   //Copy the command-line arguments to a safe place where we can manipulate them.
   //Leave 2 characters of space in case we assign a "0".
   arg1 = (char *)malloc((AUXFUNCS_size_t_max(1, strlen(argv[2])) + 1) * sizeof(char));
   arg2 = (char *)malloc((AUXFUNCS_size_t_max(1, strlen(argv[3])) + 1) * sizeof(char));
   arg3 = (char *)malloc((AUXFUNCS_size_t_max(1, strlen(argv[4])) + 1) * sizeof(char));
   if ((arg1 == NULL) || (arg2 == NULL) || (arg3 == NULL))
      {
      printf("S\n2\n25\n2\nC\n2\n2\nX\nS\n");
      return(0);
      }
   strcpy(arg1, argv[2]);
   strcpy(arg2, argv[3]);
   strcpy(arg3, argv[4]);

   //Strip all of the non-digit trash out of the arguments.
   AUXFUNCS_remove_non_digits(arg1);
   AUXFUNCS_remove_non_digits(arg2);
   AUXFUNCS_remove_non_digits(arg3);

   //Remove all leading zeros from arguments.
   AUXFUNCS_remove_leading_zeros(arg1);
   AUXFUNCS_remove_leading_zeros(arg2);
   AUXFUNCS_remove_leading_zeros(arg3);

   //If an argument is zero length, fill it in with 0.
   if (!strlen(arg1))
      strcpy(arg1, "0");
   if (!strlen(arg2))
      strcpy(arg2, "0");
   if (!strlen(arg3))
      strcpy(arg3, "0");

   //We are not allowed to have 0's in this function, so
   //abort on zeros.  Also, we can't have 1 for a number to check,
   //as 1 can't be factored.
   if ((!strcmp(arg1, "0")) || (!strcmp(arg2, "0")) || (!strcmp(arg3, "0")) || (!strcmp(arg1, "1")))
      {
      printf("S\n2\n25\n2\nC\n2\n2\nX\nS\n");
      return(0);
      }

   //If the number to factor exceeds 18 digits, abort.  Anything that has
   //18 or fewer digits is allowed.
   if (strlen(arg1) >18)
      {
      printf("S\n2\n25\n2\nC\n2\n2\nX\nS\n");
      return(0);
      }

   //Assign the number to factor.  This is definitely a
   //GMP type.
   mpz_set_str(number_to_factor, arg1, 10);

   //Assign the number of Miller-Rabin repetitons to use, subject to an
   //absolute maximum of 1000 and minimum of 1.
   miller_rabin_iterations = 25;
   if (strlen(arg2) > 3)
      {
      miller_rabin_iterations = 1000;
      }
   else
      {
      sscanf(arg2, "%d", &miller_rabin_iterations);
      if (miller_rabin_iterations < 1)
    miller_rabin_iterations = 1;
      }

   //Assign the maximum time allowed, subject to a maximum of 1000 and minimum of 3.
   if (strlen(arg3) > 3)
      {
      max_time = 1000;
      }
   else
      {
      sscanf(arg3, "%d", &max_time);
      if (max_time < 3)
    max_time = 3;
      }

   //Output the header information before beginning the search.
   printf("S\n");
   mpz_out_str(stdout, 10, number_to_factor);
   printf("\n");
   printf("%d\n", miller_rabin_iterations);
   printf("%d\n", max_time);

   //Loop through the list of divisors we should try before starting the sieve.
   //This won't possibly exceed our time, so do it.
   for (i=0; i<SIEVE_ERATOSTHENES_N_SIEVE_FACTORS; i++)
      {
      multiplicity = 0;

      //printf("Trial divisor: %d\n", SIEVE_ERATOSTHENES_sieve_factors[i]);

      //Factor out all occurrences that we can.
      while (mpz_divisible_ui_p(number_to_factor, SIEVE_ERATOSTHENES_sieve_factors[i]))
    {
    mpz_divexact_ui(number_to_factor, number_to_factor, SIEVE_ERATOSTHENES_sieve_factors[i]);
    multiplicity++;
    }

      //Now output the information record to the stdout if we could factor it.
      if (multiplicity)
    {
         printf("P\n");
         printf("%u\n", SIEVE_ERATOSTHENES_sieve_factors[i]);
         printf("%d\n", multiplicity);
         }
      }

   //Gear up for tabulated operation as we sieve.
   new_trial_divisor = trial_divisor     = SIEVE_ERATOSTHENES_FIRST_TRIAL_DIVISOR;
   sieve_table_index                     = SIEVE_ERATOSTHENES_FIRST_SIEVE_INDEX;
   mask_counter                          = 0;

   //Set the exit flag initially.  One thing that could have
   //caused us to be ready to exit already is if we brought the
   //number to factor down to 1.  We check this now because
   //otherwise only check it when have factored something out and
   //seive loop would run indefinitely if didn't do this.
   exit_flag = 0;
   if (!mpz_cmp_ui(number_to_factor, 1))
      exit_flag = 1;

   //Effectively, we may have broken down the number to factor
   //with just a few operations.  So, effectively, we are
   //starting afresh here.  We only need to proceed to the
   //square root of the current number to factor (not the
   //original one.
   mpz_sqrt(square_root_limit, number_to_factor);

   //If the last value from the numbers to try before we start
   //the sieve is already past the square root limit, then whatever
   //remains is definitely prime, and we can exit.
   if (mpz_cmp_ui(square_root_limit,  SIEVE_ERATOSTHENES_sieve_factors[SIEVE_ERATOSTHENES_N_SIEVE_FACTORS - 1]) <= 0)
      {
      if (mpz_cmp_ui(number_to_factor, 1))
         {
    exit_flag = 1;
    printf("P\n");
         mpz_out_str(stdout, 10, number_to_factor);
         printf("\n");
    printf("1\n");
         goto done;
    }
     }

   //If Miller-Rabin says that the remaining number is probably prime, that is good
   //enough.
   if (mpz_probab_prime_p(number_to_factor, miller_rabin_iterations) == 1)
      {
      exit_flag = 1;
      printf("p\n");
      mpz_out_str(stdout, 10, number_to_factor);
      printf("\n");
      printf("1\n");
      goto done;
      }

   //Loop entry condition.
   multiplicity = 0;

   //This is the main loop.  We only check for elapsed time
   //infrequently.
   while (!exit_flag)
      {
      //Replace the trial divisor.
      trial_divisor = new_trial_divisor;

      //printf("Trial divisor: %d\n", trial_divisor);

      //Factor out all occurrences that we can of the trial divisor, if we can.
      while (mpz_divisible_ui_p(number_to_factor, trial_divisor))
    {
    mpz_divexact_ui(number_to_factor, number_to_factor, trial_divisor);
    multiplicity++;
    }

      //Now output the information record to the stdout if we could factor it.
      if (multiplicity)
    {
         printf("P\n");
         printf("%u\n", trial_divisor);
         printf("%d\n", multiplicity);

         //We need to calculate a new square root bound.
         mpz_sqrt(square_root_limit, number_to_factor);

         //If we are over the square root bound, the remaining number to factor
         //is prime and we should exit.
         if (mpz_cmp_ui(square_root_limit,  trial_divisor) <= 0)
       exit_flag = 1;

         //Are we over the time bound?  We might has well check here,
         //because finding prime factors is rare.
         if ((time(NULL) - time_snapshot) > max_time)
       exit_flag = 1;

         //Does the Miller-Rabin test say that the remaining number
         //is with near perfect certainty prime?
         if (mpz_probab_prime_p(number_to_factor, miller_rabin_iterations) >= 1)
       exit_flag = 1;

         //Is the remaining number "1", indicating we've factored it fully?
         if (!mpz_cmp_ui(number_to_factor, 1))
       exit_flag = 1;

         //Set multiplicity to zero again so don't re-enter until successful
         //division again.
         multiplicity = 0;
         }

      //Advance to our next trial divisor.
      new_trial_divisor = trial_divisor + SIEVE_ERATOSTHENES_sieve[sieve_table_index];

      //If the new is < the old, we've rolled over.  This means an exit is necessary.
      if (new_trial_divisor < trial_divisor)
    exit_flag = 1;

      //Advance the sieve index.
      sieve_table_index = (sieve_table_index + 1) % SIEVE_ERATOSTHENES_N_SIEVE;

      //This is our only chance to check for termination conditions that
      //don't come about from a successful division.  But we don't do
      //this often.
      mask_counter++;
      if (!(mask_counter & 0xFFFFF))
    {
         //First, have we exceeded the square root bound?
         if (mpz_cmp_ui(square_root_limit,  trial_divisor) <= 0)
       exit_flag = 1;
         //Second, are we over the time budget?
         if ((time(NULL) - time_snapshot) > max_time)
       exit_flag = 1;
    }
      }

   //If we've made it out of the loop, there are a variety of reasons for that.
   //Find the right one and close up.
   if (!mpz_cmp_ui(number_to_factor, 1))
      {
      //We divided the number down to 1.  There is nothing further to do.
      }
   else if (mpz_cmp_ui(square_root_limit,  trial_divisor) <= 0)
      {
      //We are at or over the square root limit.  The remaining number is definitely prime.
      printf("P\n");
      mpz_out_str(stdout, 10, number_to_factor);
      printf("\n");
      printf("1\n");
      }
   else if (mpz_probab_prime_p(number_to_factor, miller_rabin_iterations) == 0)
      {
      //Miller-Rabin says the remaining number is definitely composite.
      printf("C\n");
      mpz_out_str(stdout, 10, number_to_factor);
      printf("\n");
      printf("1\n");
      }
   else if (mpz_probab_prime_p(number_to_factor, miller_rabin_iterations) == 1)
      {
      //Miller-Rabin says the remaining number is probably prime.
      printf("p\n");
      mpz_out_str(stdout, 10, number_to_factor);
      printf("\n");
      printf("1\n");
      }
   else if (mpz_probab_prime_p(number_to_factor, miller_rabin_iterations) == 2)
      {
      //Miller-Rabin says the remaining number is definitely prime.
      printf("P\n");
      mpz_out_str(stdout, 10, number_to_factor);
      printf("\n");
      printf("1\n");
      }

   //Output the invariant footer information.
   done:
   printf("X\n");
   printf("S\n");

   //Always return 0.
   return(0);
   }

//********************************************************************************
// End of SUBFUNC_PFACT_18.C.
//********************************************************************************
