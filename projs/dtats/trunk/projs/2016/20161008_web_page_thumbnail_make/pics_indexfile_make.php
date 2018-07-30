<?php
//-------------------------------------------------------------------------------------------------
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2016/20161008_web_page_thumbnail_make/pics_indexfile_make.php 118 2017-01-01 04:06:35Z dashley $
//-------------------------------------------------------------------------------------------------
//This source code and any program in which it is compiled/used is provided under the MIT
//LICENSE (full license text below).
//-------------------------------------------------------------------------------------------------
//pics_indexfile_make.php, Copyright (c) 2016 David T. Ashley
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
//This program, a PHP script, creates an index file ("index2.php") based on the contents of the
//working directory in which it is invoked.  The index file created is tailored to Dave Ashley's
//needs, but it can easily be hand-edited or this script can be modified.  This program is part
//of a 3-program suite designed to collectively create a web page directly from digital camera
//files (and of course the web page can be customized by hand-editing after it is automatically
//generated).
//
//The 3 programs in the 3-program suite are:
//
//   pics_filenames_canonize.php:
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
//   pics_indexfile_make.php (this script):
//      Scans a directory and makes an index file ("index2.php") displaying all the thumbnail
//      images, each of which link to the corresponding full-sized image.  The index file is
//      tailored to Dave Ashley's needs, but the created file can be edited and most of the
//      content pasted into an HTML file.  To avoid the accidental loss of information, any
//      existing "index2.php" file is renamed out of the way.
//
//This script is designed to be run manually (rather than automatically invoked as a result of a
//web page request).
//--------------------------------------------------------------------------------
//C O N F I G U R A T I O N
//--------------------------------------------------------------------------------
//Configuration switch combinations were not tested.  E-mail me any program
//corrections (dashley@gmail.com).
define ("CFG_PROGNAME", "pics_indexfile_make.php");
   //Program name.
define ("CFG_CONSOLE_STD_LINE_LEN", 78);
   //Number of characters per line preferred for console output.
define ("CFG_THUMBNAIL_FILENAME_SUFFIX", "_small");
   //String added just before the filename extension to choose thumbnail names
   //based on name of full-sized image.
define ("CFG_INDEXFILE_NAME", "index2.php");
   //Name of the file containing the index.  PHP code is assumed, but the
   //file can be harvested for the HTML.
define ("CFG_INDEX_LINK_INDENT", 3);
   //The number of spaces to indent each link.
define ("CFG_INDEX_PARAGRAPH_INDENT", 3);
   //The number of spaces to indent each paragraph.
define ("CFG_INDEXFILE_PICREF_INDENT", 3);
   //The number of spaces to indent each reference to a picture.
define ("CFG_FILEEXTENSIONS_PHOTO", "jpg/jpeg/png/gif");
   //The file extensions that will be recognized as photos.
define ("CFG_FILEEXTENSIONS_LINK", "mov");
   //File extensions that will be linked to.  All others will be mentioned
   //in the generated output but not linked to.
