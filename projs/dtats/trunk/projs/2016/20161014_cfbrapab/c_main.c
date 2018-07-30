// $Header: svn://localhost/dtapublic/projs/trunk/projs/20161014_cfbrapab/cfbrapab.cpp 47 2016-10-17 00:04:56Z dashley $
//-------------------------------------------------------------------------------------------------
//This file is part of "cfbrapab", a program for determining the best rational approximation to a
//real number, subject to constraints on the numerator and denominator, using continued fraction
//algorithms.
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
#include <assert.h>
#include <malloc.h>
#include <process.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#include "bstrfunc.h"
#include "ccmalloc.h"
#include "ccmfatal.h"
#include "charfunc.h"
#include "cu_msgs.h"
#include "fcmiof.h"
#include "gmp_ints.h"
#include "gmp_rats.h"
#include "gmp_ralg.h"
#include "intfunc.h"


#define PNAME "cfbrapab"
#define PNAMEUC "CFBRAPAB"


const char *C_MAIN_cvcinfo(void)
   {
   return("$Header: /cvsroot/esrg/sfesrg/esrgpcpj/cfbrapab/c_main.c,v 1.6 2002/01/27 17:58:15 dtashley Exp $");
   }


//This is a NULL-terminated table of pointers to functions
//which return version control strings for all of the files
//which make up the INTFAC program.  This information would
//be helpful for debugging.
static const char *(*C_MAIN_vcinfoptrs[])(void) =
   {
   //This is the main module, should come first.
   C_MAIN_cvcinfo,

   //And now the others, in alphabetical order.
   BSTRFUNC_hvcinfo,
   BSTRFUNC_cvcinfo,
   CCMALLOC_hvcinfo,
   CCMALLOC_cvcinfo,
   CCMFATAL_hvcinfo,
   CCMFATAL_cvcinfo,
   CHARFUNC_hvcinfo,
   CHARFUNC_cvcinfo,
   CU_MSGS_hvcinfo,
   CU_MSGS_cvcinfo,
   FCMIOF_hvcinfo,
   FCMIOF_cvcinfo,
   GMP_INTS_hvcinfo,
   GMP_INTS_cvcinfo,
   GMP_RALG_hvcinfo,
   GMP_RALG_cvcinfo,
   GMP_RATS_hvcinfo,
   GMP_RATS_cvcinfo,
   INTFUNC_hvcinfo,
   INTFUNC_cvcinfo,
   NULL
   };


//This is the structure type used to hold information about all the
//command-line parameters.
//
struct CfbrapabCmainStruct
   {
   GMP_RATS_mpq_struct rn;
      //The rational number specified on the command line.
      //symmetry.
   GMP_INTS_mpz_struct kmax;
      //The value of KMAX specified on the command line.  This must always
      //be present.
   int hmax_specified;
      //TRUE if HMAX is specified in addition to KMAX.  KMAX is mandatory
      //in all cases.
   GMP_INTS_mpz_struct hmax;
      //The value of HMAX if it is specified.  This is optional.  This will be
      //set to zero if it is not present on the command line.
   int neversmaller_specified;
      //TRUE if the -neversmaller option is specified on the command line.
   int neverlarger_specified;
      //TRUE if the -neverlarger option is specified on the command line.
   int pred_specified;
      //TRUE if the -pred option is specified on the command line.
   int succ_specified;
      //TRUE if the -succ option specified on the command line.
   int n_specified;
      //TRUE if the -n parameter is specified on the command line.
   unsigned n;
      //The value of n if it has been specified.
   CU_MSGS_std_cmd_line_par_results_struct argblock;
      //The block holding the options which are common across all
      //of these command-line utilities.
   };


