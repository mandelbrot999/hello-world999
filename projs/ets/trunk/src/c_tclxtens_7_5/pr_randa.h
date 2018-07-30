//$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tclxtens_7_5/pr_randa.h 71 2016-11-05 11:07:06Z dashley $
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
#ifndef PR_RANDA_H_INCLUDED
   #define PR_RANDA_H_INCLUDED

   #ifdef MODULE_PR_RANDA
      #define DECMOD_PR_RANDA
   #else
      #define DECMOD_PR_RANDA extern
   #endif

   DECMOD_PR_RANDA void PrRandAInit(Tcl_Interp *interp);
   DECMOD_PR_RANDA unsigned long PrRandARandSucc(unsigned long arg);
   DECMOD_PR_RANDA const char *PrRandACversion(void);
   DECMOD_PR_RANDA const char *PrRandAHversion(void);

   #define PR_RANDA_H_VERSION ("$Header: svn://localhost/dtapublic/projs/ets/trunk/src/c_tclxtens_7_5/pr_randa.h 71 2016-11-05 11:07:06Z dashley $")

#endif

/* End of pr_randa.h */
