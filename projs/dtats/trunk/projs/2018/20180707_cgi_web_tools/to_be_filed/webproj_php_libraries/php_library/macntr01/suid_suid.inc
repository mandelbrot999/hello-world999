<?php
//------------------------------------------------------------------------
//Marshall Aviation Center FBO Management Software
//Copyright (C)2005 David T. Ashley
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
//
//The author (David T. Ashley) may be contacted by e-mail at dta@e3ft.com
//and by postal mail at P.O. Box 918, Marshall MI 49068.
//------------------------------------------------------------------------
//Functions for server-unique identifiers.
//
//A server-unique identifier is something guaranteed to be unique for the
//life of the server.  These are the basis for session IDs, etc.
//------------------------------------------------------------------------
//Gets a unique integer whole time and microtime.  The time is 
//guaranteed unique because this function implements a spinlock
//until the time changes.
function suid_uniquetime(&$whole_time, &$micro_time)
   {
   list($usec_reference, $sec_reference) = explode(" ", microtime());
   $usec_reference = (int)($usec_reference * 1000000.0);

   $exit_condition = 0;

   while (!$exit_condition)
      {
      list($usec, $sec) = explode(" ", microtime());
      $usec = (int)($usec * 1000000.0);

      if (($usec == $usec_reference) && ($sec == $sec_reference))
         {
         //The time has not changed.  Use usleep() to try to 
         //give a time breather without chewing CPU time.
         usleep(100);
         }
      else
         {
         //The time has changed.  We can leave the loop.
         $exit_condition = 1;
         }      
      }

   //Assign the values for the caller.
   $whole_time = $sec_reference;
   $micro_time = $usec_reference;
   }

//------------------------------------------------------------------------
//Returns a SUID as documented.  Format will be:
//  PID        --  8 hexadecimal digits.
//  WHOLE TIME -- 10 hexadecimal digits.
//  NANO TIME  --  8 hexadecimal digits.
//
function suid_suid()
   {
   $pidstring = sprintf("0000%04X", getmypid());

   suid_uniquetime($secs_out, $usecs_out);

   $wholestring = sprintf("%010X", $secs_out);

   $usecs_out = $usecs_out * 1000;
   $fracstring  = sprintf("%08X", $usecs_out);

   return($pidstring . $wholestring . $fracstring);
   }

//------------------------------------------------------------------------
?>