//Processes the command-line parameters, and abstracts it to a 
//the contents of a structure plus a failure flag.
static void process_command_line_args(struct CfbrapabCmainStruct *parblock,
                                     int argc, 
                                     char* argv[])
   {
   int error_flag;
   int first_dashed_parameter;
   int i;
   int recognized;

   //Eyeball the input parameters.
   assert(parblock != NULL);
   assert(argc >= 1);
   assert(argv != NULL);

   //We have to have at least 3 total parameters.  However, this is covered
   //in main().

   //Process the first parameter, which has to be the rational number we
   //want to approximate.  If there is a problem, give a helpful message
   //and exit with an error code.
   GMP_RATS_mpq_init(&(parblock->rn));
   GMP_RATS_mpq_set_all_format_rat_num( argv[1],
                                       &error_flag,
                                       &(parblock->rn));

   //If there was a parse error, announce and abort.
   if (error_flag || GMP_RATS_mpq_is_nan(&(parblock->rn)))
      {
      printf("\"%s\" is not a properly formatted rational number.\n", argv[1]);
      exit(4);
      }

   //Normalize the rational number specified as input.  It is allowed to
   //be negative.
   GMP_RATS_mpq_normalize(&(parblock->rn));

   //The next item has to be a number, it has to be
   //an integer, it has to be positive, and it
   //is KMAX.  Parse out that.  If there are any
   //errors, abort.
   GMP_INTS_mpz_init(&(parblock->kmax));
   GMP_INTS_mpz_set_general_int(&(parblock->kmax), &error_flag, argv[2]);
   if (error_flag || GMP_INTS_mpz_is_zero(&(parblock->kmax)) || GMP_INTS_mpz_is_neg(&(parblock->kmax)))
      {
      printf("\"%s\" is not a properly formatted positive integer.\n", argv[2]);
      exit(4);
      }

   //Unconditionally allocate space for hmax.
   GMP_INTS_mpz_init(&(parblock->hmax));

   //If there is a third parameter, it can be two things.  It can
   //be either HMAX, or it can be the start of the parameters
   //with dashes.  First, let's decide which case applies.
   if (argc <= 3)
      {
      first_dashed_parameter = 3;
      parblock->hmax_specified = 0;
      }
   else
      {
      if (argv[3][0] == '-')
         {
         first_dashed_parameter = 3;
         parblock->hmax_specified = 0;
         }
      else
         {
         first_dashed_parameter = 4;
         parblock->hmax_specified = 1;

         GMP_INTS_mpz_set_general_int(&(parblock->hmax), &error_flag, argv[3]);
         if (error_flag || GMP_INTS_mpz_is_zero(&(parblock->hmax)) || GMP_INTS_mpz_is_neg(&(parblock->hmax)))
            {
            printf("\"%s\" is not a properly formatted positive integer.\n", argv[3]);
            exit(4);
            }
         }
      }

   //Loop through the remaining parameters, trying to process each
   //one either as a parameter specific to this program or else
   //as a general parameter.
   //
   //Initialize the internal general parameter block.
   CU_MSGS_cmd_line_par_results_struct_create(&(parblock->argblock));
   parblock->neversmaller_specified = 0;
   parblock->neverlarger_specified  = 0;
   parblock->pred_specified         = 0;
   parblock->succ_specified         = 0;
   parblock->n_specified            = 0;
   parblock->n                      = 0;

   for (i=first_dashed_parameter; i<argc; i++)
      {
      if (!strcmp("-neversmaller", argv[i]))
         {
         parblock->neversmaller_specified = 1;
         }
      else if (!strcmp("-neverlarger", argv[i]))
         {
         parblock->neverlarger_specified = 1;
         }
      else if (!strcmp("-pred", argv[i]))
         {
         parblock->pred_specified = 1;
         }
      else if (!strcmp("-succ", argv[i]))
         {
         parblock->succ_specified = 1;
         }
      else if (!strcmp("-n", argv[i]))
         {
         parblock->n_specified = 1;

         //To go along with -n, we have to have a next parameter.
         if (i == (argc-1))
            {
            printf("The \"-n\" parameter must include a following count.\n");
            exit(4);
            }

         //Bump i to index to next par.
         i++;

         //Try to parse this as a UINT24.  It must be that.
         GMP_INTS_mpz_parse_into_uint32(&(parblock->n), &error_flag, argv[i]);

         //If it couldn't be parsed as an integer, flunk it.
         if (error_flag)
            {
            printf("\"%s\" is not a valid unsigned integer or exceeds 24 bits.\n", argv[i]);
            exit(4);
            }

         //If it is too large, flunk it.
         if (parblock->n > 0x00FFFFFF)
            {
            printf("\"%s\" is an unsigned integer but exceeds 24 bits.\n", argv[i]);
            exit(4);
            }

         //OK, we're cool ...
         }
      else
         {
         //Two possibilities left.  Either general parameter, or else unrecognized.
         CU_MSGS_cmd_line_par_results_struct_process_arg(&(parblock->argblock),
                                                         argv[i],
                                                         &recognized);
         if (!recognized)
            {
            printf("\"%s\" is not a recognized command-line parameter.\n", argv[i]);
            exit(4);
            }

         //Was picked up as general parameter.
         }
      }

   //Congeal our thoughts on the "general" command-line parameters.  No errors possible
   //here.
   CU_MSGS_cmd_line_par_results_struct_finalize(&(parblock->argblock));

   //printf("Boo.\n");
   //printf("neverlarger %d succ %d\n", parblock->neverlarger_specified, parblock->succ_specified);

   //Look for mutually exclusive options among the program-specific parameters.
   if (
         (parblock->neversmaller_specified && (parblock->neverlarger_specified || parblock->pred_specified || parblock->succ_specified|| parblock->n_specified))
         ||
         (parblock->neverlarger_specified && (parblock->pred_specified || parblock->succ_specified || parblock->n_specified))
         ||
         (parblock->pred_specified && (parblock->succ_specified|| parblock->n_specified))
         ||
         (parblock->succ_specified && parblock->n_specified)
      )
      {
      printf("The \"-neversmaller\", \"-neverlarger\", \"-pred\", \"-succ\", and \"-n\" options are\nmutually exclusive.\n");
      exit(4);
      }

   //OK, we're clean, all pars in order.
   }


//Releases the dynamic memory associated with the parameter block.
static void release_command_line_args(struct CfbrapabCmainStruct *parblock)
   {
   assert(parblock != NULL);

   //This function is superfluous, since in a command-line utility it doesn't really
   //matter if everything is released.  But, here goes.
   CU_MSGS_cmd_line_par_results_struct_destroy(&(parblock->argblock));
   GMP_RATS_mpq_clear(&(parblock->rn));
   GMP_INTS_mpz_clear(&(parblock->kmax));
   GMP_INTS_mpz_clear(&(parblock->hmax));
   }


