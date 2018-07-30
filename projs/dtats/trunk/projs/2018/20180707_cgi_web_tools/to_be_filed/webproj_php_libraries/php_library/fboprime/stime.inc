<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/stime.inc 205 2018-07-15 19:00:51Z dashley $
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
//Dave Ashley, 07/06
//
//This source file contains date and time calculation and
//manipulation functions.
//
require_once("config.inc");            //Scheduling configuration.
require_once("confighard.inc");        //Necessary for date minimums and maximums.
require_once("t4.inc");
//
//--------------------------------------------------------------------------------
//Creates an STIME (low resolution) from year, month, day, hour, and minute
//passed (as integers).  Seconds and smaller time units all set to zero.
//
function STIME_stime_make_medres($year_in, $month_in, $day_in, $hour_in, $minute_in)
   {
   $rv = "ST"
         .
         sprintf("%04d%02d%02d%02d%02d", $year_in, $month_in, $day_in, $hour_in, $minute_in)
         .
         "00000000";
   return($rv);
   }
//
//--------------------------------------------------------------------------------
//Background on the functions below ... there are 48 half-hour time slots in
//a day, which we index 0 .. 47.  This provides the mappings back and forth
//between an STIME or fraction of an STIME and the integers.
//
//The integers are more machine-efficient.
//
//--------------------------------------------------------------------------------
//Maps from the embedded T4 (HHMM) to the integer representing the half-hour
//interval (0..47).
// 
function STIME_T4_lb_int($stime_in)
   {
   $extract = SubStr($stime_in, 10, 4);
   $rv = T4_lb_int($extract);
   return($rv);
   }
//
//--------------------------------------------------------------------------------
//End of $RCSfile: stime.inc,v $.
//--------------------------------------------------------------------------------
?>
