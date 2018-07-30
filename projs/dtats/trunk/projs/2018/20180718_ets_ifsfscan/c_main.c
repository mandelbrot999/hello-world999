//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180718_ets_ifsfscan/c_main.c 214 2018-07-19 02:35:29Z dashley $
//{9d0125ed-73c3-43f6-8435-8f161ab7ea6d}
//-------------------------------------------------------------------------------------------------
//Copyright (c) 2018, David T. Ashley
//
//This file is part of "ets_ifsfscan", a program for identifying gross formatting anomalies in
//source files (Windows/ASCII text files only).
//
//This source code and any program in which it is compiled/used is licensed under the MIT License,
//reproduced below.
//
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
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
//-------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <time.h>
#include <windows.h>

#define FCMIOF_HORIZONTAL_BAR_SEP_CHAR    ('-')
#define FCMIOF_LINE_LEN                   (78)

//The last column allowed for a characters below is Column 82 (or it will be
//less than aesthetic).
const char * const license_preamble[] =
{
   "ets_ifsfscan, (c) 2018 David T. Ashley (dashley@gmail.com)",
   "This program's source files, executable files, and all other related files",
   "(such as Visual Studio project files) are licensed under \"The MIT License\",",
   "reproduced below."
};

const char * const license_text[] =
{
   "Permission is hereby granted, free of charge, to any person obtaining a copy",
   "of this software and associated documentation files(the \"Software\"), to deal",
   "in the Software without restriction, including without limitation the rights",
   "to use, copy, modify, merge, publish, distribute, sublicense, and / or sell",
   "copies of the Software, and to permit persons to whom the Software is",
   "furnished to do so, subject to the following conditions:",
   "",
   "The above copyright notice and this permission notice shall be included in",
   "all copies or substantial portions of the Software.",
   "",
   "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR",
   "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,",
   "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE",
   "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER",
   "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,",
   "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE",
   "SOFTWARE."
};

const char * const prog_desc_text[] =
{
   "ets_ifsfscan (mnemonic: Ill-Formed Source File SCAN) is a program for",
   "detecting gross formatting errors in source files (Windows/ASCII text",
   "files only).  The errors detected are non-ASCII characters, tab characters,",
   "abnormal end-of-line characters, and trailing whitespace on lines."
};

const char * const prog_help_text[] =
{
   "Usage:  ets_ifsfscan [filename_or_wildcard [filename_or_wildcard [...]]]",
   "",
   "Notes:",
   "   (1) : Wildcards (\"*\", \"?\") are processed by Windows, so Windows is",
   "         the arbiter of which wildcards are accepted and how they expand.",
   "   (2) : This program never writes to a file, so it cannot destroy data",
   "         (except, possibly, by stdout output redirected to a file).",
   "   (3) : This program accepts no options (like \"-help\" or \"-verbose\").",
   "   (4) : This program accepts only Windows line endings (13-10).",
   "         This program is incompatible with *nix and *nix files.",
   "   (5) : This program accepts only the ASCII character set (it will not",
   "         process UTF-8 or any other encodings).",
};

//--------------------------------------------------------------------------------
//  T E R M I N A T I O N    F U N C T I O N S
//--------------------------------------------------------------------------------
void CCMFATAL_fatal(const char *desc, const char *file, size_t line)
{
   printf("\n");
   printf("Fatal error.  Must terminate execution.\n");
   printf("File: %s, Line: %zu.\n", file, line);
   printf("Error description: %s\n", desc);
   exit(4);  //Error code 4 for error termination.
}

//--------------------------------------------------------------------------------
//  A S S E R T I O N    F U N C T I O N S
//--------------------------------------------------------------------------------
void USERASSERT_assert(int assertion, const char *file, size_t line)
{
   if (! assertion)
   {
      printf("\n");
      printf("Assertion failed.  It is necessary to use the source code to diagnose\n");
      printf("and resolve this error.\n");
      printf("File: %s, Line: %zu.\n", file, line);
      exit(4);  //Error code 4 for error termination.
   }
}


//--------------------------------------------------------------------------------
//  S T R I N G    A N D    C H A R A C T E R    A R R A Y    F U N C T I O N S
//--------------------------------------------------------------------------------
int STRING_contains_wildcard(const char *s)
{
   if (strchr(s, '?') != NULL)
      return(1);
   else if (strchr(s, '*') != NULL)
      return(1);
   else
      return(0);
}