//Prints out a single rational number in the format endorsed
//by this program.  This often includes DAP information
//and difference information.  It is assumed that the
//previous information is terminated by a horizontal line,
//and this function terminates with a horizontal line.
static void CMAIN_print_app_in_std_form(FILE *s,
                                        int index,
                                        GMP_RATS_mpq_struct *rn,
                                        GMP_RATS_mpq_struct *approx,
                                        int nf,
                                        int show_diff,
                                        int show_dap,
                                        GMP_INTS_mpz_struct *dap_den)
   {
   char sbuf[250];
   GMP_RATS_mpq_struct diff, q_temp1;
   GMP_INTS_mpz_struct z_temp1, quotient, remainder;

   //Eyeball the input parameters.
   assert(s != NULL);
   assert(rn != NULL);
   assert(approx != NULL);
   assert(dap_den != NULL);

   //Allocate.
   GMP_RATS_mpq_init(&diff);
   GMP_RATS_mpq_init(&q_temp1);
   GMP_INTS_mpz_init(&z_temp1);
   GMP_INTS_mpz_init(&quotient);
   GMP_INTS_mpz_init(&remainder);

   //Print out the approximation numerator.
   sprintf(sbuf, "approx_num(%d)", index);
   if (!nf)
      {
      GMP_INTS_mpz_long_int_format_to_stream(s,
                                             &(approx->num),
                                             sbuf);
      }
   else
      {
      int nreserved;
      char *p;
      
      fprintf(s, "%d\n", index);
      
      nreserved = GMP_INTS_mpz_size_in_base_10(&(approx->num));
      p = CCMALLOC_malloc(sizeof(char) * nreserved);
      GMP_INTS_mpz_to_string(p, &(approx->num));
      fprintf(s, "%s\n", p);
      CCMALLOC_free(p);
      }

   if (!nf)
      FCMIOF_hline();

   //Print out the approximation denominator.
   sprintf(sbuf, "approx_den(%d)", index);
   if (!nf)
      {
      GMP_INTS_mpz_long_int_format_to_stream(s,
                                             &(approx->den),
                                             sbuf);
      }
   else
      {
      int nreserved;
      char *p;

      nreserved = GMP_INTS_mpz_size_in_base_10(&(approx->den));
      p = CCMALLOC_malloc(sizeof(char) * nreserved);
      GMP_INTS_mpz_to_string(p, &(approx->den));
      fprintf(s, "%s\n", p);
      CCMALLOC_free(p);
      }

   if (!nf)
      FCMIOF_hline();


   //If the "dap" flag is set, calculate and display decimal equivalent of the 
   //approximation.
   if (show_dap)
      {
      //Make the calculation for decimal approximation.
      GMP_RATS_mpq_copy(&q_temp1, approx);
      GMP_RATS_mpq_normalize(&q_temp1);
      GMP_INTS_mpz_mul(&z_temp1, dap_den, &q_temp1.num);
      GMP_INTS_mpz_tdiv_qr(&quotient, &remainder,
                           &z_temp1, &q_temp1.den);

      sprintf(sbuf, "dap_num(%d)", index);
      if (!nf)
         {
         GMP_INTS_mpz_long_int_format_to_stream(s,
                                                &(quotient),
                                                sbuf);
         }
      else
         {
         int nreserved;
         char *p;

         nreserved = GMP_INTS_mpz_size_in_base_10(&(quotient));
         p = CCMALLOC_malloc(sizeof(char) * nreserved);
         GMP_INTS_mpz_to_string(p, &(quotient));
         fprintf(s, "%s\n", p);
         CCMALLOC_free(p);
         }

      if (!nf)
         FCMIOF_hline();

      //Print out the approximation denominator.
      sprintf(sbuf, "dap_den(%d)", index);
      if (!nf)
         {
         GMP_INTS_mpz_long_int_format_to_stream(s,
                                                dap_den,
                                                sbuf);
         }
      else
         {
         int nreserved;
         char *p;

         nreserved = GMP_INTS_mpz_size_in_base_10(dap_den);
         p = CCMALLOC_malloc(sizeof(char) * nreserved);
         GMP_INTS_mpz_to_string(p, dap_den);
         fprintf(s, "%s\n", p);
         CCMALLOC_free(p);
         }

      if (!nf)
         FCMIOF_hline();
      }

   
   //If the "diff" flag is set, calculate and display the rational difference.
   if (show_diff)
      {
      GMP_RATS_mpq_sub(&diff, approx, rn);
      GMP_RATS_mpq_normalize(&diff);

      sprintf(sbuf, "error_num(%d)", index);
      if (!nf)
         {
         GMP_INTS_mpz_long_int_format_to_stream(s,
                                                &(diff.num),
                                                sbuf);
         }
      else
         {
         int nreserved;
         char *p;

         nreserved = GMP_INTS_mpz_size_in_base_10(&(diff.num));
         p = CCMALLOC_malloc(sizeof(char) * nreserved);
         GMP_INTS_mpz_to_string(p, &(diff.num));
         fprintf(s, "%s\n", p);
         CCMALLOC_free(p);
         }

      if (!nf)
         FCMIOF_hline();

      //Print out the approximation denominator.
      sprintf(sbuf, "error_den(%d)", index);
      if (!nf)
         {
         GMP_INTS_mpz_long_int_format_to_stream(s,
                                                &(diff.den),
                                                sbuf);
         }
      else
         {
         int nreserved;
         char *p;

         nreserved = GMP_INTS_mpz_size_in_base_10(&(diff.den));
         p = CCMALLOC_malloc(sizeof(char) * nreserved);
         GMP_INTS_mpz_to_string(p, &(diff.den));
         fprintf(s, "%s\n", p);
         CCMALLOC_free(p);
         }

      if (!nf)
         FCMIOF_hline();
      }

   //Deallocate.
   GMP_RATS_mpq_clear(&diff);
   GMP_RATS_mpq_clear(&q_temp1);
   GMP_INTS_mpz_clear(&z_temp1);
   GMP_INTS_mpz_clear(&quotient);
   GMP_INTS_mpz_clear(&remainder);
   }


