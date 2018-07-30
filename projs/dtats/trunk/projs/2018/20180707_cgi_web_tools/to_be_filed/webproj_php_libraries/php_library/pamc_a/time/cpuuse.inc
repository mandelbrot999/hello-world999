<?php
//
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
//
//Dave Ashley, 01/06
//
//CPU time measurement and display on a page.
//
//
//Returns a string containing four integers separated by colons,
//which are, in order, system time seconds, system time microseconds,
//user time seconds, and user time microseconds.  No left-zero padding
//is performed.
//
function CPUUSE_snapshot()
   {
   $snapshot = getrusage(); //Get the resource usage in a single structure.

   //Prep and return the concatenated string.
   return(
            $snapshot["ru_stime.tv_sec"]
            .
            ":"
            .
            $snapshot["ru_stime.tv_usec"]
            .
            ":"
            .
            $snapshot["ru_utime.tv_sec"]
            .
            ":"
            .
            $snapshot["ru_utime.tv_usec"]
         );
   }
//
//Returns the difference in two timestamps.  Each timestamp is in the
//format of colon-separated integers returned by CPUUSE_snapshot().
//
//This function won't behave properly on a negative difference (it is
//designed for $t1 >= $t0 only.
//
function CPUUSE_diff($t0, $t1)
   {
   //Split the strings at the colons.
   //
   $t0_exploded = explode(":", $t0);
   $t1_exploded = explode(":", $t1);
   //
   //Calculate the differences.  There is a little bit of trickiness in
   //processing the microseconds, in case the seconds has rolled over.
   //
   $rv[0] = $t1_exploded[0] - $t0_exploded[0];
   $rv[1] = $t1_exploded[1] - $t0_exploded[1];
   $rv[2] = $t1_exploded[2] - $t0_exploded[2];
   $rv[3] = $t1_exploded[3] - $t0_exploded[3];
   if ($rv[1] < 0)
      {
      $rv[1] += 1000000;
      $rv[0] -= 1;
      }
   if ($rv[3] < 0)
      {
      $rv[3] += 1000000;
      $rv[2] -= 1;
      }
   //
   //Return the result to the caller.
   return($rv[0] . ":" . $rv[1] . ":" . $rv[2] . ":" . $rv[3]);
   }
//
//Supplied a time difference in the format returned by CPUUSE_diff() (four colon-separated
//integers, which are respectively system seconds, system microseconds, user seconds, and
//user microseconds), returns two strings that can be used on a web page (seconds plus
//two decimal points).  The first string is system consumption, the second is user.
//
function CPUUSE_format_display_web($input_diff, &$systime, &$usertime)
   {
   //Split apart the passed integers.
   //
   $diff_exploded = explode(":", $input_diff);

   //Increase the time by 5000 microseconds to round in the second 
   //decimal place.
   $diff_exploded[1] += 5000;
   if ($diff_exploded[1] > 999999)
      {
      $diff_exploded[1] -= 1000000;
      $diff_exploded[0] += 1;
      }
   $diff_exploded[3] += 5000;
   if ($diff_exploded[3] > 999999)
      {
      $diff_exploded[3] -= 1000000;
      $diff_exploded[2] += 1;
      }

   //Zero-pad system microseconds.
   while(strlen($diff_exploded[1]) < 6)
      {
      $diff_exploded[1] = "0" . $diff_exploded[1];
      }   

   //Zero-pad user microseconds.
   while(strlen($diff_exploded[3]) < 6)
      {
      $diff_exploded[3] = "0" . $diff_exploded[3];
      }   

   $systime = $diff_exploded[0] . "." . Substr($diff_exploded[1], 0, 2);
   $usertime = $diff_exploded[2] . "." . Substr($diff_exploded[3], 0, 2);
   }
//
?>
