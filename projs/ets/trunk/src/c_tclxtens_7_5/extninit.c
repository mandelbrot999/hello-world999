//$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tclxtens_7_5/extninit.c 71 2016-11-05 11:07:06Z dashley $
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
#define MODULE_EXTNINIT

#include <assert.h>
#include <string.h>

#include "tcl.h"
#include "tcldecls.h"

#include "extninit.h"

#include "msgstrs.h"

#include "arblenints.h"
#include "crchashextns.h"
#include "credits.h"
#include "pr_randa.h"
#include "vcinfo.h"


//Initializes all extensions.  Will go to tabulated mechanism and checking
//return codes as soon as prototyping complaints by compiler resolved.

void ExtninitInit(Tcl_Interp *interp)
{
   //Initialize the MSGSTRS module.  This will calculate the CRC32
   //of all version control information and include it in the 
   //embedded message strings for that module.
   MsgstrsInit();

   //Initialize the arbitrary length integer extension.
   ARBLENINTS_arbint_extn_init(interp);

   //Initialize the "crc32" extension.
   CRCHASHEXTNS_Crc32extnInit(interp);

   //Initialize the "credits" extension.
   CreditsInit(interp);

   //Initialize the random number generation functions.
   PrRandAInit(interp);

   //Initialize the version control information function
   //"vcinfo".
   VcinfoInit(interp);
}

//07/28/01:  Visually inspected.  Seems OK.  That plus using
//it should be enough.
int EXTNINIT_subextension_bsearch(
      struct EXTNINIT_subextn_bsearch_record_struct *tbl,
      int nelem,
      const char *key)
   {
   int l, u, midpoint;
   int compare_result;

   //Eyeball the input parameters.
   assert(tbl != NULL);
   assert(nelem >= 0);
   assert(key != NULL);

   //Implement the standard bsearch algorithm.  
   l = 0;
   u = nelem - 1;

   while(1)
      {
      if (l > u)
         {
         return(-1);
         }
      else
         {
         midpoint = (l + u) / 2;

         assert((midpoint >= 0) && (midpoint < nelem));

         compare_result = strcmp(key, tbl[midpoint].name);

         if (!compare_result)
            {
            return(midpoint);
            }
         else if (compare_result < 0)
            {
            u = midpoint - 1;
            }
         else
            {
            l = midpoint + 1;
            }
         }
      }
   }


const char *ExtninitCversion(void)
{   
    return ("$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tclxtens_7_5/extninit.c 71 2016-11-05 11:07:06Z dashley $");
}


const char *ExtninitHversion(void)
{   
    return (EXTNINIT_H_VERSION);
}

//End of extninit.c.
