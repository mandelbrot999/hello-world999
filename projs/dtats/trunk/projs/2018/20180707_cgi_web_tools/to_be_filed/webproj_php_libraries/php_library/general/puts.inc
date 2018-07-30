<?php
if (!isset($GENERAL_TIMERAW_INCLUDED))
   {
   include("general/timeraw.inc");
   $GENERAL_TIMERAW_INCLUDED=1;
   }
?>
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
//This source file provides the code to create process-unique
//timestamps.  A process-unique timestamp is guaranteed to be unique
//because this code will spin-lock until the time changes.
//
//A process-unique timestamp is 72 bits of information (18 hexadecimal
//digits).  The breakdown is:
//
//   a)First 40 bits (10 hexadecimal digits).  The integer time, in seconds
//     since the Unix epoch.  The extra 8 bits are reserved due to the impending
//     Unix 2037 AD issue.
//
//   b)Second 32 bits (8 hexadecimal digits).  The nanoseconds representing the 
//     fractional part of the integer seconds.
//
//Note that both of the data sizes above are designed to allow future
//expansion.  The integer part is designed for the Unix 2037 issue.  The
//fractional part is designed for faster hardware in the future.
//
//
function PUTS_timestamp()
   {
   //Obtain the initial value.
   $rv = TIMERAW_time_precision_hex();

   //Wait for the time to change.  Although I don't think it would make a difference
   //in practice, there is sleep to be more efficient.
   $new_time = TIMERAW_time_precision_hex();
   if ($rv == $new_time)
      {
      do
         {
         usleep(100);
         $new_time = TIMERAW_time_precision_hex();
         }
      while ($rv == $new_time);
      }

   //The time has changed.  We are clear to return.
   return($rv);
   }
//
//
//Returns the size (in chars) of a process-unique timestamp.
//
function PUTS_timestamp_size()
   {
   return(TIMERAW_time_precision_hex_size());
   }
?>
