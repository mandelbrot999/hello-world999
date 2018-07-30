<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/sguid.inc 205 2018-07-15 19:00:51Z dashley $
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
//This source file provides the code to create server globally-unique identifiers.
//The rationale is that since no process can have the same PID at the same
//time as another process, using the PID concatenated with a guaranteed
//unique time should provide an identifier that can never recur in the lifetime
//of the server.
//
//The format of the SGUID is documented in the FBO-Prime manual.
//
require_once("strfunc.inc");     //Necesssary for zero padding.
require_once("timeraw.inc");     //Necessary to get raw time.
//
//
//--------------------------------------------------------------------------------
//Returns the full generated SGUID as described in the documentation.
//
//Unit-tested 20060408.
//
function SGUID_sguid()
   {
   return("SG" . SGUID_sguid_raw());
   }
//
//
//--------------------------------------------------------------------------------
//Returns the raw form of an SGUID (without the "SG" prefix).
//
//Unit-tested 20060408.
//
function SGUID_sguid_raw()
  {
   //Get the reference timestamp.
   $reftime = TIMERAW_time_precision_mixed_array_2();

   //Get the PID.  This may also chew up some time and hopefully let the
   //server time change.
   $pid = getmypid();

   //Form the SGUID proper.  Hopefully this will also chew up more time.
   $reftime_whole  = $reftime[0];
   $reftime_frac   = sprintf("%d", $reftime[1]);
   $pid_string     = sprintf("%d", $pid       );
   $rv =    STRFUNC_pad_left_zero($reftime_whole, 11)
          . STRFUNC_pad_left_zero($reftime_frac,   9)
          . STRFUNC_pad_left_zero($pid_string,    10);

   //Spin-lock until the time has changed.  With any luck, the statements
   //above have done that for us.  It is hard to judge without some data
   //whether microsleep would make things more efficient ... let's just leave
   //it as a pure spin-lock.
   do
      {
      $comptime = TIMERAW_time_precision_mixed_array_2();
      } 
   while (($reftime[1] == $comptime[1]) && ($reftime[0] == $comptime[0]));

   //Return the value to the caller.
   return($rv);
  }
//
//
//--------------------------------------------------------------------------------
//Returns the length of a SGUID (in characters).
//
//Unit-tested 20060408.
//
function SGUID_sguid_len()
   {
   return(32);
   }
//
//
//--------------------------------------------------------------------------------
//Returns 1 if the SGUID is syntactically valid or 0 otherwise.
//
//Unit-tested 20060408.
//
function SGUID_is_syntactically_valid($sguid_to_check)
   {
   //Must be a string data type.
   if (! is_string($sguid_to_check))
      return(0);

   //Must be of appropriate length.
   if (strlen($sguid_to_check) != 32)
      return(0);

   //First two characters must be "SG".
   if (substr($sguid_to_check, 0, 2) !== "SG")
      return(0);
  
   //The remainder of the string must be digits only.
   if (! STRFUNC_is_pure_digits(SubStr($sguid_to_check, 2, 30)))
      return(0);

   //If we're here, nothing obvious wrong with it.
   return(1);
   }
//--------------------------------------------------------------------------------
?>
