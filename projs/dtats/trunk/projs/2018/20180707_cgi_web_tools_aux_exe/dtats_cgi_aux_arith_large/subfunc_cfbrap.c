//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools_aux_exe/dtats_cgi_aux_arith_large/subfunc_cfbrap.c 207 2018-07-15 21:50:56Z dashley $
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
//This module finds the best rational approximations to a rational number
//subject to constraints on the numerator and denominator using continued
//fraction techniques.  All of the algorithms employed are O(log N) so
//there should be no problem obtaining results for any practical problem.
//This module is based on a paper written by Dave Ashley and others providing
//best rational approximation algorithms.
//
//INPUT PARAMETERS
//----------------
//This subfunction accepts the following parameters, in order.
//
// (a) The numerator of the number whose best rational approximation is to
//     be found (max 1000 digits).
//
// (b) The denominator of the number whose best rational approximation is to
//     be found (max 1000 digits).
//
// (c) The largest allowable numerator of the approximations, or "0" if the numerator
//     is unconstrained (max 1000 digits).
//
// (d) The largest allowable denominator of the approximations, or "0" if the denominator
//     is unconstrained (max 1000 digits).
//
// (e) The number of neighbors to the left of the specified number to return (max 1000).
//
// (f) The number of neighbors to the right of the specified number to return (max 1000).
//
// (g) The number of significant figures to use in floating-point results (note that
//     "significant figures" includes the numbers before the decimal point as well as
//     after).  The maximum value here is 1000.
//
// (h) The maximum number of CPU seconds to expend calculating (max 1000).
//
// NOTE (1):  Numerator and denominator may not both be unconstrained.
//
//OUTPUT RESULTS
//--------------
//The notation below gives the outputs of the program.  In some cases, [i] notation
//is used to indicate line numbers.
//
//[01] An overall success or failure code for the operation, as a string.
//     Valid responses are:
//        S       : Success.
//        FNPAR   : The number of command-line parameters was wrong.
//        FCPU    : The operation failed because ran out of CPU time.
//        FNUM    : The operation failed because the numerator of the rational number whose
//                  neighbors are to be found was invalid or too large.
//        FDEN    : The operation failed because the denominator of the rational number whose
//                  neighbors are to be found was invalid or too large.
//        FNUMMAX : The operation failed because the numerator limit was invalid or
//                  too large.
//        FDENMAX : The operation failed because the denominator limit was invalid
//                  or too large.
//        FLEFT   : The operation failed because the number of left neighbors requested
//                  was invalid or too large.
//        FRIGHT  : The operation failed because the number of right neighbors requested
//                  was invalid or too large.
//        FSIG    : The number of significant figures specified was invalid.
//        FCPU    : The CPU time limit was invalid.
//        FGEN    : General failure code (catchall, if anything else is possible).
//
//     For all failure codes, there will be no additional output if a failure code
//     appears on the first line.
//[02] The total number of lines in the output from the program, including the start
//     and ending lines.
//[03] The fully normalized numerator entered.  This means it has been
//     stripped of all weird characters, etc.  This can be used by the
//     PHP script to repopulate form boxes.
//[04] The fully normalized denominator entered.
//[05] The fully normalized maximum numerator entered.
//[06] The fully normalized maximum denominator entered.
//[07] The fully normalized number of left neighbors entered.
//[08] The fully normalized number of right neighbors entered.
//[09] The fully normalized number of significant figures requested.
//[10] The fully normalized number of CPU seconds allowed.
//
//The next section of the output contains the decimal form of the number that is to
//be approximated and also slightly more data about the number to be approximated.
//The PHP script may receive a number which is either specified as
//a rational number or as a decimal number, and the PHP script must convert it to a
//rational number so this program can process it.  Depending on what the PHP script
//was given as input, it may not have the decimal form.
//
//[11] Decimal equivalent of number entered, avoiding scientific notation if
//     possible but using it if necessary.
//[12] Scientific notation equivalent of number entered.
//[13] GCD of numerator and denominator of [04] and [05].
//[14] Numerator of reduced rational form.
//[15] Denominator of reduced rational form.
//
//This secion contains "pointers" to the major sections which may follow.
//All line numbers below are engineered so that "1" is the first line number
//in the output block and "0" represents the non-existence of the section.
//[16] Index to results section (code "NEIGHBORS").
//[17] Index to CF decomp of number to approximate (code "CFINPUT").
//[18] Index to CF decomp of reciprocal of number to approximate (code "CFINPUTRECIP").
//[19] Index to CF decomp of corner point (code "CFCORNER").
//[20] Index to CF decomp of reciprocal of corner point (code "CFCORNERRECIP").
//
//This section contains the neighbors of the number to approximate.  The number of
//neighbors is strongly influenced by the number of neighbors specified on the
//CGI-BIN form.  However, there may be fewer neighbors returned if 0/1 or the last
//formable rational number is encountered.
//[N+ 0] Constant "NEIGHBORS".
//[N+ 1] Number of neighbors to follow.
//[N+ 2] Subscript of first neighbor, from left to right.  Subscripts are assigned so they rank
//       the neighbors in relation to the number to approximate.  "0" indicates that the number
//       is the number to approximate, i.e. the number is present in the rectangular region of
//       the integer lattice being considered.
//[N+ 3] 1 if the number is the corner point, or 0 otherwise.
//[N+ 4] Numerator of number, irreducible with respect to denominator.
//[N+ 5] Denominator of number, irreducible with respect to numerator.
//[N+ 6] Decimal form of neighbor, avoiding scientific notation if possible.
//[N+ 7] Decimal form of neighbor, using scientific notation.
//[N+ 8] Sign of error.  Will be "-" for negative error or "+" otherwise.
//[N+ 9] Numerator of absolute value of error, irreducible with respect to denominator.
//[N+10] Denominator of absolute value of error, irreducible with respect to numerator.
//[N+11] Decimal form of absolute value of error, avoiding scientific notation if possible.
//[N+12] Decimal form of absolute value of error, using scientific notation.
//[N+13] Repeats at [N+2] for next neighbor, out to as many neighbors specified in
//       [N+1]
//
//The next section of the output contains the continued fraction decomposition
//of the number to approximate.
//[N+ 0] Constant "CFINPUT".
//[N+ 1] Number of partial quotients to follow.
//[N+ 2] k, subscript of iteration (first subscript is 0).
//[N+ 3] dividend_k
//[N+ 4] divisor_k
//[N+ 5] a_k
//[N+ 6] remainder_k
//[N+ 7] p_k
//[N+ 8] q_k
//[N+ 9] k+1 ... repeats as with element [N+2] out to as many partial
//       quotients specified in [N+1].
//
//The next section of the output contains the continued fraction decomposition
//of the reciprocal of the number to approximate.  If the number to approximate is 0,
//this entire section will be omitted.
//[N+ 0] Constant "CFINPUTRECIP".
//[N+ 1] Number of partial quotients to follow.
//[N+ 2] k, subscript of iteration (first subscript is 0).
//[N+ 3] dividend_k
//[N+ 4] divisor_k
//[N+ 5] a_k
//[N+ 6] remainder_k
//[N+ 7] p_k
//[N+ 8] q_k
//[N+ 9] k+1 ... repeats as with element [N+2] out to as many partial
//       quotients specified in [N+1].
//
//The next section of the output contains the continued fraction decomposition of the
//the corner point.  If the numerator and denominator were not both constrained,
//this section will be omitted.
//[N+ 0] Constant "CCORNER".
//[N+ 1] Number of partial quotients to follow.
//[N+ 2] k, subscript of iteration (first subscript is 0).
//[N+ 3] dividend_k
//[N+ 4] divisor_k
//[N+ 5] a_k
//[N+ 6] remainder_k
//[N+ 7] p_k
//[N+ 8] q_k
//[N+ 9] k+1 ... repeats as with element [N+2] out to as many partial
//       quotients specified in [N+1].
//
//The next section of the output contains the continued fraction decomposition of the
//reciprocal of the corner point.  If the numerator and denominator were not both constrained,
//this section will be omitted.
//[N+ 0] Constant "CCORNERRECIP".
//[N+ 1] Number of partial quotients to follow.
//[N+ 2] k, subscript of iteration (first subscript is 0).
//[N+ 3] dividend_k
//[N+ 4] divisor_k
//[N+ 5] a_k
//[N+ 6] remainder_k
//[N+ 7] p_k
//[N+ 8] q_k
//[N+ 9] k+1 ... repeats as with element [N+2] out to as many partial
//       quotients specified in [N+1].
//
//The next section is the footer.
//[N]    Constant "S", terminator line.