int STRING_is_longer_than_maxpath(const char *s)
{
   if (_MAX_PATH <= 5)
      return(1);
   else if (strlen(s) > (_MAX_PATH - 5))
      return(1);
   else
      return(0);
}

int STRING_contains_terminating_backslash(const char *s)
{
   size_t i;

   i = strlen(s);

   if (i == 0)
   {
      return(0);
   }
   else
   {
      do
      {
         i--;
         if (s[i] == '\\')
            return(1);
         else if ((s[i] != ' ') && (s[i] != '\t'))
            return(0);
      } while (i != 0);
      return(0);
   }
}

const char *STRING_vcinfo(size_t which)
{
   static const char * const vcinfo[] =
   {
      "$HeadURL: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180718_ets_ifsfscan/c_main.c $",
      "$Date: 2018-07-18 22:35:29 -0400 (Wed, 18 Jul 2018) $",
      "$Revision: 214 $",
      "$Author: dashley $",
      "Project GUID:           {beb3d945-d010-41c4-b7b5-7d4b84203408}",
      "c_main.c GUID:          {9d0125ed-73c3-43f6-8435-8f161ab7ea6d}",
      "ets_ifsfscan.cpp GUID:  {aa3777d0-4cd3-46e5-b84e-03f01957cc71}",
   };

   if (which < (sizeof(vcinfo) / sizeof(vcinfo[0])))
      return(vcinfo[which]);
   else
      return(NULL);
}

//--------------------------------------------------------------------------------
//  F O R M A T T E D    O U T P U T    F U N C T I O N S
//--------------------------------------------------------------------------------
int FCMIOF_get_line_len(void)
{
   return(FCMIOF_LINE_LEN);
}

void FCMIOF_stream_repchar(FILE *s, char c, unsigned n)
{
   USERASSERT_assert(s != NULL, __FILE__, __LINE__);

   while (n--)
      fprintf(s, "%c", c);
}

void FCMIOF_repchar(char c, unsigned n)
{
   while (n--)
      printf("%c", c);
}

void FCMIOF_hline(void)
{
   FCMIOF_repchar(FCMIOF_HORIZONTAL_BAR_SEP_CHAR, FCMIOF_LINE_LEN);
   printf("\n");
}

void FCMIOF_stream_hline(FILE *s)
{
   USERASSERT_assert(s != NULL, __FILE__, __LINE__);

   FCMIOF_stream_repchar(s, FCMIOF_HORIZONTAL_BAR_SEP_CHAR, FCMIOF_LINE_LEN);
   fprintf(s, "\n");
}

int is_legal_non_eol_character(char c)
{
   if ((c >= 32) && (c <= 126))
      return(1);
   else
      return(0);
}

int is_illegal_non_eol_character(char c)
{
   if (((c < 32) || (c > 126)) && (c != 13) && (c != 10))
      return(1);
   else
      return(0);
}

int is_tab(char c)
{
   if (c == 9)
      return(1);
   else
      return(0);
}

int is_cr(char c)
{
   if (c == 13)
      return(1);
   else
      return(0);
}

int is_lf(char c)
{
   if (c == 10)
      return(1);
   else
      return(0);
}

void emit_human_friendly_llu(unsigned long long arg)
{
   size_t i, len;
   char buffer[100];

   sprintf_s(buffer, sizeof(buffer)/sizeof(buffer[0]), "%llu", arg);
   len = strlen(buffer);

   for (i = 0; i < len; i++)
   {
      printf("%c", buffer[i]);
      if (((len-i-1) != 0) && (((len - i - 1) % 3) == 0))
         printf(",");
   }
}

void emit_file_pos_3tuple(unsigned long long line, unsigned long long col, unsigned long long offset)
{
   printf("      Line: ");
   emit_human_friendly_llu(line);
   printf(", Col: ");
   emit_human_friendly_llu(col);
   printf(", Offset: ");
   emit_human_friendly_llu(offset);
   printf("\n");
}

