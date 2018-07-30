<?php
//-------------------------------------------------------------------------------------------------
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2016/20161008_web_page_thumbnail_make/pics_thumbnails_make.php 117 2017-01-01 04:06:02Z dashley $
//-------------------------------------------------------------------------------------------------
//This source code and any program in which it is compiled/used is provided under the MIT
//LICENSE (full license text below).
//-------------------------------------------------------------------------------------------------
//pics_thumbnails_make.php, Copyright (c) 2016 David T. Ashley
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
//This program, a PHP script, creates thumbnails from recognized image types.  This program is part
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
//   pics_thumbnails_make.php (this script):
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
//Usually, this script is invoked using "php <path>/pics_thumbnails_make.php", but the method of
//invocation may vary based on computing platform details.
//
//Using Fedora Linux, I had trouble getting PHP to use ImageMagick (the error was something like
//"Class Imagick not found").  Finally, I figured out that the missing package was
//php-pecl-imagemagick and "dnf install php-pecl-imagick" too care of it.
//
//After all conversions are complete, this script terminates with a segmentation fault under
//Linux.  The segmentation fault is definitely tied to ImageMagick.  The reason is not known, but
//the problem appears here and there on the Internet.  All of the photo conversions occur
//correctly, and the problem seems to occur during the termination phase of the PHP script.
//-------------------------------------------------------------------------------------------------
//C O N F I G U R A T I O N
//-------------------------------------------------------------------------------------------------
//Configuration switch combinations were not tested.  E-mail me any program
//corrections (dashley@gmail.com).
define ("CFG_PROGNAME", "pics_thumbnails_make.php");
   //Program name.
define ("CFG_CONSOLE_STD_LINE_LEN", 78);
   //Number of characters per line preferred for console output.
define ("CFG_THUMBNAIL_DIMENSION_MAX", 125);
   //The maximum dimension of the created thumbnails.  Thumbnails are sized so
   //that the longest dimension is this many pixels.
define ("CFG_THUMBNAIL_BEVELED_BORDER_WIDTH", 4);
   //The number of pixels that the thumbnail beveled borders should be.
define ("CFG_THUMBNAIL_FILENAME_SUFFIX", "_small");
   //String added just before the filename extension to choose thumbnail names
   //based on name of full-sized image.
define ("CFG_LANCZOS_FILTER_APPLY", FALSE);
   //TRUE if should apply the Lanczos filter when making the thumbnail, FALSE
   //otherwise.  I have no idea if using a Lanczos filter improves the quality
   //of the thumbnails, but the filter was applied in the PHP example I found
   //online.  Applying the Lanczos filter typically adds a few seconds to the
   //time required to create each thumbnail.
define ("CFG_MAX_THUMBNAILS_PER_INVOCATION", 0);
   //The maximum number of thumbnails that should be created per invocation.
   //This is to prevent the program from being involuntarily terminated
   //for consuming too much CPU time (mostly for use in shared hosting
   //environments that cap CPU usage).  Setting this to 0 means no limit is
   //applied (unlimited number of photos processed per invocation).