//The return value (exit code) from this subfunction is always 0.
//

#define MODULE_SUBFUNC_CFBRAP

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <gmp.h>

#include "auxfuncs.h"
#include "subfunc_cfbrap.h"
#include "sieve_eratosthenes.h"


/****************************************************************************/
/* MODULE CONSTANTS                                                         */
/****************************************************************************/
#define SUBFUNC_CFBRAP_MAX_IN_DIGITS               (1000)
   //The maximum number of decimal digits that will be allowed in input rational
   //numbers and limits.
#define SUBFUNC_CFBRAP_MAX_NEIGHBORS               (1000)
   //The maximum number of integer lattice rectangular region neighbors that will
   //be allowed.

/****************************************************************************/
/* MODULE DATA STRUCTURES                                                   */
/****************************************************************************/
//A structure to hold all input parameters from the command-line.
//
struct SUBFUNC_CFBRAP_input_par_struct
   {
   mpz_t num;
   mpz_t den;
   mpz_t num_max;
   mpz_t den_max;
   int lneighbors;
   int rneighbors;
   int sig_fig;
   int max_cpu;
   };

//A structure to hold a single line that might be output from this
//program.
struct SUBFUNC_CFBRAP_line_buffer
   {
   char *line;
      //The line itself, with zero terminator.
   };

