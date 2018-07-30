<?php
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
//Dave Ashley, 01/06
//
//This source file provides raw time related code.  This file is a wrapper
//around the built-in PHP functions to provide more flexibility as we get
//near the Unix epoch.
//
//Returns the time as 18 hexadecimal digits (using upper-case letters).  The
//first 10 characters are the integer time, and the remaining 8 are
//the fractional time in nanoseconds.
//
function TIMERAW_time_precision_hex()
   {
   //Get the microseconds and seconds.
   list($usec, $sec) = explode(" ", microtime());

   //Convert the microseconds to an integer giving the
   //integer number of microseconds.  The original value is in fractional
   //seconds (a float).
   $usec = $usec * 1000000.0;
   $usec = (int) $usec;

   //Convert microseconds to nanoseconds.
   $nsec = $usec * 1000;

   //Obtain a string of length 10 hex characters representing the integer
   //time.  The first 2 characters are always "00" at the present time (until
   //Unix systems hit more than 32 bits for integers).
   $sec_string = "00" . sprintf("%08X", $sec);

   //Obtain a string of length 8 hex characters representing the fractional
   //time.
   $nsec_string = sprintf("%08X", $nsec);

   //The returned value is the concatenation.
   return($sec_string . $nsec_string);
   }

//Return the size (in chars) of a precision timestamp expressed in hex.
//
function TIMERAW_time_precision_hex_size()
   {
   return(18);
   }
?>
