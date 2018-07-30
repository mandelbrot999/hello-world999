//$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tclxtens_7_5/credits.c 71 2016-11-05 11:07:06Z dashley $
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
#define MODULE_CREDITS

#include "tcl.h"
#include "tcldecls.h"

#include <string.h>

#include "build_config.h"
#include "credits.h"


//The array below is an array of string pointers which give information about who
//is responsible for what and so forth.  Each atomic group (by atomic I mean the
//the minimum unit to be printed) is separated by a NULL pointer.
static char *credits_array[] =
   {
   "******************************************************************************",
   "* This product is an open-source statically-linked version of Tcl/Tk 8.3.1,  *",
   "* originally from Scriptics.  This product and its source code can be        *",
   "* downloaded at no cost from http://ijutools.sourceforge.net.  We are        *",
   "* especially grateful to SourceForge for providing version control and       *",
   "* hosting services to the open-source community, and for technical support   *",
   "* on many occasions.  Without SourceForge, this project would not have been  *",
   "* possible.  This product is licensed under the GNU Public License (GPL).    *",
   "******************************************************************************",
   NULL,
   "Tcl/Tk 8.3.1",
   "   Interwoven (formerly Ajuba Solutions, formerly Scriptics), with special",
   "   thanks to Jeff Hobbs, Jan Nijtmans, Dave Graveaux, D. Richard Hipp (for",
   "   \"mktclapp\"), Dan Kuchler, John Ousterhout, and everyone at comp.lang.tcl.",
   NULL,
   "arbint",
   "   Implemented by Dave Ashley.  Special thanks to the co-authors on the",
   "   original rational approximation paper (Joe DeVoe, Karl Perttunen, Cory",
   "   Pratt, and Anatoly Zhigljavsky).  Special thanks to GNU for the GNU MP",
   "   library (GMP), which was used as a model to implement large integer",
   "   arithmetic.",
   NULL,
   "credits",
   "   Dave Ashley.",
   NULL,
   "crc32",
   "   Ideas for implementation and critical subroutines from Richard A.",
   "   Ellingson.  Implemented by Dave Ashley.",
   NULL,
   "vcinfo",
   "   Dave Ashley.",
   NULL,
   "******************************************************************************",
   NULL,
   "David T. Ashley, DTASHLEY@AOL.COM, DAVEASHLEY@DAVEASHLEY.COM",
   NULL,
   "Joseph P. Devoe, JDEVOE@VISTEON.COM",
   NULL,
   "Richard A. Ellingson, RELLING@MAXINET.COM",
   NULL,
   "D. Richard Hipp, DRH@ACM.ORG",
   NULL,
   "Karl Perttunen, KPERTTUN@VISTEON.COM",
   NULL,
   "Cory Pratt, CORY_PRATT@3COM.COM",
   NULL,
   "Anatoly Zhigljavsky, ZHIGLJAVSKYAA@CARDIFF.AC.UK",
   NULL,
   "******************************************************************************",
   };


//Crude function to convert character to upper case.
static char credits_to_upper(char arg)
   {
   if ((arg >= 'a') && (arg <= 'z'))
      {
      return(arg - ('a'-'A'));
      }
   else
      {
      return(arg);
      }
   }


//Comparison function used to determine if one string exists within
//another.  The C++ library didn't have quite the function needed,
//so will write a crude and inefficient version.  Will return true
//if contained, false otherwise.
//
static int credits_string_contained(const char *container, const char *containee)
   {
   size_t   i, j, container_len, containee_len; 
   unsigned matches;

   container_len = strlen(container);
   containee_len = strlen(containee);

   for (i=0; i<container_len; i++)
      {
      if ((container_len - i) < containee_len)
         {
         return 0;
           //Not enough room to contain a match, no sense to check.
         }
      
      matches = 0;

      for (j = 0; j < containee_len; j++)
         {
         if (credits_to_upper(container[i+j]) != credits_to_upper(containee[j]))
            {
            matches = 0;
            break;
            }
         else
            {
            if (j==(containee_len - 1))
               {
               matches = 1;
               break;
               }
            }
         }

      if (matches)
         {
         return 1;
         }
      }

   return 0;
   }


