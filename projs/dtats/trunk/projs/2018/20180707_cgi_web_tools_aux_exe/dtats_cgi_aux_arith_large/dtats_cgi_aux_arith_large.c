//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools_aux_exe/dtats_cgi_aux_arith_large/dtats_cgi_aux_arith_large.c 207 2018-07-15 21:50:56Z dashley $
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
//This program is written exclusively to support a PHP script which must calculate and
//display a number of number theory results.  The necessity of this script
//(rather than using BCMATH) comes about because SourceForge does not have
//bcmath installed on its PHP system.
//
//This program is meant to be called by the PHP script using the exec()
//call, but could also be run by hand (and in fact this method is used for testing).
//
//The first parameter after the program name is the suboperation to be performed
//(each CGI page probably uses a different suboperation).  This program
//will return a non-zero exit code only if there is a missing or unrecognized
//suboperation.  Otherwise, error reporting is controlled by the rules of the
//suboperation.
//
//The currently defined suboperations are:
//
//   a)"help"
//     Display information about what the program is and how to use
//     it.
//   b)"gcd"
//     Calculate the gcd of two integers using Euclid's classic
//     algorithm and also display the intermediate results.
//   c)"gmp_prob_prime"
//     Use Miller-Rabin to determine to high certainty whther a
//     number is prime or composite.
//   d)"pfact_18"
//     Attempt to factor a number of 18 decimal digits or less into
//     component primes.
//   e)"cfbrap"
//     Finds the best rational approximation to a rational number subject
//     to constraints on the denominator and numerator using continued
//     fraction techniques.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "auxfuncs.h"
#include "subfunc_cfbrap.h"
#include "subfunc_gcd.h"
#include "subfunc_gmp_prob_prime.h"
#include "subfunc_pfact_18.h"

//Single function prototype needed for a forward reference.
static void dump_subfunction_choices(int indent);

//Implements the help.
int SUBFUNC_HELP_main(int argc, char *argv[])
   {
     int i;
   char *help[] =
     {
     "This program is a compiled 'C'-language program designed to be called from a",
     "PHP script to assist in calculating number theory and large integer",
     "arithmetic results.  This scheme (of having a separate executable like this",
     "one) was used with SourceForge web content because SourceForge did not have",
     "the bcmath library compiled into PHP, and it was determined experimentally",
     "that writing large integer arithmetic functions in PHP directly resulted in",
     "unusably slow performance.  This program makes use of the GMP library, which",
     "gives it superior performance.",
     "",
     "This program can of course be invoked from a shell or from another scripting",
     "language besides PHP.  It is designed, however, for execution from a",
     "scripting language, as you might guess from the human-unfriendly output.",
     "",
     "Please contact Dave Ashley (dtashley@aol.com) with any questions or",
     "concerns.",
     "",
     "Dave Ashley, Detroit, Michigan, USA, April, 2003.",
     "",
     "The available subfunction choices (the first parameter on the command",
     "line) are:",
     };

   for (i=0; i<sizeof(help)/sizeof(help[0]); i++)
     printf("%s\n", help[i]);
   dump_subfunction_choices(3);
   }

//Structure type used to hold the jump table of different functions
//to handle different subcommands.
struct struct_ARITH_LARGE_CGI_subcmd_jmp
      {
      char *subfunc_string;
      int (*subfunc_ptr)(int argc, char *argv[]);
      };

//The jump table.  The last element is defined to have both a
//NULL string pointer and a NULL function pointer.
static struct struct_ARITH_LARGE_CGI_subcmd_jmp subcmd_jump_tbl[] =
      {
      {"cfbrap",            SUBFUNC_CFBRAP_main               },
      {"gcd",               SUBFUNC_GCD_main                  },
      {"gmp_prob_prime",    SUBFUNC_GMP_PROB_PRIME_main       },
      {"pfact_18",          SUBFUNC_PFACT_18_main             },
      {"help",              SUBFUNC_HELP_main                 },
      {NULL,                NULL                              }
      };

//Dumps the available choices for the subfunction code to the
//standard output, each indented by "indent" characters.
static void dump_subfunction_choices(int indent)
   {
   int i, j;

   for (i=0; subcmd_jump_tbl[i].subfunc_string != NULL; i++)
      {
      for (j=0; j<indent; j++)
         printf(" ");
      printf("%s\n", subcmd_jump_tbl[i].subfunc_string);
      }
   }


int main(int argc, char *argv[])
   {
   int i;
   int rv = 0;

   if (argc < 2)
      {
      printf("Missing subfunction code.  Choices are:\n");
      dump_subfunction_choices(3);
      exit(4);
      }

   for (i=0; subcmd_jump_tbl[i].subfunc_string != NULL; i++)
      {
      if (!strcmp(argv[1], subcmd_jump_tbl[i].subfunc_string))
         {
    rv = (subcmd_jump_tbl[i].subfunc_ptr)(argc, argv);
         goto normal_return;
    }
      }

   printf("Invalid subfunction code.  Choices are:\n");
   dump_subfunction_choices(3);
   exit(4);

   normal_return:
      exit(rv);
   }

//********************************************************************************
//End of file ARITH_LARGE_CGI.C.
//********************************************************************************
