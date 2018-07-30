//----------------------------------------------------------------------------------------------------
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2016/20161007_dedup/qdedup.c 89 2016-11-11 04:19:20Z dashley $
//----------------------------------------------------------------------------------------------------
//qdedup.c
//----------------------------------------------------------------------------------------------------
//Quick and dirty program to eliminate duplicates from a file tree.  A file containing the SHA512
//hashes of all the files to be considered must already exist, and must be regenerated each time the
//underlying files are deleted/added/modified, which means the file must regenerated after each run
//of qdedup.  (WARNING:  IF YOU DO NOT REGENERATE THE FILE AFTER EACH RUN OF qdedup, YOU WILL
//PROBABLY DESTROY DATA.  THE MECHANISM WOULD BE THAT THE SHA512 MANIFEST IMPLIES THAT DUPLICATES
//EXIST WHEN THEY NO LONGER DO, SO qdedup WILL ERRONEOUSLY DELETE THE LAST COPIES OF FILES.)  The
//program will eliminate duplicates within a single specified directory or outside a single specified
//directory.
//
//This program will compile and run only on *nix systems and under Cygwin on Windows systems.
//----------------------------------------------------------------------------------------------------
//Copyright David T. Ashley (dashley@gmail.com), 2016.
//----------------------------------------------------------------------------------------------------
//Provided under the MIT LICENSE, reproduced immediately below.
//----------------------------------------------------------------------------------------------------
//Permission is hereby granted, free of charge, to any person obtaining a copy of
//this software and associated documentation files (the "Software"), to deal in the
//Software without restriction, including without limitation the rights to use,
//copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
//Software, and to permit persons to whom the Software is furnished to do so,
//subject to the following conditions:
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
//----------------------------------------------------------------------------------------------------
//All paths in the SHA512 file must be absolute or must be relative to the current working directory
//at the time this program is run.
//
//The recommended method to generate the SHA512 file is using the "-exec" option of the "find"
//command, i.e.
//
//   find target_directory -type f -exec sha512sum {} \; >sha512sums.txt
//
//If any files are deleted by the program, a new SHA512 file must be generated before the program is
//run again to delete files.  The reason for this restriction is that the program will never knowingly
//delete the last copy of a file.  If the SHA512 file contains the digests of files that no longer
//exist, the program may unknowingly delete the last copies of files (because it believes based on
//the SHA512 file that other copies exist when in fact they do not).
//
//The SHA512 file does not need to be sorted (this program sorts it internally by hash before using it).
//
//This program is designed to compile and run under Cygwin or *nix only.
//
//Usage:
//   qdedup
//      Prints help information and exits.
//   qdedup ndups <sha512file>
//      Prints statistics about the number of duplicates in <sha512file>.
//   qdedup filterdups <sha512file>
//      Analyzes duplicates and prints the filenames of groups of duplicates.  The output is designed
//      for hand analysis so that insight can be gained into what duplicates exist and where they
//      are located.
//   qdedup dedup_preserve_inside <sha512file> <path>
//      For each group of duplicates that exists, preserves the duplicates that exist within path
//      and removes all others.  If no copies of the duplicate exist within path, no copies of the
//      duplicate will be removed.
//   qdedup dryrun_preserve_inside <sha512file> <path>
//      Exactly like "dedup_preserve_inside", except that no files will be deleted.  Text will be
//      output to explain what would be deleted by "dedup_preserve_inside".
//   qdedup dedup_nopath <sha512file>
//      For each group of duplicates that exists, preserves only the first (the only with lowest
//      sort-order filename).
//   qdedup dryrun_nopath <sha512file> <path>
//      Exactly like "dedup_nopath", except that no files will be deleted.  Text will be
//      output to explain what would be deleted by "dedup_nopath".
//   qdedup dedup_preserve_outside <sha512file> <path>
//      For each group of duplicates that exists, deletes duplicates only from within the specified
//      path.  If any duplicates do not have at least one copy within <path> no instances of the
//      duplicate are deleted.
//   qdedup dryrun_preserve_outside <sha512file>
//      Exactly like "dedup_preserve_outside", except that no files will be deleted.  Text will be
//      output to explain what would be deleted by "dedup_preserve_outside".
//----------------------------------------------------------------------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
//----------------------------------------------------------------------------------------------------
#define LINELEN           (78)  //Number of printable characters in a line.
#define MAXLINELEN      (2000)  //The maximum number of characters that may be in a line of the
                                //SHA512 input file.  This count includes the \0 terminator, so only
                                //this value minus 1 characters may be in a line.
