<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/utimex.inc 205 2018-07-15 19:00:51Z dashley $
//
//utimex.inc--UTIME-related functions that are not needed by the dayview
//            scheduler.
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
//Dave Ashley, 05/06
//
//This source file contains Unix time functions.
//
require_once("strfunc.inc");           //Necessary to left-zero pad string representations of integers
require_once("timeraw.inc");           //Raw time acquisition.
//
//--------------------------------------------------------------------------------
//Returns a UTIME corresponding to the time (in a coarse sense, meaning that
//fractional seconds are ignored) a certain integer number of seconds offset from
//The minimum and maximum values of the UTIME are used as the floor and ceiling
//limits of the result.
//
function UTIME_time_offset_coarse($ut_in, $offset_in)
   {
   //Extract the integer seconds string.
   $int_secs_string = SubStr($ut_in, 2, 11);

   //Strip off any leading zeros.
   while ((strlen($int_secs_string) > 1) && (SubStr($int_secs_string, 0, 1) == "0"))
      $int_secs_string = SubStr($int_secs_string, 1);

   //Form an integer result that is offset from this integer by the passed
   //value.
   $offset_time = bcadd($int_secs_string, (string)$offset_in);

   //Apply the floor and ceiling.
   if (bccomp($offset_time, "0") == -1)
      {
      //Result is below the Unix epoch.  Apply floor.
      //
      return("UT00000000000000000000");
      }
   else if (bccomp($offset_time, "99999999999") == 1)
      {
      //Result is above the max value that can be represented.  Apply ceiling.
      //
      return("UT99999999999000000000");
      }
   else
      {
      //Result is valid.  Format the string and return.
      $offset_time = (string)$offset_time;
      //
      $offset_time = STRFUNC_pad_left_zero($offset_time, 11);
      return("UT" . $offset_time . "000000000");
      }
   }
//
//--------------------------------------------------------------------------------
//Reformats an UTIME string to include dots at strategic places for more
//human-friendly display.
//
function UTIME_dotted_display_string_a($utime_in)
   {
   if (! is_string($utime_in))
      {
      //Don't know what this is ... it isn't an utime.  Just send it back.
      return($utime_in);
      }
   else if (strlen($utime_in) != 22)
      {
      //This doesn't seem to be the right length for an utime.  Give it back.
      return($utime_in);
      }
   else
      {
      //Seems right.
      return(
            SubStr($utime_in, 0, 2)
            .
            "."
            .
            SubStr($utime_in, 2, 11)
            .
            "."
            .
            SubStr($utime_in, 13, 9)
            );
      }
   }
//
//--------------------------------------------------------------------------------
//End of $RCSfile: utimex.inc,v $.
//--------------------------------------------------------------------------------
?>
