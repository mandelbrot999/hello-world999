//$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tclxtens_7_5/arblenints.c 71 2016-11-05 11:07:06Z dashley $
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
#define MODULE_ARBLENINTS

#include <assert.h>
#include <string.h>

#include "tcl.h"
#include "tcldecls.h"

#include "arblenints.h"
#include "bstrfunc.h"
#include "extninit.h"
#include "gmp_ints.h"
#include "gmp_rats.h"
#include "gmp_ralg.h"
#include "intfunc.h"
#include "tclalloc.h"


//Handles the "cfbrapab" subextension.
//08/16/01: Visual inspection OK.
static
int ARBLENINTS_cfbrapab_handler(ClientData dummy, 
                                Tcl_Interp *interp, 
                                int objc,
                                Tcl_Obj *objv[])
   {
   Tcl_Obj *rv;

   //We must have at least two additional arguments
   //to this extension.
   if (objc < 4)
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "srn uint_kmax ?uint_hmax? ?options?");
      return(TCL_ERROR);
      }
   else
      {
      char *input_arg;
      int failure, first_dashed_parameter;
      char *string_result;
      int string_result_n_allocd;
      int chars_reqd;
      int i;
      int pred_option_specified         = 0;
      int succ_option_specified         = 0;
      int neversmaller_option_specified = 0;
      int neverlarger_option_specified  = 0;
      int n_option_specified            = 0;
      unsigned n                        = 0;

      GMP_RATS_mpq_struct q_rn;
      GMP_INTS_mpz_struct z_kmax;
      GMP_INTS_mpz_struct z_hmax;

      //Allocate dynamic memory.
      GMP_RATS_mpq_init(&q_rn);
      GMP_INTS_mpz_init(&z_kmax);
      GMP_INTS_mpz_init(&z_hmax);

      //Grab a pointer to the string representation of
      //the first input argument.  The storage does not belong to us.
      input_arg = Tcl_GetString(objv[2]);
      assert(input_arg != NULL);

      //Try to parse our first input string as a rational number.
      //If we are not successful in this, must abort.
      GMP_RATS_mpq_set_all_format_rat_num(input_arg,
                                          &failure,
                                          &q_rn);

      if (failure)
         {
         rv = Tcl_NewStringObj("arbint cfbrapab: \"", -1);
         Tcl_AppendToObj(rv, input_arg, -1);

         Tcl_AppendToObj(rv, "\" is not a recognized rational number.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_RATS_mpq_clear(&q_rn);
         GMP_INTS_mpz_clear(&z_kmax);
         GMP_INTS_mpz_clear(&z_hmax);

         return(TCL_ERROR);
         }

      //Try to parse our next argument as an integer, which
      //will be KMAX.  This must be specified.
      //
      //Get string pointer.  Storage does not belong to us.
      input_arg = Tcl_GetString(objv[3]);
      assert(input_arg != NULL);

      //Try to convert KMAX to an integer.  Fatal if an error,
      //and fatal if the argument is zero or negative.
      GMP_INTS_mpz_set_general_int(&z_kmax, &failure, input_arg);

      //If there was a parse failure or if the integer is zero
      //or negative, must flag error.
      if (failure || GMP_INTS_mpz_is_neg(&z_kmax) || GMP_INTS_mpz_is_zero(&z_kmax))
         {
         rv = Tcl_NewStringObj("arbint cfbrapab: \"", -1);
         Tcl_AppendToObj(rv, input_arg, -1);
         Tcl_AppendToObj(rv, "\" is not a recognized positive integer.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_RATS_mpq_clear(&q_rn);
         GMP_INTS_mpz_clear(&z_kmax);
         GMP_INTS_mpz_clear(&z_hmax);

         return(TCL_ERROR);
         }

      //We need to look for HMAX as the next parameter, if it exists.
      //The way we will figure this out is by whether the
      //parameter begins with a "-" or not.
      if (objc >= 5)
         {
         input_arg = Tcl_GetString(objv[4]);
         assert(input_arg != NULL);

         if (input_arg[0] == '-')
            {
            first_dashed_parameter = 4;
            }
         else
            {
            first_dashed_parameter = 5;
            }
         }
      else
         {
         first_dashed_parameter = 4;
         }

      //If there is another parameter and it
      //doesn't begin with a dash, try to parse
      //it as HMAX.  We don't explicitly record whether
      //HMAX is specified, because zero is a signal
      //when calculating Farey neighbors that HMAX isn't
      //to be considered.
      if ((objc >= 5) && (first_dashed_parameter == 5))
         {
         //Get string pointer.  Storage does not belong to us.
         input_arg = Tcl_GetString(objv[4]);
         assert(input_arg != NULL);

         //Try to convert HMAX to an integer.  Fatal if an error,
         //and fatal if the argument is zero or negative.
         GMP_INTS_mpz_set_general_int(&z_hmax, &failure, input_arg);

         //If there was a parse failure or if the integer is zero
         //or negative, must flag error.
         if (failure || GMP_INTS_mpz_is_neg(&z_hmax) || GMP_INTS_mpz_is_zero(&z_hmax))
            {
            rv = Tcl_NewStringObj("arbint cfbrapab: \"", -1);
            Tcl_AppendToObj(rv, input_arg, -1);
            Tcl_AppendToObj(rv, "\" is not a recognized positive integer.", -1);
            Tcl_SetObjResult(interp, rv);

            GMP_RATS_mpq_clear(&q_rn);
            GMP_INTS_mpz_clear(&z_kmax);
            GMP_INTS_mpz_clear(&z_hmax);

            return(TCL_ERROR);
            }
         }

      //Process all of the dashed command-line arguments.
      //This involves iterating through all of the 
      //parameters and processing them.
      for (i=first_dashed_parameter; i<objc; i++)
         {
         input_arg = Tcl_GetString(objv[i]);
         assert(input_arg != NULL);

         if (!strcmp("-pred", input_arg))
            {
            pred_option_specified = 1;
            }
         else if (!strcmp("-succ", input_arg))
            {
            succ_option_specified = 1;
            }
         else if (!strcmp("-neversmaller", input_arg))
            {
            neversmaller_option_specified = 1;
            }
         else if (!strcmp("-neverlarger", input_arg))
            {
            neverlarger_option_specified = 1;
            }
         else if (!strcmp("-n", input_arg))
            {
            n_option_specified = 1;

            //If -n was specified, there must be a following
            //parameter which supplies the integer.  First
            //check for existence of an additional parameter.
            if (i >= (objc - 1))
               {
               rv = Tcl_NewStringObj("arbint cfbrapab: -n option specified without following integer.", -1);
               Tcl_SetObjResult(interp, rv);

               GMP_RATS_mpq_clear(&q_rn);
               GMP_INTS_mpz_clear(&z_kmax);
               GMP_INTS_mpz_clear(&z_hmax);

               return(TCL_ERROR);
               }

            //We have at least one additional parameter.  Try
            //to parse out the next parameter as the integer
            //we need for n.
            i++;

            input_arg = Tcl_GetString(objv[i]);
            assert(input_arg != NULL);

            GMP_INTS_mpz_parse_into_uint32(&n, &failure, input_arg);

            //If the parse was unsuccessful, terminate.
            if (failure)
               {
               rv = Tcl_NewStringObj("arbint cfbrapab: -n option followed by invalid integer.", -1);
               Tcl_SetObjResult(interp, rv);

               GMP_RATS_mpq_clear(&q_rn);
               GMP_INTS_mpz_clear(&z_kmax);
               GMP_INTS_mpz_clear(&z_hmax);

               return(TCL_ERROR);
               }

            //Clip the integer into a 24-bit quantity.
            n &= 0x00FFFFFF;
            }
         else
            {
            //Unrecognized option.  Crash out.
            rv = Tcl_NewStringObj("arbint cfbrapab: \"", -1);
            Tcl_AppendToObj(rv, input_arg, -1);
            Tcl_AppendToObj(rv, "\" is not a recognized option.", -1);
            Tcl_SetObjResult(interp, rv);

            GMP_RATS_mpq_clear(&q_rn);
            GMP_INTS_mpz_clear(&z_kmax);
            GMP_INTS_mpz_clear(&z_hmax);

            return(TCL_ERROR);
            }
         }

      //Look for any mutually exclusive options.  Give a catchall if any of
      //them specified.  Because we set them all to 1, addition is the easiest
      //way to do this.
      if ((pred_option_specified + succ_option_specified + neversmaller_option_specified 
           + neverlarger_option_specified + n_option_specified) > 1)
         {
         rv = Tcl_NewStringObj("arbint cfbrapab: -pred, -succ, -neversmaller, -neverlarger, and -n are mutually exclusive options.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_RATS_mpq_clear(&q_rn);
         GMP_INTS_mpz_clear(&z_kmax);
         GMP_INTS_mpz_clear(&z_hmax);

         return(TCL_ERROR);
         }

      //Split into cases based on what we're doing.  This is wasteful of code,
      //but this is a PC application, not an embedded application.  In all cases
      //create a hard error if something goes wrong.  Any anomalies should trash
      //a script.
      if (!pred_option_specified && !succ_option_specified && !n_option_specified)
         {
         //This is the traditional best approximation case, with the possibility of
         //the -neverlarger or -neversmaller being specified.  This is the most messy
         //of all the cases.  We must gather neighbors and figure out which is closer,
         //and if there is a tie, which has the smaller magnitude.  It is fairly 
         //messy.
         GMP_RALG_fab_neighbor_collection_struct neighbor_data;
         GMP_RATS_mpq_struct left_neigh, right_neigh, diff_left, diff_right, closer_neighbor;
         int dist_cmp;
         int mag_cmp;

         //Allocate inner dynamic variables.
         GMP_RATS_mpq_init(&left_neigh);
         GMP_RATS_mpq_init(&right_neigh);
         GMP_RATS_mpq_init(&diff_left);
         GMP_RATS_mpq_init(&diff_right);
         GMP_RATS_mpq_init(&closer_neighbor);

         //Form up the neighbor data.  We're only looking for up to one neighbor on each
         //side.
         GMP_RALG_consecutive_fab_terms(
                                       &q_rn,
                                       &z_kmax,
                                       &z_hmax,
                                       1,
                                       1,
                                       &neighbor_data
                                       );

         //If there was an error or we couldn't get any neighbors to play with, give
         //an error return.  As long as we have one neighbor on either side, we can definitely
         //complete.
         if (neighbor_data.error || (!neighbor_data.equality && (!neighbor_data.n_left_out || !neighbor_data.n_right_out)))
            {
            rv = Tcl_NewStringObj("arbint cfbrapab: unable to form neighbors.", -1);
            Tcl_SetObjResult(interp, rv);

            GMP_RALG_consecutive_fab_terms_result_free(&neighbor_data);
            GMP_RATS_mpq_clear(&q_rn);
            GMP_INTS_mpz_clear(&z_kmax);
            GMP_INTS_mpz_clear(&z_hmax);

            GMP_RATS_mpq_clear(&left_neigh);
            GMP_RATS_mpq_clear(&right_neigh);
            GMP_RATS_mpq_clear(&diff_left);
            GMP_RATS_mpq_clear(&diff_right);
            GMP_RATS_mpq_clear(&closer_neighbor);

            return(TCL_ERROR);
            }

         if (neighbor_data.equality)
            {
            //The equality case takes precedence, always.
            GMP_RATS_mpq_copy(&closer_neighbor, &(neighbor_data.norm_rn));
            }
         else
            {
            //The boolean test somewhat above guaranteed that we have both left
            //and right neighbors.  We can assume this.
            GMP_RATS_mpq_copy(&left_neigh,  &(neighbor_data.lefts[0].neighbor));
            GMP_RATS_mpq_copy(&right_neigh, &(neighbor_data.rights[0].neighbor));

            GMP_RATS_mpq_sub(&diff_left,  &left_neigh,  &(neighbor_data.norm_rn));
            GMP_RATS_mpq_sub(&diff_right, &right_neigh, &(neighbor_data.norm_rn));
            GMP_INTS_mpz_abs(&(diff_left.num));
            GMP_INTS_mpz_abs(&(diff_right.num));
            dist_cmp = GMP_RATS_mpq_cmp(&diff_left, &diff_right, NULL);

            //If we have a tie on the distance, will need to revert to magnitude of the neighbors.
            GMP_INTS_mpz_abs(&(left_neigh.num));
            GMP_INTS_mpz_abs(&(right_neigh.num));
            mag_cmp = GMP_RATS_mpq_cmp(&left_neigh, &right_neigh, NULL);

            if (!neversmaller_option_specified 
               && 
               (neverlarger_option_specified || (dist_cmp < 0) || ((dist_cmp==0) && (mag_cmp < 0))))
               {
               GMP_RATS_mpq_copy(&closer_neighbor, &(neighbor_data.lefts[0].neighbor));
               }
            else
               {
               GMP_RATS_mpq_copy(&closer_neighbor, &(neighbor_data.rights[0].neighbor));
               }
            }

         //Stuff our variable of choice into a string ...
         chars_reqd = INTFUNC_max(
                                 GMP_INTS_mpz_size_in_base_10(&(closer_neighbor.num)),
                                 GMP_INTS_mpz_size_in_base_10(&(closer_neighbor.den))
                                 );
         string_result = TclpAlloc(sizeof(char) * chars_reqd);
         assert(string_result != NULL);

         GMP_INTS_mpz_to_string(string_result, &(closer_neighbor.num));
         rv = Tcl_NewStringObj(string_result, -1);
         Tcl_AppendToObj(rv, "/", -1);
         GMP_INTS_mpz_to_string(string_result, &(closer_neighbor.den));
         Tcl_AppendToObj(rv, string_result, -1);

         Tcl_SetObjResult(interp, rv);

         //Deallocate variables, make normal return.
         TclpFree(string_result);
         GMP_RALG_consecutive_fab_terms_result_free(&neighbor_data);
         GMP_RATS_mpq_clear(&q_rn);
         GMP_INTS_mpz_clear(&z_kmax);
         GMP_INTS_mpz_clear(&z_hmax);

         GMP_RATS_mpq_clear(&left_neigh);
         GMP_RATS_mpq_clear(&right_neigh);
         GMP_RATS_mpq_clear(&diff_left);
         GMP_RATS_mpq_clear(&diff_right);
         GMP_RATS_mpq_clear(&closer_neighbor);

         return(TCL_OK);
         }
      else if (n_option_specified)
         {
         char sbuf[50];
            //Static buffer just to stage 32-bit integers.
           
         //Multiple neighbors.  Must iterate through.

         GMP_RALG_fab_neighbor_collection_struct neighbor_data;

         //Form up the neighbor data.       
         GMP_RALG_consecutive_fab_terms(
                                       &q_rn,
                                       &z_kmax,
                                       &z_hmax,
                                       n,
                                       n,
                                       &neighbor_data
                                       );

         //If there was an error forming up the neighbor data, create a hard error.
         if (neighbor_data.error)
            {
            rv = Tcl_NewStringObj("arbint cfbrapab: unable to form neighbors.", -1);
            Tcl_SetObjResult(interp, rv);

            GMP_RALG_consecutive_fab_terms_result_free(&neighbor_data);
            GMP_RATS_mpq_clear(&q_rn);
            GMP_INTS_mpz_clear(&z_kmax);
            GMP_INTS_mpz_clear(&z_hmax);

            return(TCL_ERROR);
            }

         //Allocate a default buffer of 10K for the ASCII representation of integers.
         //In the vast majority of cases, there will be only one allocation, because it
         //takes a mean integer to exceed 10K.  However, the logic allows it to grow.
         string_result_n_allocd = 10000;
         string_result = TclpAlloc(sizeof(char) * string_result_n_allocd);
         assert(string_result != NULL);

         //Start off with a return value of the null string.
         rv = Tcl_NewStringObj("", -1);

         //Loop through, spitting out the left neighbors.
         for (i = neighbor_data.n_left_out-1; i >= 0; i--)
            {
            //The protocol here is everyone spits out one space before
            //they print anything.  Must skip this on first loop iteration.
            if (i != neighbor_data.n_left_out-1)
               Tcl_AppendToObj(rv, " ", -1);

            //The index will be the negative of the iteration variable minus one.
            sprintf(sbuf, "%d", -i - 1);
            Tcl_AppendToObj(rv, sbuf, -1);
            
            //Force the buffer to have enough space for the components of the rational
            //number.
            chars_reqd = INTFUNC_max(
                                    GMP_INTS_mpz_size_in_base_10(&(neighbor_data.lefts[i].neighbor.num)),
                                    GMP_INTS_mpz_size_in_base_10(&(neighbor_data.lefts[i].neighbor.den))
                                    );
            if (chars_reqd > string_result_n_allocd)
               {
               string_result_n_allocd = chars_reqd;
               string_result = TclpRealloc(string_result, sizeof(char) * string_result_n_allocd);
               assert(string_result != NULL);
               }

            //Print the rational number out to the Tcl object.
            Tcl_AppendToObj(rv, " ", -1);
            GMP_INTS_mpz_to_string(string_result, &(neighbor_data.lefts[i].neighbor.num));
            Tcl_AppendToObj(rv, string_result, -1);
            Tcl_AppendToObj(rv, "/", -1);
            GMP_INTS_mpz_to_string(string_result, &(neighbor_data.lefts[i].neighbor.den));
            Tcl_AppendToObj(rv, string_result, -1);
            }

         //Spit out the equality case if appropriate.
         if (neighbor_data.equality)
            {
            if (neighbor_data.n_left_out)
               Tcl_AppendToObj(rv, " ", -1);

            Tcl_AppendToObj(rv, "0", -1);
         
            //Force the buffer to have enough space for the components of the rational
            //number.
            chars_reqd = INTFUNC_max(
                                    GMP_INTS_mpz_size_in_base_10(&(neighbor_data.norm_rn.num)),
                                    GMP_INTS_mpz_size_in_base_10(&(neighbor_data.norm_rn.den))
                                    );
            if (chars_reqd > string_result_n_allocd)
               {
               string_result_n_allocd = chars_reqd;
               string_result = TclpRealloc(string_result, sizeof(char) * string_result_n_allocd);
               assert(string_result != NULL);
               }

            //Print the rational number out to the Tcl object.
            Tcl_AppendToObj(rv, " ", -1);
            GMP_INTS_mpz_to_string(string_result, &(neighbor_data.norm_rn.num));
            Tcl_AppendToObj(rv, string_result, -1);
            Tcl_AppendToObj(rv, "/", -1);
            GMP_INTS_mpz_to_string(string_result, &(neighbor_data.norm_rn.den));
            Tcl_AppendToObj(rv, string_result, -1);
            }

         //Loop through, spitting out the right neighbors.
         for (i = 0; i < neighbor_data.n_right_out; i++)
            {
            //The protocol here is everyone spits out one space before
            //they print anything.  Must skip this on first loop iteration.
            if (neighbor_data.n_left_out || neighbor_data.equality || i)
               Tcl_AppendToObj(rv, " ", -1);

            //The index will be the iteration variable plus one.
            sprintf(sbuf, "%d", i+1);
            Tcl_AppendToObj(rv, sbuf, -1);
            
            //Force the buffer to have enough space for the components of the rational
            //number.
            chars_reqd = INTFUNC_max(
                                    GMP_INTS_mpz_size_in_base_10(&(neighbor_data.rights[i].neighbor.num)),
                                    GMP_INTS_mpz_size_in_base_10(&(neighbor_data.rights[i].neighbor.den))
                                    );
            if (chars_reqd > string_result_n_allocd)
               {
               string_result_n_allocd = chars_reqd;
               string_result = TclpRealloc(string_result, sizeof(char) * string_result_n_allocd);
               assert(string_result != NULL);
               }

            //Print the rational number out to the Tcl object.
            Tcl_AppendToObj(rv, " ", -1);
            GMP_INTS_mpz_to_string(string_result, &(neighbor_data.rights[i].neighbor.num));
            Tcl_AppendToObj(rv, string_result, -1);
            Tcl_AppendToObj(rv, "/", -1);
            GMP_INTS_mpz_to_string(string_result, &(neighbor_data.rights[i].neighbor.den));
            Tcl_AppendToObj(rv, string_result, -1);
            }

         //Set up for a normal return.
         Tcl_SetObjResult(interp, rv);

         TclpFree(string_result);
         GMP_RALG_consecutive_fab_terms_result_free(&neighbor_data);
         GMP_RATS_mpq_clear(&q_rn);
         GMP_INTS_mpz_clear(&z_kmax);
         GMP_INTS_mpz_clear(&z_hmax);

         return(TCL_OK);
         }
      else if (pred_option_specified)
         { 
         //Simple predecessor case.

         GMP_RALG_fab_neighbor_collection_struct neighbor_data;

         //Form up the neighbor data.       
         GMP_RALG_consecutive_fab_terms(
                                       &q_rn,
                                       &z_kmax,
                                       &z_hmax,
                                       1,
                                       0,
                                       &neighbor_data
                                       );

         //If there was an error forming up the neighbor data or there are no left neighbors,
         //create a hard error.
         if (neighbor_data.error || !neighbor_data.n_left_out)
            {
            rv = Tcl_NewStringObj("arbint cfbrapab: unable to find predecessor.", -1);
            Tcl_SetObjResult(interp, rv);

            GMP_RALG_consecutive_fab_terms_result_free(&neighbor_data);
            GMP_RATS_mpq_clear(&q_rn);
            GMP_INTS_mpz_clear(&z_kmax);
            GMP_INTS_mpz_clear(&z_hmax);

            return(TCL_ERROR);
            }

         //The test above confirmed that we have at least one left neighbor calculated.
         //We can dump it to a string and finish up.
         chars_reqd = INTFUNC_max(
                                 GMP_INTS_mpz_size_in_base_10(&(neighbor_data.lefts[0].neighbor.num)),
                                 GMP_INTS_mpz_size_in_base_10(&(neighbor_data.lefts[0].neighbor.den))
                                 );
         string_result = TclpAlloc(sizeof(char) * chars_reqd);
         assert(string_result != NULL);

         GMP_INTS_mpz_to_string(string_result, &(neighbor_data.lefts[0].neighbor.num));
         rv = Tcl_NewStringObj(string_result, -1);
         Tcl_AppendToObj(rv, "/", -1);
         GMP_INTS_mpz_to_string(string_result, &(neighbor_data.lefts[0].neighbor.den));
         Tcl_AppendToObj(rv, string_result, -1);

         Tcl_SetObjResult(interp, rv);

         TclpFree(string_result);
         GMP_RALG_consecutive_fab_terms_result_free(&neighbor_data);
         GMP_RATS_mpq_clear(&q_rn);
         GMP_INTS_mpz_clear(&z_kmax);
         GMP_INTS_mpz_clear(&z_hmax);

         return(TCL_OK);
         }
      else if (succ_option_specified)
         {
         //Simple successor.

         GMP_RALG_fab_neighbor_collection_struct neighbor_data;

         //Form up the neighbor data.       
         GMP_RALG_consecutive_fab_terms(
                                       &q_rn,
                                       &z_kmax,
                                       &z_hmax,
                                       0,
                                       1,
                                       &neighbor_data
                                       );

         //If there was an error forming up the neighbor data or there are no right neighbors,
         //create a hard error.
         if (neighbor_data.error || !neighbor_data.n_right_out)
            {
            rv = Tcl_NewStringObj("arbint cfbrapab: unable to find successor.", -1);
            Tcl_SetObjResult(interp, rv);

            GMP_RALG_consecutive_fab_terms_result_free(&neighbor_data);
            GMP_RATS_mpq_clear(&q_rn);
            GMP_INTS_mpz_clear(&z_kmax);
            GMP_INTS_mpz_clear(&z_hmax);

            return(TCL_ERROR);
            }

         //The test above confirmed that we have at least one right neighbor calculated.
         //We can dump it to a string and finish up.
         chars_reqd = INTFUNC_max(
                                 GMP_INTS_mpz_size_in_base_10(&(neighbor_data.rights[0].neighbor.num)),
                                 GMP_INTS_mpz_size_in_base_10(&(neighbor_data.rights[0].neighbor.den))
                                 );
         string_result = TclpAlloc(sizeof(char) * chars_reqd);
         assert(string_result != NULL);

         GMP_INTS_mpz_to_string(string_result, &(neighbor_data.rights[0].neighbor.num));
         rv = Tcl_NewStringObj(string_result, -1);
         Tcl_AppendToObj(rv, "/", -1);
         GMP_INTS_mpz_to_string(string_result, &(neighbor_data.rights[0].neighbor.den));
         Tcl_AppendToObj(rv, string_result, -1);

         Tcl_SetObjResult(interp, rv);

         TclpFree(string_result);
         GMP_RALG_consecutive_fab_terms_result_free(&neighbor_data);
         GMP_RATS_mpq_clear(&q_rn);
         GMP_INTS_mpz_clear(&z_kmax);
         GMP_INTS_mpz_clear(&z_hmax);

         return(TCL_OK);
         }

      //Free up all dynamic memory.
      GMP_RATS_mpq_clear(&q_rn);
      GMP_INTS_mpz_clear(&z_kmax);
      GMP_INTS_mpz_clear(&z_hmax);

      //Return
      return(TCL_OK);
      }
   }


//Handles the "cfratnum" subextension.
//08/07/01:  Visually inspected, OK.
static
int ARBLENINTS_cfratnum_handler(ClientData dummy, 
                              Tcl_Interp *interp, 
                              int objc,
                              Tcl_Obj *objv[])
   {
   Tcl_Obj *rv;

   //We must have exactly one additional argument
   //to this function, which is the rational number
   //whose continued fraction decomposition is to be
   //calculated.
   if (objc != 3)
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "urn");
      return(TCL_ERROR);
      }
   else
      {
      char *input_arg;
      int failure;
      unsigned chars_reqd;
      char *string_result;
      int n_string_result;
      int i;
      GMP_RATS_mpq_struct rn;
      GMP_RALG_cf_app_struct decomp;

      //In this function, we are going to return a string
      //result formed by starting with a string and then
      //concatenating  to it again and again.  We start
      //off believing that 10,000 characters of space is enough,
      //but we may need to revise upward and reallocate.  
      //A 10,000 character block is chosen because it is quick 
      //to allocate and most times won't go beyond that.
      n_string_result = 10000;
      string_result = TclpAlloc(sizeof(char) * n_string_result);
      assert(string_result != NULL);

      //We will need a rational number to hold the return value
      //from the parsing function.  Allocate that now.
      GMP_RATS_mpq_init(&rn);

      //Grab a pointer to the string representation of
      //the input argument.  The storage does not belong to us.
      input_arg = Tcl_GetString(objv[2]);
      assert(input_arg != NULL);

      //Try to parse our input string as a rational number.
      //If we are not successful in this, must abort.
      GMP_RATS_mpq_set_all_format_rat_num(input_arg,
                                          &failure,
                                          &rn);

      if (failure)
         {
         rv = Tcl_NewStringObj("arbint cfratnum: \"", -1);
         Tcl_AppendToObj(rv, input_arg, -1);

         Tcl_AppendToObj(rv, "\" is not a recognized non-negative rational number.", -1);
         Tcl_SetObjResult(interp, rv);

         TclpFree(string_result);
         GMP_RATS_mpq_clear(&rn);

         return(TCL_ERROR);
         }

      //OK, we have a rational number, but there is a possibility
      //it is negative, which is a no-no.  Normalize the signs
      //for easier testing.
      GMP_RATS_mpq_normalize_sign(&rn);
      if (GMP_INTS_mpz_is_neg(&(rn.num)))
         {
         rv = Tcl_NewStringObj("arbint cfratnum: \"", -1);
         Tcl_AppendToObj(rv, input_arg, -1);

         Tcl_AppendToObj(rv, "\" is negative.", -1);
         Tcl_SetObjResult(interp, rv);

         TclpFree(string_result);
         GMP_RATS_mpq_clear(&rn);

         return(TCL_ERROR);
         }

      //OK, we have a rational number.  Form the continued fraction
      //decomposition of it.  The function called is set up so that
      //one must deallocate, even in an error condition.
      GMP_RALG_cfdecomp_init(&decomp,
                             &failure,
                             &(rn.num),
                             &(rn.den));

      //If we failed in the decomposition (don't know why that would
      //happen) use the general error flag "NAN".
      if (failure)
         {
         rv = Tcl_NewStringObj("NAN", -1);

         Tcl_SetObjResult(interp, rv);

         TclpFree(string_result);
         GMP_RATS_mpq_clear(&rn);
         GMP_RALG_cfdecomp_destroy(&decomp);

         return(TCL_ERROR);
         }

      //OK, that really is the last error we could have.
      //Iterate, adding the partial quotients and convergents
      //to the string which we'll return.  We need to watch out
      //for running over our 10K buffer.
      rv = Tcl_NewStringObj("", -1);
      for (i=0; i<decomp.n; i++)
         {
         //Partial quotient.
         chars_reqd = GMP_INTS_mpz_size_in_base_10(&(decomp.a[i]));
         if (chars_reqd > (unsigned)n_string_result)
            {
            n_string_result = chars_reqd;
            string_result = TclpRealloc(string_result, 
                                        sizeof(char) * n_string_result);
            }
         GMP_INTS_mpz_to_string(string_result, &(decomp.a[i]));
         Tcl_AppendToObj(rv, string_result, -1);
         Tcl_AppendToObj(rv, " ", -1);

         //Numerator of convergent.
         chars_reqd = GMP_INTS_mpz_size_in_base_10(&(decomp.p[i]));
         if (chars_reqd > (unsigned)n_string_result)
            {
            n_string_result = chars_reqd;
            string_result = TclpRealloc(string_result, 
                                        sizeof(char) * n_string_result);
            }
         GMP_INTS_mpz_to_string(string_result, &(decomp.p[i]));
         Tcl_AppendToObj(rv, string_result, -1);
         Tcl_AppendToObj(rv, " ", -1);

         //Denominator of convergent.
         chars_reqd = GMP_INTS_mpz_size_in_base_10(&(decomp.q[i]));
         if (chars_reqd > (unsigned)n_string_result)
            {
            n_string_result = chars_reqd;
            string_result = TclpRealloc(string_result, 
                                        sizeof(char) * n_string_result);
            }
         GMP_INTS_mpz_to_string(string_result, &(decomp.q[i]));
         Tcl_AppendToObj(rv, string_result, -1);
         if (i != (decomp.n - 1)) //No space after last number.
            Tcl_AppendToObj(rv, " ", -1);
         }

      //Assign the result to be the return value.
      Tcl_SetObjResult(interp, rv);

      //Free up all dynamic memory.
      TclpFree(string_result);
      GMP_RATS_mpq_clear(&rn);
      GMP_RALG_cfdecomp_destroy(&decomp);

      //Return
      return(TCL_OK);
      }
   }


