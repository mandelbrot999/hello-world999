<?php
//-------------------------------------------------------------------------------------------------
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2016/20161008_web_page_thumbnail_make/pics_filenames_canonize.php 117 2017-01-01 04:06:02Z dashley $
//-------------------------------------------------------------------------------------------------
//This source code and any program in which it is compiled/used is provided under the MIT
//LICENSE (full license text below).
//-------------------------------------------------------------------------------------------------
//pics_filenames_canonize.php, Copyright (c) 2016 David T. Ashley
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
//associated documentation files (the "Software"), to deal in the Software without restriction,
//including without limitation the rights to use, copy, modify, merge, publish, distribute,
//sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all copies or
//substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
//NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
//DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//-------------------------------------------------------------------------------------------------
//This program, a PHP script, modifies all filenames in a directory to a canonical form (no
//upper-case letters or unusual characters).  This program is part of a 3-program suite designed to
//collectively create a web page directly from digital camera files (and of course the web page can
//be customized by hand-editing after it is automatically generated).
//
//The 3 programs in the 3-program suite are:
//
//   pics_filenames_canonize.php (this script):
//      Converts all names of files in a directory to lower-case, and makes substitutions for any
//      unusual characters.
//
//   pics_thumbnails_make.php:
//      Creates thumbnails from recognized image types.  The thumbnails are named relative to the
//      original image file with the suffix "_small".  To support shared hosting environments where
//      CPU utilization of a script may be capped, there is a configuration constant in the script
//      that will perform only a fixed number of conversions per invocation.  If this configuration
//      option is used, the script should be run repeatedly until it indicates that it has no more
//      thumbnails to create.
//
//      If any full-sized photos are modified, any corresponding thumbnails should be deleted and
//      pics_thumbnails_make.php and pics_indexfile_make.php should be run again.
//
//   pics_indexfile_make.php:
//      Scans a directory and makes an index file ("index2.php") displaying all the thumbnail
//      images, each of which link to the corresponding full-sized image.  The index file is
//      tailored to Dave Ashley's needs, but the created file can be edited and most of the
//      content pasted into an HTML file.  To avoid the accidental loss of information, any
//      existing "index2.php" file is renamed out of the way.
//
//This script is designed to be run manually (rather than automatically invoked as a result of a
//web page request).  It was written in PHP for convenience simply because DreamHost (the web
//hosting company Dave Ashley used at the time these scripts were written) has as part of its
//hosting environment PHP with the ImageMagick library compiled in.
//
//Usually, this script is invoked using "php <path>/pics_filenames_canonize.php", but the method of
//invocation may vary based on computing platform details.
//-------------------------------------------------------------------------------------------------
//C O N F I G U R A T I O N
//--------------------------------------------------------------------------------
//Configuration switch combinations were not tested.  E-mail me any program
//corrections (dashley@gmail.com).
define ("CFG_PROGNAME", "pics_filenames_canonize.php");
   //Number of characters per line preferred for console output.
define ("CFG_CONSOLE_STD_LINE_LEN", 78);
   //Number of characters per line preferred for console output.
define (
   "CFG_FILENAME_SUBSTITUTION_MAP", 
   ".."                                                    //Dots unchanged.
   .
   "aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz"  //LC letters unchanged.
   .
   "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz"  //UC converted to LC.
   .
   "00112233445566778899"                                  //Digits unchanged.
   .
   "-_"                                                    //Hyphens become underscores,
                                                           //and anything unmapped
                                                           //becomes an underscore.
   );
   //Pairs of characters, the first is the character to match and the second
   //is the replacement.  Any characters not found in the map will be replaced
   //by the last character of the constant.
