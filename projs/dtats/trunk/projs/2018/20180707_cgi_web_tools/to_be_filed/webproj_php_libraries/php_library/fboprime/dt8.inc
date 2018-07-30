<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/dt8.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------------------------------------
//dt8.inc--FboPrime Functions Manipulating DT8 Data Type
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
//This contains functions that deal with the DT8 data type (calenadar dates in
//the form "YYYYMMDD", for example "20060415".
//--------------------------------------------------------------------------------------------------------------
require_once("config.inc");
require_once("confighard.inc");
require_once("datefunc.inc");
//--------------------------------------------------------------------------------------------------------------
//
//Returns (1) if the DT8 is valid, or (0) otherwise.  Additionally, if valid, the components
//are returned as integers, otherwise the page load date is returned.  Here, "valid" is defined as:
//  a)Right type.
//  b)Syntactically valid.
//  c)Date is within minimums and maximums of calendaring logic.
//  d)Date is consistent with number of months in year and number of days in affected month.
//
//Parameters:
//   dt8                        :   Value to examine.
//   valid                      :   (Output) 1 if valid, 0 otherwise.
//   components                 :   (Output) Defined only if valid,
//                                  [0] Year, integer.
//                                  [1] Month
//                                  [2] Day
//
function DT8_extract_components($dt8, &$valid, &$components)
   {
   global $GLOBAL_stime_year;
   global $GLOBAL_stime_month;
   global $GLOBAL_stime_day;

   //Define the output array to be today's date, just in case the parse fails.
   $components = array ($GLOBAL_stime_year, $GLOBAL_stime_month, $GLOBAL_stime_day);

   //Similarly, define $valid to be 0 so that a return creates an invalid flag.
   $valid = 0;

   if (!is_string($dt8))                     //Must be right type.
      return;

   if (strlen($dt8) != 8)                    //Must be right length.
      return;

   //Extract characters.
   $c0 = SubStr($dt8, 0, 1);
   $c1 = SubStr($dt8, 1, 1);
   $c2 = SubStr($dt8, 2, 1);
   $c3 = SubStr($dt8, 3, 1);
   $c4 = SubStr($dt8, 4, 1);
   $c5 = SubStr($dt8, 5, 1);
   $c6 = SubStr($dt8, 6, 1);
   $c7 = SubStr($dt8, 7, 1);

   //Check the character sets.  Conditions below are necessary but not sufficient.
   //
   if (strpos("2"             , $c0) === FALSE)   //Thousands of  year must be 2.
      return;
   if (strpos("0"             , $c1) === FALSE)   //Hundreds of year must be 0.
      return;
   if (strpos("0123456789"    , $c2) === FALSE)   //Tens of year may be any digit.
      return;
   if (strpos("0123456789"    , $c3) === FALSE)   //Ones of year may be any digit.
      return;
   if (strpos("01"            , $c4) === FALSE)   //Tens of month must be 0 or 1.
      return;
   if (strpos("0123456789"    , $c5) === FALSE)   //Ones of month may be any digit.
      return;
   if (strpos("0123"          , $c6) === FALSE)   //Tens of day must be 0-3.
      return;
   if (strpos("0123456789"    , $c7) === FALSE)   //Ones of day may be any digit.
      return;

   //Grab the values.
   $val0 = strpos("0123456789", $c0);
   $val1 = strpos("0123456789", $c1);
   $val2 = strpos("0123456789", $c2);
   $val3 = strpos("0123456789", $c3);
   $val4 = strpos("0123456789", $c4);
   $val5 = strpos("0123456789", $c5);
   $val6 = strpos("0123456789", $c6);
   $val7 = strpos("0123456789", $c7);

   //Calculate the integers representing year, month, and day.
   $year_int  = $val0 * 1000 + $val1 * 100 + $val2 * 10 + $val3;
   $month_int =                              $val4 * 10 + $val5;
   $day_int   =                              $val6 * 10 + $val7;

   //Confine year.
   if (($year_int < CONFIGHARD_DATEFUNC_MINYEAR) || ($year_int >= CONFIGHARD_DATEFUNC_MAXYEAR))
     return;

   //Confine month.
   if (($month_int < 1) || ($month_int > 12))
      return;

   //Figure out how many days are supposed to be in that month, anyway.
   $ndays = DATEFUNC_year_month_days($year_int, $month_int);

   //Confine days.
   if (($day_int < 1) || ($day_int > $ndays))
      return;

   //We have a confirmed good date.  Return the info.
   $valid         = 1;
   $components[0] = $year_int;
   $components[1] = $month_int;
   $components[2] = $day_int;
   }
//
//--------------------------------------------------------------------------------------------------------------
//
//Makes a DT8 from components of integer year, integer month, and integer day.
//
function DT8_make_from_ints($year, $month, $day)
   {
   return(sprintf("%04d", $year) . sprintf("%02d", $month) . sprintf("%02d", $day));
   }
//
//--------------------------------------------------------------------------------------------------------------
//End of $RCSfile: dt8.inc,v $.
//--------------------------------------------------------------------------------------------------------------
?>