//A structure to hold the collection of lines that will eventually be
//output from this program.  These must be buffered because it is
//not known how many there will be.
//
struct SUBFUNC_CFBRAP_program_output_buffer
   {
   int nlines;
      //The number of lines.
   struct SUBFUNC_CFBRAP_line_buffer *lines;
      //Pointer to the first element of array of line structures.
   };


/****************************************************************************/
/* PROGRAM OUTPUT BUFFER MANIPULATION FUNCTIONS                             */
/****************************************************************************/
void SUBFUNC_CFBRAP_pob_init(struct SUBFUNC_CFBRAP_program_output_buffer *arg)
   {
   arg->nlines  = 0;
   arg->lines   = NULL;
   }

void SUBFUNC_CFBRAP_pob_destroy(struct SUBFUNC_CFBRAP_program_output_buffer *arg)
   {
   int i;

   for (i=0; i<arg->nlines; i++)
      {
      free(arg->lines[i].line);
      }

   if (i)
      free(arg->lines);

   arg->nlines = 0;
   arg->lines = NULL;
   }

//Tacks a line onto the output buffer.
//
void SUBFUNC_CFBRAP_pob_tack_line(struct SUBFUNC_CFBRAP_program_output_buffer *arg,
                                  const char *line)
   {
   int tack_strlen;
      //String length of the line to tack.  Must allocate one more space for it.

   //Figure out how long the input string is.
   tack_strlen = strlen(line);

   //If there are no lines in the buffer, allocate space for 1 else realloc.
   if (!arg->nlines)
      arg->lines = malloc(sizeof(struct SUBFUNC_CFBRAP_line_buffer));
   else
      arg->lines = realloc(arg->lines, (arg->nlines + 1) * sizeof(struct SUBFUNC_CFBRAP_line_buffer));

   //Set up for the line itself.
   arg->lines[arg->nlines].line = malloc(tack_strlen + 1);

   //Copy in the line.
   strcpy(arg->lines[arg->nlines].line, line);

   //We now have one more line.
   arg->nlines++;
   }