//--------------------------------------------------------------------------------
//Repeats a character $c to the console output $n times.
function rep_char_con($c, $n)
{
   while ($n--)
      echo $c;
}
//--------------------------------------------------------------------------------
//Writes a standard thick horizontal line to the console.
function hor_line_thick()
{
   rep_char_con("=", CFG_CONSOLE_STD_LINE_LEN);
   echo "\n";
}
//--------------------------------------------------------------------------------
//Writes a standard thin horizontal line to the console.
function hor_line_thin()
{
   rep_char_con("-", CFG_CONSOLE_STD_LINE_LEN);
   echo "\n";
}
//--------------------------------------------------------------------------------
//Returns an array of all files in the working directory.
//If no files can be found, returns FALSE.
function get_file_names_in_dir()
{
   //Get directory list.
   $rv = scandir (".");

   //If the list is empty, something went wrong.  Return FALSE.
   if ($rv === FALSE)
      return FALSE;

   return $rv;
}
//--------------------------------------------------------------------------------
//Canonizes a filename by performing character substitutions.
function canonize($in_fname)
{
   //Well, the algorithm below is O(N^2) or worse ... I knew there was a reason
   //that computers get faster every year.  (Yes, that was a joke.)
   $out_fname = "";

   for ($i = 0; $i < strlen($in_fname); $i++)
   {
      $map = CFG_FILENAME_SUBSTITUTION_MAP;
      $c = substr($in_fname, $i, 1);

      $sub_made = FALSE;
      while (strlen($map) >= 2)
      {
         if (substr($map, 0, 1) == $c)
         {
            $c = substr($map, 1, 1);
            $sub_made = TRUE;
            break;
         }
         else
         {
            $map = substr($map, 2);
         }
      }

      if (! $sub_made)
      {
         $c = substr(CFG_FILENAME_SUBSTITUTION_MAP, strlen(CFG_FILENAME_SUBSTITUTION_MAP) - 1, 1);
         //echo "Default sub made: " . $c . "\n";
      }

      $out_fname = $out_fname . $c;
   }

   return $out_fname;
}
//--------------------------------------------------------------------------------
   //Write introductory message.
   hor_line_thick();
   echo CFG_PROGNAME . ", Copyright (c) 2016 David T. Ashley\n";
   echo "This program comes with ABSOLUTELY NO WARRANTY; and is licensed under the\n";
   echo "MIT License.  A copy of this license is provided in the source code\n";
   echo "of this program.\n";
   hor_line_thin();
   //-----------------------------------------------------------------------------
   //Get and emit the names of everything in the directory.
   $file_list = get_file_names_in_dir();
   if ($file_list === FALSE)
   {
      echo "List of files from PHP function scandir() is empty (rv === FALSE).\n";
      echo "Serious internal error, or nothing to do.  Script cannot continue.\n";
      hor_line_thick();
      exit(1);
   }
   else
   {
     echo "Files in working directory (unsorted, unfiltered, " 
          . 
          count($file_list)
          . 
          " files):\n";
     for ($i = 0; $i < count($file_list); $i++)
        echo "   " . sprintf("[%5d]", $i) . " " . $file_list[$i] . "\n";
   }
   hor_line_thin();
   //-----------------------------------------------------------------------------
   //Remove everything that is not a file we can rename.
   $temp_list = $file_list;
   unset($file_list);
   $n = 0;
   for ($i = 0; $i < count($temp_list); $i++)
   {
      //echo "Checking " . $temp_list[$i] . "\n";

      if (strcmp($temp_list[$i], ".") == 0)
      {
         //. entry, not a file.
      }
      else if (strcmp($temp_list[$i], "..") == 0)
      {
         //.. entry, not a file.
      }
      else if (is_file($temp_list[$i]))
      {
         //This is a regular file.
         $file_list[] = $temp_list[$i];
         $n++;
      }
   }
   
   if ($n == 0)
      $file_list = FALSE;

   unset($n);
   unset($temp_list);
   //-----------------------------------------------------------------------------
   //If there is nothing to do, end the script.
   if ($file_list === FALSE)
   {
      echo "No files to rename.\n";
      hor_line_thick();
      exit(0);
   }
   //-----------------------------------------------------------------------------
   //Sort the list.  This is a non-event.  The only rationale for sorting is that
   //it ensures that the same set of files will be processed in the same order,
   //regardless of the order provided by the underlying OS internals.
   sort($file_list);
   //-----------------------------------------------------------------------------
   //Emit the names we now have.
   echo "Files in working directory (directory entries removed, sorted, " 
        . 
        count($file_list)
        . 
        " files):\n";
   for ($i = 0; $i < count($file_list); $i++)
      echo "   " . sprintf("[%5d]", $i) . " " . $file_list[$i] . "\n";
   hor_line_thin();
   //-----------------------------------------------------------------------------
   //For each file in the directory, form a filename which would be the result
   //of applying character substitutions and any other corrections.
   for ($i = 0; $i < count($file_list); $i++)
   {
      $rename_target[$i] = canonize($file_list[$i]);

      //echo $file_list[$i] . " " . $rename_target[$i] . "\n";
   }
   //-----------------------------------------------------------------------------
   //In all those cases where the name of the file as we would like it to be is
   //different from the name of the file as it exists, rename it.  Watch for 
   //collisions, because renaming on top of a file represents the loss of
   //data.
   $n = 0;
   for ($i = 0; $i < count($file_list); $i++)
   {
      if (strcmp($file_list[$i], $rename_target[$i]) != 0)
         $n++;
   }

   if ($n == 0)
   {
      echo "No files need to be renamed.\n";
      hor_line_thin();
   }
   else
   {
      echo "Renaming " . $n . " file(s).\n";
      hor_line_thin();

      $count = 0;
      for ($i = 0; $i < count($file_list); $i++)
      {
         if (strcmp($file_list[$i], $rename_target[$i]) != 0)
         {
            $count++;
            echo "[" . sprintf("%5d/%5d", $count, $n) . "]" 
                 . 
                 " Renaming " . $file_list[$i] . " to " . $rename_target[$i] . " ... ";
            if (file_exists($rename_target[$i]))
            {
               echo "Aborted.\nRename target already exists.\n";
               echo "Choose non-colliding filenames and run this script again.\n";
               echo "Script terminating.\n";
               hor_line_thin();
               exit(1);
            }

            $result = rename($file_list[$i], $rename_target[$i]);
            if ($result)
            {
               echo "Done.\n";
               hor_line_thin();
            }
            else
            {
               echo "Failed.\nScript must terminate.\n";
               hor_line_thick();
               exit(1);
            }
         }
      }
   }
   //-----------------------------------------------------------------------------
   echo CFG_PROGNAME . " execution ends.\n";
   hor_line_thick();
//--------------------------------------------------------------------------------
//End of File
//--------------------------------------------------------------------------------
?>
