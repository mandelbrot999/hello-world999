//$Header: svn://localhost/dtapublic/projs/ets/trunk/src/lib_c/c_datd/fcmiof.h 71 2016-11-05 11:07:06Z dashley $
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
#ifndef FCMIOF_H_INCLUDED
   #define FCMIOF_H_INCLUDED

   #ifdef MODULE_FCMIOF
      #define DECMOD_FCMIOF
   #else
      #define DECMOD_FCMIOF extern
   #endif


   //Returns the assumed line length for formatted output.
   DECMOD_FCMIOF FCMIOF_get_line_len(void);


   /****************************************************************************/
   /* FCMIOF_repchar():                                                        */
   /*--------------------------------------------------------------------------*/ 
   /* DESCRIPTION                                                              */
   /*   Repeats a character to stdout the specified number of times.           */
   /*                                                                          */
   /* INPUTS                                                                   */
   /*   c  :  The character to repeat.                                         */
   /*                                                                          */
   /*   n  :  The number of times to repeat it.                                */
   /****************************************************************************/
   DECMOD_FCMIOF void FCMIOF_repchar(char c, unsigned n);

   //Repeats characters to a stream.
   DECMOD_FCMIOF void FCMIOF_stream_repchar(FILE *s, char c, unsigned n);

   /****************************************************************************/
   /* FCMIOF_hline():                                                          */
   /*--------------------------------------------------------------------------*/ 
   /* DESCRIPTION                                                              */
   /*   Dumps a horizontal line of the standard length to the standard output. */
   /****************************************************************************/
   DECMOD_FCMIOF void FCMIOF_hline(void);

   //Dumps horizontal line to stream.
   DECMOD_FCMIOF void FCMIOF_stream_hline(FILE *s);


   DECMOD_FCMIOF void FCMIOF_stream_bannerheading(FILE *f,
                                 char *s, 
                                 int n_extra_lines);

   /****************************************************************************/
   /* FCMIOF_bannerheading():                                                  */
   /*--------------------------------------------------------------------------*/ 
   /* DESCRIPTION                                                              */
   /*   Prints a banner heading bracketed by astreisks to the standard output. */
   /*   This function is useful for separating different sections of output.   */
   /****************************************************************************/
   DECMOD_FCMIOF void FCMIOF_bannerheading(char *s, int n_extra_lines);


   DECMOD_FCMIOF void FCMIOF_time_stream(FILE *s, time_t ltime);


   /* Two functions below return version control information for .C and
   ** .H files.
   */
   DECMOD_FCMIOF const char *FCMIOF_cvcinfo(void);
   DECMOD_FCMIOF const char *FCMIOF_hvcinfo(void);
   #define FCMIOF_H_VERSION ("$Header: svn://localhost/dtapublic/projs/ets/trunk/src/lib_c/c_datd/fcmiof.h 71 2016-11-05 11:07:06Z dashley $")

#endif

//End of fcmiof.h.