//Changes a line in the buffer to be something different.  The first line is "1".  If the line
//does not already exist, this function does nothing.
//
void SUBFUNC_CFBRAP_pob_modify_line(struct SUBFUNC_CFBRAP_program_output_buffer *arg,
                                    int which_line,
                                    const char *new_line)
   {
   int modify_strlen;
      //String length of the line to swap in.  Must allocate one more space for it.

   //Figure out how long the input string is.
   modify_strlen = strlen(new_line);

   //The line number specified must be at least number 1 and the line must already
   //exist, else do nothing.
   if ((which_line >= 1) && (which_line <= arg->nlines))
      {
      //Reallocate the space to hold the new line and copy it in.
      arg->lines[which_line-1].line = realloc(arg->lines[which_line-1].line, modify_strlen + 1);
      strcpy(arg->lines[which_line-1].line, new_line);
      }
   }


//Dumps the entire output buffer to the standard output.
//
void SUBFUNC_CFBRAP_pob_dump(struct SUBFUNC_CFBRAP_program_output_buffer *arg)
   {
   int i;

   for (i=0; i<arg->nlines; i++)
     {
       printf("%s\n", arg->lines[i].line);
     }
   }


/****************************************************************************/
/* INPUT PARAMETER BLOCK MANIPULATION                                       */
/****************************************************************************/
//Initializes the input parameter block (allocates initial storage).
//
void SUBFUNC_CFBRAP_ipblock_init(struct SUBFUNC_CFBRAP_input_par_struct *arg)
   {
   mpz_init(arg->num);
   mpz_init(arg->den);
   mpz_init(arg->num_max);
   mpz_init(arg->den_max);
   arg->lneighbors         =  1;
   arg->rneighbors         =  1;
   arg->sig_fig            =  9;
   arg->max_cpu            = 20;
   }

//Deallocates the input parameter block (deallocates storage).
//
void SUBFUNC_CFBRAP_ipblock_destroy(struct SUBFUNC_CFBRAP_input_par_struct *arg)
   {
   mpz_clear(arg->num);
   mpz_clear(arg->den);
   mpz_clear(arg->num_max);
   mpz_clear(arg->den_max);
   arg->lneighbors         =  1;
   arg->rneighbors         =  1;
   arg->sig_fig            =  9;
   arg->max_cpu            = 20;
   }


/****************************************************************************/
/* ERROR PATH OUTPUT                                                        */
/****************************************************************************/
//Dumps an error code and associated proper information out to the output stream
//and returns.
//
int SUBFUNC_CFBRAP_error_dump(int argc, char *argv[])
   {
     return 0;
   }