//Handles the classic case of finding the closest
//neighbor(s).
static int CMAIN_classic_closest_neighbor(struct CfbrapabCmainStruct *parblock)
   {
   int rv = 0;
   GMP_RATS_mpq_struct hmax_over_one, hmax_over_kmax, rn_in_abs;
   GMP_INTS_mpz_struct dap_denominator;
   GMP_RALG_cf_app_struct cf_decomp;
   GMP_RALG_fab_neighbor_collection_struct neighbor_data;
   int error_flag;

   //Allocate all dynamic memory.
   GMP_RATS_mpq_init(&hmax_over_one);
   GMP_RATS_mpq_init(&hmax_over_kmax);
   GMP_INTS_mpz_init(&dap_denominator);
   GMP_RATS_mpq_init(&rn_in_abs);

   //Set the DAP denominator to 1e108.
   GMP_INTS_mpz_set_general_int(&dap_denominator,
                                &error_flag,
                                "1e108");

   //By convention, we will not mess with anything with an
   //absolute value greater than HMAX/1.  If such a condition exists, puke out.
   //Form up the value of HMAX/1 if HMAX was specified.
   if (parblock->hmax_specified)
      {
      GMP_INTS_mpz_copy(&(hmax_over_one.num), &(parblock->hmax));
      GMP_INTS_mpz_set_ui(&(hmax_over_one.den), 1);
      GMP_RATS_mpq_copy(&rn_in_abs, &(parblock->rn));
      GMP_INTS_mpz_abs(&(rn_in_abs.num));
      if (GMP_RATS_mpq_cmp(&(rn_in_abs), &hmax_over_one, NULL) > 0)
         {
         printf("The magnitude of the number supplied exceeds HMAX/1, and hence the number\n"
                "has no neighbors in the series of interest.  Calculation cannot continue.\n");
         exit(4);
         }
      }

   //If the "verbose" option is specified, we want to give the continued fraction
   //partial quotients and convergents of either the number to approximate,
   //its reciprocal, or none of the above, as appropriate; and give a bit more 
   //information, in addition.
   if (parblock->argblock.verbose)
      {
      if (parblock->hmax_specified)
         {
         //Stuff HMAX/KMAX.  This is necessary for comparison.
         GMP_INTS_mpz_copy(&(hmax_over_kmax.num), &(parblock->hmax));
         GMP_INTS_mpz_copy(&(hmax_over_kmax.den), &(parblock->kmax));
         }

      if (!(parblock->hmax_specified) || (GMP_RATS_mpq_cmp(&(parblock->rn), &hmax_over_kmax, NULL) < 0))
         {
         //Either HMAX was not specified or else we are below the corner point on the 
         //integer lattice.  Get the continued fraction representation of the number
         //rather than its reciprocal.
         GMP_RALG_cfdecomp_init(&cf_decomp, &error_flag, &(rn_in_abs.num), &(rn_in_abs.den));

         //Print out the continued fraction decomposition of the rational number.
         GMP_RALG_cfdecomp_emit(stdout,
                                "CF Rep Of Abs Value Of Number Specified",
                                &cf_decomp,
                                0,
                                1,
                                &dap_denominator);

         //Destroy the decomposition--free the memory.
         GMP_RALG_cfdecomp_destroy(&cf_decomp);
         }
      else if (GMP_RATS_mpq_cmp(&(rn_in_abs), &hmax_over_kmax, NULL) == 0)
         {
         //In this case, the rational number specified is exactly the same in
         //magnitude as HMAX/KMAX.  I am inclined to suppress the CF decomp.
         printf("Rational number specified is HMAX/KMAX.  CF decomp not provided.\n");
         }
      else
         {
         //The number specified is beyond the corner point.  It is appropriate to 
         //provide the decomposition of the reciprocal rather than of the number
         //itself.
         GMP_RALG_cfdecomp_init(&cf_decomp, &error_flag, &(rn_in_abs.den), &(rn_in_abs.num));

         //Print out the continued fraction decomposition of the rational number.
         GMP_RALG_cfdecomp_emit(stdout,
                                "CF Rep Of Reciprocal Of Abs Value Of Number Specified",
                                &cf_decomp,
                                0,
                                1,
                                &dap_denominator);

         //Destroy the decomposition--free the memory.
         GMP_RALG_cfdecomp_destroy(&cf_decomp);
         }
      } //End if verbose.

   //Do all the work to get the neighbors of the number passed.
   GMP_RALG_consecutive_fab_terms(
           &(parblock->rn),
           &(parblock->kmax),
           (parblock->hmax_specified) ? (&(parblock->hmax)) : (NULL),
           1,
           1,
           &neighbor_data);

   //Print the neighbor data block for debugging.
   #if 0
   GMP_RALG_consecutive_fab_terms_result_dump(stdout, &neighbor_data);
   #endif

   //There are four possibilities at this point.
   //  a)Attempting to find the rational neighbors generated an error.
   //  b)The rational number specified was already in the series of interest,
   //    in which case we will use it.
   //  c)The left neighbor is closer or in a tie we want to choose it.
   //  d)The right neighbor is closer or in a tie we want to choose it.
   if (neighbor_data.error)
      {
      //
      printf("Internal error: %s\n", neighbor_data.error);
      }
   else if (neighbor_data.equality)
      {
      CMAIN_print_app_in_std_form(stdout,
                                  0,
                                  &(neighbor_data.rn_in),
                                  &(neighbor_data.rn_in),
                                  parblock->argblock.noformat,
                                  0,
                                  1,
                                  &dap_denominator);
      }
   else
      {
      GMP_RATS_mpq_struct left_neighbor, right_neighbor,
                          left_diff, right_diff,
                          left_abs, right_abs;
      int error_cmp;
      int mag_cmp;

      GMP_RATS_mpq_init(&left_neighbor);
      GMP_RATS_mpq_init(&right_neighbor);
      GMP_RATS_mpq_init(&left_diff);
      GMP_RATS_mpq_init(&right_diff);
      GMP_RATS_mpq_init(&left_abs);
      GMP_RATS_mpq_init(&right_abs);

      //Snatch the left neighbor.
      if (neighbor_data.n_left_out)
         {
         GMP_RATS_mpq_copy(&left_neighbor, &(neighbor_data.lefts[0].neighbor));
         }

      //Snatch the right neighbor.
      if (neighbor_data.n_right_out)
         {
         GMP_RATS_mpq_copy(&right_neighbor, &(neighbor_data.rights[0].neighbor));
         }

      //Calculate the differences, take their absolute
      //values.
      GMP_RATS_mpq_sub(&left_diff,  &left_neighbor,  &(neighbor_data.rn_in));
      GMP_RATS_mpq_sub(&right_diff, &right_neighbor, &(neighbor_data.rn_in));
      GMP_RATS_mpq_normalize(&left_diff);
      GMP_RATS_mpq_normalize(&right_diff);
      GMP_INTS_mpz_abs(&(left_diff.num));
      GMP_INTS_mpz_abs(&(right_diff.num));

      //Now that the differences are calculated, take the
      //absolute values of the neighbors themselves.
      //We will use this to break ties.
      GMP_RATS_mpq_normalize(&left_neighbor);
      GMP_RATS_mpq_normalize(&right_neighbor);
      GMP_INTS_mpz_abs(&(left_neighbor.num));
      GMP_INTS_mpz_abs(&(right_neighbor.num));

      //Compare the relative differences and magnitudes.
      error_cmp = GMP_RATS_mpq_cmp(&left_diff, &right_diff, NULL);
      mag_cmp   = GMP_RATS_mpq_cmp(&left_neighbor, &right_neighbor, NULL);

      //Figure out which to present as the best approximation and
      //do it.
      if (!(parblock->neversmaller_specified) &&
         ((parblock->neverlarger_specified) || (error_cmp < 0) || ((error_cmp == 0) && (mag_cmp < 0))))
         {
         CMAIN_print_app_in_std_form(stdout,
                                     -1,
                                     &(neighbor_data.rn_in),
                                     &(neighbor_data.lefts[0].neighbor),
                                     parblock->argblock.noformat,
                                     1,
                                     1,
                                     &dap_denominator);
         }
      else
         {
         CMAIN_print_app_in_std_form(stdout,
                                     1,
                                     &(neighbor_data.rn_in),
                                     &(neighbor_data.rights[0].neighbor),
                                     parblock->argblock.noformat,
                                     1,
                                     1,
                                     &dap_denominator);
         }

      //Deallocate.
      GMP_RATS_mpq_clear(&left_neighbor);
      GMP_RATS_mpq_clear(&right_neighbor);
      GMP_RATS_mpq_clear(&left_diff);
      GMP_RATS_mpq_clear(&right_diff);
      GMP_RATS_mpq_clear(&left_abs);
      GMP_RATS_mpq_clear(&right_abs);
      }

   //Deallocate all dynamic memory.
   GMP_RALG_consecutive_fab_terms_result_free(&neighbor_data);
   GMP_RATS_mpq_clear(&hmax_over_one);
   GMP_RATS_mpq_clear(&hmax_over_kmax);
   GMP_INTS_mpz_clear(&dap_denominator);
   GMP_RATS_mpq_clear(&rn_in_abs);

   return(rv);
   }


