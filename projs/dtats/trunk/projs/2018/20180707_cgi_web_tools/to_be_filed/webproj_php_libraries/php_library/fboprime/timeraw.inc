<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/timeraw.inc 205 2018-07-15 19:00:51Z dashley $
//********************************************************************************
//Copyright (C) 2006 David T. Ashley
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
//This source file provides raw time related code.  This file is a wrapper
//around the built-in PHP functions to provide more flexibility as we get
//near the Unix epoch.  All functions that obtain from the machine time must 
//go through this module.
//
//--------------------------------------------------------------------------------
//Returns the current Unix time as an array of:
//   a)A decimal string representing the seconds since the Unix epoch.  A string
//     representation is used because then this function can be modified as the
//     Unix epoch grows closer (but, we'll probably all be using 64-bit machines
//     by then).  The string representation must not exceed 11 characters (but
//     this should not be a problem until after 5,000 A.D.).
//
//   b)An integer representing the nanoseconds of the fractional part of the
//     Unix time.  An integer is used because the fractional part of the time
//     is not affected by the Unix epoch issue.
//
//
function TIMERAW_time_precision_mixed_array_2()
   {
   //Get the high-precision time microseconds and seconds.
   list($usec, $sec) = explode(" ", microtime());

   //Convert the integer seconds time to a string.
   $string_sec = sprintf("%d", $sec);

   //Convert the microseconds to an integer giving the
   //integer number of microseconds.  The original value is in fractional
   //seconds (a float).
   $usec = $usec * 1000000.0;
   $usec = (int) $usec;

   //Convert microseconds to nanoseconds.
   $nsec = $usec * 1000;

   //Stuff the return array and return.
   $rv[0] = (string) $string_sec;
   $rv[1] = (int)    $nsec;
   return($rv);
   }
//--------------------------------------------------------------------------------
?>
