//$Header: svn://localhost/dtapublic/projs/ets/trunk/src/lib_c/c_datd/fcmiof.c 71 2016-11-05 11:07:06Z dashley $
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
#define MODULE_FCMIOF

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "fcmiof.h"


#define FCMIOF_HORIZONTAL_BAR_SEP_CHAR    ('-')
#define FCMIOF_LINE_LEN                   (78)


//08/16/01:  Visual inspection OK.
int FCMIOF_get_line_len(void)
   {
   return(FCMIOF_LINE_LEN);
   }


//08/16/01:  Visual inspection OK.
void FCMIOF_stream_repchar(FILE *s, char c, unsigned n)
   {
   assert(s != NULL);

   while(n--)
	   fprintf(s, "%c", c);
   }


//08/16/01:  Visual inspection OK.
void FCMIOF_repchar(char c, unsigned n)
   {
   while(n--)
	   printf("%c", c);
   }


//08/16/01:  Visual inspection OK.
void FCMIOF_hline(void)
   {
   FCMIOF_repchar(FCMIOF_HORIZONTAL_BAR_SEP_CHAR, FCMIOF_LINE_LEN);
   printf("\n");
   }


//08/16/01:  Visual inspection OK.
void FCMIOF_stream_hline(FILE *s)
   {
   assert(s != NULL);

   FCMIOF_stream_repchar(s, FCMIOF_HORIZONTAL_BAR_SEP_CHAR, FCMIOF_LINE_LEN);
   fprintf(s, "\n");
   }


//08/16/01:  Visual inspection OK.
void FCMIOF_stream_bannerheading(FILE *f,
                                 char *s, 
                                 int n_extra_lines)
   {
   const int lr_padding = 3;
      /* The number of spaces on each side of what is printed.
      */
   int i;
      /* General iteration variable.
      */

   int n_asterisks;
   int input_arg_len;
   int n_left_spaces;
   int n_right_spaces;

   /* Check the file pointer, string pointer, and other par.
   */
   assert(f != NULL);
   assert(s != NULL);
   assert(n_extra_lines >= 0);

   /* Print the right number of solid lines of asterisks to the
   ** standard output.
   */
   for (i=0; i<n_extra_lines; i++)
      {
      FCMIOF_stream_repchar(f, '*', FCMIOF_LINE_LEN);
      fprintf(f, "\n");
      }

   /* Figure out how many asterisks to print on each side of the
   ** argument, and how many spaces.  We also need to figure out
   ** how many characters of the input argument to print--if there
   ** are too many characters, we need to truncate.
   */
   input_arg_len = strlen(s);
   if(input_arg_len > (FCMIOF_LINE_LEN - 2 * lr_padding - 2))
      input_arg_len = FCMIOF_LINE_LEN - 2 * lr_padding - 2;

   n_asterisks = (FCMIOF_LINE_LEN - 2*lr_padding - input_arg_len)/2;

   n_left_spaces = lr_padding;

   if ((FCMIOF_LINE_LEN - 2*lr_padding - input_arg_len) % 2)
      {
      /* Odd, need to pad the right by one. */
      n_right_spaces = lr_padding+1;
      }
   else
      {
      n_right_spaces = lr_padding;
      }

   /* Print the text. */
   FCMIOF_stream_repchar(f, '*', n_asterisks);
   FCMIOF_stream_repchar(f, ' ', n_left_spaces);
   for (i=0; i<input_arg_len; i++)
      fprintf(f, "%c", s[i]);
   FCMIOF_stream_repchar(f, ' ', n_right_spaces);
   FCMIOF_stream_repchar(f, '*', n_asterisks);
   fprintf(f, "\n");

   /* Print the right number of solid lines of asterisks to the
   ** standard output.
   */
   for (i=0; i<n_extra_lines; i++)
      {
      FCMIOF_stream_repchar(f, '*', FCMIOF_LINE_LEN);
      fprintf(f, "\n");
      }
   }


//08/16/01:  Visual inspection OK.
void FCMIOF_bannerheading(char *s, int n_extra_lines)
   {
   assert(s != NULL);
   assert(n_extra_lines >= 0);

   FCMIOF_stream_bannerheading(stdout, s, n_extra_lines);
   }


void FCMIOF_time_stream(FILE *s, time_t ltime)
   {
   char *p;

   assert(s != NULL);

   time(&ltime);

   p = ctime(&ltime);

   if (p)
      {
      int i;

      for (i=11; i<19; i++)
         fprintf(s, "%c", p[i]);
      fprintf(s, " ");
      for (i=0; i<10; i++)
         fprintf(s, "%c", p[i]);
      fprintf(s, " ");
      for (i=20; i<24; i++)
         fprintf(s, "%c", p[i]);
      }
   else
      {
      fprintf(s, "??? ??? ?? ??:??:?? ????");
      }
   }



//08/16/01:  Visual inspection OK.
const char *FCMIOF_cvcinfo(void)
   {
   return("$Header: svn://localhost/dtapublic/projs/ets/trunk/src/lib_c/c_datd/fcmiof.c 71 2016-11-05 11:07:06Z dashley $");
   }


//08/16/01:  Visual inspection OK.
const char *FCMIOF_hvcinfo(void)
   {
   return(FCMIOF_H_VERSION);
   }

//End of fcmiof.c.