//Handles the "commanate" subextension.
//07/29/01:  Visual inspection OK.  Have not located my Tcl book, am doing this
//from memory an intuition as far as how to set return results and so forth.
static
int ARBLENINTS_commanate_handler(ClientData dummy, 
                              Tcl_Interp *interp, 
                              int objc,
                              Tcl_Obj *objv[])
   {
   Tcl_Obj *rv;

   //We must have one and exactly one additional argument
   //to this function, which is the string we want to
   //commanate.
   if (objc != 3)
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "sint");
      return(TCL_ERROR);
      }
   else
      {
      char *string_arg;

      //Grab a pointer to the string representation of
      //the input argument.  The storage does not belong to us.
      string_arg = Tcl_GetString(objv[2]);
      assert(string_arg != NULL);

      //Try to parse the string as one of the error tags.
      //If it is one of those, it isn't an error, but don't
      //want to touch the string.
      if (GMP_INTS_identify_nan_string(string_arg) >= 0)
         {
         rv = Tcl_NewStringObj(string_arg, -1);
         Tcl_SetObjResult(interp, rv);
         return(TCL_OK);
         }
      //Try to parse it as a signed integer with commas already.
      //If it already has commas, there is no need to add any.
      else if (BSTRFUNC_is_sint_w_commas(string_arg))
         {
         //This is already an acceptable commanated signed integer.  Send it
         //back as the return value.
         rv = Tcl_NewStringObj(string_arg, -1);
         Tcl_SetObjResult(interp, rv);
         return(TCL_OK);
         }
      //Try to parse the argument as a signed integer without commas.
      //If it is one of those, commanate it and return it.
      else if (BSTRFUNC_is_sint_wo_commas(string_arg))
         {
         size_t len;
         char *buffer;

         len = strlen(string_arg);
         buffer = TclpAlloc(((sizeof(char) * 4 * len) / 3) + 10);
         strcpy(buffer, string_arg);
         BSTRFUNC_commanate(buffer);
         rv = Tcl_NewStringObj(buffer, -1);
         TclpFree(buffer);
         Tcl_SetObjResult(interp, rv);
         return(TCL_OK);
         }
      else
         {
         //Error case.  Must give error message.
         rv = Tcl_NewStringObj("arbint commanate: \"", -1);
         Tcl_AppendToObj(rv, string_arg, -1);
         Tcl_AppendToObj(rv, "\" is not a recognized integer.", -1);
         Tcl_SetObjResult(interp, rv);
         return(TCL_ERROR);
         }
      }
   }