/****************************************************************************/
/* INPUT PARAMETER PARSING                                                  */
/****************************************************************************/
//Parses input parameters, stuffs the structure containing these parameters,
//and in the event of an error will return 1 and will stuff the output
//buffer with only the error code.
int SUBFUNC_CFBRAP_parse_input_pars(
                                    int argc,
                                    char *argv[],
                                    struct SUBFUNC_CFBRAP_input_par_struct *ipb,
                                    struct SUBFUNC_CFBRAP_program_output_buffer *pob
                                    )
   {
   char *scratch = NULL;

   //There should be 8 input parameters in addition to the 2 required (the
   //program name plus the subfunction code.  Error out if wrong.
   if (argc != 10)
      {
      SUBFUNC_CFBRAP_pob_tack_line(pob, "FNPAR");
      return(1);
      }

   //The first input parameter should be the numerator of the rational number to
   //approximate.  We can parse this out and place it into the input parameter
   //block.
   scratch = malloc(strlen(argv[2]) + 1);
   strcpy(scratch, argv[2]);
   AUXFUNCS_remove_non_digits(scratch);
   AUXFUNCS_remove_leading_zeros(scratch);

   if (!strlen(scratch))
      {
      //The only possibility is that this was zero.  Assign zero.
      mpz_set_ui(ipb->num, 0);
      }
   else
      {
      //What is left must be a valid integer.  We need to be sure it is not too
      //long.
      if (strlen(scratch) > SUBFUNC_CFBRAP_MAX_IN_DIGITS)
         {
         SUBFUNC_CFBRAP_pob_tack_line(pob, "FNUM");
         return(1);
    }
      else
    {
         mpz_set_str(ipb->num, scratch, 10);
         }
      }

   //The second input parameter should be the denominator of the rational number to
   //approximate.  We can parse this out and place it into the input parameter
   //block.
   scratch = realloc(scratch, strlen(argv[3]) + 1);
   strcpy(scratch, argv[3]);
   AUXFUNCS_remove_non_digits(scratch);
   AUXFUNCS_remove_leading_zeros(scratch);

   if (!strlen(scratch))
      {
      //The only possibility is that this was zero.  This is a no-no.
      SUBFUNC_CFBRAP_pob_tack_line(pob, "FDEN");
      return(1);
      }
   else
      {
      //What is left must be a valid integer.  We need to be sure it is not too
      //long.
      if (strlen(scratch) > SUBFUNC_CFBRAP_MAX_IN_DIGITS)
         {
         SUBFUNC_CFBRAP_pob_tack_line(pob, "FDEN");
         return(1);
    }
      else
    {
         mpz_set_str(ipb->den, scratch, 10);
         }
      }

   //The third input parameter should be the max numerator value for approximations.
   //We can parse this out and place it into the input parameter
   //block.
   scratch = malloc(strlen(argv[4]) + 1);
   strcpy(scratch, argv[4]);
   AUXFUNCS_remove_non_digits(scratch);
   AUXFUNCS_remove_leading_zeros(scratch);

   if (!strlen(scratch))
      {
      //The only possibility is that this was zero.  Assign zero.
      mpz_set_ui(ipb->num_max, 0);
      }
   else
      {
      //What is left must be a valid integer.  We need to be sure it is not too
      //long.
      if (strlen(scratch) > SUBFUNC_CFBRAP_MAX_IN_DIGITS)
         {
         SUBFUNC_CFBRAP_pob_tack_line(pob, "FNUMMAX");
         return(1);
    }
      else
    {
         mpz_set_str(ipb->num_max, scratch, 10);
         }
      }

   //The fourth input parameter should be the max denominator value for approximations.
   //We can parse this out and place it into the input parameter
   //block.
   scratch = malloc(strlen(argv[5]) + 1);
   strcpy(scratch, argv[5]);
   AUXFUNCS_remove_non_digits(scratch);
   AUXFUNCS_remove_leading_zeros(scratch);

   if (!strlen(scratch))
      {
      //The only possibility is that this was zero.  Assign zero.
      mpz_set_ui(ipb->den_max, 0);
      }
   else
      {
      //What is left must be a valid integer.  We need to be sure it is not too
      //long.
      if (strlen(scratch) > SUBFUNC_CFBRAP_MAX_IN_DIGITS)
         {
         SUBFUNC_CFBRAP_pob_tack_line(pob, "FDENMAX");
         return(1);
    }
      else
    {
         mpz_set_str(ipb->den_max, scratch, 10);
         }
      }

   //The fifth input parameter should be the number of desired left neighbors.
   //We can parse this out and place it into the input parameter
   //block.
   scratch = malloc(strlen(argv[6]) + 1);
   strcpy(scratch, argv[6]);
   AUXFUNCS_remove_non_digits(scratch);
   AUXFUNCS_remove_leading_zeros(scratch);

   if (!strlen(scratch))
      {
      //The only possibility is that this was zero.  Assign 0.
      ipb->lneighbors = 0;
      }
   else
      {
      //What is left must be a valid integer.  Scan it in.
      //
      if (strlen(scratch) > SUBFUNC_CFBRAP_MAX_IN_DIGITS)
         {
         SUBFUNC_CFBRAP_pob_tack_line(pob, "FDENMAX");
         return(1);
    }
      else
    {
         mpz_set_str(ipb->den_max, scratch, 10);
         }
      }

   return(0);
   }


