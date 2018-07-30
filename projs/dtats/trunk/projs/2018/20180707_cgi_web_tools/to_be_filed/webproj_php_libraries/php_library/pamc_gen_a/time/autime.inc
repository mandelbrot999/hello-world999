<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/pamc_gen_a/time/autime.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------
//autime.inc -- PAMC functions related to augmented Unix-esque time.
//Copyright (C) 2007  David T. Ashley
//--------------------------------------------------------------------------------
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
//Author contact information:
//   David T. Ashley
//   P.O. Box 918
//   Marshall, Michigan, 49068
//   dta@e3ft.com
//--------------------------------------------------------------------------------
require_once("string/strfunc_int.inc");     //Necessary to left-zero pad string 
                                            //representations of integers.
require_once("time/timeraw.inc");           //Raw time acquisition.
//--------------------------------------------------------------------------------
//Returns the AUTIME as known to the server's clock (probably synchronized
//by NNTP).  Possible ambiguity due to leap seconds is excised by the
//function called.
//
//Dave's note 20070624:  In GLOBAL.INC, standard timestamps are gathered at the 
//start of execution of each script.  These standard values (global variables) 
//should be used from a web script instead of calling this function in the
//body of the script.
//
//Unit-tested 20070624.
//
function AUTIME_autime()
   {
   //Get the raw time as a string and an integer.  Leap seconds are automatically
   //excised.
   $raw_time = TIMERAW_time_precision_mixed_array_2_noleap();

   //Convert the integers to strings.
   $rt_whole = $raw_time[0];   
   $rt_frac  = sprintf("%d", $raw_time[1]);

   //The Unix time is origined at the Unix epoch (January 1, 1970) whereas the
   //notion of augmented Unix time is origined at January 1, 1900.  The
   //difference between these two values is 2,208,988,800 seconds.
   $rt_whole = bcadd($rt_whole, "2208988800");
 
   //Pad the strings with zeros out to the required lengths.
   $rt_whole = STRFUNC_pad_left_zero($rt_whole, 10);
   $rt_frac  = STRFUNC_pad_left_zero($rt_frac,   9);

   //Concatenate the strings as required by the definition of AUTIME, and return
   //this value to the caller.
   return($rt_whole . $rt_frac);
   }
//
//--------------------------------------------------------------------------------
//Returns the time difference in seconds between AUTIME time values as new - old,
//floored/ceilinged at:
//
//  -(2^28 - 1)   :  -268,435,455  :  -8.5 years.
//  2^28 - 1      :   268,435,455  :  +8.5 years.
//
//This function is "coarse" in that fractional seconds are ignored, and so the
//results may be erroneous by up to nearly a second or two.
//
//No error checking is done, and so the AUTIME values must be valid or there will
//probably be a script error.
//
//The value of 2^28 was chosen because it will definitely fit within the
//integer representation of all PHP implementations.
//
//This implementation is Y2038 safe, as it relies on the BCMATH library.
//
//Unit-tested 20070624.
//
function AUTIME_time_diff_coarse_28($ut_new, $ut_old)
   {
   //Extract the new and old seconds.
   $new_secs_string = SubStr($ut_new, 0, 10);
   $old_secs_string = SubStr($ut_old, 0, 10);

   //Strip off any leading zeros.
   while ((strlen($new_secs_string) > 1) && (SubStr($new_secs_string, 0, 1) == "0"))
      $new_secs_string = SubStr($new_secs_string, 1);
   while ((strlen($old_secs_string) > 1) && (SubStr($old_secs_string, 0, 1) == "0"))
      $old_secs_string = SubStr($old_secs_string, 1);

   //Use the BCMATH library to get the difference.
   $diff_string = bcadd($new_secs_string, "-" . $old_secs_string);

   //Floor and ceiling the result.
   if (bccomp($diff_string, "-268535455") == -1)
      $diff_string = -268535455;
   else if (bccomp($diff_string, "268535455") == 1)
      $diff_string = 268535455;

   return((int) $diff_string);
   }
// 
//--------------------------------------------------------------------------------
//End of $RCSfile: autime.inc,v $.
//--------------------------------------------------------------------------------
?>