//Handles the "const" subextension.
//08/17/01: Visual inspection OK.
static
int ARBLENINTS_const_handler(ClientData dummy, 
                             Tcl_Interp *interp, 
                             int objc,
                             Tcl_Obj *objv[])
   {
   //Table of constants used.
   static struct 
      {
      char *tag;
         //The symbolic tag used to identify the number.
      char *desc;
         //The full description of the number.  It must consist
         //of a string with lines no longer than about 70 chars,
         //separated by newlines, and indented by 6 spaces.
      char *minmant;
         //The minimum mantissa or minimum representation.
         //May not be empty or NULL.
      char *mantrem;
         //The remaining mantissa or remaining portion of 
         //number.  May be empty, but may not be NULL.
      char *exp;
         //The exponent portion, if any, or NULL otherwise.
      int deflen;
         //The default number of digits for the constant
         //if none is specified.
      int digit_count_offset;
         //The offset to go from string length of mantissa
         //portions to number of digits.  Cheap way to adjust
         //for - sign and decimal point.
      } tbl[] =
      {
      //e--the transcendental number e.
         {
         //tag
         "e",
         //desc
         "      Historically significant transcendental constant.  Digits obtained\n"
         "      from http://fermi.udw.ac.za/physics/e.html on 08/17/01.",
         //minmant
         "2.7",
         //mantrem
         "182818284590452353602874713526624977572470936999595749669676277240766303535"
         "475945713821785251664274274663919320030599218174135966290435729003342952605956"
         "307381323286279434907632338298807531952510190115738341879307021540891499348841"
         "675092447614606680822648001684774118537423454424371075390777449920695517027618"
         "386062613313845830007520449338265602976067371132007093287091274437470472306969"
         "772093101416928368190255151086574637721112523897844250569536967707854499699679"
         "468644549059879316368892300987931277361782154249992295763514822082698951936680"
         "331825288693984964651058209392398294887933203625094431173012381970684161403970"
         "198376793206832823764648042953118023287825098194558153017567173613320698112509"
         "961818815930416903515988885193458072738667385894228792284998920868058257492796"
         "104841984443634632449684875602336248270419786232090021609902353043699418491463"
         "140934317381436405462531520961836908887070167683964243781405927145635490613031"
         "07208510383750510115747704171898610687396965521267154688957035035",
         //exp
         NULL,
         //deflen
         30,
         //digit_count_offset
         1
         },
      //g_metric
         {
         //tag
         "g_si",
         //desc
         "      Gravitational acceleration in SI units, meters per second**2.\n"
         "      Obtained from NIST Special Publication 811 on 08/17/01.",
         //minmant
         "9.80665",
         //mantrem
         "",
         //exp
         NULL,
         //deflen
         30,
         //digit_count_offset
         1
         },
      //in2m
         {
         //tag
         "in2m",
         //desc
         "      Multiplicative conversion factor from inches to meters.\n"
         "      Obtained from NIST Special Publication 811 on 08/17/01.",
         //minmant
         "2.54",
         //mantrem
         "",
         //exp
         "e-2",
         //deflen
         30,
         //digit_count_offset
         1
         },
      //mi2km
         {
         //tag
         "mi2km",
         //desc
         "      Multiplicative conversion factor from miles to kilometers.\n"
         "      Obtained from NIST Special Publication 811 on 08/17/01.",
         //minmant
         "1.609344",
         //mantrem
         "",
         //exp
         NULL,
         //deflen
         30,
         //digit_count_offset
         1
         },
      //pi--the transcendental number PI.
         {
         //tag
         "pi",
         //desc
         "      Transcendental constant supplying ratio of a circle's circumference\n"
         "      to its diameter.  Digits obtained from http://www.joyofpi.com/\n"
         "      pi.htm on 08/17/01.",
         //minmant
         "3.14",
         //mantrem
         "15926535897932384626433832795028841971"
         "6939937510582097494459230781640628620899"
         "8628034825342117067982148086513282306647"
         "0938446095505822317253594081284811174502"
         "8410270193852110555964462294895493038196"
         "4428810975665933446128475648233786783165"
         "2712019091456485669234603486104543266482"
         "1339360726024914127372458700660631558817"
         "4881520920962829254091715364367892590360"
         "0113305305488204665213841469519415116094"
         "3305727036575959195309218611738193261179"
         "3105118548074462379962749567351885752724"
         "8912279381830119491298336733624406566430"
         "8602139494639522473719070217986094370277"
         "0539217176293176752384674818467669405132"
         "0005681271452635608277857713427577896091"
         "7363717872146844090122495343014654958537"
         "1050792279689258923542019956112129021960"
         "8640344181598136297747713099605187072113"
         "4999999837297804995105973173281609631859"
         "5024459455346908302642522308253344685035"
         "2619311881710100031378387528865875332083"
         "8142061717766914730359825349042875546873"
         "1159562863882353787593751957781857780532"
         "1712268066130019278766111959092164201989"
         "3809525720106548586327886593615338182796"
         "8230301952035301852968995773622599413891"
         "2497217752834791315155748572424541506959"
         "5082953311686172785588907509838175463746"
         "4939319255060400927701671139009848824012",
         //exp
         NULL,
         //deflen
         30,
         //digit_count_offset
         1
         },
      //sqrt5--the square root of 5.
         {
         //tag
         "sqrt5",
         //desc
         "      The square root of 5.  Digits obtained from\n"
         "      http://home.earthlink.net/~maryski/sqrt51000000.txt on 08/17/01.",
         //minmant
         "2.236",
         //mantrem
         "0679774997896964091736687312762354406183596115257242708972454105209256378048"
         "99414414408378782274969508176150773783504253267724447073863586360121533452708866"
         "77817319187916581127664532263985658053576135041753378500342339241406444208643253"
         "90972525926272288762995174024406816117759089094984923713907297288984820886415426"
         "89894099131693577019748678884425089754132956183176921499977424801530434115035957"
         "66833251249881517813940800056242085524354223555610630634282023409333198293395974"
         "63522712013417496142026359047378855043896870611356600457571399565955669569175645"
         "78221952500060539231234005009286764875529722056766253666074485853505262330678494"
         "63342224231763727702663240768010444331582573350589309813622634319868647194698997"
         "01808189524264459620345221411922329125981963258111041704958070481204034559949435"
         "06855551855572512388641655010262436312571024449618789424682903404474716115455723"
         "20173767659046091852957560357798439805415538077906439363972302875606299948221385"
         "21773485924535151210463455550407072278724215347787529112121211843317893351910380",
         //exp
         NULL,
         //deflen
         30,
         //digit_count_offset
         1
         },
      };
      
   Tcl_Obj *rv;
      //Value that will be returned to caller.
   int i;
      //Iteration variable.
   int tbl_idx;
      //Index into lookup table, of -1 if not found.
   int ndigits;
      //The number of digits to supply.
   int result_code;
      //Return value from Tcl library function.

   //We must have either one or two additional arguments.
   if ((objc != 3) && (objc != 4))
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "constant_tag ?ndigits?");
      return(TCL_ERROR);
      }
   else
      {
      char *string_arg;

      //Grab a pointer to the string representation of
      //the input argument.  The storage does not belong to us.
      string_arg = Tcl_GetString(objv[2]);
      assert(string_arg != NULL);

      //Try to look up the string argument in the table.
      tbl_idx = -1;
      for (i=0; i<sizeof(tbl)/sizeof(tbl[0]); i++)
         {
         if (!strcmp(string_arg, tbl[i].tag))
            {
            tbl_idx = i;
            break;
            }
         }

      //If the tag was not found in the table, print a hostile
      //message and abort.
      if (tbl_idx == -1)
         {
         char buf[100];

         //Error case.  Must give error message.    
         //Must also list the constants available.
         rv = Tcl_NewStringObj("arbint const: \"", -1);
         Tcl_AppendToObj(rv, string_arg, -1);
         Tcl_AppendToObj(rv, "\" is not a recognized constant.\n", -1);

         Tcl_AppendToObj(rv, "Available constants are:\n", -1);

         for (i=0; i<sizeof(tbl)/sizeof(tbl[0]); i++)
            {
            Tcl_AppendToObj(rv, "   ", -1);
            Tcl_AppendToObj(rv, tbl[i].tag, -1);
            sprintf(buf, " (%d digits available)\n", 
                    strlen(tbl[i].minmant) + strlen(tbl[i].mantrem) - tbl[i].digit_count_offset);
            Tcl_AppendToObj(rv, buf, -1);
            Tcl_AppendToObj(rv, tbl[i].desc, -1);
            if (i != (sizeof(tbl)/sizeof(tbl[0]) - 1))
               Tcl_AppendToObj(rv, "\n", -1);
            }

         Tcl_SetObjResult(interp, rv);
         return(TCL_ERROR);
         }

      //Make assertions about the string pointers.
      assert(tbl[tbl_idx].tag     != NULL);
      assert(tbl[tbl_idx].desc    != NULL);
      assert(tbl[tbl_idx].minmant != NULL);
      assert(tbl[tbl_idx].mantrem != NULL);

      //Assume the default number of digits by default.
      ndigits = tbl[tbl_idx].deflen;

      //If there is an additional parameter, try to interpret
      //that as the number of digits.
      if (objc == 4)
         {
         //SetIntFromAny(interp, objPtr)
         result_code = Tcl_GetIntFromObj(NULL, objv[3], &ndigits);

         if (result_code != TCL_OK)
            {
            //Could not obtain an integer.  Use hostile error
            //message and abort.
            string_arg = Tcl_GetString(objv[3]);
            assert(string_arg != NULL);

            rv = Tcl_NewStringObj("arbint const: \"", -1);
            Tcl_AppendToObj(rv, string_arg, -1);
            Tcl_AppendToObj(rv, "\" is not a recognized integer.", -1);
            Tcl_SetObjResult(interp, rv);
            return(TCL_ERROR);
            }
         }

      //Ndigits may be corrupt.  We have to be careful below to not
      //allow any funny stuff.
      rv = Tcl_NewStringObj(tbl[tbl_idx].minmant, -1);
      ndigits = ndigits - strlen(tbl[tbl_idx].minmant) + tbl[tbl_idx].digit_count_offset;
      if (ndigits > 0)
         {
         if (ndigits >= (int)strlen(tbl[tbl_idx].mantrem))
            {
            Tcl_AppendToObj(rv, tbl[tbl_idx].mantrem, -1);
            }
         else
            {
            Tcl_AppendToObj(rv, tbl[tbl_idx].mantrem, ndigits);
            }
         }

      //Append the exponent portion.
      if (tbl[tbl_idx].exp)
         Tcl_AppendToObj(rv, tbl[tbl_idx].exp, -1);

      //Default successful return.
      Tcl_SetObjResult(interp, rv);
      return(TCL_OK);
      }
   }


//Handles the "decommanate" subextension.
//07/29/01:  Visual inspection OK.  Have not located my Tcl book, am doing this
//from memory an intuition as far as how to set return results and so forth.
static
int ARBLENINTS_decommanate_handler(ClientData dummy, 
                              Tcl_Interp *interp, 
                              int objc,
                              Tcl_Obj *objv[])
   {
   Tcl_Obj *rv;

   //We must have one and exactly one additional argument
   //to this function, which is the string we want to
   //decommanate.
   if (objc != 3)
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "sint");
      return(TCL_ERROR);
      }
   else
      {
      char *string_arg;

      //Grab a pointer to the string representation of
      //the input argument.  The storage does not belong to us.
      string_arg = Tcl_GetString(objv[2]);
      assert(string_arg != NULL);

      //Try to parse the string as one of the error tags.
      //If it is one of those, it isn't an error, but don't
      //want to touch the string.
      if (GMP_INTS_identify_nan_string(string_arg) >= 0)
         {
         rv = Tcl_NewStringObj(string_arg, -1);
         Tcl_SetObjResult(interp, rv);
         return(TCL_OK);
         }
      //Try to parse it as a signed integer without commas.
      //If it has no commas, there is no need to decommanate it.
      else if (BSTRFUNC_is_sint_wo_commas(string_arg))
         {
         //This is already an acceptable commanated signed integer.  Send it
         //back as the return value.
         rv = Tcl_NewStringObj(string_arg, -1);
         Tcl_SetObjResult(interp, rv);
         return(TCL_OK);
         }
      //Try to parse the argument as a signed integer with commas.
      //If it is one of those, decommanate it and return it.
      else if (BSTRFUNC_is_sint_w_commas(string_arg))
         {
         size_t len;
         char *buffer;

         len = strlen(string_arg);
         buffer = TclpAlloc(sizeof(char) * len + 1);
         strcpy(buffer, string_arg);
         BSTRFUNC_decommanate(buffer);
         rv = Tcl_NewStringObj(buffer, -1);
         TclpFree(buffer);
         Tcl_SetObjResult(interp, rv);
         return(TCL_OK);
         }
      else
         {
         //Error case.  Must give error message.
         rv = Tcl_NewStringObj("arbint decommanate: \"", -1);
         Tcl_AppendToObj(rv, string_arg, -1);
         Tcl_AppendToObj(rv, "\" is not a recognized integer.", -1);
         Tcl_SetObjResult(interp, rv);
         return(TCL_ERROR);
         }
      }
   }


