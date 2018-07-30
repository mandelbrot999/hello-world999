<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/stimex.inc 205 2018-07-15 19:00:51Z dashley $
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
//Dave Ashley, 08/06
//
//This source file contains functions that operate on STIME, but are not needed
//by the day view scheduler.
//
require_once("datefunc.inc");
require_once("stime.inc");
//
//--------------------------------------------------------------------------------
//Calculates the difference between two STIMEs, and returns a string representing
//that difference.  The string returned will be either of the form (by example):
//   a)34m
//   b)4h 34m
//   c)1d 9h
//   d)44d
//
//The string returned is absolute value.
//
function STIME_diff_string_a($st0_in, $st1_in)
   {
   //We require st1 to be no sooner than st0.  Reorder if necessary.
   if (strcmp($st0_in, $st1_in) > 0)
      {
      $temp   = $st0_in;
      $st0_in = $st1_in;
      $st1_in = $temp;
      }
   //
   //Extract components.
   //
   sscanf(SubStr($st0_in, 2), "%04d%02d%02d%02d%02d", $year0, $month0, $day0, $hour0, $minute0);
   sscanf(SubStr($st1_in, 2), "%04d%02d%02d%02d%02d", $year1, $month1, $day1, $hour1, $minute1);
   //
   //Calculate relative offset of dates in minutes.
   //
   $dayoffset0 = 24 * 60 * (DATEFUNC_year_predecessor_sum($year0) + DATEFUNC_year_julian_offset($year0, $month0, $day0));
   $dayoffset1 = 24 * 60 * (DATEFUNC_year_predecessor_sum($year1) + DATEFUNC_year_julian_offset($year1, $month1, $day1));
   //
   //Calculate relative offset of times in minutes.
   $minuteoffset0 = $hour0 * 60 + $minute0;
   $minuteoffset1 = $hour1 * 60 + $minute1;

   $diffminutes = ($dayoffset1 + $minuteoffset1) - ($dayoffset0 + $minuteoffset0);

   //Figure out which display format to use.
   if ($diffminutes < 60)
      {
      //a
      $rv = sprintf("%dm", $diffminutes);
      }
   else if ($diffminutes < 2880)
      {
      //b
      $inthours = (int)($diffminutes/60);
      $leftoverminutes = $diffminutes - ($inthours * 60);
      $rv = sprintf("%dh %dm", $inthours, $leftoverminutes);
      }
   else if ($diffminutes < 7200)
      {
      //c
      $intdays = (int)($diffminutes/1440);
      $leftoverminutes = $diffminutes - ($intdays * 1440);
      $inthours = (int)($leftoverminutes / 60);

      $rv = sprintf("%dd %dh", $intdays, $inthours);
      }
   else
      {
      //d
      $rv = sprintf("%dd", (int)($diffminutes/1440));
      }

   return($rv);
   }
//
//--------------------------------------------------------------------------------
//Returns a 2-character day-of-week representation of the date of an STIME.
//Values are Su, Mo, Tu, We, Th, Fr, Sa.
//
function STIME_dow_string_a($st_in)
   {
   //Extract components.
   //
   sscanf(SubStr($st_in, 2), "%04d%02d%02d", $year, $month, $day);
   //
   //Calculate day of week.
   $dow = DATEFUNC_intdayofweek_intdate($year, $month, $day);
   //
   //Calc the string, return to caller.
   return(SubStr("SuMoTuWeThFrSa", $dow*2, 2));
   }
//
//--------------------------------------------------------------------------------
//Reformats an STIME string to include dots at strategic places for more
//human-friendly display.
//
function STIME_dotted_display_string_a($stime_in)
   {
   if (! is_string($stime_in))
      {
      //Don't know what this is ... it isn't an stime.  Just send it back.
      return($stime_in);
      }
   else if (strlen($stime_in) != 22)
      {
      //This doesn't seem to be the right length for an stime.  Give it back.
      return($stime_in);
      }
   else
      {
      //Seems right.
      return(
            SubStr($stime_in, 0, 2)
            .
            "."
            .
            SubStr($stime_in, 2, 4)
            .
            "."
            .
            SubStr($stime_in, 6, 2)
            .
            "."
            .
            SubStr($stime_in, 8, 2)
            .
            "."
            .
            SubStr($stime_in, 10, 2)
            .
            "."
            .
            SubStr($stime_in, 12, 2)
            .
            "."
            .
            SubStr($stime_in, 14, 2)
            .
            "."
            .
            SubStr($stime_in, 16, 6)
            );
      }
   }
//
//--------------------------------------------------------------------------------
//End of $RCSfile: stimex.inc,v $.
//--------------------------------------------------------------------------------
?>
