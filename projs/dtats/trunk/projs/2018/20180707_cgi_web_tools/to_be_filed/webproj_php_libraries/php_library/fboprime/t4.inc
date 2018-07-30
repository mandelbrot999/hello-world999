<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/t4.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//t4.inc--Functions Manipulating the T4 Data Type
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
//********************************************************************************
//This contains functions that deal with the T4 format.  The T4 format is
//"HHMM", and may range from "0000" through "2359".
//--------------------------------------------------------------------------------------------------------------
require_once("config.inc");
//--------------------------------------------------------------------------------------------------------------
//
//Returns 1 if the T4 is syntactically valid, or 0 otherwise.
//
//Unit-tested on 20060414.
//
function T4_is_valid($t4)
   {
   if (!is_string($t4))                                      //Must be string.
      return(0);

   if (strlen($t4) != 4)                                     //Must be right length.
      return(0);

   if (strpos("0123456789", SubStr($t4, 3, 1)) === FALSE)    //Minutes character must be 0-9.
      return(0);
 
   if (strpos("012345",     SubStr($t4, 2, 1)) === FALSE)    //Tens of minutes character must be 0-5.
      return(0);
 
   $c0 = SubStr($t4, 0, 1);                                  //Extract tens of hours.
   $c1 = SubStr($t4, 1, 1);                                  //Extract hours.

   if (($c0 == "0") || ($c0 == "1"))
      {
      if (strpos("0123456789", $c1) === FALSE)               //If tens of hours is 0 or 1, hours must be 0-9.
         return(0);
      }
   else if ($c0 == "2")
      {
      if (strpos("0123", $c1) === FALSE)                     //If tens of hours is 2, hours must be 0-3.
         return(0);
      }
   else
      {
      return(0);  //The tens of hours digit is invalid.
      }

   //If we've made it here, it is valid.
   return(1);
   }
//
//
//--------------------------------------------------------------------------------------------------------------
//
//Returns the time captured at page load, as a T4.
//
//Unit-tested on 20060414.
//
function T4_now_pageload()
   {
   global $GLOBAL_stime_string;

   return(SubStr($GLOBAL_stime_string, 10, 4));
   }
//
//
//--------------------------------------------------------------------------------------------------------------
//
//Extract the hours and minutes from a valid T4.  The T4 must be known valid.
//
//   t4     :    The string to extract from.
//   hour   :    The hour, as an integer.
//   minute :    The minute, as an integer.
//
//Unit-tested on 20060414.
//
function T4_extract_ints($t4, &$hour, &$minute)
   {
   $c0 = SubStr($t4, 0, 1);                                  //Extract tens of hours.
   $c1 = SubStr($t4, 1, 1);                                  //Extract hours.
   $c2 = SubStr($t4, 2, 1);                                  //Extract tens of minutes.
   $c3 = SubStr($t4, 3, 1);                                  //Extract minutes.

   $val0 = strpos("012",        $c0);
   $val1 = strpos("0123456789", $c1);
   $val2 = strpos("012345",     $c2);
   $val3 = strpos("0123456789", $c3);

   $hour   = $val0 * 10 + $val1;
   $minute = $val2 * 10 + $val3;
   }
//
//
//--------------------------------------------------------------------------------------------------------------
//Maps from a T4 to the integer (0..47) corresponding to the half-hour interval that the T4 is a lower-bound
//of.  0 is returned on error.  The passed T4 must be on a half-hour for this function to operate correctly.
//
function T4_lb_int($t4_in)
   {
   $result = strpos ( "0000/0030/0100/0130/0200/0230/0300/0330/0400/0430/0500/0530/" .
                      "0600/0630/0700/0730/0800/0830/0900/0930/1000/1030/1100/1130/" .
                      "1200/1230/1300/1330/1400/1430/1500/1530/1600/1630/1700/1730/" .
                      "1800/1830/1900/1930/2000/2030/2100/2130/2200/2230/2300/2330",
                      $t4_in);

   if ($result === FALSE)
      {
      return(0);
      }
   else
      {
      return((int)($result / 5));
      }
   }
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: t4.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