//Handles the "intadd" subextension.
//08/06/01:  Visual inspection OK.
static
int ARBLENINTS_intadd_handler(ClientData dummy, 
                              Tcl_Interp *interp, 
                              int objc,
                              Tcl_Obj *objv[])
   {
   Tcl_Obj *rv;

   //We must have two and exactly two additional arguments
   //to this function, which are the integers whose
   //sum is to be calculated.
   if (objc != 4)
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "sint sint");
      return(TCL_ERROR);
      }
   else
      {
      GMP_INTS_mpz_struct arb_arg1, arb_arg2, arb_result;
      char *add_arg1, *add_arg2;
      int failure1, failure2;
      unsigned chars_reqd;
      char *string_result;
      int i, j;

      //Allocate space for the arbitrary-length integer result.
      GMP_INTS_mpz_init(&arb_arg1);
      GMP_INTS_mpz_init(&arb_arg2);
      GMP_INTS_mpz_init(&arb_result);

      //Grab pointers to the string representation of
      //the input arguments.  The storage does not belong to us.
      add_arg1 = Tcl_GetString(objv[2]);
      assert(add_arg1 != NULL);
      add_arg2 = Tcl_GetString(objv[3]);
      assert(add_arg2 != NULL);

      //Try to interpret either of the  strings as one of the NAN tags.
      //If it is one, return the appropriate result for
      //a binary operation.
      i = GMP_INTS_identify_nan_string(add_arg1);
      j = GMP_INTS_identify_nan_string(add_arg2);

      if ((i >= 0) || (j >= 0))
         {
         const char *p;

         //Find the max of i and j.  This isn't a scientific way to tag the
         //result, but will be OK.  Some information is lost no matter what
         //we do.
         if (i > j)
            ;
         else
            i = j;

         //i now contains the max.
         switch (i)
            {
            case 0:  p = GMP_INTS_supply_nan_string(2);
                     break;
            case 1:  p = GMP_INTS_supply_nan_string(3);
                     break;
            case 2:  p = GMP_INTS_supply_nan_string(2);
                     break;
            case 3:  p = GMP_INTS_supply_nan_string(3);
                     break;
            default:
                     assert(0);
                     break;
            }

         rv = Tcl_NewStringObj(p, -1);
         Tcl_SetObjResult(interp, rv);

         GMP_INTS_mpz_clear(&arb_arg1);
         GMP_INTS_mpz_clear(&arb_arg2);
         GMP_INTS_mpz_clear(&arb_result);

         return(TCL_OK);
         }

      //Try to convert both strings into arbitrary integers.
      GMP_INTS_mpz_set_general_int(&arb_arg1, &failure1, add_arg1);
      GMP_INTS_mpz_set_general_int(&arb_arg2, &failure2, add_arg2);

      //If there was a parse failure, we have to return an error 
      //message.  It is possible that both arguments failed the parse,
      //but only return one in the error message.
      if (failure1 || failure2)
         {
         rv = Tcl_NewStringObj("arbint intadd: \"", -1);
         if (failure1)
            Tcl_AppendToObj(rv, add_arg1, -1);
         else
            Tcl_AppendToObj(rv, add_arg2, -1);

         Tcl_AppendToObj(rv, "\" is not a recognized signed integer.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_INTS_mpz_clear(&arb_arg1);
         GMP_INTS_mpz_clear(&arb_arg2);
         GMP_INTS_mpz_clear(&arb_result);

         return(TCL_ERROR);
         }

      //Calculate the sum.
      GMP_INTS_mpz_add(&arb_result, &arb_arg1, &arb_arg2);

      //Figure out the number of characters required for
      //the output string.
      chars_reqd = GMP_INTS_mpz_size_in_base_10(&arb_result);

      //Allocate space for the conversion result.
      string_result = TclpAlloc(sizeof(char) * chars_reqd);
      assert(string_result != NULL);

      //Make the conversion to a character string.
      GMP_INTS_mpz_to_string(string_result, &arb_result);

      //Assign the string result to a Tcl object.
      rv = Tcl_NewStringObj(string_result, -1);

      //Deallocate the string.
      TclpFree(string_result);

      //Deallocate space for the arbitrary-length integers.
      GMP_INTS_mpz_clear(&arb_arg1);
      GMP_INTS_mpz_clear(&arb_arg2);
      GMP_INTS_mpz_clear(&arb_result);

      //Assign the result to be the return value.
      Tcl_SetObjResult(interp, rv);

      //Return
      return(TCL_OK);
      }
   }


//08/01/01:  Visual inspection and some unit testing, OK.
//Handles the "intcmp" subextension.
static
int ARBLENINTS_intcmp_handler(ClientData dummy, 
                              Tcl_Interp *interp, 
                              int objc,
                              Tcl_Obj *objv[])
   {
   Tcl_Obj *rv;

   //We must have two and exactly two additional arguments
   //to this function, which are the integers to be compared.
   if (objc != 4)
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "sint sint");
      return(TCL_ERROR);
      }
   else
      {
      GMP_INTS_mpz_struct arb_arg1, arb_arg2;
      char *cmp_arg1, *cmp_arg2;
      int failure1, failure2;
      int i, j, compare_result;

      //Allocate space for the arbitrary-length integer result.
      GMP_INTS_mpz_init(&arb_arg1);
      GMP_INTS_mpz_init(&arb_arg2);

      //Grab pointers to the string representation of
      //the input arguments.  The storage does not belong to us.
      cmp_arg1 = Tcl_GetString(objv[2]);
      assert(cmp_arg1 != NULL);
      cmp_arg2 = Tcl_GetString(objv[3]);
      assert(cmp_arg2 != NULL);

      //Try to interpret either of the  strings as one of the NAN tags.
      //We cannot compare NAN tags.  If either is a NAN tag, we must signal an
      //error.
      i = GMP_INTS_identify_nan_string(cmp_arg1);
      j = GMP_INTS_identify_nan_string(cmp_arg2);

      if ((i >= 0) || (j >= 0))
         {
         rv = Tcl_NewStringObj("arbint intcmp: cannot compare NAN symbolic tags.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_INTS_mpz_clear(&arb_arg1);
         GMP_INTS_mpz_clear(&arb_arg2);

         return(TCL_ERROR);
         }

      //Try to convert both strings into arbitrary integers.
      GMP_INTS_mpz_set_general_int(&arb_arg1, &failure1, cmp_arg1);
      GMP_INTS_mpz_set_general_int(&arb_arg2, &failure2, cmp_arg2);

      //If there was a parse failure, we have to return an error 
      //message.  It is possible that both arguments failed the parse,
      //but only return one in the error message.
      if (failure1 || failure2)
         {
         rv = Tcl_NewStringObj("arbint intcmp: \"", -1);
         if (failure1)
            Tcl_AppendToObj(rv, cmp_arg1, -1);
         else
            Tcl_AppendToObj(rv, cmp_arg2, -1);

         Tcl_AppendToObj(rv, "\" is not a recognized signed integer.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_INTS_mpz_clear(&arb_arg1);
         GMP_INTS_mpz_clear(&arb_arg2);

         return(TCL_ERROR);
         }

      //Calculate the compare result.
      compare_result = GMP_INTS_mpz_cmp(&arb_arg1, &arb_arg2);

      //Assign the return value based on the result.
      if (compare_result < 0)
         rv = Tcl_NewStringObj("-1", -1);
      else if (compare_result == 0)
         rv = Tcl_NewStringObj("0", -1);
      else
         rv = Tcl_NewStringObj("1", -1);

      //Deallocate space for the arbitrary-length integers.
      GMP_INTS_mpz_clear(&arb_arg1);
      GMP_INTS_mpz_clear(&arb_arg2);

      //Assign the result to be the return value.
      Tcl_SetObjResult(interp, rv);

      //Return
      return(TCL_OK);
      }
   }


//Handles the "intdiv" subextension.
//07/31/01:  Visually inspected, OK.
static
int ARBLENINTS_intdiv_handler(ClientData dummy, 
                              Tcl_Interp *interp, 
                              int objc,
                              Tcl_Obj *objv[])
   {
   Tcl_Obj *rv;

   //We must have two and exactly two additional arguments
   //to this function, which are the integers whose
   //integer quotient is to be calculated.
   if (objc != 4)
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "sint sint");
      return(TCL_ERROR);
      }
   else
      {
      GMP_INTS_mpz_struct arb_dividend, arb_divisor, arb_quotient, arb_remainder;
      char *dividend_arg1, *divisor_arg2;
      int failure1, failure2;
      unsigned chars_reqd;
      char *string_result;
      int i, j;

      //Allocate space for the arbitrary-length integer arguments and results.
      GMP_INTS_mpz_init(&arb_dividend);
      GMP_INTS_mpz_init(&arb_divisor);
      GMP_INTS_mpz_init(&arb_quotient);
      GMP_INTS_mpz_init(&arb_remainder);

      //Grab pointers to the string representation of
      //the input arguments.  The storage does not belong to us.
      dividend_arg1 = Tcl_GetString(objv[2]);
      assert(dividend_arg1 != NULL);
      divisor_arg2 = Tcl_GetString(objv[3]);
      assert(divisor_arg2 != NULL);

      //Try to interpret either of the  strings as one of the NAN tags.
      //If it is one, return the appropriate result for
      //a binary operation.
      i = GMP_INTS_identify_nan_string(dividend_arg1);
      j = GMP_INTS_identify_nan_string(divisor_arg2);

      if ((i >= 0) || (j >= 0))
         {
         const char *p;

         //Find the max of i and j.  This isn't a scientific way to tag the
         //result, but will be OK.  Some information is lost no matter what
         //we do.
         if (i > j)
            ;
         else
            i = j;

         //i now contains the max.
         switch (i)
            {
            case 0:  p = GMP_INTS_supply_nan_string(2);
                     break;
            case 1:  p = GMP_INTS_supply_nan_string(3);
                     break;
            case 2:  p = GMP_INTS_supply_nan_string(2);
                     break;
            case 3:  p = GMP_INTS_supply_nan_string(3);
                     break;
            default:
                     assert(0);
                     break;
            }

         rv = Tcl_NewStringObj(p, -1);
         Tcl_SetObjResult(interp, rv);

         GMP_INTS_mpz_clear(&arb_dividend);
         GMP_INTS_mpz_clear(&arb_divisor);
         GMP_INTS_mpz_clear(&arb_quotient);
         GMP_INTS_mpz_clear(&arb_remainder);

         return(TCL_OK);
         }

      //Try to convert both strings into arbitrary integers.
      GMP_INTS_mpz_set_general_int(&arb_dividend, &failure1, dividend_arg1);
      GMP_INTS_mpz_set_general_int(&arb_divisor,  &failure2, divisor_arg2);

      //If there was a parse failure, we have to return an error 
      //message.  It is possible that both arguments failed the parse,
      //but only return one in the error message.
      if (failure1 || failure2)
         {
         rv = Tcl_NewStringObj("arbint intdiv: \"", -1);
         if (failure1)
            Tcl_AppendToObj(rv, dividend_arg1, -1);
         else
            Tcl_AppendToObj(rv, divisor_arg2, -1);

         Tcl_AppendToObj(rv, "\" is not a recognized signed integer.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_INTS_mpz_clear(&arb_dividend);
         GMP_INTS_mpz_clear(&arb_divisor);
         GMP_INTS_mpz_clear(&arb_quotient);
         GMP_INTS_mpz_clear(&arb_remainder);

         return(TCL_ERROR);
         }

      //Calculate the quotient.
      GMP_INTS_mpz_tdiv_qr(&arb_quotient, &arb_remainder, &arb_dividend, &arb_divisor);

      //Figure out the number of characters required for
      //the output string.
      chars_reqd = GMP_INTS_mpz_size_in_base_10(&arb_quotient);

      //Allocate space for the conversion result.
      string_result = TclpAlloc(sizeof(char) * chars_reqd);
      assert(string_result != NULL);

      //Make the conversion to a character string.
      GMP_INTS_mpz_to_string(string_result, &arb_quotient);

      //Assign the string result to a Tcl object.
      rv = Tcl_NewStringObj(string_result, -1);

      //Deallocate the string.
      TclpFree(string_result);

      //Deallocate space for the arbitrary-length integers.
      GMP_INTS_mpz_clear(&arb_dividend);
      GMP_INTS_mpz_clear(&arb_divisor);
      GMP_INTS_mpz_clear(&arb_quotient);
      GMP_INTS_mpz_clear(&arb_remainder);

      //Assign the result to be the return value.
      Tcl_SetObjResult(interp, rv);

      //Return
      return(TCL_OK);
      }
   }


