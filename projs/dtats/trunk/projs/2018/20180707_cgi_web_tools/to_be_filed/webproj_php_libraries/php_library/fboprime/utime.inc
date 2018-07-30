<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/utime.inc 205 2018-07-15 19:00:51Z dashley $
//********************************************************************************
//Copyright (C)2006 David T. Ashley
//********************************************************************************
//This program or source file is free software; you can redistribute it and/or 
//modify it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 2 of the License, or (at your 
//option) any later version.
//
//This program or source file is distributed in the hope that it will 
//be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You may have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//********************************************************************************
//Dave Ashley, 04/06
//
//This source file contains Unix time functions.
//
require_once("strfunc.inc");           //Necessary to left-zero pad string representations of integers
require_once("timeraw.inc");           //Raw time acquisition.
//
//
//--------------------------------------------------------------------------------
//Returns the UTIME, as a properly-formatted string.  The precise
//UTIME format is documented in the manual.
//
//Dave's note 20060430:  This function has been deprecated.  In GLOBAL.INC,
//standard timestamps are gathered at the start of execution of each script.
//These standard values (global variables) should be used instead.
//
//Unit-tested 20060408.
//
function UTIME_utime()
   {
   return("UT" . UTIME_utime_raw());
   }
//
//--------------------------------------------------------------------------------
//Returns the UTIME without the "UT" prefix.
//
//Dave's note 20060430:  This function has been deprecated.  In GLOBAL.INC,
//standard timestamps are gathered at the start of execution of each script.
//These standard values (global variables) should be used instead.
//
//Unit-tested 20060408.
//
function UTIME_utime_raw()
   {
   //Get the raw time as a string and an integer.
   $raw_time = TIMERAW_time_precision_mixed_array_2();

   //Convert the integers to strings.
   $rt_whole = $raw_time[0];   
   $rt_frac  = sprintf("%d", $raw_time[1]);

   //Pad the strings with zeros out to the required lengths.
   $rt_whole = STRFUNC_pad_left_zero($rt_whole, 11);
   $rt_frac  = STRFUNC_pad_left_zero($rt_frac,   9);

   //Concatenate the strings as required by the definition of UTIME, and return
   //this value to the caller.
   return($rt_whole . $rt_frac);
   }
//
//--------------------------------------------------------------------------------
//Returns the time difference in seconds between UT time values as new - old,
//floored/ceilinged at:
//
//  -(2^28 - 1)   :  -268,435,455  :  -8.5 years.
//  2^28 - 1      :   268,435,455  :  +8.5 years.
//
//This function is "coarse" in that fractional seconds are ignored, and so the
//results may be erroneous by up to nearly a second or two.
//
//No error checking is done, and so the UTIME values must be valid or there will
//probably be a script error.
//
//The value of 2^28 was chosen because it will definitely fit within the
//integer representation of all PHP implementations.
//
//This implementation is Y2038 safe, as it relies on the BCMATH library.
//
function UTIME_time_diff_coarse_28($ut_new, $ut_old)
   {
   //Extract the new and old seconds.
   $new_secs_string = SubStr($ut_new, 2, 11);
   $old_secs_string = SubStr($ut_old, 2, 11);

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
//End of $RCSfile: utime.inc,v $.
//--------------------------------------------------------------------------------
?>
