#!/usr/bin/php -q
<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/sitehashkeygen.php 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------
//sitehashkeygen.php--Generates FboPrime Cryptographic Hash Key
//Copyright (C) 2006  David T. Ashley
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//--------------------------------------------------------------------------------
//Configuration constant--the number of characters in the key.
define("SITEHASHKEYGEN_KEYNUMCHARS", 200);
//
//Configuration constant--the number of characters presented on each
//line of the key.
define("SITEHASHKEYGEN_KEYNUMCHARSPERLINE", 50);
//
//Configuration constant--the file name in which to write the
//key.
define("SITEHASHKEYGEN_OUTPUTFILENAME", "sitehashkey.inc");
//
//--------------------------------------------------------------------------------
//Returns a version control string.  Used for randomness.
//
function vc_info()
   {
   return("\$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/sitehashkeygen.php 205 2018-07-15 19:00:51Z dashley $");
   }
//--------------------------------------------------------------------------------
function write_preamble($handle)
   {
   fwrite($handle, "<?php\n");
   fwrite($handle, "//This PHP include file contains the FboPrime site hash key.  This key is\n");
   fwrite($handle, "//normally automatically generated at the time the software is set up.\n");
   fwrite($handle, "//This key can be edited by hand safely--it is just an ordinary string of\n");
   fwrite($handle, "//arbitrary length.  However, if it is manually edited, it should be\n");
   fwrite($handle, "//edited only at the time the system is set up.  Modifying this key on a\n");
   fwrite($handle, "//working system will invalidate every user password and may have other ill\n");
   fwrite($handle, "//effects as well.\n");
   fwrite($handle, "//\n");
   fwrite($handle, "//Permissions on this file should be set so that FboPrime users cannot view\n");
   fwrite($handle, "//its contents (it should be private to the Apache server).  If FboPrime\n");
   fwrite($handle, "//users can view this key, it may enable some security attacks on the\n");
   fwrite($handle, "//FboPrime software (as users may be able to forge some data).\n");
   fwrite($handle, "//\n");
   fwrite($handle, "//Generating program:                    \$RCSfile: sitehashkeygen.php,v $\n");
   fwrite($handle, "//Generating program CVS revision:       \$Revision: 1.7 $\n");
   fwrite($handle, "//Generating program CVS revision date:  \$Date: 2006/02/05 19:13:37 $\n");
   $datestring = date("d-M-Y H:i:s (\U\T\C O)");
   fwrite($handle, "//Time of key generation:                " . $datestring . "\n");
   fwrite($handle, "//------------------------------------------------------------------------------------------\n");
   fwrite($handle, "define(\"SITEHASHKEY_SITEHASHKEY\", \"");
   }