//--------------------------------------------------------------------------------
//Repeats a character to the console output a certain number of times.
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
//Accepts a non-negative integer as an integer or a string.  Adds commas in the 
//right places to make it more human readable.
function int_nonneg_commanate($in_ui)
{
   //Ensure the integer is an integer from PHP's point of view.
   $in_ui = (int)$in_ui;

   //If a negative number was passed in, clip it.
   if ($in_ui < 0)
      $in_ui = 0;

   //Make a proper numerical string with commas out of it.
   $s_ui = number_format($in_ui);

   return $s_ui;
}
//--------------------------------------------------------------------------------
//Returns TRUE if a file name appears to be a valid full-sized image name, 
//or FALSE otherwise.
function is_full_sized_image_file_name($in_filename)
{
   //Convert the string name to all lower case.  This will do for
   //comparisons and tests.
   $in_filename = strtolower($in_filename);

   //Attempt to split the name into a base and an extension.  Any failure
   //means it is an unsuitable name.
   $extension_start = strrpos($in_filename, ".");
      //Find position of last "." in string.  This should precede the
      //file extension.

   if ($extension_start === FALSE)
   {
      //Bad name.  Unsuitable.
      return FALSE;
   } 

   //Calculate the base and extension.
   $filename_base    = substr($in_filename, 0, $extension_start);
   $filename_extension = substr($in_filename, $extension_start + 1);

   //If the extension is neither "jpg" nor "jpeg", it is unsuitable.
   if (($filename_extension != "jpg") && ($filename_extension != "jpeg"))
      return FALSE;

   //If the filename base is empty, the filename is unsuitable.
   if (strlen($filename_base) == 0)
      return FALSE;

   //If the last characters of the base are the CFG_THUMBNAIL_FILENAME_SUFFIX,
   //the name is unsuitable.
   if (strlen($filename_base) >= strlen(CFG_THUMBNAIL_FILENAME_SUFFIX))
   {
      if (substr($filename_base, strlen($filename_base) - strlen(CFG_THUMBNAIL_FILENAME_SUFFIX)) 
          == CFG_THUMBNAIL_FILENAME_SUFFIX)
         return FALSE;
   }

   //Looks good.
   return TRUE;
}
//--------------------------------------------------------------------------------
//As a function of the file name, creates the file name for the thumbnail.
function file_name_to_thumbnail_name($in_filename)
{
   $extension_start = strrpos($in_filename, ".");
      //Find position of last "." in string.  This should precede the
      //file extension.
   if ($extension_start === FALSE)
   {
      //"." not found.  Should not happen.  Filenames were checked in advance.
      echo "Fatal internal error at line " . __LINE__ . "\n";
      exit(1);
   } 

   $filename_prefix    = substr($in_filename, 0, $extension_start);
   $filename_extension = substr($in_filename, $extension_start);

   $rv = $filename_prefix . CFG_THUMBNAIL_FILENAME_SUFFIX . $filename_extension;

   return $rv;
}
//--------------------------------------------------------------------------------
//Writes the index file preamble to the index file.  This is very much
//dependent on how the thumbnails will be used.  This is currently customized
//for what Dave Ashley does.
function write_index_file_preamble($handle, $idstring)
{
   fwrite($handle, "<" . "?" . "php\n");
   fwrite($handle, "require_once(\"style/std/stdwpstyle.inc\");\n");
   fwrite($handle, "?" . ">" . "\n");
   fwrite($handle, "<" . "?" . "php\n");
   fwrite($handle, "   $" . "thispage = new StdWpStyle();\n");
   fwrite($handle, "\n");
   fwrite($handle, "   $" . "thispage->static_page_header_title_std(\"" . $idstring . "\",\n");
   fwrite($handle, "                                           \"" . $idstring . "\",\n");
   fwrite($handle, "                                           \"\");\n");
   fwrite($handle, "   $" . "thispage->static_page_photo_thumbnail_explanation(TRUE, TRUE);\n");
   fwrite($handle, "?" . ">" . "\n");
   for ($i = 0; $i < CFG_INDEX_PARAGRAPH_INDENT; $i++)
   {
      fwrite($handle, " ");
   }
   fwrite($handle, "\n<p align=\"center\">\n");
}
//--------------------------------------------------------------------------------
//Writes the index file postamble to the index file.  This is very much
//dependent on how the thumbnails will be used.  This is currently customized
//for what Dave Ashley does.
function write_index_file_postamble($handle)
{
   for ($i = 0; $i < CFG_INDEX_PARAGRAPH_INDENT; $i++)
   {
      fwrite($handle, " ");
   }
   fwrite($handle, "</p>\n\n");
   fwrite($handle, "<" . "?" . "php\n");
   fwrite($handle, "   $" . "thispage->static_page_footer_std();\n");
   fwrite($handle, "?" . ">" . "\n");
}
//--------------------------------------------------------------------------------
//Writes a line to the index file corresponding to a linked larger picture
//reprsented by a thumbnail.
function write_index_line(  $handle,
                            $filename, 
                            $thumbnailname,
                            $filename_filesize,
                            $filename_xdim,
                            $filename_ydim,
                            $thumbnailname_filesize,
                            $thumbnailname_xdim,
                            $thumbnailname_ydim)
{
   //<a href="dscn1258.jpg"><img border="0" src="dscn1258_small.jpg" alt="dscn1258.jpg (4932338 bytes)" width="125" height="93"></a>
   //Indent.
   for ($i = 0; $i < CFG_INDEX_LINK_INDENT; $i++)
   {
      fwrite($handle, " ");
   }

   fwrite($handle, "<a href=\"");
   fwrite($handle, $filename);
   fwrite($handle, "\"><img border=\"0\" src=\"");
   fwrite($handle, $thumbnailname);
   fwrite($handle, "\" alt=\"");
   fwrite($handle, $filename);
   fwrite($handle, " (");
   fwrite($handle, int_nonneg_commanate($filename_filesize));
   fwrite($handle, " bytes)\" ");
   fwrite($handle, "title=\"");
   fwrite($handle, $filename);
   fwrite($handle, " (");
   fwrite($handle, int_nonneg_commanate($filename_filesize));
   fwrite($handle, " bytes)\" width=\"");
   fwrite($handle, $thumbnailname_xdim);
   fwrite($handle, "\" height=\"");
   fwrite($handle, $thumbnailname_ydim);
   fwrite($handle, "\"></a>");
   fwrite($handle, "\n");
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
   //Get the date, time, and PID strings that will be used for the rest of the
   //script.
   $scr_datestring = date("Ymd_His");
   $scr_pid        = getmypid();
   if ($scr_pid === FALSE)
      $scr_pid = 0;
   //-----------------------------------------------------------------------------
   //If the index file exists, rename it out of the way.  This is to prevent
   //the loss of information.
   if (file_exists(CFG_INDEXFILE_NAME))
   {
      rename(CFG_INDEXFILE_NAME, $scr_datestring . "_" . $scr_pid . ".php");
   }      
   //-----------------------------------------------------------------------------
   //Open the index file and write the preamble.
   $indexfile_handle = fopen(CFG_INDEXFILE_NAME, "w");
   if ($indexfile_handle === FALSE)
   {
      echo "FATAL:  unable to open index file.\n";
      exit(1);
   }
   write_index_file_preamble($indexfile_handle, $scr_datestring . "_" . $scr_pid);
   //-----------------------------------------------------------------------------
   //Get and emit the names of everything in the directory.
   $file_list = get_file_names_in_dir();
   if ($file_list === FALSE)
   {
      echo "List of files from PHP function scandir() is empty.\n";
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
   //Remove the standard directory entries "." and ".." from the list, and 
   //remove any directories.
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
      echo "No files to process.\n";
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
   //For each file in the list, process it.  There are different processing
   //actions for each one.
   for ($i = 0; $i < count($file_list); $i++)
   {
      if (is_full_sized_image_file_name($file_list[$i]))
      {
         $thumbnail_name = file_name_to_thumbnail_name($file_list[$i]);

         $image_data = getimagesize($file_list[$i]);
         $thumbnail_data = getimagesize($thumbnail_name);

         write_index_line(  $indexfile_handle,
                            $file_list[$i], 
                            $thumbnail_name,
                            filesize($file_list[$i]),
                            $image_data[0],
                            $image_data[1],
                            filesize($thumbnail_name),
                            $thumbnail_data[0],
                            $thumbnail_data[1]);

      }
   }

   //-----------------------------------------------------------------------------
   //Complete and close up the index file.
   write_index_file_postamble($indexfile_handle);
   fclose($indexfile_handle);
//--------------------------------------------------------------------------------
   echo CFG_PROGNAME . " execution ends.\n";
   hor_line_thick();
//--------------------------------------------------------------------------------
//End of File
//--------------------------------------------------------------------------------
?>