//08/01/01:  Visually inspected.
//Handles the "intexp" subextension.
static
int ARBLENINTS_intexp_handler(ClientData dummy, 
                              Tcl_Interp *interp, 
                              int objc,
                              Tcl_Obj *objv[])
   {
   Tcl_Obj *rv;

   //We must have two and exactly two additional arguments
   //to this function, which are the integers used to 
   //calculate the exponential.
   if (objc != 4)
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "sint uint32");
      return(TCL_ERROR);
      }
   else
      {
      GMP_INTS_mpz_struct arb_arg1, arb_result;
      unsigned arg2;
      char *str_arg1, *str_arg2;
      int failure1, failure2;
      unsigned chars_reqd;
      char *string_result;
      int i, j;

      //Allocate space for the arbitrary-length integers.
      GMP_INTS_mpz_init(&arb_arg1);
      GMP_INTS_mpz_init(&arb_result);

      //Grab pointers to the string representation of
      //the input arguments.  The storage does not belong to us.
      str_arg1 = Tcl_GetString(objv[2]);
      assert(str_arg1 != NULL);
      str_arg2 = Tcl_GetString(objv[3]);
      assert(str_arg2 != NULL);

      //Try to interpret either of the  strings as one of the NAN tags.
      //If it is one, return the appropriate result for
      //a binary operation.
      i = GMP_INTS_identify_nan_string(str_arg1);
      j = GMP_INTS_identify_nan_string(str_arg2);

      if ((i >= 0) || (j >= 0))
         {
         const char *p;

         //Find the max of i and j.  This isn't a scientific way to tag the
         //result, but will be OK.  Some information is lost no matter what
         //we do.
         if (i > j)
            ;
         else
            i = j;

         //i now contains the max.
         switch (i)
            {
            case 0:  p = GMP_INTS_supply_nan_string(2);
                     break;
            case 1:  p = GMP_INTS_supply_nan_string(3);
                     break;
            case 2:  p = GMP_INTS_supply_nan_string(2);
                     break;
            case 3:  p = GMP_INTS_supply_nan_string(3);
                     break;
            default:
                     assert(0);
                     break;
            }

         rv = Tcl_NewStringObj(p, -1);
         Tcl_SetObjResult(interp, rv);

         GMP_INTS_mpz_clear(&arb_arg1);
         GMP_INTS_mpz_clear(&arb_result);

         return(TCL_OK);
         }

      //Try to convert the first string into arbitrary integers.
      //The first string can be anything, including zero or a negative
      //arugument.
      GMP_INTS_mpz_set_general_int(&arb_arg1, &failure1, str_arg1);

      //If the conversion of the first string did not go alright, 
      //print error message and abort.
      if (failure1)
         {
         rv = Tcl_NewStringObj("arbint intexp: \"", -1);
         Tcl_AppendToObj(rv, str_arg1, -1);
         Tcl_AppendToObj(rv, "\" is not a recognized signed integer.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_INTS_mpz_clear(&arb_arg1);
         GMP_INTS_mpz_clear(&arb_result);

         return(TCL_ERROR);
         }


      //Try to convert the second string into an unsigned 32-bit
      //integer.
      GMP_INTS_mpz_parse_into_uint32(&arg2, &failure2, str_arg2);

      //If the conversion of the second string did not go alright, 
      //print error message and abort.
      if (failure2)
         {
         rv = Tcl_NewStringObj("arbint intexp: \"", -1);
         Tcl_AppendToObj(rv, str_arg2, -1);
         Tcl_AppendToObj(rv, "\" is not a recognized unsigned 32-bit integer.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_INTS_mpz_clear(&arb_arg1);
         GMP_INTS_mpz_clear(&arb_result);

         return(TCL_ERROR);
         }

      //Calculate the exponential.
      GMP_INTS_mpz_pow_ui(&arb_result, &arb_arg1, arg2);

      //Figure out the number of characters required for
      //the output string.
      chars_reqd = GMP_INTS_mpz_size_in_base_10(&arb_result);

      //Allocate space for the conversion result.
      string_result = TclpAlloc(sizeof(char) * chars_reqd);
      assert(string_result != NULL);

      //Make the conversion to a character string.
      GMP_INTS_mpz_to_string(string_result, &arb_result);

      //Assign the string result to a Tcl object.
      rv = Tcl_NewStringObj(string_result, -1);

      //Deallocate the string.
      TclpFree(string_result);

      //Deallocate space for the arbitrary-length integers.
      GMP_INTS_mpz_clear(&arb_arg1);
      GMP_INTS_mpz_clear(&arb_result);

      //Assign the result to be the return value.
      Tcl_SetObjResult(interp, rv);

      //Return
      return(TCL_OK);
      }
   }


//Handles the "intfac" subextension.
//07/29/01:  Visual inspection OK.  Have not located my Tcl book, am doing this
//from memory an intuition as far as how to set return results and so forth.
static
int ARBLENINTS_intfac_handler(ClientData dummy, 
                              Tcl_Interp *interp, 
                              int objc,
                              Tcl_Obj *objv[])
   {
   Tcl_Obj *rv;

   //We must have one and exactly one additional argument
   //to this function, which is the integer whose
   //factorial is to be evaluated.
   if (objc != 3)
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "uint32");
      return(TCL_ERROR);
      }
   else
      {
      GMP_INTS_mpz_struct arb_result;
      char *fac_arg;
      int failure;
      unsigned fac_ui_arg;
      unsigned chars_reqd;
      char *string_result;
      int i;

      //Allocate space for the arbitrary-length integer result.
      GMP_INTS_mpz_init(&arb_result);

      //Grab a pointer to the string representation of
      //the input argument.  The storage does not belong to us.
      fac_arg = Tcl_GetString(objv[2]);
      assert(fac_arg != NULL);

      //Try to interpret the string as one of the NAN tags.
      //If it is one, return the appropriate result for
      //a unary operation.
      if ((i = GMP_INTS_identify_nan_string(fac_arg)) >= 0)
         {
         const char *p;

         switch (i)
            {
            case 0:  p = GMP_INTS_supply_nan_string(2);
                     break;
            case 1:  p = GMP_INTS_supply_nan_string(3);
                     break;
            case 2:  p = GMP_INTS_supply_nan_string(2);
                     break;
            case 3:  p = GMP_INTS_supply_nan_string(3);
                     break;
            default:
                     assert(0);
                     break;
            }

         rv = Tcl_NewStringObj(p, -1);
         Tcl_SetObjResult(interp, rv);
         GMP_INTS_mpz_clear(&arb_result);
         return(TCL_OK);
         }

      //Try to convert the string to a UINT32 using all
      //known methods.
      GMP_INTS_mpz_parse_into_uint32(&fac_ui_arg, &failure, fac_arg);

      //If there was a parse failure, we have to return an error 
      //message.
      if (failure)
         {
         rv = Tcl_NewStringObj("arbint intfac: \"", -1);
         Tcl_AppendToObj(rv, fac_arg, -1);
         Tcl_AppendToObj(rv, "\" is not a recognized 32-bit unsigned integer.", -1);
         Tcl_SetObjResult(interp, rv);
         GMP_INTS_mpz_clear(&arb_result);
         return(TCL_ERROR);
         }

      //Calculate the factorial.
      GMP_INTS_mpz_fac_ui(&arb_result, fac_ui_arg);

      //Figure out the number of characters required for
      //the output string.
      chars_reqd = GMP_INTS_mpz_size_in_base_10(&arb_result);

      //Allocate space for the conversion result.
      string_result = TclpAlloc(sizeof(char) * chars_reqd);
      assert(string_result != NULL);

      //Make the conversion to a character string.
      GMP_INTS_mpz_to_string(string_result, &arb_result);

      //Assign the string result to a Tcl object.
      rv = Tcl_NewStringObj(string_result, -1);

      //Deallocate the string.
      TclpFree(string_result);

      //Deallocate space for the arbitrary-length integer.
      GMP_INTS_mpz_clear(&arb_result);

      //Assign the result to be the return value.
      Tcl_SetObjResult(interp, rv);

      //Return
      return(TCL_OK);
      }
   }


//Handles the "intgcd" subextension.
//08/06/01:  Visual inspection OK.
static
int ARBLENINTS_intgcd_handler(ClientData dummy, 
                              Tcl_Interp *interp, 
                              int objc,
                              Tcl_Obj *objv[])
   {
   Tcl_Obj *rv;

   //We must have two and exactly two additional arguments
   //to this function, which are the integers whose
   //gcd is to be calculated.
   if (objc != 4)
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "sint sint");
      return(TCL_ERROR);
      }
   else
      {
      GMP_INTS_mpz_struct arb_arg1, arb_arg2, arb_result;
      char *gcd_arg1, *gcd_arg2;
      int failure1, failure2;
      unsigned chars_reqd;
      char *string_result;
      int i, j;

      //Allocate space for the arbitrary-length integer result.
      GMP_INTS_mpz_init(&arb_arg1);
      GMP_INTS_mpz_init(&arb_arg2);
      GMP_INTS_mpz_init(&arb_result);

      //Grab pointers to the string representation of
      //the input arguments.  The storage does not belong to us.
      gcd_arg1 = Tcl_GetString(objv[2]);
      assert(gcd_arg1 != NULL);
      gcd_arg2 = Tcl_GetString(objv[3]);
      assert(gcd_arg2 != NULL);

      //Try to interpret either of the  strings as one of the NAN tags.
      //If it is one, return the appropriate result for
      //a binary operation.
      i = GMP_INTS_identify_nan_string(gcd_arg1);
      j = GMP_INTS_identify_nan_string(gcd_arg2);

      if ((i >= 0) || (j >= 0))
         {
         const char *p;

         //Find the max of i and j.  This isn't a scientific way to tag the
         //result, but will be OK.  Some information is lost no matter what
         //we do.
         if (i > j)
            ;
         else
            i = j;

         //i now contains the max.
         switch (i)
            {
            case 0:  p = GMP_INTS_supply_nan_string(2);
                     break;
            case 1:  p = GMP_INTS_supply_nan_string(3);
                     break;
            case 2:  p = GMP_INTS_supply_nan_string(2);
                     break;
            case 3:  p = GMP_INTS_supply_nan_string(3);
                     break;
            default:
                     assert(0);
                     break;
            }

         rv = Tcl_NewStringObj(p, -1);
         Tcl_SetObjResult(interp, rv);

         GMP_INTS_mpz_clear(&arb_arg1);
         GMP_INTS_mpz_clear(&arb_arg2);
         GMP_INTS_mpz_clear(&arb_result);

         return(TCL_OK);
         }

      //Try to convert both strings into arbitrary integers.
      GMP_INTS_mpz_set_general_int(&arb_arg1, &failure1, gcd_arg1);
      GMP_INTS_mpz_set_general_int(&arb_arg2, &failure2, gcd_arg2);

      //If there was a parse failure, we have to return an error 
      //message.  It is possible that both arguments failed the parse,
      //but only return one in the error message.
      if (failure1 || failure2)
         {
         rv = Tcl_NewStringObj("arbint intgcd: \"", -1);
         if (failure1)
            Tcl_AppendToObj(rv, gcd_arg1, -1);
         else
            Tcl_AppendToObj(rv, gcd_arg2, -1);

         Tcl_AppendToObj(rv, "\" is not a recognized signed integer.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_INTS_mpz_clear(&arb_arg1);
         GMP_INTS_mpz_clear(&arb_arg2);
         GMP_INTS_mpz_clear(&arb_result);

         return(TCL_ERROR);
         }

      //Calculate the gcd.
      GMP_INTS_mpz_gcd(&arb_result, &arb_arg1, &arb_arg2);

      //Figure out the number of characters required for
      //the output string.
      chars_reqd = GMP_INTS_mpz_size_in_base_10(&arb_result);

      //Allocate space for the conversion result.
      string_result = TclpAlloc(sizeof(char) * chars_reqd);
      assert(string_result != NULL);

      //Make the conversion to a character string.
      GMP_INTS_mpz_to_string(string_result, &arb_result);

      //Assign the string result to a Tcl object.
      rv = Tcl_NewStringObj(string_result, -1);

      //Deallocate the string.
      TclpFree(string_result);

      //Deallocate space for the arbitrary-length integers.
      GMP_INTS_mpz_clear(&arb_arg1);
      GMP_INTS_mpz_clear(&arb_arg2);
      GMP_INTS_mpz_clear(&arb_result);

      //Assign the result to be the return value.
      Tcl_SetObjResult(interp, rv);

      //Return
      return(TCL_OK);
      }
   }


//Handles the "intlcm" subextension.
//08/10/01:  Visual inspection OK.
static
int ARBLENINTS_intlcm_handler(ClientData dummy, 
                              Tcl_Interp *interp, 
                              int objc,
                              Tcl_Obj *objv[])
   {
   Tcl_Obj *rv;

   //We must have two and exactly two additional arguments
   //to this function, which are the integers whose
   //lcm is to be calculated.
   if (objc != 4)
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "sint sint");
      return(TCL_ERROR);
      }
   else
      {
      GMP_INTS_mpz_struct arb_arg1, arb_arg2, gcd, remainder, arb_result;
      char *lcm_arg1, *lcm_arg2;
      int failure1, failure2;
      unsigned chars_reqd;
      char *string_result;
      int i, j;

      //Allocate space for the arbitrary-length integers.
      GMP_INTS_mpz_init(&arb_arg1);
      GMP_INTS_mpz_init(&arb_arg2);
      GMP_INTS_mpz_init(&gcd);
      GMP_INTS_mpz_init(&remainder);
      GMP_INTS_mpz_init(&arb_result);

      //Grab pointers to the string representation of
      //the input arguments.  The storage does not belong to us.
      lcm_arg1 = Tcl_GetString(objv[2]);
      assert(lcm_arg1 != NULL);
      lcm_arg2 = Tcl_GetString(objv[3]);
      assert(lcm_arg2 != NULL);

      //Try to interpret either of the  strings as one of the NAN tags.
      //If it is one, return the appropriate result for
      //a binary operation.
      i = GMP_INTS_identify_nan_string(lcm_arg1);
      j = GMP_INTS_identify_nan_string(lcm_arg2);

      if ((i >= 0) || (j >= 0))
         {
         const char *p;

         //Find the max of i and j.  This isn't a scientific way to tag the
         //result, but will be OK.  Some information is lost no matter what
         //we do.
         if (i > j)
            ;
         else
            i = j;

         //i now contains the max.
         switch (i)
            {
            case 0:  p = GMP_INTS_supply_nan_string(2);
                     break;
            case 1:  p = GMP_INTS_supply_nan_string(3);
                     break;
            case 2:  p = GMP_INTS_supply_nan_string(2);
                     break;
            case 3:  p = GMP_INTS_supply_nan_string(3);
                     break;
            default:
                     assert(0);
                     break;
            }

         rv = Tcl_NewStringObj(p, -1);
         Tcl_SetObjResult(interp, rv);

         GMP_INTS_mpz_clear(&arb_arg1);
         GMP_INTS_mpz_clear(&arb_arg2);
         GMP_INTS_mpz_clear(&gcd);
         GMP_INTS_mpz_clear(&remainder);
         GMP_INTS_mpz_clear(&arb_result);

         return(TCL_OK);
         }

      //Try to convert both strings into arbitrary integers.
      GMP_INTS_mpz_set_general_int(&arb_arg1, &failure1, lcm_arg1);
      GMP_INTS_mpz_set_general_int(&arb_arg2, &failure2, lcm_arg2);

      //If there was a parse failure, we have to return an error 
      //message.  It is possible that both arguments failed the parse,
      //but only return one in the error message.
      if (failure1 || failure2)
         {
         rv = Tcl_NewStringObj("arbint intlcm: \"", -1);
         if (failure1)
            Tcl_AppendToObj(rv, lcm_arg1, -1);
         else
            Tcl_AppendToObj(rv, lcm_arg2, -1);

         Tcl_AppendToObj(rv, "\" is not a recognized signed integer.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_INTS_mpz_clear(&arb_arg1);
         GMP_INTS_mpz_clear(&arb_arg2);
         GMP_INTS_mpz_clear(&gcd);
         GMP_INTS_mpz_clear(&remainder);
         GMP_INTS_mpz_clear(&arb_result);

         return(TCL_ERROR);
         }

      //Adjust errant arguments.
      if (GMP_INTS_mpz_is_neg(&arb_arg1))
         GMP_INTS_mpz_negate(&arb_arg1);
      else if (GMP_INTS_mpz_is_zero(&arb_arg1))
         GMP_INTS_mpz_set_ui(&arb_arg1, 1);
      if (GMP_INTS_mpz_is_neg(&arb_arg2))
         GMP_INTS_mpz_negate(&arb_arg2);
      else if (GMP_INTS_mpz_is_zero(&arb_arg2))
         GMP_INTS_mpz_set_ui(&arb_arg2, 1);
      
      //Calculate the gcd.
      GMP_INTS_mpz_gcd(&gcd, &arb_arg1, &arb_arg2);

      //Calculate the lcm.
      GMP_INTS_mpz_mul(&arb_arg1, &arb_arg1, &arb_arg2);
      GMP_INTS_mpz_tdiv_qr(&arb_result, &remainder,
                           &arb_arg1, &gcd);

      //Figure out the number of characters required for
      //the output string.
      chars_reqd = GMP_INTS_mpz_size_in_base_10(&arb_result);

      //Allocate space for the conversion result.
      string_result = TclpAlloc(sizeof(char) * chars_reqd);
      assert(string_result != NULL);

      //Make the conversion to a character string.
      GMP_INTS_mpz_to_string(string_result, &arb_result);

      //Assign the string result to a Tcl object.
      rv = Tcl_NewStringObj(string_result, -1);

      //Deallocate the string.
      TclpFree(string_result);

      //Deallocate space for the arbitrary-length integers.
      GMP_INTS_mpz_clear(&arb_arg1);
      GMP_INTS_mpz_clear(&arb_arg2);
      GMP_INTS_mpz_clear(&gcd);
      GMP_INTS_mpz_clear(&remainder);
      GMP_INTS_mpz_clear(&arb_result);

      //Assign the result to be the return value.
      Tcl_SetObjResult(interp, rv);

      //Return
      return(TCL_OK);
      }
   }


