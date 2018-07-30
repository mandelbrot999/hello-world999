//$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tclxtens_7_5/extninit.h 71 2016-11-05 11:07:06Z dashley $
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
#ifndef EXTNINIT_H_INCLUDED
   #define EXTNINIT_H_INCLUDED

   #ifdef MODULE_EXTNINIT
      #define DECMOD_EXTNINIT
   #else
      #define DECMOD_EXTNINIT extern
   #endif

   //This is the structure type used to hold
   //a record for a binary search operation to locate
   //Tcl sub-extensions.  Each record is the subextension
   //name, and then a pointer to the function which
   //handles that type of sub-extension.  An array of this
   //type of record is binary searched.
   struct EXTNINIT_subextn_bsearch_record_struct
      {
      char *name;
         //The name of the subextension.
      int (*fptr)(ClientData dummy, Tcl_Interp *interp, 
              int objc, Tcl_Obj *objv[]);
         //Function pointer to the subextension handler.
      };


   DECMOD_EXTNINIT void ExtninitInit(Tcl_Interp *interp);

   //Searches for the record having the name as a key.
   //Returns the index of the record or -1 if not found.
   //Used for processing Tcl subextensions.  Algorithm
   //is binary search.
   DECMOD_EXTNINIT int EXTNINIT_subextension_bsearch(
      struct EXTNINIT_subextn_bsearch_record_struct *tbl,
      int nelem,
      const char *key);

   DECMOD_EXTNINIT const char *ExtninitCversion(void);
   DECMOD_EXTNINIT const char *ExtninitHversion(void);

   #define EXTNINIT_H_VERSION ("$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tclxtens_7_5/extninit.h 71 2016-11-05 11:07:06Z dashley $")

#endif

//End of extninit.h.