//--------------------------------------------------------------------------------
//Calculates important integer indices related to creating a thumbnail, in order
//to minimize distortion in the thumbnail.
//
//When creating a thumbnail, the longer side may be relatively short (perhaps
//100 pixels), and the shorter side may be even shorter (perhaps even as short
//as 10 pixels).  If the dimensions of the original image were not changed,
//converting the image to a thumbnail may result in distortion of up to about
//one percent.  As an example, suppose that a 1600 x 900 image is converted to a
//thumbnail with the longer side of 125 pixels.  The ideal dimension for the
//shorter side would be (900/1600) * 125 = 70.3125 pixels.  The aspect ratio of
//the thumbnail can't be made to match the aspect ratio of the original image.
//
//To avoid any aspect ratio distortion that might be noticeable, this program
//chooses the shorter dimension for the thumbnail that is the ceiling of the actual
//quotient, then crops the longer dimension of the original image before the
//conversion to try and match the aspect ratios as closely as possible.
//
//In the example a paragraph or two above, the shorter side of the thumbnail
//would be chosen to be 71 pixels.
//
//Once this choice is made, we want to trim the original image before conversion
//so that n/900 is as close as possible to 125/71.  n = (900 * 125) / 71 = 
//1584.5070 pixels, so we choose 1585.  This keeps the aspect ratio of the 
//original image and the thumbnail as close as possible.
//
//Although the longer side of the original image may be reduced prior to the
//conversion to a thumbnail, this information is not written to disk, and
//the original image is not modified.  The adjustment of the longer side is
//just a conversion trick to hopefully get better thumbnails. 
function calc_thumbnail_conversion_pars
         (
           $in_orig_longer,
              //Longer dimension of original image.
           $in_orig_shorter,
              //Shorter dimension of original image.
           $in_thumbnail_longer,
              //Longer dimension of desired thumbnail.
         & $out_thumbnail_longer,
              //Longer dimension of thumbnail that should be created.
         & $out_thumbnail_shorter,
              //Shorter dimension of thumbnail that should be created.
         & $out_orig_crop_dim_longer,
              //The size to crop to on the longer axis of the original.
         & $out_orig_crop_dim_shorter,
              //The size to crop to on the shorter axis of the original.
         & $out_orig_crop_start_longer,
              //For use with the Imagick:cropImage() method, the start
              //position of the crop on the longer axis.
         & $out_orig_crop_start_shorter
              //For use with the Imagick:cropImage() method, the start
              //position of the crop on the shorter axis.
         )
{
   //Set the thumbnail shorter dimension to the floor.  This means would need to trim
   //longest dimension of original to match aspect ratio as closely as possible.
   $out_thumbnail_longer        = $in_thumbnail_longer;
   $out_thumbnail_shorter       = ceil(((float)$in_thumbnail_longer * 
                                  (float)$in_orig_shorter) / (float)$in_orig_longer);
   settype($out_thumbnail_shorter, "integer");

   //The aspect ratio of the thumbnail is now set.  Try to match the aspect ratio of the larger
   //image as closely as possible by selecting a smaller number for the long axis of the
   //original image.
   $out_orig_crop_dim_longer = round(((float)$in_thumbnail_longer * 
                               (float)$in_orig_shorter) / (float)$out_thumbnail_shorter);
   settype($out_orig_crop_dim_longer, "integer");

   //The original keeps its shorter dimension unchanged.
   $out_orig_crop_dim_shorter   = $in_orig_shorter;

   //Set the cropping of the longer side of the original to cover half the necessary
   //reduction.
   $out_orig_crop_start_longer  = round(((float)$in_orig_longer - 
                                  (float)$out_orig_crop_dim_longer) / 2.0);
   settype($out_orig_crop_start_longer, "integer");

   //No cropping of original shorter side.
   $out_orig_crop_start_shorter = 0;
}
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

   //If the extension is not "jpg", "jpeg", "gif", or "png"; it isn't anything we recognize.
   if (
         ($filename_extension != "jpg")
 	 &&
	 ($filename_extension != "jpeg")
 	 &&
	 ($filename_extension != "gif")
 	 &&
	 ($filename_extension != "png")
      )
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
//Actually creates the thumbnail, and returns some information about what was
//done.
//
//The calls to the ImagMagick library take on the order of 5s per image if there
//is filtering.
function create_thumbnail(  $in_filename, 
                            $in_thumbnailname,
                          & $out_filename_filesize,
                          & $out_filename_xdim,
                          & $out_filename_ydim,
                          & $out_thumbnailname_filesize,
                          & $out_thumbnailname_xdim,
                          & $out_thumbnailname_ydim)
{
   //Assign output parameters just in case something doesn't get assigned.
   $out_filename_filesize      = 0;
   $out_filename_xdim          = 0;
   $out_filename_ydim          = 0;
   $out_thumbnailname_filesize = 0;
   $out_thumbnailname_xdim     = 0;
   $out_thumbnailname_ydim     = 0;

   //Establish target dimensions.  Two cases, depending on which is the longer
   //side.

   //Construct.
   $imagick = new Imagick();

   //Load image.
   $imagick->readImage($in_filename);

   //Get the dimensions of the image we just loaded.
   $geo               = $imagick->getImageGeometry(); 
   $out_filename_xdim = $geo['width']; 
   $out_filename_ydim = $geo['height']; 

   //Calculate target sizes.  We rearrange parameters based on which is our
   //longest side.
   if ($out_filename_xdim >= $out_filename_ydim)
   {
      //Longer width (x-dimension), or square.
      calc_thumbnail_conversion_pars
         (
         $out_filename_xdim,
         $out_filename_ydim,
         CFG_THUMBNAIL_DIMENSION_MAX,
         $out_thumbnailname_xdim,
         $out_thumbnailname_ydim,
         $orig_crop_dim_x,
         $orig_crop_dim_y,
         $orig_crop_start_x,
         $orig_crop_start_y
         );
   }
   else
   {
      //Longer height (y-dimension).
      calc_thumbnail_conversion_pars
         (
         $out_filename_ydim,
         $out_filename_xdim,
         CFG_THUMBNAIL_DIMENSION_MAX,
         $out_thumbnailname_ydim,
         $out_thumbnailname_xdim,
         $orig_crop_dim_y,
         $orig_crop_dim_x,
         $orig_crop_start_y,
         $orig_crop_start_x
         );
   }

   //For debugging only, might want to know intermediate calculation results.
   //echo "xcropdim, ycropdim, xcropstart, ycropstart: "
   //     .
   //     $orig_crop_dim_x
   //     .
   //     " "
   //     . 
   //     $orig_crop_dim_y
   //     .
   //     " "
   //     . 
   //     $orig_crop_start_x
   //     .
   //     " "
   //     . 
   //     $orig_crop_start_y
   //     .
   //     "\n";
           
   //Crop the original to try to preserve the aspect ratio of the thumbnail
   //as precisely as possible.
   $imagick->cropImage( 
                      $orig_crop_dim_x, 
                      $orig_crop_dim_y,
                      $orig_crop_start_x,
                      $orig_crop_start_y
                      );

   //For debugging only, might want to get a look at the cropped image, to
   //be sure nothing unexpected happens on the canvas.
   //$imagick->writeImage($in_filename . ".cropped.jpg");

   //Resize to thumbnail size.
   if (CFG_LANCZOS_FILTER_APPLY)
   {
      $imagick->resizeImage($out_thumbnailname_xdim, 
                            $out_thumbnailname_ydim, 
                            Imagick::FILTER_LANCZOS, 
                            1);
   }
   else
   {
      $imagick->resizeImage($out_thumbnailname_xdim, 
                            $out_thumbnailname_ydim, 
                            0, 
                            1);
   }

   //Create the border.
   $imagick->raiseImage(CFG_THUMBNAIL_BEVELED_BORDER_WIDTH, 
                        CFG_THUMBNAIL_BEVELED_BORDER_WIDTH, 
                        0, 
                        0, 
                        1);

   //Set compression to get a smaller thumbnail written, and strip
   //header information.  stripImage() seems to have the largest effect
   //on thumbnail file size, so leaving the thumbnail quality near 100%
   //is feasible.  The jump in file size between 90% and 95% seemed to be
   //fairly large (40% to 50%), so I left it at 90%.  My rationale is
   //that with the proliferation of mobile devices and cellular data,
   //getting the thumbnail as small as possible is more important than
   //the thumbnail looking perfect.  If the viewer wants a perfect image,
   //they can view the full-sized image.
   $imagick->setImageCompression(Imagick::COMPRESSION_JPEG); 
   $imagick->setImageCompressionQuality(90);
   $imagick->stripImage(); 

   //Write the thumbnail.
   $imagick->writeImage($in_thumbnailname);

   //Destroy to prevent possible memory leak.
   $imagick->destroy();

   //All of the writing is done.  Try to obtain the file sizes.
   $fsize = filesize($in_filename);
   if ($fsize !== FALSE)
      $out_filename_filesize = $fsize;
   $fsize = filesize($in_thumbnailname);
   if ($fsize !== FALSE)
      $out_thumbnailname_filesize = $fsize;
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
   //For each file that is appropriate and where the thumbnail does not already
   //exist, up to the maximum we may do in one invocation, create the thumbnail.
   $i         = 0;
   $completed = 0;
   while (
            (
	       (CFG_MAX_THUMBNAILS_PER_INVOCATION == 0)
	       ||
	       ($completed < CFG_MAX_THUMBNAILS_PER_INVOCATION)
	    )
	    &&
	    ($i < count($file_list))
	 )
   {
      if (is_full_sized_image_file_name($file_list[$i]))
      {
         $thumbnail_name = file_name_to_thumbnail_name($file_list[$i]);

         if (file_exists($thumbnail_name))
         {
            echo "   " . sprintf("[%5d]", $i) . " " . $file_list[$i] . " : skipping because corresponding thumbnail exists.\n";
            hor_line_thin();
         }
         else
         {
            echo "   " . sprintf("[%5d]", $i) . " " . $file_list[$i] . " : creating thumbnail.\n";

            echo "Creating thumbnail \"" .
                 $thumbnail_name .
                 "\" from image \"" .
                 $file_list[$i] .
                 "\".\n";

            create_thumbnail($file_list[$i], 
                             $thumbnail_name,
                             $filename_filesize,
                             $filename_xdim,
                             $filename_ydim,
                             $thumbnail_filesize,
                             $thumbnail_xdim,
                             $thumbnail_ydim);

            echo "Conversion complete.\n";
            echo "   Full-sized image file size/xdim/ydim = " .
                 $filename_filesize . "/" . $filename_xdim . "/" . $filename_ydim .
                 ",\n";
            echo "   Thumbnail image  filesize/xdim/ydim = " .
                 $thumbnail_filesize . "/" . $thumbnail_xdim . "/" . $thumbnail_ydim .
                 ",\n";

            hor_line_thin();
            $completed++;
         }
      }
      else
      {
         //Unsuitable base name.  Can't use it.
         echo "   " . sprintf("[%5d]", $i) . " " . $file_list[$i] . " : skipping due to unsuitable name.\n";
         hor_line_thin();
      }

      $i++;
   }

   //Emit a message about whether the program should be run again.  I am aware of
   //the uncovered case--where the last thumbnail was made on the last iteration
   //of this invocation--but I will leave it uncovered for now.  All that happens
   //is the user runs the program unnecessarily one more time.
   if ($completed == 0)
   {
      echo "No thumbnails were created--this program is done creating thumbnails.\n";
      echo "It is not necessary to run this program again.\n";
      hor_line_thin();
   }
   else
   {
      echo $completed . " thumbnail(s) were created.  Please run this program repeatedly again\n";
      echo "until no more thumbnails are created.\n";
      hor_line_thin();
   }

   echo CFG_PROGNAME . " execution ends.\n";
   hor_line_thick();
//--------------------------------------------------------------------------------
//End of File
//--------------------------------------------------------------------------------
?>