//Handles the "intmod" subextension.
//08/06/01:  Visual inspection OK.
static
int ARBLENINTS_intmod_handler(ClientData dummy, 
                              Tcl_Interp *interp, 
                              int objc,
                              Tcl_Obj *objv[])
   {
   Tcl_Obj *rv;

   //We must have two and exactly two additional arguments
   //to this function, which are the integers whose
   //integer quotient is to be calculated.
   if (objc != 4)
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "sint sint");
      return(TCL_ERROR);
      }
   else
      {
      GMP_INTS_mpz_struct arb_dividend, arb_divisor, arb_quotient, arb_remainder;
      char *dividend_arg1, *divisor_arg2;
      int failure1, failure2;
      unsigned chars_reqd;
      char *string_result;
      int i, j;

      //Allocate space for the arbitrary-length integer arguments and results.
      GMP_INTS_mpz_init(&arb_dividend);
      GMP_INTS_mpz_init(&arb_divisor);
      GMP_INTS_mpz_init(&arb_quotient);
      GMP_INTS_mpz_init(&arb_remainder);

      //Grab pointers to the string representation of
      //the input arguments.  The storage does not belong to us.
      dividend_arg1 = Tcl_GetString(objv[2]);
      assert(dividend_arg1 != NULL);
      divisor_arg2 = Tcl_GetString(objv[3]);
      assert(divisor_arg2 != NULL);

      //Try to interpret either of the  strings as one of the NAN tags.
      //If it is one, return the appropriate result for
      //a binary operation.
      i = GMP_INTS_identify_nan_string(dividend_arg1);
      j = GMP_INTS_identify_nan_string(divisor_arg2);

      if ((i >= 0) || (j >= 0))
         {
         const char *p;

         //Find the max of i and j.  This isn't a scientific way to tag the
         //result, but will be OK.  Some information is lost no matter what
         //we do.
         if (i > j)
            ;
         else
            i = j;

         //i now contains the max.
         switch (i)
            {
            case 0:  p = GMP_INTS_supply_nan_string(2);
                     break;
            case 1:  p = GMP_INTS_supply_nan_string(3);
                     break;
            case 2:  p = GMP_INTS_supply_nan_string(2);
                     break;
            case 3:  p = GMP_INTS_supply_nan_string(3);
                     break;
            default:
                     assert(0);
                     break;
            }

         rv = Tcl_NewStringObj(p, -1);
         Tcl_SetObjResult(interp, rv);

         GMP_INTS_mpz_clear(&arb_dividend);
         GMP_INTS_mpz_clear(&arb_divisor);
         GMP_INTS_mpz_clear(&arb_quotient);
         GMP_INTS_mpz_clear(&arb_remainder);

         return(TCL_OK);
         }

      //Try to convert both strings into arbitrary integers.
      GMP_INTS_mpz_set_general_int(&arb_dividend, &failure1, dividend_arg1);
      GMP_INTS_mpz_set_general_int(&arb_divisor,  &failure2, divisor_arg2);

      //If there was a parse failure, we have to return an error 
      //message.  It is possible that both arguments failed the parse,
      //but only return one in the error message.
      if (failure1 || failure2)
         {
         rv = Tcl_NewStringObj("arbint intmod: \"", -1);
         if (failure1)
            Tcl_AppendToObj(rv, dividend_arg1, -1);
         else
            Tcl_AppendToObj(rv, divisor_arg2, -1);

         Tcl_AppendToObj(rv, "\" is not a recognized signed integer.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_INTS_mpz_clear(&arb_dividend);
         GMP_INTS_mpz_clear(&arb_divisor);
         GMP_INTS_mpz_clear(&arb_quotient);
         GMP_INTS_mpz_clear(&arb_remainder);

         return(TCL_ERROR);
         }

      //Calculate the quotient and remainder.
      GMP_INTS_mpz_tdiv_qr(&arb_quotient, &arb_remainder, &arb_dividend, &arb_divisor);

      //Figure out the number of characters required for
      //the output string.
      chars_reqd = GMP_INTS_mpz_size_in_base_10(&arb_remainder);

      //Allocate space for the conversion result.
      string_result = TclpAlloc(sizeof(char) * chars_reqd);
      assert(string_result != NULL);

      //Make the conversion to a character string.
      GMP_INTS_mpz_to_string(string_result, &arb_remainder);

      //Assign the string result to a Tcl object.
      rv = Tcl_NewStringObj(string_result, -1);

      //Deallocate the string.
      TclpFree(string_result);

      //Deallocate space for the arbitrary-length integers.
      GMP_INTS_mpz_clear(&arb_dividend);
      GMP_INTS_mpz_clear(&arb_divisor);
      GMP_INTS_mpz_clear(&arb_quotient);
      GMP_INTS_mpz_clear(&arb_remainder);

      //Assign the result to be the return value.
      Tcl_SetObjResult(interp, rv);

      //Return
      return(TCL_OK);
      }
   }


//Handles the "intmul" subextension.
//08/06/01:  Visual inspection OK.
static
int ARBLENINTS_intmul_handler(ClientData dummy, 
                              Tcl_Interp *interp, 
                              int objc,
                              Tcl_Obj *objv[])
   {
   Tcl_Obj *rv;

   //We must have two and exactly two additional arguments
   //to this function, which are the integers whose
   //product is to be calculated.
   if (objc != 4)
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "sint sint");
      return(TCL_ERROR);
      }
   else
      {
      GMP_INTS_mpz_struct arb_arg1, arb_arg2, arb_result;
      char *mul_arg1, *mul_arg2;
      int failure1, failure2;
      unsigned chars_reqd;
      char *string_result;
      int i, j;

      //Allocate space for the arbitrary-length integer result.
      GMP_INTS_mpz_init(&arb_arg1);
      GMP_INTS_mpz_init(&arb_arg2);
      GMP_INTS_mpz_init(&arb_result);

      //Grab pointers to the string representation of
      //the input arguments.  The storage does not belong to us.
      mul_arg1 = Tcl_GetString(objv[2]);
      assert(mul_arg1 != NULL);
      mul_arg2 = Tcl_GetString(objv[3]);
      assert(mul_arg2 != NULL);

      //Try to interpret either of the  strings as one of the NAN tags.
      //If it is one, return the appropriate result for
      //a binary operation.
      i = GMP_INTS_identify_nan_string(mul_arg1);
      j = GMP_INTS_identify_nan_string(mul_arg2);

      if ((i >= 0) || (j >= 0))
         {
         const char *p;

         //Find the max of i and j.  This isn't a scientific way to tag the
         //result, but will be OK.  Some information is lost no matter what
         //we do.
         if (i > j)
            ;
         else
            i = j;

         //i now contains the max.
         switch (i)
            {
            case 0:  p = GMP_INTS_supply_nan_string(2);
                     break;
            case 1:  p = GMP_INTS_supply_nan_string(3);
                     break;
            case 2:  p = GMP_INTS_supply_nan_string(2);
                     break;
            case 3:  p = GMP_INTS_supply_nan_string(3);
                     break;
            default:
                     assert(0);
                     break;
            }

         rv = Tcl_NewStringObj(p, -1);
         Tcl_SetObjResult(interp, rv);

         GMP_INTS_mpz_clear(&arb_arg1);
         GMP_INTS_mpz_clear(&arb_arg2);
         GMP_INTS_mpz_clear(&arb_result);

         return(TCL_OK);
         }

      //Try to convert both strings into arbitrary integers.
      GMP_INTS_mpz_set_general_int(&arb_arg1, &failure1, mul_arg1);
      GMP_INTS_mpz_set_general_int(&arb_arg2, &failure2, mul_arg2);

      //If there was a parse failure, we have to return an error 
      //message.  It is possible that both arguments failed the parse,
      //but only return one in the error message.
      if (failure1 || failure2)
         {
         rv = Tcl_NewStringObj("arbint intmul: \"", -1);
         if (failure1)
            Tcl_AppendToObj(rv, mul_arg1, -1);
         else
            Tcl_AppendToObj(rv, mul_arg2, -1);

         Tcl_AppendToObj(rv, "\" is not a recognized signed integer.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_INTS_mpz_clear(&arb_arg1);
         GMP_INTS_mpz_clear(&arb_arg2);
         GMP_INTS_mpz_clear(&arb_result);

         return(TCL_ERROR);
         }

      //Calculate the product.
      GMP_INTS_mpz_mul(&arb_result, &arb_arg1, &arb_arg2);

      //Figure out the number of characters required for
      //the output string.
      chars_reqd = GMP_INTS_mpz_size_in_base_10(&arb_result);

      //Allocate space for the conversion result.
      string_result = TclpAlloc(sizeof(char) * chars_reqd);
      assert(string_result != NULL);

      //Make the conversion to a character string.
      GMP_INTS_mpz_to_string(string_result, &arb_result);

      //Assign the string result to a Tcl object.
      rv = Tcl_NewStringObj(string_result, -1);

      //Deallocate the string.
      TclpFree(string_result);

      //Deallocate space for the arbitrary-length integers.
      GMP_INTS_mpz_clear(&arb_arg1);
      GMP_INTS_mpz_clear(&arb_arg2);
      GMP_INTS_mpz_clear(&arb_result);

      //Assign the result to be the return value.
      Tcl_SetObjResult(interp, rv);

      //Return
      return(TCL_OK);
      }
   }


//Handles the "intsub" subextension.
//08/06/01:  Visual inspection OK.
static
int ARBLENINTS_intsub_handler(ClientData dummy, 
                              Tcl_Interp *interp, 
                              int objc,
                              Tcl_Obj *objv[])
   {
   Tcl_Obj *rv;

   //We must have two and exactly two additional arguments
   //to this function, which are the integers whose
   //difference is to be calculated.
   if (objc != 4)
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "sint sint");
      return(TCL_ERROR);
      }
   else
      {
      GMP_INTS_mpz_struct arb_arg1, arb_arg2, arb_result;
      char *sub_arg1, *sub_arg2;
      int failure1, failure2;
      unsigned chars_reqd;
      char *string_result;
      int i, j;

      //Allocate space for the arbitrary-length integer result.
      GMP_INTS_mpz_init(&arb_arg1);
      GMP_INTS_mpz_init(&arb_arg2);
      GMP_INTS_mpz_init(&arb_result);

      //Grab pointers to the string representation of
      //the input arguments.  The storage does not belong to us.
      sub_arg1 = Tcl_GetString(objv[2]);
      assert(sub_arg1 != NULL);
      sub_arg2 = Tcl_GetString(objv[3]);
      assert(sub_arg2 != NULL);

      //Try to interpret either of the  strings as one of the NAN tags.
      //If it is one, return the appropriate result for
      //a binary operation.
      i = GMP_INTS_identify_nan_string(sub_arg1);
      j = GMP_INTS_identify_nan_string(sub_arg2);

      if ((i >= 0) || (j >= 0))
         {
         const char *p;

         //Find the max of i and j.  This isn't a scientific way to tag the
         //result, but will be OK.  Some information is lost no matter what
         //we do.
         if (i > j)
            ;
         else
            i = j;

         //i now contains the max.
         switch (i)
            {
            case 0:  p = GMP_INTS_supply_nan_string(2);
                     break;
            case 1:  p = GMP_INTS_supply_nan_string(3);
                     break;
            case 2:  p = GMP_INTS_supply_nan_string(2);
                     break;
            case 3:  p = GMP_INTS_supply_nan_string(3);
                     break;
            default:
                     assert(0);
                     break;
            }

         rv = Tcl_NewStringObj(p, -1);
         Tcl_SetObjResult(interp, rv);

         GMP_INTS_mpz_clear(&arb_arg1);
         GMP_INTS_mpz_clear(&arb_arg2);
         GMP_INTS_mpz_clear(&arb_result);

         return(TCL_OK);
         }

      //Try to convert both strings into arbitrary integers.
      GMP_INTS_mpz_set_general_int(&arb_arg1, &failure1, sub_arg1);
      GMP_INTS_mpz_set_general_int(&arb_arg2, &failure2, sub_arg2);

      //If there was a parse failure, we have to return an error 
      //message.  It is possible that both arguments failed the parse,
      //but only return one in the error message.
      if (failure1 || failure2)
         {
         rv = Tcl_NewStringObj("arbint intsub: \"", -1);
         if (failure1)
            Tcl_AppendToObj(rv, sub_arg1, -1);
         else
            Tcl_AppendToObj(rv, sub_arg2, -1);

         Tcl_AppendToObj(rv, "\" is not a recognized signed integer.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_INTS_mpz_clear(&arb_arg1);
         GMP_INTS_mpz_clear(&arb_arg2);
         GMP_INTS_mpz_clear(&arb_result);

         return(TCL_ERROR);
         }

      //Calculate the difference.
      GMP_INTS_mpz_sub(&arb_result, &arb_arg1, &arb_arg2);

      //Figure out the number of characters required for
      //the output string.
      chars_reqd = GMP_INTS_mpz_size_in_base_10(&arb_result);

      //Allocate space for the conversion result.
      string_result = TclpAlloc(sizeof(char) * chars_reqd);
      assert(string_result != NULL);

      //Make the conversion to a character string.
      GMP_INTS_mpz_to_string(string_result, &arb_result);

      //Assign the string result to a Tcl object.
      rv = Tcl_NewStringObj(string_result, -1);

      //Deallocate the string.
      TclpFree(string_result);

      //Deallocate space for the arbitrary-length integers.
      GMP_INTS_mpz_clear(&arb_arg1);
      GMP_INTS_mpz_clear(&arb_arg2);
      GMP_INTS_mpz_clear(&arb_result);

      //Assign the result to be the return value.
      Tcl_SetObjResult(interp, rv);

      //Return
      return(TCL_OK);
      }
   }


//Handles the "iseflag" subextension.
//07/29/01:  Visual inspection OK.  Have not located my Tcl book, am doing this
//from memory an intuition as far as how to set return results and so forth.
static
int ARBLENINTS_iseflag_handler(ClientData dummy, 
                               Tcl_Interp *interp, 
                               int objc,
                               Tcl_Obj *objv[])
   {
   Tcl_Obj *rv;

   //We must have one and exactly one additional argument
   //to this function, which is the string we want to
   //classify.
   if (objc != 3)
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "stringarg");
      return(TCL_ERROR);
      }
   else
      {
      char *string_arg;

      //Grab a pointer to the string representation of
      //the input argument.  The storage does not belong to us.
      string_arg = Tcl_GetString(objv[2]);
      assert(string_arg != NULL);

      //Try to parse it out.  We will definitely get one of
      //the return values.
      if (!strcmp(string_arg, GMP_INTS_EF_INTOVF_POS_STRING))
         {
         rv = Tcl_NewStringObj("1", -1);
         }
      else if (!strcmp(string_arg, GMP_INTS_EF_INTOVF_NEG_STRING))
         {
         rv = Tcl_NewStringObj("2", -1);
         }
      else if (!strcmp(string_arg, GMP_INTS_EF_INTOVF_TAINT_POS_STRING))
         {
         rv = Tcl_NewStringObj("3", -1);
         }
      else if (!strcmp(string_arg, GMP_INTS_EF_INTOVF_TAINT_NEG_STRING))
         {
         rv = Tcl_NewStringObj("4", -1);
         }
      else
         {
         rv = Tcl_NewStringObj("0", -1);
         }

      //Assign the result to be the return value.
      Tcl_SetObjResult(interp, rv);

      //Return
      return(TCL_OK);
      }
   }