//--------------------------------------------------------------------------------
function write_key($handle)
   {
   //It is a little tricky to get get a lot of randomness.  An MD5 is 128 bits (32 hex digits).
   //32 digits of MD5 plus 48 other random characters ought to do it.
   //
   //The set of characters allowed for the non-MD5 part of the hash key.
   //
   $allowed_chars =    "0123456789"
                     . "abcdefghijklmnopqrstuvwxyz"
                     . "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                     . "_=+-*/()[]<>;:.,?";
   $n_allowed_chars = strlen($allowed_chars);

   //-------------------------------------------------------------------------------------
   //Phase I:  Generate an MD5 based on a fair amount of randomness.  The intent is to
   //create randomness by tying the microtimes generated to the execution of this program
   //on the system, which might depend on CPU speed, system load, and a number of other
   //factors.
   //-------------------------------------------------------------------------------------
   $value = vc_info();

   for ($i=0; $i<500; $i++)
      {
      $value .= microtime() . rand();

      $r = rand(1000, 5000);

      for ($j=0; $j<$r; $j++)
	 {
	 //The goal here is to burn a variable amount of time.  In addition to depending
         //on r, this depends on the characteristics of the server and server load.
         //The variable amount of time should make the results of microtime() unpredictable.
         //
	 $trash = sqrt($j);
	 }
      }

   $key_out = md5($value);

   //-------------------------------------------------------------------------------------
   //Phase II:  Mix the previously-generated randomness with more stuff we can get from
   //the system.
   //-------------------------------------------------------------------------------------
   $value = $key_out . date("dDjlNSwzWFmmntLoYyaABgGhHiseIOTZcrU") . $key_out;
   $key_out .= md5($value);

   //-------------------------------------------------------------------------------------
   //Phase III:  Use the PHP random number generator to generate more pseudo-random stuff.
   //-------------------------------------------------------------------------------------
   while (strlen($key_out) < SITEHASHKEYGEN_KEYNUMCHARS)
      {
      $idx = rand(0, $n_allowed_chars - 1);
      $key_out .= Substr($allowed_chars, $idx, 1);
      }

   //The key is fully formed.  Now, output it.
   for ($z=0; $z<strlen($key_out); $z++)
      {
      $c = substr($key_out, $z, 1);
      fwrite($handle, $c);
      if ((($z % SITEHASHKEYGEN_KEYNUMCHARSPERLINE) == (SITEHASHKEYGEN_KEYNUMCHARSPERLINE - 1)) && ($z != (strlen($key_out) - 1)))
         {
	 fwrite($handle, "\" .\n                                  \"");
	 }
      }
   }
//--------------------------------------------------------------------------------
function write_postamble($handle)
   {
   fwrite($handle, "\" );\n");
   fwrite($handle, "?>\n");
   }
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//------  M A I N    S C R I P T  ------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//Process the input parameters.  There must be either zero or one of those
//on the command-line, otherwise there is an error.  If there is one,
//it is the path in which the site hash key file should be written.
if ($argc == 1)
   {
   //The no parameters case--we just use the working directory.
   $outputfilename = (string) SITEHASHKEYGEN_OUTPUTFILENAME;
   }
else if ($argc == 2)
   {
   //The path was passed to the script.
   $outputfilepath = (string) $argv[1];

   //If the path doesn't end with a slash, add the slash.
   if (substr($outputfilepath, strlen($outputfilepath) - 1, 1) != "/")
      $outputfilepath .= "/";

   //Add in the filename.
   $outputfilename = $outputfilepath . SITEHASHKEYGEN_OUTPUTFILENAME;
   }
else
   { 
   //Wrong number of parameters.
   echo "Wrong number of parameters to script.\n";
   exit(1);
   }


//Try to open the file for writing.
$handle = fopen($outputfilename, "w");
if ($handle===FALSE)
   {
   echo "File open failure.\n";
   exit(1);
   }
//
//Write the preamble.  This is everything up to the key itself.
write_preamble($handle);
//
//Generate and write the key.
write_key($handle);
//
//Write the postamble.  This is everything after the key.
write_postamble($handle);
//
//Close the file.
if (fclose($handle)===FALSE)
   {
   echo "File close failure.\n";
   exit(1);
   }
//
//If we're here, success.  Per the standard Unix way of thinking
//say nothing.  Silence means OK.
exit(0);
//
//--------------------------------------------------------------------------------
//$Log: sitehashkeygen.php,v $
//Revision 1.7  2006/02/05 19:13:37  dashley
//Documentation tweaks.
//
//Revision 1.6  2006/02/05 19:07:18  dashley
//Path to include file added as command-line parameter to script.  Script
//now also checks for wrong number of command-line parameters.
//
//Revision 1.5  2006/02/05 18:34:12  dashley
//Enhancements to randomness.
//
//Revision 1.4  2006/02/05 18:12:17  dashley
//Checkin to exercise keyword expansion.
//
//Revision 1.3  2006/02/05 08:50:40  dashley
//Edits.
//
//Revision 1.2  2006/02/05 08:11:24  dashley
//Edits.
//
//Revision 1.1  2006/02/05 06:52:59  dashley
//Initial checkin.
//--------------------------------------------------------------------------------
?>