//Handles the case of finding multiple neighbors.

static int CMAIN_multiple_neighbor(struct CfbrapabCmainStruct *parblock)
   {
   int rv = 0;
   GMP_RATS_mpq_struct hmax_over_one, hmax_over_kmax, rn_in_abs;
   GMP_INTS_mpz_struct dap_denominator;
   GMP_RALG_cf_app_struct cf_decomp;
   GMP_RALG_fab_neighbor_collection_struct neighbor_data;
   int error_flag;
   int i;

   //Allocate all dynamic memory.
   GMP_RATS_mpq_init(&hmax_over_one);
   GMP_RATS_mpq_init(&hmax_over_kmax);
   GMP_INTS_mpz_init(&dap_denominator);
   GMP_RATS_mpq_init(&rn_in_abs);

   //Set the DAP denominator to 1e108.
   GMP_INTS_mpz_set_general_int(&dap_denominator,
                                &error_flag,
                                "1e108");

   //By convention, we will not mess with anything with an
   //absolute value greater than HMAX/1.  If such a condition exists, puke out.
   //Form up the value of HMAX/1 if HMAX was specified.
   if (parblock->hmax_specified)
      {
      GMP_INTS_mpz_copy(&(hmax_over_one.num), &(parblock->hmax));
      GMP_INTS_mpz_set_ui(&(hmax_over_one.den), 1);
      GMP_RATS_mpq_copy(&rn_in_abs, &(parblock->rn));
      GMP_INTS_mpz_abs(&(rn_in_abs.num));
      if (GMP_RATS_mpq_cmp(&(rn_in_abs), &hmax_over_one, NULL) > 0)
         {
         printf("The magnitude of the number supplied exceeds HMAX/1, and hence the number\n"
                "has no neighbors in the series of interest.  Calculation cannot continue.\n");
         exit(4);
         }
      }

   //If the "verbose" option is specified, we want to give the continued fraction
   //partial quotients and convergents of either the number to approximate,
   //its reciprocal, or none of the above, as appropriate; and give a bit more 
   //information, in addition.
   if (parblock->argblock.verbose)
      {
      if (parblock->hmax_specified)
         {
         //Stuff HMAX/KMAX.  This is necessary for comparison.
         GMP_INTS_mpz_copy(&(hmax_over_kmax.num), &(parblock->hmax));
         GMP_INTS_mpz_copy(&(hmax_over_kmax.den), &(parblock->kmax));
         }

      if (!(parblock->hmax_specified) || (GMP_RATS_mpq_cmp(&(parblock->rn), &hmax_over_kmax, NULL) < 0))
         {
         //Either HMAX was not specified or else we are below the corner point on the 
         //integer lattice.  Get the continued fraction representation of the number
         //rather than its reciprocal.
         GMP_RALG_cfdecomp_init(&cf_decomp, &error_flag, &(rn_in_abs.num), &(rn_in_abs.den));

         //Print out the continued fraction decomposition of the rational number.
         GMP_RALG_cfdecomp_emit(stdout,
                                "CF Representation Of Absolute Value Of Rational Number Specified",
                                &cf_decomp,
                                0,
                                1,
                                &dap_denominator);

         //Destroy the decomposition--free the memory.
         GMP_RALG_cfdecomp_destroy(&cf_decomp);
         }
      else if (GMP_RATS_mpq_cmp(&(rn_in_abs), &hmax_over_kmax, NULL) == 0)
         {
         //In this case, the rational number specified is exactly the same in
         //magnitude as HMAX/KMAX.  I am inclined to suppress the CF decomp.
         printf("Rational number specified is HMAX/KMAX.  CF decomp not provided.\n");
         }
      else
         {
         //The number specified is beyond the corner point.  It is appropriate to 
         //provide the decomposition of the reciprocal rather than of the number
         //itself.
         GMP_RALG_cfdecomp_init(&cf_decomp, &error_flag, &(rn_in_abs.den), &(rn_in_abs.num));

         //Print out the continued fraction decomposition of the rational number.
         GMP_RALG_cfdecomp_emit(stdout,
                                "CF Representation Of Reciprocal Of Absolute Value Of Rational Number Specified",
                                &cf_decomp,
                                0,
                                1,
                                &dap_denominator);

         //Destroy the decomposition--free the memory.
         GMP_RALG_cfdecomp_destroy(&cf_decomp);
         }
      } //End if verbose.

   //Do all the work to get the neighbors of the number passed.
   GMP_RALG_consecutive_fab_terms(
           &(parblock->rn),
           &(parblock->kmax),
           (parblock->hmax_specified) ? (&(parblock->hmax)) : (NULL),
           parblock->n,
           parblock->n,
           &neighbor_data);

   //Print the neighbor data block for debugging.
   #if 0
   GMP_RALG_consecutive_fab_terms_result_dump(stdout, &neighbor_data);
   #endif

   //Loop through, printing out the left neighbors in order.
   for (i = neighbor_data.n_left_out - 1; i >= 0; i--)
      {
      CMAIN_print_app_in_std_form(stdout,
                                  -(i + 1),
                                  &(neighbor_data.rn_in),
                                  &(neighbor_data.lefts[i].neighbor),
                                  parblock->argblock.noformat,
                                  1,
                                  1,
                                  &dap_denominator);
      }

   //If the number itself appears in the series of interest, spit that out.
   if (neighbor_data.equality)
      {
      CMAIN_print_app_in_std_form(stdout,
                                  0,
                                  &(neighbor_data.rn_in),
                                  &(neighbor_data.norm_rn),
                                  parblock->argblock.noformat,
                                  1,
                                  1,
                                  &dap_denominator);
      }

   //Loop through, printing out the right neighbors in order.
   for (i = 0; i < neighbor_data.n_right_out; i++)
      {
      CMAIN_print_app_in_std_form(stdout,
                                  i+1,
                                  &(neighbor_data.rn_in),
                                  &(neighbor_data.rights[i].neighbor),
                                  parblock->argblock.noformat,
                                  1,
                                  1,
                                  &dap_denominator);
      }

   //Deallocate all dynamic memory.
   GMP_RALG_consecutive_fab_terms_result_free(&neighbor_data);
   GMP_RATS_mpq_clear(&hmax_over_one);
   GMP_RATS_mpq_clear(&hmax_over_kmax);
   GMP_INTS_mpz_clear(&dap_denominator);
   GMP_RATS_mpq_clear(&rn_in_abs);

   return(rv);
   }