//08/08/01:  Visual inspection OK.
static
int ARBLENINTS_rnadd_handler(ClientData dummy, 
                             Tcl_Interp *interp, 
                             int objc,
                             Tcl_Obj *objv[])
   {
   Tcl_Obj *rv;

   //We must have exactly two additional arguments
   //to this function, which are the rational numbers
   //to add.
   if (objc != 4)
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "srn srn");
      return(TCL_ERROR);
      }
   else
      {
      char *input_arg;
      int failure;
      char *string_result;
      GMP_RATS_mpq_struct arg1, arg2, result;

      //Allocate space for the rational numbers.
      GMP_RATS_mpq_init(&arg1);
      GMP_RATS_mpq_init(&arg2);
      GMP_RATS_mpq_init(&result);

      //Grab a pointer to the string representation of
      //the first input argument.  The storage does not belong to us.
      input_arg = Tcl_GetString(objv[2]);
      assert(input_arg != NULL);

      //Try to parse our first input string as a rational number.
      //If we are not successful in this, must abort.
      GMP_RATS_mpq_set_all_format_rat_num(input_arg,
                                          &failure,
                                          &arg1);

      if (failure)
         {
         rv = Tcl_NewStringObj("arbint rnadd: \"", -1);
         Tcl_AppendToObj(rv, input_arg, -1);

         Tcl_AppendToObj(rv, "\" is not a recognized rational number.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_RATS_mpq_clear(&arg1);
         GMP_RATS_mpq_clear(&arg2);
         GMP_RATS_mpq_clear(&result);

         return(TCL_ERROR);
         }

      //Grab a pointer to the string representation of
      //the second input argument.  The storage does not belong to us.
      input_arg = Tcl_GetString(objv[3]);
      assert(input_arg != NULL);

      //Try to parse our second input string as a rational number.
      //If we are not successful in this, must abort.
      GMP_RATS_mpq_set_all_format_rat_num(input_arg,
                                          &failure,
                                          &arg2);

      if (failure)
         {
         rv = Tcl_NewStringObj("arbint rnadd: \"", -1);
         Tcl_AppendToObj(rv, input_arg, -1);

         Tcl_AppendToObj(rv, "\" is not a recognized rational number.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_RATS_mpq_clear(&arg1);
         GMP_RATS_mpq_clear(&arg2);
         GMP_RATS_mpq_clear(&result);

         return(TCL_ERROR);
         }

      //Perform the actual addition of the rational numbers.  All
      //error cases are covered.  If either of the inputs has a 
      //denominator of zero, this will propagate to the result.
      GMP_RATS_mpq_add(&result, &arg1, &arg2);

      //If the result has been NAN'd, return the string "NAN".
      if (GMP_RATS_mpq_is_nan(&result))
         {
         rv = Tcl_NewStringObj("NAN", -1);

         Tcl_SetObjResult(interp, rv);

         GMP_RATS_mpq_clear(&arg1);
         GMP_RATS_mpq_clear(&arg2);
         GMP_RATS_mpq_clear(&result);

         return(TCL_OK);
         }

      //Allocate space for the string result which we'll form for
      //both numerator and denominator.  We need the maximum, because we'll only
      //do one number at a time.
      string_result = TclpAlloc(sizeof(char) 
                                * 
                                INTFUNC_max
                                   (
                                   GMP_INTS_mpz_size_in_base_10(&(result.num)),
                                   GMP_INTS_mpz_size_in_base_10(&(result.den))
                                   )
                                );
      assert(string_result != NULL);

      //Convert the numerator to a string and set that to be the
      //return value.
      GMP_INTS_mpz_to_string(string_result, &(result.num));
      rv = Tcl_NewStringObj(string_result, -1);

      //Append the separating slash.
      Tcl_AppendToObj(rv, "/", -1);

      //Convert the denominator to a string and append that to the
      //return value.
      GMP_INTS_mpz_to_string(string_result, &(result.den));
      Tcl_AppendToObj(rv, string_result, -1);

      //Assign the result to be the return value.
      Tcl_SetObjResult(interp, rv);

      //Free up all dynamic memory.
      TclpFree(string_result);
      GMP_RATS_mpq_clear(&arg1);
      GMP_RATS_mpq_clear(&arg2);
      GMP_RATS_mpq_clear(&result);

      //Return
      return(TCL_OK);
      }
   }


//08/16/01: Visual inspection OK.   
static
int ARBLENINTS_rncmp_handler(ClientData dummy, 
                             Tcl_Interp *interp, 
                             int objc,
                             Tcl_Obj *objv[])
   {
   Tcl_Obj *rv;

   //We must have exactly two additional arguments
   //to this function, which are the rational numbers
   //to compare.
   if (objc != 4)
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "srn srn");
      return(TCL_ERROR);
      }
   else
      {
      char *input_arg;
      int failure, compare_result;
      GMP_RATS_mpq_struct arg1, arg2;

      //Allocate space for the rational numbers.
      GMP_RATS_mpq_init(&arg1);
      GMP_RATS_mpq_init(&arg2);

      //Grab a pointer to the string representation of
      //the first input argument.  The storage does not belong to us.
      input_arg = Tcl_GetString(objv[2]);
      assert(input_arg != NULL);

      //Try to parse our first input string as a rational number.
      //If we are not successful in this, must abort.
      GMP_RATS_mpq_set_all_format_rat_num(input_arg,
                                          &failure,
                                          &arg1);

      if (failure)
         {
         rv = Tcl_NewStringObj("arbint rncmp: \"", -1);
         Tcl_AppendToObj(rv, input_arg, -1);

         Tcl_AppendToObj(rv, "\" is not a recognized rational number.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_RATS_mpq_clear(&arg1);
         GMP_RATS_mpq_clear(&arg2);

         return(TCL_ERROR);
         }

      //Grab a pointer to the string representation of
      //the second input argument.  The storage does not belong to us.
      input_arg = Tcl_GetString(objv[3]);
      assert(input_arg != NULL);

      //Try to parse our second input string as a rational number.
      //If we are not successful in this, must abort.
      GMP_RATS_mpq_set_all_format_rat_num(input_arg,
                                          &failure,
                                          &arg2);

      if (failure)
         {
         rv = Tcl_NewStringObj("arbint rncmp: \"", -1);
         Tcl_AppendToObj(rv, input_arg, -1);

         Tcl_AppendToObj(rv, "\" is not a recognized rational number.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_RATS_mpq_clear(&arg1);
         GMP_RATS_mpq_clear(&arg2);

         return(TCL_ERROR);
         }

      //Perform the actual comparison of the rational numbers.  All
      //error cases are covered.  If either of the inputs has a 
      //denominator of zero, this will propagate to the result.
      compare_result = GMP_RATS_mpq_cmp(&arg1, &arg2, &failure);

      //If the failure flag was thrown, we have to throw an error.
      //The reason is that if we can't successfully compare the two
      //rational numbers, then we have to kill the script--logical
      //correctness is not possible.
      if (failure)
         {
         rv = Tcl_NewStringObj("arbint rncmp: can't compare supplied rational numbers.", -1);

         Tcl_SetObjResult(interp, rv);

         GMP_RATS_mpq_clear(&arg1);
         GMP_RATS_mpq_clear(&arg2);

         return(TCL_ERROR);
         }

      //Convert the comparison result to a string.
      if (compare_result < 0)
         rv = Tcl_NewStringObj("-1", -1);
      else if (compare_result == 0)
         rv = Tcl_NewStringObj("0", -1);
      else
         rv = Tcl_NewStringObj("1", -1);

      //Assign the result to be the return value.
      Tcl_SetObjResult(interp, rv);

      //Free up all dynamic memory.
      GMP_RATS_mpq_clear(&arg1);
      GMP_RATS_mpq_clear(&arg2);

      //Return
      return(TCL_OK);
      }
   }


//08/09/01:  Visual inspection OK.
static
int ARBLENINTS_rndiv_handler(ClientData dummy, 
                             Tcl_Interp *interp, 
                             int objc,
                             Tcl_Obj *objv[])
   {
   Tcl_Obj *rv;

   //We must have exactly two additional arguments
   //to this function, which are the rational numbers
   //to divide.
   if (objc != 4)
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "srn srn");
      return(TCL_ERROR);
      }
   else
      {
      char *input_arg;
      int failure;
      char *string_result;
      GMP_RATS_mpq_struct arg1, arg2, result;

      //Allocate space for the rational numbers.
      GMP_RATS_mpq_init(&arg1);
      GMP_RATS_mpq_init(&arg2);
      GMP_RATS_mpq_init(&result);

      //Grab a pointer to the string representation of
      //the first input argument.  The storage does not belong to us.
      input_arg = Tcl_GetString(objv[2]);
      assert(input_arg != NULL);

      //Try to parse our first input string as a rational number.
      //If we are not successful in this, must abort.
      GMP_RATS_mpq_set_all_format_rat_num(input_arg,
                                          &failure,
                                          &arg1);

      if (failure)
         {
         rv = Tcl_NewStringObj("arbint rndiv: \"", -1);
         Tcl_AppendToObj(rv, input_arg, -1);

         Tcl_AppendToObj(rv, "\" is not a recognized rational number.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_RATS_mpq_clear(&arg1);
         GMP_RATS_mpq_clear(&arg2);
         GMP_RATS_mpq_clear(&result);

         return(TCL_ERROR);
         }

      //Grab a pointer to the string representation of
      //the second input argument.  The storage does not belong to us.
      input_arg = Tcl_GetString(objv[3]);
      assert(input_arg != NULL);

      //Try to parse our second input string as a rational number.
      //If we are not successful in this, must abort.
      GMP_RATS_mpq_set_all_format_rat_num(input_arg,
                                          &failure,
                                          &arg2);

      if (failure)
         {
         rv = Tcl_NewStringObj("arbint rndiv: \"", -1);
         Tcl_AppendToObj(rv, input_arg, -1);

         Tcl_AppendToObj(rv, "\" is not a recognized rational number.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_RATS_mpq_clear(&arg1);
         GMP_RATS_mpq_clear(&arg2);
         GMP_RATS_mpq_clear(&result);

         return(TCL_ERROR);
         }

      //Perform the actual division of the rational numbers.  All
      //error cases are covered.  If either of the inputs has a 
      //denominator of zero, this will propagate to the result.
      GMP_RATS_mpq_div(&result, &arg1, &arg2);

      //If the result has been NAN'd, return the string "NAN".
      if (GMP_RATS_mpq_is_nan(&result))
         {
         rv = Tcl_NewStringObj("NAN", -1);

         Tcl_SetObjResult(interp, rv);

         GMP_RATS_mpq_clear(&arg1);
         GMP_RATS_mpq_clear(&arg2);
         GMP_RATS_mpq_clear(&result);

         return(TCL_OK);
         }

      //Allocate space for the string result which we'll form for
      //both numerator and denominator.  We need the maximum, because we'll only
      //do one number at a time.
      string_result = TclpAlloc(sizeof(char) 
                                * 
                                INTFUNC_max
                                   (
                                   GMP_INTS_mpz_size_in_base_10(&(result.num)),
                                   GMP_INTS_mpz_size_in_base_10(&(result.den))
                                   )
                                );
      assert(string_result != NULL);

      //Convert the numerator to a string and set that to be the
      //return value.
      GMP_INTS_mpz_to_string(string_result, &(result.num));
      rv = Tcl_NewStringObj(string_result, -1);

      //Append the separating slash.
      Tcl_AppendToObj(rv, "/", -1);

      //Convert the denominator to a string and append that to the
      //return value.
      GMP_INTS_mpz_to_string(string_result, &(result.den));
      Tcl_AppendToObj(rv, string_result, -1);

      //Assign the result to be the return value.
      Tcl_SetObjResult(interp, rv);

      //Free up all dynamic memory.
      TclpFree(string_result);
      GMP_RATS_mpq_clear(&arg1);
      GMP_RATS_mpq_clear(&arg2);
      GMP_RATS_mpq_clear(&result);

      //Return
      return(TCL_OK);
      }
   }


//08/09/01:  Visual inspection OK.
static
int ARBLENINTS_rnmul_handler(ClientData dummy, 
                             Tcl_Interp *interp, 
                             int objc,
                             Tcl_Obj *objv[])
   {
   Tcl_Obj *rv;

   //We must have exactly two additional arguments
   //to this function, which are the rational numbers
   //to add.
   if (objc != 4)
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "srn srn");
      return(TCL_ERROR);
      }
   else
      {
      char *input_arg;
      int failure;
      char *string_result;
      GMP_RATS_mpq_struct arg1, arg2, result;

      //Allocate space for the rational numbers.
      GMP_RATS_mpq_init(&arg1);
      GMP_RATS_mpq_init(&arg2);
      GMP_RATS_mpq_init(&result);

      //Grab a pointer to the string representation of
      //the first input argument.  The storage does not belong to us.
      input_arg = Tcl_GetString(objv[2]);
      assert(input_arg != NULL);

      //Try to parse our first input string as a rational number.
      //If we are not successful in this, must abort.
      GMP_RATS_mpq_set_all_format_rat_num(input_arg,
                                          &failure,
                                          &arg1);

      if (failure)
         {
         rv = Tcl_NewStringObj("arbint rnmul: \"", -1);
         Tcl_AppendToObj(rv, input_arg, -1);

         Tcl_AppendToObj(rv, "\" is not a recognized rational number.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_RATS_mpq_clear(&arg1);
         GMP_RATS_mpq_clear(&arg2);
         GMP_RATS_mpq_clear(&result);

         return(TCL_ERROR);
         }

      //Grab a pointer to the string representation of
      //the second input argument.  The storage does not belong to us.
      input_arg = Tcl_GetString(objv[3]);
      assert(input_arg != NULL);

      //Try to parse our second input string as a rational number.
      //If we are not successful in this, must abort.
      GMP_RATS_mpq_set_all_format_rat_num(input_arg,
                                          &failure,
                                          &arg2);

      if (failure)
         {
         rv = Tcl_NewStringObj("arbint rnmul: \"", -1);
         Tcl_AppendToObj(rv, input_arg, -1);

         Tcl_AppendToObj(rv, "\" is not a recognized rational number.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_RATS_mpq_clear(&arg1);
         GMP_RATS_mpq_clear(&arg2);
         GMP_RATS_mpq_clear(&result);

         return(TCL_ERROR);
         }

      //Perform the actual multiplication of the rational numbers.  All
      //error cases are covered.  If either of the inputs has a 
      //denominator of zero, this will propagate to the result.
      GMP_RATS_mpq_mul(&result, &arg1, &arg2);

      //If the result has been NAN'd, return the string "NAN".
      if (GMP_RATS_mpq_is_nan(&result))
         {
         rv = Tcl_NewStringObj("NAN", -1);

         Tcl_SetObjResult(interp, rv);

         GMP_RATS_mpq_clear(&arg1);
         GMP_RATS_mpq_clear(&arg2);
         GMP_RATS_mpq_clear(&result);

         return(TCL_OK);
         }

      //Allocate space for the string result which we'll form for
      //both numerator and denominator.  We need the maximum, because we'll only
      //do one number at a time.
      string_result = TclpAlloc(sizeof(char) 
                                * 
                                INTFUNC_max
                                   (
                                   GMP_INTS_mpz_size_in_base_10(&(result.num)),
                                   GMP_INTS_mpz_size_in_base_10(&(result.den))
                                   )
                                );
      assert(string_result != NULL);

      //Convert the numerator to a string and set that to be the
      //return value.
      GMP_INTS_mpz_to_string(string_result, &(result.num));
      rv = Tcl_NewStringObj(string_result, -1);

      //Append the separating slash.
      Tcl_AppendToObj(rv, "/", -1);

      //Convert the denominator to a string and append that to the
      //return value.
      GMP_INTS_mpz_to_string(string_result, &(result.den));
      Tcl_AppendToObj(rv, string_result, -1);

      //Assign the result to be the return value.
      Tcl_SetObjResult(interp, rv);

      //Free up all dynamic memory.
      TclpFree(string_result);
      GMP_RATS_mpq_clear(&arg1);
      GMP_RATS_mpq_clear(&arg2);
      GMP_RATS_mpq_clear(&result);

      //Return
      return(TCL_OK);
      }
   }


//08/09/01:  Visual inspection OK.
static
int ARBLENINTS_rnred_handler(ClientData dummy, 
                             Tcl_Interp *interp, 
                             int objc,
                             Tcl_Obj *objv[])
   {
   Tcl_Obj *rv;

   //We must have exactly one additional argument
   //to this function, which is the rational number
   //to provide the fully reduced form of.
   if (objc != 3)
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "srn");
      return(TCL_ERROR);
      }
   else
      {
      char *input_arg;
      int failure;
      char *string_result;
      GMP_RATS_mpq_struct rn;

      //We will need a rational number to hold the return value
      //from the parsing function.  Allocate that now.
      GMP_RATS_mpq_init(&rn);

      //Grab a pointer to the string representation of
      //the input argument.  The storage does not belong to us.
      input_arg = Tcl_GetString(objv[2]);
      assert(input_arg != NULL);

      //Try to parse our input string as a rational number.
      //If we are not successful in this, must abort.
      GMP_RATS_mpq_set_all_format_rat_num(input_arg,
                                          &failure,
                                          &rn);

      if (failure)
         {
         rv = Tcl_NewStringObj("arbint rnred: \"", -1);
         Tcl_AppendToObj(rv, input_arg, -1);

         Tcl_AppendToObj(rv, "\" is not a recognized rational number.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_RATS_mpq_clear(&rn);

         return(TCL_ERROR);
         }

      //Normalize the rational number.  This takes care of the
      //sign and also of the coprimality of numerator and
      //denominator.
      GMP_RATS_mpq_normalize(&rn);

      //Allocate space for the string result which we'll form for
      //both numbers.  We need the maximum, because we'll only
      //do one number at a time.
      string_result = TclpAlloc(sizeof(char) 
                                * 
                                INTFUNC_max
                                   (
                                   GMP_INTS_mpz_size_in_base_10(&(rn.num)),
                                   GMP_INTS_mpz_size_in_base_10(&(rn.den))
                                   )
                                );
      assert(string_result != NULL);

      //Convert the numerator to a string and set that to be the
      //return value.
      GMP_INTS_mpz_to_string(string_result, &(rn.num));
      rv = Tcl_NewStringObj(string_result, -1);

      //Append the separating slash.
      Tcl_AppendToObj(rv, "/", -1);

      //Convert the denominator to a string and append that to the
      //return value.
      GMP_INTS_mpz_to_string(string_result, &(rn.den));
      Tcl_AppendToObj(rv, string_result, -1);

      //Assign the result to be the return value.
      Tcl_SetObjResult(interp, rv);

      //Free up all dynamic memory.
      TclpFree(string_result);
      GMP_RATS_mpq_clear(&rn);

      //Return
      return(TCL_OK);
      }
   }