void process_opened_handle(FILE *f)
{
   unsigned long long char_no;
   unsigned long long line_no;
   unsigned long long col_no;
   enum {PST_LINE, PST_CR_FOUND, PST_LF_FOUND} state = PST_LINE;
   int exit_flag = 0;
   char in_c, prev_c;
   unsigned char in_uc;
   int in_i;

   in_i = fgetc(f);

   if (in_i == EOF)
   {
      //Zero-length file or error.  Because this tool isn't critical, no need to figure out which, exactly.
      printf("      Zero-length file.\n");
      return;
   }

   prev_c = ' ';
   char_no = 0;
   line_no = 1;
   col_no  = 1;
   in_c    = in_i & 0xff;
   in_uc   = in_i & 0xff;

   do
   {
      //Illegal characters always get flagged.
      if (is_illegal_non_eol_character(in_c))
      {
         emit_file_pos_3tuple(line_no, col_no, char_no);
         printf("         Illegal character: 0x%02x.\n", ((unsigned)in_uc));
      }

      //printf("Character: %02x  State: %u\n", in_c, (unsigned)state);

      //Run through the state machine, which would look for bad EOL sequences.
      switch (state)
      {
      case PST_LINE:
         //Processing non-EOL characters.
         if (is_lf(in_c))
         {
            if ((char_no != 0) && (prev_c == ' '))
            {
               emit_file_pos_3tuple(line_no, col_no, char_no);
               printf("         Line contains trailing whitespace.\n");
            }

            //Line feeds not allowed without preceding carriage return.
            emit_file_pos_3tuple(line_no, col_no, char_no);
            printf("         Out of sequence line feed character (0x0a).\n");
            line_no++;
            col_no = 1;
            state = PST_LF_FOUND;
         }
         else if (is_cr(in_c))
         {
            if ((char_no != 0) && (prev_c == ' '))
            {
               emit_file_pos_3tuple(line_no, col_no, char_no);
               printf("         Line contains trailing whitespace.\n");
            }

            //Legal
            state = PST_CR_FOUND;
         }
         else
         {
            //Ordinary character.
            col_no++;
         }
         break;
      case PST_CR_FOUND:
         if (is_lf(in_c))
         {
            //Legal
            line_no++;
            col_no = 1;
            state = PST_LF_FOUND;
         }
         else if (is_cr(in_c))
         {
            //Back-to-back carriage returns not allowed.
            emit_file_pos_3tuple(line_no, col_no, char_no);
            printf("         Out of sequence carriage return character (0x0D).\n");
            col_no++;
         }
         else
         {
            //Ordinary character.  Illegal, because LF must follow CR.
            emit_file_pos_3tuple(line_no, col_no, char_no);
            printf("         Carriage return followed by 0x%02x rather than LF.\n", (unsigned)in_uc);
            col_no++;
         }
         break;
      case PST_LF_FOUND:
         if (is_lf(in_c))
         {
            //Illegal.  Back-to-back line feeds not allowed.
            emit_file_pos_3tuple(line_no, col_no, char_no);
            printf("         Out of sequence line feed character (0x0A).\n");
            line_no++;
            col_no = 1;
         }
         else if (is_cr(in_c))
         {
            //Legal.  Blank lines are fine.
            col_no++;
            state = PST_CR_FOUND;
         }
         else
         {
            //Ordinary character.  Legal.
            col_no++;
            state = PST_LINE;
         }
         break;
      default:
         USERASSERT_assert(0, __FILE__, __LINE__);
         break;
      }

      in_i = fgetc(f);
      prev_c = in_c;
      in_c = in_i & 0xff;
      in_uc = in_i & 0xff;
      char_no++;
      if (in_i == EOF)
      {
         if (state != PST_LF_FOUND)
         {
            emit_file_pos_3tuple(line_no, col_no, char_no-1);
            printf("         Final line of file does not have CR/LF sequence.\n");
         }
         if ((state == PST_LINE) && (prev_c == ' '))
         {
            emit_file_pos_3tuple(line_no, col_no, char_no - 1);
            printf("         Final line contains trailing whitespace.\n");
         }

         exit_flag = 1;
      }
   } while (!exit_flag);
}

void process_file_by_name(const char *s)
{
   FILE *f;

   printf("   %s\n", s);

   f = fopen(s, "rb");

   if (!f)
   {
      printf("      fopen() failed.\n");
   }
   else
   {
      process_opened_handle(f);

      if (fclose(f))
      {
         printf("      fclose() failed.\n");
      }
   }
}