//Handles the case of finding the predecessor.
int CMAIN_predecessor(struct CfbrapabCmainStruct *parblock)
   {
   int rv = 0;
   GMP_RATS_mpq_struct hmax_over_one, hmax_over_kmax, rn_in_abs;
   GMP_INTS_mpz_struct dap_denominator;
   GMP_RALG_cf_app_struct cf_decomp;
   GMP_RALG_fab_neighbor_collection_struct neighbor_data;
   int error_flag;

   //Allocate all dynamic memory.
   GMP_RATS_mpq_init(&hmax_over_one);
   GMP_RATS_mpq_init(&hmax_over_kmax);
   GMP_INTS_mpz_init(&dap_denominator);
   GMP_RATS_mpq_init(&rn_in_abs);

   //Set the DAP denominator to 1e108.
   GMP_INTS_mpz_set_general_int(&dap_denominator,
                                &error_flag,
                                "1e108");

   //By convention, we will not mess with anything with an
   //absolute value greater than HMAX/1.  If such a condition exists, puke out.
   //Form up the value of HMAX/1 if HMAX was specified.
   if (parblock->hmax_specified)
      {
      GMP_INTS_mpz_copy(&(hmax_over_one.num), &(parblock->hmax));
      GMP_INTS_mpz_set_ui(&(hmax_over_one.den), 1);
      GMP_RATS_mpq_copy(&rn_in_abs, &(parblock->rn));
      GMP_INTS_mpz_abs(&(rn_in_abs.num));
      if (GMP_RATS_mpq_cmp(&(rn_in_abs), &hmax_over_one, NULL) > 0)
         {
         printf("The magnitude of the number supplied exceeds HMAX/1, and hence the number\n"
                "has no neighbors in the series of interest.  Calculation cannot continue.\n");
         exit(4);
         }
      }

   //If the "verbose" option is specified, we want to give the continued fraction
   //partial quotients and convergents of either the number to approximate,
   //its reciprocal, or none of the above, as appropriate; and give a bit more 
   //information, in addition.
   if (parblock->argblock.verbose)
      {
      if (parblock->hmax_specified)
         {
         //Stuff HMAX/KMAX.  This is necessary for comparison.
         GMP_INTS_mpz_copy(&(hmax_over_kmax.num), &(parblock->hmax));
         GMP_INTS_mpz_copy(&(hmax_over_kmax.den), &(parblock->kmax));
         }

      if (!(parblock->hmax_specified) || (GMP_RATS_mpq_cmp(&(parblock->rn), &hmax_over_kmax, NULL) < 0))
         {
         //Either HMAX was not specified or else we are below the corner point on the 
         //integer lattice.  Get the continued fraction representation of the number
         //rather than its reciprocal.
         GMP_RALG_cfdecomp_init(&cf_decomp, &error_flag, &(rn_in_abs.num), &(rn_in_abs.den));

         //Print out the continued fraction decomposition of the rational number.
         GMP_RALG_cfdecomp_emit(stdout,
                                "CF Representation Of Absolute Value Of Rational Number Specified",
                                &cf_decomp,
                                0,
                                1,
                                &dap_denominator);

         //Destroy the decomposition--free the memory.
         GMP_RALG_cfdecomp_destroy(&cf_decomp);
         }
      else if (GMP_RATS_mpq_cmp(&(rn_in_abs), &hmax_over_kmax, NULL) == 0)
         {
         //In this case, the rational number specified is exactly the same in
         //magnitude as HMAX/KMAX.  I am inclined to suppress the CF decomp.
         printf("Rational number specified is HMAX/KMAX.  CF decomp not provided.\n");
         }
      else
         {
         //The number specified is beyond the corner point.  It is appropriate to 
         //provide the decomposition of the reciprocal rather than of the number
         //itself.
         GMP_RALG_cfdecomp_init(&cf_decomp, &error_flag, &(rn_in_abs.den), &(rn_in_abs.num));

         //Print out the continued fraction decomposition of the rational number.
         GMP_RALG_cfdecomp_emit(stdout,
                                "CF Representation Of Reciprocal Of Absolute Value Of Rational Number Specified",
                                &cf_decomp,
                                0,
                                1,
                                &dap_denominator);

         //Destroy the decomposition--free the memory.
         GMP_RALG_cfdecomp_destroy(&cf_decomp);
         }
      } //End if verbose.

   //Do all the work to get the neighbors of the number passed.
   GMP_RALG_consecutive_fab_terms(
           &(parblock->rn),
           &(parblock->kmax),
           (parblock->hmax_specified) ? (&(parblock->hmax)) : (NULL),
           1,
           0,
           &neighbor_data);

   //Print the neighbor data block for debugging.
   #if 0
   GMP_RALG_consecutive_fab_terms_result_dump(stdout, &neighbor_data);
   #endif

   //Print the neighbor on the left, if it exists.
   if (neighbor_data.n_left_out)
      {
      CMAIN_print_app_in_std_form(stdout,
                                  -1,
                                  &(neighbor_data.rn_in),
                                  &(neighbor_data.lefts[0].neighbor),
                                  parblock->argblock.noformat,
                                  0,
                                  0,
                                  &dap_denominator);
      }

   //Deallocate all dynamic memory.
   GMP_RALG_consecutive_fab_terms_result_free(&neighbor_data);
   GMP_RATS_mpq_clear(&hmax_over_one);
   GMP_RATS_mpq_clear(&hmax_over_kmax);
   GMP_INTS_mpz_clear(&dap_denominator);
   GMP_RATS_mpq_clear(&rn_in_abs);

   return(rv);
   }