//Procedure called when the "credits" command is encountered in a Tcl script.
//
int CreditsCmd(ClientData dummy, 
               Tcl_Interp *interp, 
               int objc,
               Tcl_Obj *objv[]) 
   {
 Tcl_Obj *rv;
      //Value that will be returned.
   unsigned idx, cur;
      //Iteration variable.
   unsigned something_found;
      //Set TRUE if at least one match is located so that something from the
      //credits array is displayed.
   unsigned return_string_populated;
      //TRUE if return string has something in it already.
   unsigned mark_all_true;
      //Set TRUE if should return everything.
   unsigned display_this_group;
      //Set TRUE if should display the group we are iterating through.
   char *sptr;
      //Pointer to the Tcl-build obj string representation.
      //This belongs to Tcl and may not be modified.

   /* Check to be sure if any arguments.  If more than one argument,
   ** should gen error.
   */
   if (objc > 2)
      {
      Tcl_WrongNumArgs(interp, 
                       1, 
                       objv, 
                       "?searchstring?");

      return TCL_ERROR;
      }
   else if ((objc == 1) || (objc == 2))
      {
      //If we have only one argument on the command-line, return everything,
      //otherwise search.
      mark_all_true = (objc == 1);

      //Start off having found nothing.
      something_found = 0;
      
      //Return string is not yet populated.
      return_string_populated = 0;

      //Initialize the credits to an empty string.  This will be added to.
      rv = Tcl_NewStringObj("", -1);

      //Loop through the list, either trying to match against
      //the searchstring or adding unconditionally.
      for (idx = 0; idx < (sizeof(credits_array)/sizeof(credits_array[0])); idx++)
         {
         //We just can't do a lot if we are resting on a NULL pointer.
         if (credits_array[idx])
            {
            //We are resting on a pointer which is necessarily the start
            //of an array of strings that should be displayed
            //atomically.  If we had that second argument on the
            //command line, must search the array for a match.
            if (mark_all_true)
               {
               display_this_group = 1;
               something_found = 1;
               }
            else
               {
               //We need to work a bit harder to figure out whether to display
               //this group of strings.
               //
               //Get the internal pointer.
               sptr = Tcl_GetString(objv[1]);

               //Loop through the embedded strings to see what to do.  If find a 
               //match, can break immediately.
               display_this_group = 0;
               cur = idx;
               while (credits_array[cur] && (cur < (sizeof(credits_array)/sizeof(credits_array[0]))))
                  {
                  if (credits_string_contained(credits_array[cur], sptr))
                     {
                     display_this_group = 1;
                     something_found = 1;
                     break;
                     }
                  cur++;
                  }
               }


            //We need to append a newline here if this ain't our first time
            //tacking something into the return string.
            if (display_this_group)
               {
               if (return_string_populated)
                  {
                  Tcl_AppendToObj(rv, "\n", -1);
                  }
               else
                  {
                  return_string_populated = 1;
                  }
               }


            //Stage the material of interest in the return object.  This also advances
            //the array index.
            while (credits_array[idx] && (idx < (sizeof(credits_array)/sizeof(credits_array[0]))))
               {
               if (display_this_group)
                  {
                  //Add the line of interest.
                  Tcl_AppendToObj(rv, credits_array[idx], -1);

                  //If not the very last string of the array or the last of a
                  //group, append newline.
                  if (idx != ((sizeof(credits_array)/sizeof(credits_array[0]))-1))
                     {
                     if (credits_array[idx+1])
                        {
                        Tcl_AppendToObj(rv, "\n", -1);
                        }
                     }
                  }

               idx++;
               }
            }
         }
      }
   else
      {
      //Should never get here.  If do, no harm, as will do
      //nothing and "credits" will not work--that is a bug
      //that will definitely get looked at.
      }

   //Return the right result to the caller.  If nothing was found, must say so.
   if (!something_found)
      {
      Tcl_AppendToObj(rv, "No matches.", -1);
      }
   Tcl_SetObjResult(interp, rv);
   return(TCL_OK);
   }


//Performs initial registration to the hash table.
//
void CreditsInit(Tcl_Interp *interp)
   {
   //Register a command named "credits".
   Tcl_CreateObjCommand(interp, 
                        "credits",
                        (Tcl_ObjCmdProc *)CreditsCmd,
                        NULL,
                        NULL);
   }


const char *CreditsCversion(void)
   {   
   return ("$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tclxtens_7_5/credits.c 71 2016-11-05 11:07:06Z dashley $");
   }


const char *CreditsHversion(void)
   {   
   return (CREDITS_H_VERSION);
   }

/* End of credits.c */