#define UNLINKPAUSETIME  (0.1)  //Number of seconds to pause between file unlinks (deletions).  This
                                //is designed to give the user time to abort the program if desired
                                //before catastrophic quantities of files are deleted.
//----------------------------------------------------------------------------------------------------
//Data structure that holds the character representation of and SHA512 hash, plus the specified
//filename.
typedef struct 
{
   char hash[129];
      //512/4 = 128 characters for the hash, plus 1 character for zero terminator.
   char *fname;
      //Filename as specified in the file, allocated via malloc() family.
} tFileHashRecord;
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//-----  CHARACTER CLASSIFICATION FUNCTIONS  ---------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//TRUE if character is part of valid hash.
int is_valid_hash_char(char c)
{
   switch(c)
   {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case 'a':
      case 'b':
      case 'c':
      case 'd':
      case 'e':
      case 'f':
         return(1);
         break;
      default:
         return(0);
         break;
   }
}
//----------------------------------------------------------------------------------------------------
//TRUE if character is part of newline sequence
int is_newline_sequence_char(char c)
{
   switch(c)
   {
      case 13:
      case 10:
         return(1);
         break;
      default:
         return(0);
         break;
   }
}

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//-----  FORMATTED OUTPUT FUNCTIONS  -----------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//Repeats a character to a stream a specified number of times.
//
void stream_rep_char(FILE *s, char c, unsigned n)
{
   while(n--)
   {
      fprintf(s, "%c", c);
   }
}
//----------------------------------------------------------------------------------------------------
//Prints a horizontal line to a stream, including the newline.
//
void stream_hline(FILE *s)
{
   stream_rep_char(s, '-', LINELEN);
   fprintf(s, "\n");
}
//----------------------------------------------------------------------------------------------------
//Prints a horizontal line to a stdout, including the newline.
//
void stdout_hline(void)
{
   stream_rep_char(stdout, '-', LINELEN);
   fprintf(stdout, "\n");
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//-----  FATAL ERROR FUNCTIONS  ----------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//Errors out fatally.
//
void fatal(const char *desc, const char *file, unsigned line)
{
   stdout_hline();
   printf("Fatal error:  %s\n", desc);
   printf("Source file:  %s\n", file);
   printf("Line       :  %u\n", line);
   stdout_hline();
   exit(1);
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//-----  MEMORY ALLOCATION WRAPPERS  -----------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//malloc() wrapper.
void *w_malloc(size_t nbytes)
{
   void *rv;

   if (!nbytes)
   {
      fatal("Memory allocation request for 0 bytes.", __FILE__, __LINE__);
   }

   rv = malloc(nbytes);

   if (!rv)
   {
      fatal("Out of memory in malloc() request.", __FILE__, __LINE__);
   }

   //Zero out, just for consistency.
   memset(rv, 0, nbytes);
}
//----------------------------------------------------------------------------------------------------
//realloc() wrapper.
void *w_realloc(void *p, size_t n)
{
   void *rv;

   if (!n)
   {
      fatal("Memory reallocation request for 0 bytes.", __FILE__, __LINE__);
   }

   if (!p)
   {
      fatal("Memory reallocation request with NULL pointer.", __FILE__, __LINE__);
   }

   rv = realloc(p, n);

   if (!rv)
   {
      fatal("Out of memory in realloc() request.", __FILE__, __LINE__);
   }
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//-----  SLEEP FUNCTIONS  ----------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//Sleep for a time, in seconds.
void w_sleep(double seconds)
{
   struct timespec t;

   if (seconds < 0)
   {
      fatal("Sleep for negative time request.", __FILE__, __LINE__);
   }
   else if (seconds > 3600) 
   {
      fatal("Sleep for too long request.", __FILE__, __LINE__);
   }

   t.tv_sec  = floor(seconds);
   t.tv_nsec = (seconds - floor(seconds)) * 1E9;

   nanosleep(&t, NULL);
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//-----  SHA512 FIELD READ FUNCTIONS  ----------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//These functions read in an individual field of a standard SHA512 file generated using application
//of the standard sha512sum program.
//
//*rcode = 1, success.
//         0, legal end of file, record assigned.
void get_sha512file_line(FILE *s, int *rcode, tFileHashRecord *hash_rec)
{
   unsigned bidx;
   unsigned nchars;
   int ic;
   int exitflag;
   int eoffound;
   int eolfound;
   char c;
   char buf[MAXLINELEN];

   //Zero out the buffer.  This handles string termination automatically.
   memset(buf, 0, sizeof(buf));

   //Read characters into the buffer until either hit EOF, newline, or can't
   //fill the buffer any longer.
   eoffound  = 0;
   eolfound  = 0;
   exitflag  = 0;
   bidx      = 0;
   do
   {
      ic = fgetc(s);
      c  = ic;

      if (ic == EOF)
      {
         eoffound  = 1;
         eolfound  = 0;
         nchars    = bidx;
         exitflag  = 1;
      }
      else if (is_newline_sequence_char(c))
      {
         eoffound  = 0;
         eolfound  = 1;
         nchars    = bidx;
         exitflag  = 1;
      }
      else if (bidx >= (MAXLINELEN - 1))
      {
         fatal("SHA512 hash file line too long to parse.", __FILE__, __LINE__);
      }
      else
      {
         buf[bidx] = c;
         bidx++;
         exitflag  = 0;
      }
   } while(! exitflag);

   //If we encountered a newline, inch past it.  We may encounter an EOF.
   if (eolfound)
   {
      exitflag = 0;
      do
      {
         ic = fgetc(s);
         c  = ic;

         if (ic == EOF)
         {
            eoffound = 1;
            eolfound = 0;
            exitflag = 1;
         }
         else if (is_newline_sequence_char(c))
         {
            exitflag = 0;
         }
         else
         {
            //We hit the next line.  Put the character back.
            eoffound = 0;
            eolfound = 1;
            ungetc(ic, s);
            exitflag = 1;
         }
      } while(! exitflag);
   }

   //For better or worse, we have a \0-terminated line in the buffer.
   //
   //Zero the caller's area.  This takes care of the hash terminator as well.
   memset(hash_rec, 0, sizeof(*hash_rec));

   //Ensure that we have at least 128 characters, and they are all hex characters.
   //Otherwise, we can't proceed.
   if (nchars < 128)
   {
      fatal("SHA512 hash file line too short.", __FILE__, __LINE__);
   }
   else
   {
      for (bidx = 0; bidx < 128; bidx++)
      {
         if (! is_valid_hash_char(buf[bidx]))
         {
            fatal("Character in SHA512 hash portion of line inconsistent with hash.", __FILE__, __LINE__);
         }
      }
   }

   //The 129th and 130'th character must be present and must be a space and asterisk, respectively.
   if (nchars < 130)
   {
      fatal("SHA512 hash file line too short.", __FILE__, __LINE__);
   }
   else if (buf[128] != ' ')
   {
      fatal("129th hash line character must be \" \".", __FILE__, __LINE__);
   }
   else if (buf[129] != '*')
   {
      fatal("130th hash line character must be \"*\".", __FILE__, __LINE__);
   }   
//   else if (buf[129] != ' ')
//   {
//      //130th character is ' '.  Need to figure out why sometimes space and sometimes '*'.
//      fatal("130th hash line character must be \" \".", __FILE__, __LINE__);
//   }

   //There must be a 131'st character.  Beyond that, we can't qualify, because filenames may
   //have odd characters and may be of any length.
   if (nchars < 131)
   {
      fatal("SHA512 hash file line too short.", __FILE__, __LINE__);
   }

   //Copy the hash to the caller's area.  The terminator has already been inserted.
   memcpy(&(hash_rec->hash[0]), buf, 128);

   //Allocate space for the filename.
   hash_rec->fname = w_malloc(strlen(buf+130) + 1);

   //Make the copy.
   strcpy(hash_rec->fname, buf+130);

   if (eoffound)
      *rcode = 0;
   else
      *rcode = 1;
}
//----------------------------------------------------------------------------------------------------
void parseinputfile(tFileHashRecord **parsed_recs, unsigned *count, char *fname)
{
   FILE *s;
   int rcode;

   //Try to open the file for reading.  Inability is a failure.
   s = fopen(fname, "r");
   if (!s)
   {
       fatal("Hash file open failure.", __FILE__, __LINE__);
   }

   //Start off with a count of 0 and a NULL pointer.
   *count       = 0;
   *parsed_recs = NULL;

   do
   {
      //For the first time, allocate space for one record.  Beyond that,
      //expand it.
      if (! *parsed_recs)
      {
         *parsed_recs = w_malloc(sizeof(tFileHashRecord));
      }
      else
      {
         *parsed_recs = w_realloc(*parsed_recs, (size_t)((*count + 1)) * sizeof(tFileHashRecord));
      }

      //Parse and fill in the space.
      get_sha512file_line(s, &rcode, (*parsed_recs) + (*count));

      //We now have one more.
      (*count)++;
   } while(rcode == 1);

   //Try to close the file.  Inability is a failure.
   if (fclose(s))
   {
       fatal("Hash file close failure.", __FILE__, __LINE__);
   }
}
//----------------------------------------------------------------------------------------------------
int sortcmpascendinghash(const void *p0_in, const void *p1_in)
{
   const tFileHashRecord *p0, *p1;

   p0 = p0_in;
   p1 = p1_in;

   return(strcmp(p0->hash, p1->hash));
}

//----------------------------------------------------------------------------------------------------
void sortinternaldsbyhash(tFileHashRecord *parsed_recs, unsigned count)
{
   qsort(parsed_recs, count, sizeof(tFileHashRecord), sortcmpascendinghash);
}
//----------------------------------------------------------------------------------------------------
int sortcmpascendingfname(const void *p0_in, const void *p1_in)
{
   const tFileHashRecord *p0, *p1;

   p0 = p0_in;
   p1 = p1_in;

   return(strcmp(p0->fname, p1->fname));
}
//----------------------------------------------------------------------------------------------------
//This sort has to be run after the hash sort.  Within groups of identical hashes, it sorts by 
//ascending filename.
void sortinternalgroupfname(tFileHashRecord *parsed_recs, unsigned count)
{
    unsigned ui;
    unsigned i_group_min, i_group_max;

    if (! count)
       return;

    i_group_min = 0;
    i_group_max = 0;

    do
    {
       //Advance i_group_max to the end of the group of duplicates.
       while ((i_group_max < (count - 1)) && (! strcmp(parsed_recs[i_group_min].hash, parsed_recs[i_group_max + 1].hash)))
       {
          i_group_max++;
       }

       if (i_group_min != i_group_max)
       {
          //Sort the internal group.
          qsort(parsed_recs + i_group_min,
                i_group_max - i_group_min + 1,
                sizeof(tFileHashRecord), 
                sortcmpascendingfname);
       }

       //On to the next group.
       i_group_max++;
       i_group_min = i_group_max;

    } while (i_group_max < (count - 1));
}
//----------------------------------------------------------------------------------------------------
void printsinglerecord(tFileHashRecord *rec, unsigned elno)
{
   printf("[%9u]\n", elno);
   printf("Hash       : %s\n", rec->hash);
   printf("Filename   : %s\n", rec->fname);
   stdout_hline();
}
//----------------------------------------------------------------------------------------------------
void printinternalds(tFileHashRecord *parsed_recs, unsigned count)
{
    unsigned i;

    for (i=0; i<count; i++)
    {
       printsinglerecord(parsed_recs + i, i);
    }
}
//----------------------------------------------------------------------------------------------------
void gather_dup_stats(tFileHashRecord *parsed_recs, unsigned count, unsigned *out_num_dups, unsigned *out_cumulative_dups)
{
   unsigned i_group_min, i_group_max;

   *out_num_dups = 0;
   *out_cumulative_dups = 0;

   if (! count)
      return;

   i_group_min = 0;
   i_group_max = 0;

   do
   {
      //Advance i_group_max to the end of the group of duplicates.
      while ((i_group_max < (count - 1)) && (! strcmp(parsed_recs[i_group_min].hash, parsed_recs[i_group_max + 1].hash)))
      {
         i_group_max++;
      }

      //Log the findings.
      if (i_group_min != i_group_max)
      {
         (*out_num_dups)++;
         (*out_cumulative_dups) += (i_group_max - i_group_min + 1);
      }

      //On to the next group.
      i_group_max++;
      i_group_min = i_group_max;

   } while (i_group_max < (count - 1));
}
//----------------------------------------------------------------------------------------------------
void option_dups(char *fname)
{
   tFileHashRecord *parsed_recs;
   unsigned count, num_dups, cumulative_dups;

   parseinputfile(&parsed_recs, &count, fname);
   //printf("%u records parsed.\n", count);
   sortinternaldsbyhash(parsed_recs, count);
   sortinternalgroupfname(parsed_recs, count);
   printinternalds(parsed_recs, count);
   stdout_hline();
   gather_dup_stats(parsed_recs, count, &num_dups, &cumulative_dups);
   printf("Number of duplicated files  : %u\n", num_dups);
   if (num_dups)
   {
      printf("Average number of duplicates: %.2f\n", (double)cumulative_dups/(double)num_dups);
   }
}
//----------------------------------------------------------------------------------------------------
void option_filterdups(char *fname)
{
   tFileHashRecord *parsed_recs;
   unsigned dupgroup;
   unsigned count;
   unsigned ui;
   unsigned i_group_min, i_group_max;

   parseinputfile(&parsed_recs, &count, fname);
   //printf("%u records parsed.\n", count);
   sortinternaldsbyhash(parsed_recs, count);
   sortinternalgroupfname(parsed_recs, count);

   if (! count)
      return;

   dupgroup = 0;
   i_group_min = 0;
   i_group_max = 0;

   do
   {
      //Advance i_group_max to the end of the group of duplicates.
      while ((i_group_max < (count - 1)) && (! strcmp(parsed_recs[i_group_min].hash, parsed_recs[i_group_max + 1].hash)))
      {
         i_group_max++;
      }

      //Print the findings.
      if (i_group_min != i_group_max)
      {
          printf("Duplicate group %u:\n", dupgroup);
          for (ui = i_group_min; ui <= i_group_max; ui++)
          {
             printf("%s\n", parsed_recs[ui].fname);
          }

          dupgroup++;

          stdout_hline();
      }

      //On to the next group.
      i_group_max++;
      i_group_min = i_group_max;

   } while (i_group_max < (count - 1));
}
//----------------------------------------------------------------------------------------------------
//Returns true if the filename is within the specified path, or false otherwise.
int is_path_member(const char *fname, const char *path)
{
   if (strlen(fname) == 0)
   {
      fatal("Zero-length filename.", __FILE__, __LINE__);
   }
   else if (strlen(path) == 0)
   {
      fatal("Zero-length path.", __FILE__, __LINE__);
   }
   else if (path[strlen(path) - 1] != '/')
   {
      fatal("Paths must canonically end with forward slash character.", __FILE__, __LINE__);
   }
   else if (strlen(fname) <= strlen(path))
   {
      //Can't be in the path because filename is not longer than path name.
      return 0;
   }
   else if (memcmp(fname, path, strlen(path)) == 0)
   {
      return 1;
   }
   else
   {  
      return 0;
   }
}
//----------------------------------------------------------------------------------------------------
void option_dedup(char *fname, char *path, int may_delete, double pause_time)
{
   tFileHashRecord *parsed_recs;
   unsigned dupgroup;
   unsigned count;
   unsigned ui;
   unsigned within_path;
   unsigned i_group_min, i_group_max;

   parseinputfile(&parsed_recs, &count, fname);
   //printf("%u records parsed.\n", count);
   sortinternaldsbyhash(parsed_recs, count);
   sortinternalgroupfname(parsed_recs, count);

   if (! count)
      return;

   dupgroup = 0;
   i_group_min = 0;
   i_group_max = 0;

   do
   {
      //Advance i_group_max to the end of the group of duplicates.
      while ((i_group_max < (count - 1)) && (! strcmp(parsed_recs[i_group_min].hash, parsed_recs[i_group_max + 1].hash)))
      {
         i_group_max++;
      }

      //If this is a group of duplicates.
      if (i_group_min != i_group_max)
      {
          //Print the findings.
          printf("Duplicate group %u:\n", dupgroup);
          for (ui = i_group_min; ui <= i_group_max; ui++)
          {
             printf("%s\n", parsed_recs[ui].fname);
          }

          dupgroup++;

          stdout_hline();

          //Count how many of the group of duplicates are within the supplied path.
          within_path = 0;
          for (ui = i_group_min; ui <= i_group_max; ui++)
          {
             if (is_path_member(parsed_recs[ui].fname, path))
             {
                within_path++;
             }
          }

          //We have to take different actions based on whether we do or don't have any within path.
          //If we don't have any, we may delete nothing.
          if (! within_path)
          {
             printf("None of these duplicates in path--taking no action.\n");
             //stdout_hline();
          }
          else
          {
             for (ui = i_group_min; ui <= i_group_max; ui++)
             {
                if (is_path_member(parsed_recs[ui].fname, path))
                {
                   printf("Not deleting: %s\n", parsed_recs[ui].fname);
                }
                else
                {
                   printf("Deleting    : %s\n", parsed_recs[ui].fname);
                   if (may_delete)
                   {
                      if (! unlink(parsed_recs[ui].fname))
                      {
                          printf("   File deleted (unlinked) successfully.\n");
                      }
                      else
                      {
                          printf("   Failure attempting to delete (unlink) file.\n");
                      }
                   }
                   else
                   {
                      printf("   Dry run only.\n");
                   }
                }

                //w_sleep(pause_time);
             }
          }

         stdout_hline();
      }

      //On to the next group.
      i_group_max++;
      i_group_min = i_group_max;

   } while (i_group_max < (count - 1));
}
//----------------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   stdout_hline();
   printf("Execution begins.\n");
   stdout_hline();

   if (argc == 1)
   {
   }
   else if ((argc == 3) && (strcmp(argv[1], "ndups") == 0))
   {
      option_dups(argv[2]);
   }
   else if ((argc == 3) && (strcmp(argv[1], "filterdups") == 0))
   {
      option_filterdups(argv[2]);
   }
   else if ((argc == 3) && (strcmp(argv[1], "dedup_nopath") == 0))
   {
      //option_filterdups(argv[2]);
   }
   else if ((argc == 3) && (strcmp(argv[1], "dryrun_nopath") == 0))
   {
      //option_filterdups(argv[2]);
   }
   else if ((argc == 4) && (strcmp(argv[1], "dedup_preserve_inside") == 0))
   {
      option_dedup(argv[2], argv[3], 1, UNLINKPAUSETIME);
   }
   else if ((argc == 4) && (strcmp(argv[1], "dryrun_preserve_inside") == 0))
   {
      option_dedup(argv[2], argv[3], 0, UNLINKPAUSETIME/10.0);
   }
   else
   {
      printf("Unrecognized parameter form.  Try \"dedup\".\n");
   }

   //w_sleep(-3 /* UNLINKPAUSETIME*/ );

   //stdout_hline();
   printf("Execution ends.\n");
   stdout_hline();

   return 0;
}
//----------------------------------------------------------------------------------------------------