//Handles the case of finding the successor.
int CMAIN_successor(struct CfbrapabCmainStruct *parblock)
   {
   int rv = 0;
   GMP_RATS_mpq_struct hmax_over_one, hmax_over_kmax, rn_in_abs;
   GMP_INTS_mpz_struct dap_denominator;
   GMP_RALG_cf_app_struct cf_decomp;
   GMP_RALG_fab_neighbor_collection_struct neighbor_data;
   int error_flag;

   //Allocate all dynamic memory.
   GMP_RATS_mpq_init(&hmax_over_one);
   GMP_RATS_mpq_init(&hmax_over_kmax);
   GMP_INTS_mpz_init(&dap_denominator);
   GMP_RATS_mpq_init(&rn_in_abs);

   //Set the DAP denominator to 1e108.
   GMP_INTS_mpz_set_general_int(&dap_denominator,
                                &error_flag,
                                "1e108");

   //By convention, we will not mess with anything with an
   //absolute value greater than HMAX/1.  If such a condition exists, puke out.
   //Form up the value of HMAX/1 if HMAX was specified.
   if (parblock->hmax_specified)
      {
      GMP_INTS_mpz_copy(&(hmax_over_one.num), &(parblock->hmax));
      GMP_INTS_mpz_set_ui(&(hmax_over_one.den), 1);
      GMP_RATS_mpq_copy(&rn_in_abs, &(parblock->rn));
      GMP_INTS_mpz_abs(&(rn_in_abs.num));
      if (GMP_RATS_mpq_cmp(&(rn_in_abs), &hmax_over_one, NULL) > 0)
         {
         printf("The magnitude of the number supplied exceeds HMAX/1, and hence the number\n"
                "has no neighbors in the series of interest.  Calculation cannot continue.\n");
         exit(4);
         }
      }

   //If the "verbose" option is specified, we want to give the continued fraction
   //partial quotients and convergents of either the number to approximate,
   //its reciprocal, or none of the above, as appropriate; and give a bit more 
   //information, in addition.
   if (parblock->argblock.verbose)
      {
      if (parblock->hmax_specified)
         {
         //Stuff HMAX/KMAX.  This is necessary for comparison.
         GMP_INTS_mpz_copy(&(hmax_over_kmax.num), &(parblock->hmax));
         GMP_INTS_mpz_copy(&(hmax_over_kmax.den), &(parblock->kmax));
         }

      if (!(parblock->hmax_specified) || (GMP_RATS_mpq_cmp(&(parblock->rn), &hmax_over_kmax, NULL) < 0))
         {
         //Either HMAX was not specified or else we are below the corner point on the 
         //integer lattice.  Get the continued fraction representation of the number
         //rather than its reciprocal.
         GMP_RALG_cfdecomp_init(&cf_decomp, &error_flag, &(rn_in_abs.num), &(rn_in_abs.den));

         //Print out the continued fraction decomposition of the rational number.
         GMP_RALG_cfdecomp_emit(stdout,
                                "CF Representation Of Absolute Value Of Rational Number Specified",
                                &cf_decomp,
                                0,
                                1,
                                &dap_denominator);

         //Destroy the decomposition--free the memory.
         GMP_RALG_cfdecomp_destroy(&cf_decomp);
         }
      else if (GMP_RATS_mpq_cmp(&(rn_in_abs), &hmax_over_kmax, NULL) == 0)
         {
         //In this case, the rational number specified is exactly the same in
         //magnitude as HMAX/KMAX.  I am inclined to suppress the CF decomp.
         printf("Rational number specified is HMAX/KMAX.  CF decomp not provided.\n");
         }
      else
         {
         //The number specified is beyond the corner point.  It is appropriate to 
         //provide the decomposition of the reciprocal rather than of the number
         //itself.
         GMP_RALG_cfdecomp_init(&cf_decomp, &error_flag, &(rn_in_abs.den), &(rn_in_abs.num));

         //Print out the continued fraction decomposition of the rational number.
         GMP_RALG_cfdecomp_emit(stdout,
                                "CF Representation Of Reciprocal Of Absolute Value Of Rational Number Specified",
                                &cf_decomp,
                                0,
                                1,
                                &dap_denominator);

         //Destroy the decomposition--free the memory.
         GMP_RALG_cfdecomp_destroy(&cf_decomp);
         }
      } //End if verbose.

   //Do all the work to get the neighbors of the number passed.
   GMP_RALG_consecutive_fab_terms(
           &(parblock->rn),
           &(parblock->kmax),
           (parblock->hmax_specified) ? (&(parblock->hmax)) : (NULL),
           0,
           1,
           &neighbor_data);

   //Print the neighbor data block for debugging.
   #if 0
   GMP_RALG_consecutive_fab_terms_result_dump(stdout, &neighbor_data);
   #endif

   //Print the neighbor on the right, if it exists.
   if (neighbor_data.n_right_out)
      {
      CMAIN_print_app_in_std_form(stdout,
                                  -1,
                                  &(neighbor_data.rn_in),
                                  &(neighbor_data.rights[0].neighbor),
                                  parblock->argblock.noformat,
                                  0,
                                  0,
                                  &dap_denominator);
      }

   //Deallocate all dynamic memory.
   GMP_RALG_consecutive_fab_terms_result_free(&neighbor_data);
   GMP_RATS_mpq_clear(&hmax_over_one);
   GMP_RATS_mpq_clear(&hmax_over_kmax);
   GMP_INTS_mpz_clear(&dap_denominator);
   GMP_RATS_mpq_clear(&rn_in_abs);

   return(rv);
   }


