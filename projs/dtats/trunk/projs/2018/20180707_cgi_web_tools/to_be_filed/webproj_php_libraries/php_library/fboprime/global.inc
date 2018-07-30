<?php
//$Header: svn://localhost/dtapublic/projs/dtats/trunk/projs/2018/20180707_cgi_web_tools/to_be_filed/webproj_php_libraries/php_library/fboprime/global.inc 205 2018-07-15 19:00:51Z dashley $
//********************************************************************************
//global.inc--FboPrime Global Variable Definition and Initialization
//Copyright (C) 2006  David T. Ashley
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
//********************************************************************************
//This file defines and initializes the global variables used by the
//application (there are very few of these).
//--------------------------------------------------------------------------------
require_once("config.inc");
require_once("strfunc.inc");
require_once("timeraw.inc");
//
//--------------------------------------------------------------------------------
//FULL LIST OF GLOBAL VARIABLES
//-----------------------------
//  GLOBAL_dbhandle
//     The handle to the MySQL database.  This is used because there is only
//     one database, and it would add a lot of typing to pass it as a formal
//     parameter always.  If a connection to the database can't be made
//     (very near the start of nearly every script), and error screen is
//     displayed and the script gracefully aborts.
//
//  GLOBAL_dblocked
//     TRUE if the database is locked, or FALSE if not.  As mentioned in
//     the manual, one can use a global variable of this type to implement
//     a protocol that allows critical sections within critical sections
//     with no risk of unlocking the database prematurely.
//
//  GLOBAL_html_indent_level
//     The indent level of HTML output.  The no-indent level is 0, and the
//     successive levels are 1, 2, 3, etc.  This is used to create HTML
//     output that is human-friendly so it can be proofread.  It also allows
//     functions to be used in multiple contexts and they will pick up the
//     correct indent level.
//
//  GLOBAL_client_ip
//     The IP address as reported by the server (a string).
//--------------------------------------------------------------------------------
//  Note:  The values below are derived from a common time snapshot in order
//         to ensure they are absolutely consistent.  The snapshot is obtained
//         at approximately the start of page execution.
//
//  GLOBAL_utime_sec
//     The Unix integer time, expressed as a string.  A string format
//     is used due to the uncertainty surrounding the 2037 Unix epoch issue.
//
//  GLOBAL_utime_sec_11
//     The Unix integer time, expressed as a string, zero-padded on the left
//     out to 11 characters.  This is provided because with a constant-length
//     string, the lexical sort order (i.e. strcmp) is the same as the
//     numerical order.
//
//  GLOBAL_utime_nsec
//     The Unix integer nanoseconds associated with the integer seconds above.
//     An integer format is used because the Unix epoch issue does not affect
//     the fractional part of the seconds.
//
//  GLOBAL_utime_ut
//     A string in the UTIME format as described in the manual, describing
//     the time at the approximate page load time.
//
//  GLOBAL_stime_year
//     The integer year (2000-2999) in the FBO locale.
//
//  GLOBAL_stime_month
//     The integer month (1-12) in the FBO locale.
//
//  GLOBAL_stime_day
//     The integer day of the month (1-31) in the FBO locale.
//
//  GLOBAL_stime_hour
//     The integer hour (0-23) in the FBO locale.
//
//  GLOBAL_stime_minute
//     The integer minute (0-59) in the FBO locale.
//
//  GLOBAL_stime_second
//     The integer second (0-59) in the FBO locale.
//
//  GLOBAL_stime_usec
//     The integer microseconds (0-999,999) in the
//     FBO locale.
//
//  GLOBAL_stime_dow
//     The day of the week, an integer, 0-6, 0=Sunday, 1=Monday, etc.
//     in the FBO locale.
//
//  GLOBAL_stime_string
//     A string in the STIME format as described in the manual.
//--------------------------------------------------------------------------------
//Initializes global variables to correct starting values.
//
function GLOBAL_init()
   {
   global $GLOBAL_dbhandle;
   global $GLOBAL_dblocked;
   global $GLOBAL_html_indent_level;
   global $GLOBAL_client_ip;
   global $GLOBAL_utime_sec;
   global $GLOBAL_utime_sec_11;
   global $GLOBAL_utime_nsec;
   global $GLOBAL_utime_ut;
   global $GLOBAL_stime_year;
   global $GLOBAL_stime_month;
   global $GLOBAL_stime_day;
   global $GLOBAL_stime_hour;
   global $GLOBAL_stime_minute;
   global $GLOBAL_stime_second;
   global $GLOBAL_stime_usec;
   global $GLOBAL_stime_dow;
   global $GLOBAL_stime_string;

   $GLOBAL_dbhandle               = FALSE;
   $GLOBAL_dblocked               = FALSE;
   $GLOBAL_html_indent_level      = 0;

   //Grab the client IP as known to the server and sanitize it.
   if (isset($_SERVER["REMOTE_ADDR"]))
      $GLOBAL_client_ip              = $_SERVER["REMOTE_ADDR"];
   else
      $GLOBAL_client_ip              = "";
   $GLOBAL_client_ip= STRFUNC_force_stringtype_subset_truncate($GLOBAL_client_ip, ".0123456789", 40);

   //Obtain a Unix timestamp.
   $timestamp = TIMERAW_time_precision_mixed_array_2();
   $GLOBAL_utime_sec  = $timestamp[0];
   $GLOBAL_utime_nsec = $timestamp[1];

   //Provide the left-zero-padded version of the Unix seconds.
   $GLOBAL_utime_sec_11 = STRFUNC_pad_left_zero($GLOBAL_utime_sec, 11);

   //Provide the UTIME.
   $GLOBAL_utime_ut = "UT" . $GLOBAL_utime_sec_11 . STRFUNC_pad_left_zero((string)$GLOBAL_utime_nsec, 9);

   //Run the Unix timestamp through a conversion to get the time details
   //in the locale.  The time details in the locale are maintained as integers
   //for efficient calculation.  The Unix epoch issue does not affect locale
   //time maintained in this way.
   CONFIG_unix_sched_time_map(
                                $GLOBAL_utime_sec,
                                $GLOBAL_utime_nsec,
                                $GLOBAL_stime_year,
                                $GLOBAL_stime_month,
                                $GLOBAL_stime_day,
                                $GLOBAL_stime_hour,
                                $GLOBAL_stime_minute,
                                $GLOBAL_stime_second,
                                $GLOBAL_stime_usec,
                                $GLOBAL_stime_dow
                             );

   //From the values obtained, form an STIME string that is consistent with the 
   //Unix time and the integer values.
   $GLOBAL_stime_string = "ST"
                          . sprintf("%04d", $GLOBAL_stime_year)
                          . sprintf("%02d", $GLOBAL_stime_month)
                          . sprintf("%02d", $GLOBAL_stime_day)
                          . sprintf("%02d", $GLOBAL_stime_hour)
                          . sprintf("%02d", $GLOBAL_stime_minute)
                          . sprintf("%02d", $GLOBAL_stime_second)
                          . sprintf("%06d", $GLOBAL_stime_usec);
   //echo " + " . $GLOBAL_stime_string . " + ";
   }
//
//--------------------------------------------------------------------------------
//End of $RCSfile: global.inc,v $.
//--------------------------------------------------------------------------------
?>