/****************************************************************************/
/* MAIN CALCULATION FUNCTION                                                */
/****************************************************************************/
//Carries out the best rational approximation calculation and display, knowing that
//all parameters have been validated.
//
int SUBFUNC_CFBRAP_calc_brap(int argc, char *argv[])
   {
     return 0;
   }



//Main function.  Checks parameters and carries out the calculations.
//
int SUBFUNC_CFBRAP_main(int argc, char *argv[])
   {
   //The time snapshot against which we compare to see if we're over
   //time budget.
   time_t time_snapshot;

   struct SUBFUNC_CFBRAP_input_par_struct ipb;
   //The input parameters.

   struct SUBFUNC_CFBRAP_program_output_buffer pob;
   //The program output.  Output is buffered because there are some lines
   //early that point to later lines.

   //Scratch structure.
   char *scratchstr = NULL;

   //Initialize the input parameter structure.
   SUBFUNC_CFBRAP_ipblock_init(&ipb);

   //Initialize the output buffer.
   SUBFUNC_CFBRAP_pob_init(&pob);

   //Parse, check, etc. the input parameters.  If there are any issues,
   //Jump to the end and just dump what we have.
   if (SUBFUNC_CFBRAP_parse_input_pars(argc, argv, &ipb, &pob))
      goto error_return;


   //This is a success event.  What this means is that we should store the output,
   //which will then be send to stdout.
   //
   //Initial success code.
   SUBFUNC_CFBRAP_pob_tack_line(&pob, "S");
   //
   //Total number of lines in the program.  This is just a placeholder, until we know how
   //many.
   SUBFUNC_CFBRAP_pob_tack_line(&pob, "NUMLINES_PLACEHOLDER");
   //
   //Numerator of number to be approximated.
   scratchstr = realloc(scratchstr, mpz_sizeinbase(ipb.num, 10) + 20);
   gmp_sprintf(scratchstr, "%Zd", ipb.num);
   SUBFUNC_CFBRAP_pob_tack_line(&pob, scratchstr);
   //
   //Denominator of number to be approximated.
   scratchstr = realloc(scratchstr, mpz_sizeinbase(ipb.den, 10) + 20);
   gmp_sprintf(scratchstr, "%Zd", ipb.den);
   SUBFUNC_CFBRAP_pob_tack_line(&pob, scratchstr);
   //
   //Maximum numerator of approximations.
   scratchstr = realloc(scratchstr, mpz_sizeinbase(ipb.num_max, 10) + 20);
   gmp_sprintf(scratchstr, "%Zd", ipb.num_max);
   SUBFUNC_CFBRAP_pob_tack_line(&pob, scratchstr);
   //
   //Maximum denominator of approximations.
   scratchstr = realloc(scratchstr, mpz_sizeinbase(ipb.den_max, 10) + 20);
   gmp_sprintf(scratchstr, "%Zd", ipb.den_max);
   SUBFUNC_CFBRAP_pob_tack_line(&pob, scratchstr);
   //
   //Fill in the number of lines that we have.  This replaces the placeholder.
      {
      char buf[100];

      sprintf(buf, "%d", pob.nlines);
      SUBFUNC_CFBRAP_pob_modify_line(&pob, 2, buf);
      }



   error_return:

   //Destroy the input parameter structure.
   SUBFUNC_CFBRAP_ipblock_destroy(&ipb);

   //Dump the output to STDOUT.
   SUBFUNC_CFBRAP_pob_dump(&pob);

   //Destroy the output buffer.
   SUBFUNC_CFBRAP_pob_destroy(&pob);

   //Always return 0.
   return(0);
   }

//********************************************************************************
// End of SUBFUNC_CFBRAP.C.
//********************************************************************************
