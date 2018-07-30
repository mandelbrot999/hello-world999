//$Header: svn://localhost/dtapublic/projs/ets/trunk/src/lib_c/c_cmode/ccmfatal.c 71 2016-11-05 11:07:06Z dashley $
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
#define MODULE_CCMFATAL

#include <process.h>
#include <stdio.h>

#include "ccmfatal.h"


void CCMFATAL_fatal(const char *desc,
                    const char *file,
                    int        line)
   {
   printf("Fatal error.  Must terminate execution.\n");
   printf("File: %s, Line: %d.\n", file, line);
   printf("Error description: %s\n", desc);
   exit(4);  //Error code 4 for error termination.
   }


const char *CCMFATAL_cvcinfo(void)
   {
   return("$Header: svn://localhost/dtapublic/projs/ets/trunk/src/lib_c/c_cmode/ccmfatal.c 71 2016-11-05 11:07:06Z dashley $");
   }


const char *CCMFATAL_hvcinfo(void)
   {
   return(CCMFATAL_H_VERSION);
   }

//End of ccmfatal.c.