//08/08/01:  Visual inspection OK.
static
int ARBLENINTS_rnsub_handler(ClientData dummy, 
                             Tcl_Interp *interp, 
                             int objc,
                             Tcl_Obj *objv[])
   {
   Tcl_Obj *rv;

   //We must have exactly two additional arguments
   //to this function, which are the rational numbers
   //to subtract.
   if (objc != 4)
      {
      Tcl_WrongNumArgs(interp,
                       2,
                       objv,
                       "srn srn");
      return(TCL_ERROR);
      }
   else
      {
      char *input_arg;
      int failure;
      char *string_result;
      GMP_RATS_mpq_struct arg1, arg2, result;

      //Allocate space for the rational numbers.
      GMP_RATS_mpq_init(&arg1);
      GMP_RATS_mpq_init(&arg2);
      GMP_RATS_mpq_init(&result);

      //Grab a pointer to the string representation of
      //the first input argument.  The storage does not belong to us.
      input_arg = Tcl_GetString(objv[2]);
      assert(input_arg != NULL);

      //Try to parse our first input string as a rational number.
      //If we are not successful in this, must abort.
      GMP_RATS_mpq_set_all_format_rat_num(input_arg,
                                          &failure,
                                          &arg1);

      if (failure)
         {
         rv = Tcl_NewStringObj("arbint rnsub: \"", -1);
         Tcl_AppendToObj(rv, input_arg, -1);

         Tcl_AppendToObj(rv, "\" is not a recognized rational number.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_RATS_mpq_clear(&arg1);
         GMP_RATS_mpq_clear(&arg2);
         GMP_RATS_mpq_clear(&result);

         return(TCL_ERROR);
         }

      //Grab a pointer to the string representation of
      //the second input argument.  The storage does not belong to us.
      input_arg = Tcl_GetString(objv[3]);
      assert(input_arg != NULL);

      //Try to parse our second input string as a rational number.
      //If we are not successful in this, must abort.
      GMP_RATS_mpq_set_all_format_rat_num(input_arg,
                                          &failure,
                                          &arg2);

      if (failure)
         {
         rv = Tcl_NewStringObj("arbint rnsub: \"", -1);
         Tcl_AppendToObj(rv, input_arg, -1);

         Tcl_AppendToObj(rv, "\" is not a recognized rational number.", -1);
         Tcl_SetObjResult(interp, rv);

         GMP_RATS_mpq_clear(&arg1);
         GMP_RATS_mpq_clear(&arg2);
         GMP_RATS_mpq_clear(&result);

         return(TCL_ERROR);
         }

      //Perform the actual subtraction of the rational numbers.  All
      //error cases are covered.  If either of the inputs has a 
      //denominator of zero, this will propagate to the result.
      GMP_RATS_mpq_sub(&result, &arg1, &arg2);

      //If the result has been NAN'd, return the string "NAN".
      if (GMP_RATS_mpq_is_nan(&result))
         {
         rv = Tcl_NewStringObj("NAN", -1);

         Tcl_SetObjResult(interp, rv);

         GMP_RATS_mpq_clear(&arg1);
         GMP_RATS_mpq_clear(&arg2);
         GMP_RATS_mpq_clear(&result);

         return(TCL_OK);
         }

      //Allocate space for the string result which we'll form for
      //both numerator and denominator.  We need the maximum, because we'll only
      //do one number at a time.
      string_result = TclpAlloc(sizeof(char) 
                                * 
                                INTFUNC_max
                                   (
                                   GMP_INTS_mpz_size_in_base_10(&(result.num)),
                                   GMP_INTS_mpz_size_in_base_10(&(result.den))
                                   )
                                );
      assert(string_result != NULL);

      //Convert the numerator to a string and set that to be the
      //return value.
      GMP_INTS_mpz_to_string(string_result, &(result.num));
      rv = Tcl_NewStringObj(string_result, -1);

      //Append the separating slash.
      Tcl_AppendToObj(rv, "/", -1);

      //Convert the denominator to a string and append that to the
      //return value.
      GMP_INTS_mpz_to_string(string_result, &(result.den));
      Tcl_AppendToObj(rv, string_result, -1);

      //Assign the result to be the return value.
      Tcl_SetObjResult(interp, rv);

      //Free up all dynamic memory.
      TclpFree(string_result);
      GMP_RATS_mpq_clear(&arg1);
      GMP_RATS_mpq_clear(&arg2);
      GMP_RATS_mpq_clear(&result);

      //Return
      return(TCL_OK);
      }
   }


//This is the search data table of possible subcommands
//for the "arbint" extension.  These must be kept 
//in alphabetical order, because a binary search is done
//on this table in order to find an entry.  If this table
//falls out of alphabetical order, the binary search may
//fail when in fact the entry exists.
//
//In a lot of cases below, this table is set up to accept
//short forms.  This is purely undocumented, and I won't put
//it in any documentation.  In a lot of cases, these table
//entries cover common mistakes where people forget the "int".
//
static struct EXTNINIT_subextn_bsearch_record_struct 
   ARBLENINTS_subextn_tbl[] =
      {
         { "brap",             ARBLENINTS_cfbrapab_handler      },
         { "cfbrapab",         ARBLENINTS_cfbrapab_handler      },
         { "cfratnum",         ARBLENINTS_cfratnum_handler      },
         { "cmp",              ARBLENINTS_intcmp_handler        },
         { "commanate",        ARBLENINTS_commanate_handler     },
         { "compare",          ARBLENINTS_intcmp_handler        },
         { "const",            ARBLENINTS_const_handler         },
         { "decommanate",      ARBLENINTS_decommanate_handler   },
         { "div",              ARBLENINTS_intdiv_handler        },
         { "divide",           ARBLENINTS_intdiv_handler        },
         { "exp",              ARBLENINTS_intexp_handler        },
         { "fac",              ARBLENINTS_intfac_handler        },
         { "factorial",        ARBLENINTS_intfac_handler        },
         { "gcd",              ARBLENINTS_intgcd_handler        },
         { "intadd",           ARBLENINTS_intadd_handler        },
         { "intcmp",           ARBLENINTS_intcmp_handler        },
         { "intdiv",           ARBLENINTS_intdiv_handler        },
         { "intexp",           ARBLENINTS_intexp_handler        },
         { "intfac",           ARBLENINTS_intfac_handler        },
         { "intgcd",           ARBLENINTS_intgcd_handler        },
         { "intlcm",           ARBLENINTS_intlcm_handler        },
         { "intmod",           ARBLENINTS_intmod_handler        },
         { "intmul",           ARBLENINTS_intmul_handler        },
         { "intsub",           ARBLENINTS_intsub_handler        },
         { "iseflag",          ARBLENINTS_iseflag_handler       },
         { "lcm",              ARBLENINTS_intlcm_handler        },
         { "mod",              ARBLENINTS_intmod_handler        },
         { "mul",              ARBLENINTS_intmul_handler        },
         { "multiply",         ARBLENINTS_intmul_handler        },
         { "rnadd",            ARBLENINTS_rnadd_handler         },
         { "rncmp",            ARBLENINTS_rncmp_handler         },
         { "rndiv",            ARBLENINTS_rndiv_handler         },
         { "rnmul",            ARBLENINTS_rnmul_handler         },
         { "rnred",            ARBLENINTS_rnred_handler         },
         { "rnsub",            ARBLENINTS_rnsub_handler         },
         { "times",            ARBLENINTS_intmul_handler        },
      };


//Procedure called when the "arbint" command is encountered in a Tcl script.
//07/29/01:  Visual inspection OK.  Have not located my Tcl book, am doing this
//from memory an intuition as far as how to set return results and so forth.
int ARBLENINTS_arbint_extn_command(ClientData dummy, 
                                   Tcl_Interp *interp, 
                                   int objc,
                                   Tcl_Obj *objv[]) 
   {
   char *subcommand;
      //Pointer to subcommand string.
   int tbl_entry;
      //Index into the subcommand lookup table, or -1
      //if no match.
   Tcl_Obj *rv;
      //The return result (a string) if there is an error.
      //In the normal execution case, one of the functions
      //above supplies the return object.
   
   if (objc < 2)
      {
      //It isn't possible to have an object count of less than 
      //2, because you must have at least the command name
      //plus a subcommand.  The best way to handle this is
      //to indicate wrong number of arguments.
      Tcl_WrongNumArgs(interp, 
                       1,
                       objv,
                       "option ?args?");
      return(TCL_ERROR);
      }
   else
      {
      //A potentially appropriate number of arguments has been
      //specified.  Try to look up the subcommand.

      subcommand = Tcl_GetString(objv[1]);
         //Grab the string representation of the subcommand.
         //This is constant, belongs to Tcl, and cannot be
         //modified.

      tbl_entry = EXTNINIT_subextension_bsearch(
                     ARBLENINTS_subextn_tbl,
                     sizeof(ARBLENINTS_subextn_tbl)/sizeof(ARBLENINTS_subextn_tbl[0]),
                     subcommand);
      assert(tbl_entry < (int)(sizeof(ARBLENINTS_subextn_tbl)/sizeof(ARBLENINTS_subextn_tbl[0])));

      //If the integer returned is zero or positive, should
      //run the subfunction.  If negative, this is an error and 
      //should generate meaningful message.  A meaningful message
      //would definitely consist of all valid subcommands.
      if (tbl_entry < 0)
         {
         //This is an error path.
         rv = Tcl_NewStringObj("arbint: bad option \"", -1);
         subcommand = Tcl_GetString(objv[1]);
         Tcl_AppendToObj(rv, subcommand, -1);
         Tcl_AppendToObj(rv, "\": valid options are ", -1);

         for (tbl_entry=0;
              tbl_entry < sizeof(ARBLENINTS_subextn_tbl)/sizeof(ARBLENINTS_subextn_tbl[0]);
              tbl_entry++)
            {
            if ((sizeof(ARBLENINTS_subextn_tbl)/sizeof(ARBLENINTS_subextn_tbl[0]) != 1)
                && (tbl_entry == sizeof(ARBLENINTS_subextn_tbl)/sizeof(ARBLENINTS_subextn_tbl[0]) - 1))
            Tcl_AppendToObj(rv, "and ", -1);
            Tcl_AppendToObj(rv, ARBLENINTS_subextn_tbl[tbl_entry].name, -1);
            if (tbl_entry == sizeof(ARBLENINTS_subextn_tbl)/sizeof(ARBLENINTS_subextn_tbl[0]) - 1)
               Tcl_AppendToObj(rv, ".", -1);
            else
               Tcl_AppendToObj(rv, ", ", -1);
            }

         //Now, set the return value to be the object with our
         //meaningful string message.
         Tcl_SetObjResult(interp, rv);

         return(TCL_ERROR);
         }
      else
         {
         //Call the function pointer.  Called function will
         //set the string return value.
         return((*ARBLENINTS_subextn_tbl[tbl_entry].fptr)
                (dummy, interp, objc, objv));
         }
      }
   }


//Performs initial registration to the hash table.
//07/29/01:  Visual inspection OK.  Have not located my Tcl book, am doing this
//from memory an intuition as far as how to set return results and so forth.
void ARBLENINTS_arbint_extn_init(Tcl_Interp *interp)
   {
   //Register a command named "crc32".
   Tcl_CreateObjCommand(interp, 
                        "arbint",
                        (Tcl_ObjCmdProc *)ARBLENINTS_arbint_extn_command,
                        NULL,
                        NULL);
   }



//Returns version control string for file.
//
const char *ARBLENINTS_cvcinfo(void)
{   
    return ("$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tclxtens_7_5/arblenints.c 71 2016-11-05 11:07:06Z dashley $");
}


//Returns version control string for associated .H file.
//
const char *ARBLENINTS_hvcinfo(void)
{   
    return (ARBLENINTS_H_VERSION);
}

//End of arblenints.c.
