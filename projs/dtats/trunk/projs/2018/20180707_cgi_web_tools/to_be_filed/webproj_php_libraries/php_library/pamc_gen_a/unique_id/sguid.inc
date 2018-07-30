<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/pamc_gen_a/unique_id/sguid.inc 205 2018-07-15 19:00:51Z dashley $
//--------------------------------------------------------------------------------
//sguid.inc -- Server globally-unique identifiers.
//Copyright (C) 2007  David T. Ashley
//--------------------------------------------------------------------------------
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
//--------------------------------------------------------------------------------
//Author contact information:
//   David T. Ashley
//   P.O. Box 918
//   Marshall, Michigan, 49068
//   dta@e3ft.com
//--------------------------------------------------------------------------------
require_once("string/strfunc_charset.inc");
require_once("time/timeraw.inc");
require_once("time/autime.inc");
//--------------------------------------------------------------------------------
//Returns an SGUID.  Leap seconds situations are avoided.
//
//Unit-tested 20070624.
//
function SGUID_sguid()
  {
   //Get the reference timestamp.
   $reftime = TIMERAW_time_precision_mixed_array_2_noleap();

   //Get the PID.  This may also chew up some time and hopefully let the
   //server time change.
   $pid = getmypid();

   //Add the number of seconds between Jan 1, 1900 and Jan 1, 1970.  This
   //time is based from beginning of the century, whereas Unix time is
   //based from the Unix epoch (Jan 1, 1970).
   $reftime[0] = bcadd($reftime[0], "2208988800");

   //Form the SGUID proper.  Hopefully this will also chew up more time.
   $reftime_whole  = $reftime[0];
   $reftime_frac   = sprintf("%d", $reftime[1]);
   $pid_string     = sprintf("%d", $pid       );
   $rv =    STRFUNC_pad_left_zero($reftime_whole, 10)
          . STRFUNC_pad_left_zero($reftime_frac,   9)
          . STRFUNC_pad_left_zero($pid_string,    10);

   //Spin-lock until the time has changed.  With any luck, the statements
   //above have done that for us.  It is hard to judge without some data
   //whether microsleep would make things more efficient ... let's just leave
   //it as a pure spin-lock.
   do
      {
      $comptime = TIMERAW_time_precision_mixed_array_2_noleap();
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
//Unit-tested 20070624.
//
function SGUID_sguid_len()
   {
   return(29);
   }
//
//
//--------------------------------------------------------------------------------
//Returns 1 if the SGUID is syntactically valid or 0 otherwise.
//
//Unit-tested 20070624.
//
function SGUID_is_syntactically_valid($sguid_to_check)
   {
   //Must be a string data type.
   if (! is_string($sguid_to_check))
      return(0);

   //Must be of appropriate length.
   if (strlen($sguid_to_check) != 29)
      return(0);

   //The string must be digits only.
   if (! STRFUNC_is_pure_digits($sguid_to_check))
      return(0);

   //If we're here, nothing obvious wrong with it.
   return(1);
   }
//--------------------------------------------------------------------------------
//End of $RCSfile: sguid.inc,v $.
//--------------------------------------------------------------------------------
?>