int c_main(int argc, char* argv[])
   {
   int rv=0;
   struct CfbrapabCmainStruct parblock;

   if (argc==2 && !strcmp(argv[1], "-help"))
      {
      FCMIOF_hline();
      printf("DESCRIPTION\n");
      printf("   This utility calculates best rational approximations of the form h/k\n");
      printf("   under the constraint k <= KMAX (i.e. in the Farey series of order KMAX),\n");
      printf("   or under the constraints k <= KMAX and h <= HMAX (i.e. in a rectangular\n");
      printf("   region of the integer lattice).  This utility uses continued fraction\n");
      printf("   algorithms presented in the accompanying book \"A Practitioner's Guide\n");
      printf("   ...\", and this book (a work in progress) should be consulted both as a\n");
      printf("   reference to the algorithms and a reference for this utility.  All\n");
      printf("   rational numbers calculated are in lowest terms.  This utility will\n");
      printf("   operate on negative numbers, but all results are produced by symmetry\n");
      printf("   (the continued fraction representation of negative numbers is NOT\n");
      printf("   calculated).  The default operation of this utility is to calculated the\n");
      printf("   closest rational number in the series of interest.  If the rational\n");
      printf("   number supplied is equidistant between two formable rational numbers in\n");
      printf("   the series of interest, the neighbor smaller in magnitude is returned.  If\n");
      printf("   the rational number supplied is already formable, it is returned in lowest\n");
      printf("   terms.  If the rational number supplied does not have neighbors (i.e. it\n");
      printf("   is larger than HMAX/1), an error is generated.\n");
      printf("\n");
      printf("USAGE\n");
      printf("   cfbrapab srn urn_kmax [options]\n");
      printf("   cfbrapab srn urn_kmax urn_hmax [options]\n");
      printf("   cfbrapab -help\n");
      printf("\n");
      printf("OPTIONS\n");
      printf("   -neversmaller, -neverlarger\n");
      printf("      The -neversmaller option will prohibit this utility from choosing a\n");
      printf("      rational approximation which is smaller than the rational number\n");
      printf("      supplied.  Thus, this option will force the utility to choose the right\n");
      printf("      neighbor rather than the left, regardless of relative distance.  The\n");
      printf("      behavior if the rational number supplied is formable under the \n");
      printf("      constraints is unchanged.  The -neverlarger option is analogous.\n");
      printf("      These options cannot be used with -n, -pred, or -succ.\n");
      printf("   -pred, -succ\n");
      printf("      Will cause the utility to find the predecessor or successor in the\n");
      printf("      series of interest to the rational number supplied (in the event the\n");
      printf("      number supplied is already formable under the constraints).  For\n");
      printf("      numbers not already formable under the constraints, the left or right\n");
      printf("      formable neighbor will be returned.  Supplying a rational number that\n");
      printf("      does not have a predecessor or successor (i.e. < 0/1 or > HMAX/1) will\n");
      printf("      generate an error.  These options cannot be used with -neversmaller,\n");
      printf("      -neverlarger, or -n.\n");
      CU_MSGS_std_options(stdout, PNAME);
      FCMIOF_hline();
      CU_MSGS_toolset_info_msg(stdout, PNAME);
      FCMIOF_hline();
      }
   else if (argc < 3)
      {
      CU_MSGS_too_few_args_msg(stdout, PNAME);
      rv = 4;
      goto ret_pt;
      }
   else
      {
      //In this branch, we must have an invocation of the form
      //   cfbrapab SRN KMAX <options>
      //or
      //   cfbrapab SRN KMAX HMAX <options>
      //
      //Call the function to collect all the command-line parameters.
      //This function takes care of error processing, as well.  If there
      //is an error of any kind, the function will simply abort and 
      //supply the right return error code of 4.
      process_command_line_args(&parblock,
                                 argc, 
                                 argv);

      //If the debug option was set, emit the debugging information.
      if (parblock.argblock.debug)
         {
         FCMIOF_hline();
         CU_MSGS_emit_vcinfo_from_ptr_table(stdout,C_MAIN_vcinfoptrs,PNAMEUC);
         }

      //Emit the opening horizontal line iff the -nf option isn't set.
      if (!(parblock.argblock.noformat))
         FCMIOF_hline();

      //Print out a major mode message to indicate what we are trying to do.
      if (!(parblock.argblock.noformat))
         {
         if (!parblock.neversmaller_specified && !parblock.neverlarger_specified && !parblock.pred_specified && !parblock.succ_specified)
            {
            printf("MAJOR MODE:  Finding closest rational number(s) under the constraints.\n");
            }
         else if (parblock.neversmaller_specified)
            {
            printf("MAJOR MODE:  Finding closest rational number with magnitude not smaller under\n             the constraints.\n");
            }
         else if (parblock.neverlarger_specified)
            {
            printf("MAJOR MODE:  Finding closest rational number with magnitude not larger under\n             the constraints.\n");
            }
         else if (parblock.pred_specified)
            {
            printf("MAJOR MODE:  Finding predecessor under the constraints.\n");
            }
         else if (parblock.succ_specified)
            {
            printf("MAJOR MODE:  Finding successor under the constraints.\n");
            }
         else
            {
            assert(0);
            }

         FCMIOF_hline();
         }

      //Echo back the command-line parameters.
      if (!(parblock.argblock.noformat))
         {
         GMP_INTS_mpz_long_int_format_to_stream(stdout,
                                                &(parblock.rn.num),
                                                "RI_IN   Numerator");
         FCMIOF_hline();
         GMP_INTS_mpz_long_int_format_to_stream(stdout,
                                                &(parblock.rn.den),
                                                "RI_IN Denominator");
         FCMIOF_hline();

         GMP_INTS_mpz_long_int_format_to_stream(stdout,
                                                &(parblock.kmax),
                                                "K_MAX");
         FCMIOF_hline();

         if (parblock.hmax_specified)
            {
            GMP_INTS_mpz_long_int_format_to_stream(stdout,
                                                   &(parblock.hmax),
                                                   "H_MAX");
            FCMIOF_hline();
            }

         if (parblock.n_specified)
            {
            GMP_INTS_mpz_struct temp24;

            GMP_INTS_mpz_init(&temp24);

            GMP_INTS_mpz_set_ui(&temp24, parblock.n);

            GMP_INTS_mpz_long_int_format_to_stream(stdout,
                                                   &temp24,
                                                   "Number Of Neighbors");

            FCMIOF_hline();

            GMP_INTS_mpz_clear(&temp24);
            }
         }

      //We need to split now into distinct cases
      //depending on the command-line parameters.  We will
      //then hack out solutions for each case.
      if (!parblock.pred_specified && !parblock.succ_specified && !parblock.n_specified)
         {
         //Classic closest neighbor case.
         rv = CMAIN_classic_closest_neighbor(&parblock);
         }
      else if (parblock.n_specified)
         {
         //Classic multiple neighbor case.
         rv = CMAIN_multiple_neighbor(&parblock);
         }
      else if (parblock.pred_specified)
         {
         rv = CMAIN_predecessor(&parblock);
         }
      else if (parblock.succ_specified)
         {
         rv = CMAIN_successor(&parblock);
         }
      else
         {
         assert(0);
         }

      //Emit the closing horizontal line iff the -nf option isn't set.
      //if (!(parblock.argblock.noformat))
      //   FCMIOF_hline();

      //Release all dynamic memory.
      release_command_line_args(&parblock);
      }

   ret_pt:
   return(rv);
   }

// End of c_main.c.
