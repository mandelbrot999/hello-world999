<?php
if (!isset($GENERAL_PUTS_INCLUDED))
   {
   include("general/puts.inc");
   $GENERAL_PUTS_INCLUDED=1;
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
//This source file provides the code to create globally-unique identifiers.
//The rationale is that since no process can have the same PID at the same
//time as another process, using the PID concatenated with a guaranteed
//unique time should provide an identifier that can never recur in the lifetime
//of the server.
//
//A SUID is 104 bits of information (26 hexadecimal
//digits).  The breakdown is:
//
//   a)First 32 bits (8 hexadecimal digits) is the PID.  At present, PIDs
//     are only 16 bits, but in the future (faster systems, etc.) they may be
//     expanded to 32 bits.
//
//   b)Second 40 bits (10 hexadecimal digits).  The integer time, in seconds
//     since the Unix epoch.  The extra 8 bits are reserved due to the impending
//     Unix 2037 AD issue.
//
//   c)Third 32 bits (8 hexadecimal digits).  The nanoseconds representing the 
//     fractional part of the integer seconds.
//
//Note that both of the data sizes above are designed to allow future
//expansion.  The integer part is designed for the Unix 2037 issue.  The
//fractional part is designed for faster hardware in the future.
//
//
function SUID_suid()
   {
   return(sprintf("%08X", getmypid()) . PUTS_timestamp());
   }
//
//
//Returns the size of a SUID (in bytes).
//
function SUID_suid_size()
   {
   return(8 + PUTS_timestamp_size());
   }
?>