void process_filename_or_wildcard(const char *fname_or_wildcard)
{
   HANDLE hFind;
   WIN32_FIND_DATA FindFileData;

   //Incoming pointer is worthy of an assertion.  The OS should not every deliver
   //a NULL pointer or empty string to us.
   USERASSERT_assert(fname_or_wildcard != NULL, __FILE__, __LINE__);
   USERASSERT_assert(strlen(fname_or_wildcard) > 0, __FILE__, __LINE__);

   printf("%s\n", fname_or_wildcard);

   if (STRING_is_longer_than_maxpath(fname_or_wildcard))
   {
      printf("   Specified filename or wildcard too long--cannot process.\n");
   }
   else if (STRING_contains_terminating_backslash(fname_or_wildcard))
   {
      printf("   Specified filename or wildcard contains terminating \"\\\"--cannot process.\n");
   }
   else if (STRING_contains_wildcard(fname_or_wildcard))
   {
      hFind = FindFirstFile((TCHAR *)fname_or_wildcard, &FindFileData);

      if (hFind == INVALID_HANDLE_VALUE)
      {
         printf("   Wildcard does not match existing files or is invalid.\n");
      }
      else
      {
         char path_drive[_MAX_PATH + 5];
         char path_dir[_MAX_PATH + 5];
         char path_fname[_MAX_PATH + 5];
         char path_ext[_MAX_PATH + 5];
         char path_full[_MAX_PATH + 5];

         if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
         {
            _splitpath(fname_or_wildcard, path_drive, path_dir, path_fname, path_ext);

            strcpy(path_full, path_drive);
            strcat(path_full, path_dir);
            strcat(path_full, FindFileData.cFileName);

            process_file_by_name(path_full);
         }

         while (FindNextFile(hFind, &FindFileData) != 0)
         {
            if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
               _splitpath(fname_or_wildcard, path_drive, path_dir, path_fname, path_ext);

               strcpy(path_full, path_drive);
               strcat(path_full, path_dir);
               strcat(path_full, FindFileData.cFileName);

               process_file_by_name(path_full);
            }
         }
      }

      if (hFind != INVALID_HANDLE_VALUE)
      {
         FindClose(hFind);
      }
   }
   else
   {
      process_file_by_name(fname_or_wildcard);
   }
}

void emit_no_par_documentation(void)
{
   size_t i;

   FCMIOF_stream_hline(stdout);
   for (i = 0; i < (sizeof(prog_desc_text) / sizeof(prog_desc_text[0])); i++)
      printf("%s\n", prog_desc_text[i]);
   FCMIOF_stream_hline(stdout);
   for (i = 0; i < (sizeof(license_preamble) / sizeof(license_preamble[0])); i++)
      printf("%s\n", license_preamble[i]);
   FCMIOF_stream_hline(stdout);
   for (i = 0; i < (sizeof(license_text) / sizeof(license_text[0])); i++)
      printf("%s\n", license_text[i]);
   FCMIOF_stream_hline(stdout);
   printf("Program built on %s at %s.\n", __DATE__, __TIME__);
   i = 0;
   while (STRING_vcinfo(i))
   {
      printf("%s\n", STRING_vcinfo(i));
      i++;
   }
   FCMIOF_stream_hline(stdout);
   for (i = 0; i < (sizeof(prog_help_text) / sizeof(prog_help_text[0])); i++)
      printf("%s\n", prog_help_text[i]);
   FCMIOF_stream_hline(stdout);
}

void emit_execution_preamble(void)
{
   FCMIOF_stream_hline(stdout);
   printf("Use \"ets_ifsfscan\" with no parameters to obtain license and help information.\n");
   FCMIOF_stream_hline(stdout);
}

int c_main(int argc, char **argv)
{
   int i;

   if (argc <= 1)
   {
      //This is  most likely someone trying to figure out what the program is or does.
      //Spit everything.
      emit_no_par_documentation();
   }
   else
   {
      emit_execution_preamble();

      //Every argument beyond the program name has to be either a file name or
      //wildcard.  Just process them in order.
      for (i = 1; i < argc; i++)
         process_filename_or_wildcard(argv[i]);

      FCMIOF_stream_hline(stdout);
   }

   return 0;
}
